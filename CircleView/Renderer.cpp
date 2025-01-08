#include <numbers>
#include <simd/simd.h>
#include "Renderer.hpp"
#include "AutoRelease.hpp"

static constexpr size_t POLY_NUM = 360;
static constexpr float SCALE = 0.8;

std::shared_ptr<MTL::RenderPipelineState> createRenderPipelineState(MTL::Device&);
std::shared_ptr<MTL::Buffer> createVertexBuffer(MTL::Device&);
std::shared_ptr<MTL::Buffer> createIndexBuffer(MTL::Device&);
std::shared_ptr<MTL::Buffer> createViewSizeBuffer(MTL::Device&, CGSize);

Renderer::Renderer(std::shared_ptr<MTL::Device> device, CGSize viewSize)
: device(device)
, commandQueue(sharedPtr(device->newCommandQueue()))
, renderPipelineState(createRenderPipelineState(*device.get()))
, vertexBuffer(createVertexBuffer(*device.get()))
, indexBuffer(createIndexBuffer(*device.get()))
, viewSizeBuffer(createViewSizeBuffer(*device.get(), viewSize))
{}

void Renderer::draw(MTK::View* view) {
    auto pool = sharedPtr(NS::AutoreleasePool::alloc()->init());
    auto commandBuffer = commandQueue->commandBuffer();
    auto renderPassDescriptor = view->currentRenderPassDescriptor();
    auto renderCommandEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);
    renderCommandEncoder->setRenderPipelineState(renderPipelineState.get());
    renderCommandEncoder->setVertexBuffer(vertexBuffer.get(), 0, 0);
    renderCommandEncoder->setVertexBuffer(viewSizeBuffer.get(), 0, 1);
    renderCommandEncoder->setTriangleFillMode(MTL::TriangleFillMode::TriangleFillModeFill);
    renderCommandEncoder->drawIndexedPrimitives(
        /* primitiveType */ MTL::PrimitiveType::PrimitiveTypeTriangle,
        /* indexCount */ POLY_NUM * 3,
        /* indexType */ MTL::IndexType::IndexTypeUInt16,
        /* indexBuffer */ indexBuffer.get(),
        /* indexBufferOffset */ 0
    );
    renderCommandEncoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();
}

void Renderer::viewSizeChanged(CGSize size) {
    viewSizeBuffer = createViewSizeBuffer(*device.get(), size);
}

std::shared_ptr<MTL::RenderPipelineState> createRenderPipelineState(MTL::Device& device) {
    using NS::StringEncoding::UTF8StringEncoding;
    auto library = sharedPtr(device.newDefaultLibrary());
    auto vertexShader = sharedPtr(library->newFunction(NS::String::string("vertexShader", UTF8StringEncoding)));
    auto fragmentShader = sharedPtr(library->newFunction(NS::String::string("fragmentShader", UTF8StringEncoding)));
    auto renderPipelineDescriptor = sharedPtr(MTL::RenderPipelineDescriptor::alloc()->init());
    renderPipelineDescriptor->setVertexFunction(vertexShader.get());
    renderPipelineDescriptor->setFragmentFunction(fragmentShader.get());
    renderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    NS::Error* error = nullptr;
    return sharedPtr(device.newRenderPipelineState(renderPipelineDescriptor.get(), &error), &error);
}

std::shared_ptr<MTL::Buffer> createVertexBuffer(MTL::Device& device) {
    simd::float2 vertices[POLY_NUM + 1];
    vertices[0] = {0, 0};
    float angle = std::numbers::pi_v<float> * 2.f / POLY_NUM;
    for (int i = 0; i < POLY_NUM; ++i) {
        vertices[i + 1] = {cos(angle * i) * SCALE, sin(angle * i) * SCALE};
    }
    return sharedPtr(device.newBuffer(vertices, sizeof(vertices), MTL::ResourceStorageModeShared));
}

std::shared_ptr<MTL::Buffer> createIndexBuffer(MTL::Device& device) {
    uint16_t indices[POLY_NUM * 3];
    for (int i = 0; i < POLY_NUM; ++i) {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i < POLY_NUM - 1 ? (i + 2) : 1;
    }
    return sharedPtr(device.newBuffer(indices, sizeof(indices), MTL::ResourceStorageModeShared));
}

std::shared_ptr<MTL::Buffer> createViewSizeBuffer(MTL::Device& device, CGSize size) {
    float sizeData[] = {static_cast<float>(size.width), static_cast<float>(size.height)};
    return sharedPtr(device.newBuffer(sizeData, sizeof(sizeData), MTL::ResourceStorageModeShared));
}
