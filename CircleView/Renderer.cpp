#include "Renderer.hpp"
#include "AutoRelease.hpp"

Renderer::Renderer(std::shared_ptr<MTL::Device> device)
: device(device)
, commandQueue(sharedPtr(device->newCommandQueue()))
{}
               
void Renderer::draw(MTK::View* view) {
    auto pool = sharedPtr(NS::AutoreleasePool::alloc()->init());
    auto commandBuffer = commandQueue->commandBuffer();
    auto renderPassDescriptor = view->currentRenderPassDescriptor();
    auto renderCommandEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);
    renderCommandEncoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();
}
