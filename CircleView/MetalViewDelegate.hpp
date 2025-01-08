#ifndef MetalViewDelegate_hpp
#define MetalViewDelegate_hpp

#include "Renderer.hpp"

class MetalViewDelegate : public MTK::ViewDelegate {
public:
    MetalViewDelegate(std::shared_ptr<MTL::Device> device, CGSize viewSize);
    void drawInMTKView(MTK::View* view) override;
    void drawableSizeWillChange(MTK::View* view, CGSize size) override;
    
private:
    std::unique_ptr<Renderer> renderer;
};

#endif /* MetalViewDelegate_hpp */
