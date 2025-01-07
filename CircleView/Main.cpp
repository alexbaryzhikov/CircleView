#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include <MetalKit/MetalKit.hpp>
#include "AppDelegate.hpp"
#include "AutoRelease.hpp"

int main() {
    auto pool = sharedPtr(NS::AutoreleasePool::alloc()->init());
    auto device = sharedPtr(MTL::CreateSystemDefaultDevice());
    AppDelegate appDelegate(device);
    auto app = NS::Application::sharedApplication();
    app->setDelegate(&appDelegate);
    app->run();
}
