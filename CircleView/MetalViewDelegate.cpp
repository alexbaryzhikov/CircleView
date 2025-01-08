#include "MetalViewDelegate.hpp"

MetalViewDelegate::MetalViewDelegate(std::shared_ptr<MTL::Device> device, CGSize viewSize)
: renderer(std::make_unique<Renderer>(device, viewSize))
{}

void MetalViewDelegate::drawInMTKView(MTK::View* view) {
    renderer->draw(view);
}

void MetalViewDelegate::drawableSizeWillChange(MTK::View* pView, CGSize size ) {
    renderer->viewSizeChanged(size);
}
