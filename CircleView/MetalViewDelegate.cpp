#include "MetalViewDelegate.hpp"

MetalViewDelegate::MetalViewDelegate(std::shared_ptr<MTL::Device> device)
: renderer(std::make_unique<Renderer>(device))
{}

void MetalViewDelegate::drawInMTKView(MTK::View* view) {
    renderer->draw(view);
}
