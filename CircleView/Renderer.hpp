#ifndef Renderer_hpp
#define Renderer_hpp

#include <MetalKit/MetalKit.hpp>

class Renderer {
public:
    Renderer(std::shared_ptr<MTL::Device> device, CGSize viewSize);
    void draw(MTK::View* pView);
    void viewSizeChanged(CGSize size);
    
private:
    std::shared_ptr<MTL::Device> device;
    std::shared_ptr<MTL::CommandQueue> commandQueue;
    std::shared_ptr<MTL::RenderPipelineState> renderPipelineState;
    std::shared_ptr<MTL::Buffer> vertexBuffer;
    std::shared_ptr<MTL::Buffer> indexBuffer;
    std::shared_ptr<MTL::Buffer> viewSizeBuffer;
};

#endif /* Renderer_hpp */
