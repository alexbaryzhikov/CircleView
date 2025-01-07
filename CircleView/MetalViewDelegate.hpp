#ifndef MetalViewDelegate_hpp
#define MetalViewDelegate_hpp

#include "Renderer.hpp"

class MetalViewDelegate : public MTK::ViewDelegate {
public:
    MetalViewDelegate(std::shared_ptr<MTL::Device> device);
    void drawInMTKView(MTK::View* pView) override;
    
private:
    std::unique_ptr<Renderer> renderer;
};

#endif /* MetalViewDelegate_hpp */
