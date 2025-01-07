#ifndef Renderer_hpp
#define Renderer_hpp

#include <MetalKit/MetalKit.hpp>

class Renderer {
public:
    Renderer(std::shared_ptr<MTL::Device> device);
    void draw(MTK::View* pView);
    
private:
    std::shared_ptr<MTL::Device> device;
    std::shared_ptr<MTL::CommandQueue> commandQueue;
};

#endif /* Renderer_hpp */
