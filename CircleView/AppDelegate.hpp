#ifndef AppDelegate_hpp
#define AppDelegate_hpp

#include "MetalViewDelegate.hpp"

class AppDelegate : public NS::ApplicationDelegate {
public:
    AppDelegate(std::shared_ptr<MTL::Device> device);
    NS::Menu* createMainMenu();
    void applicationWillFinishLaunching(NS::Notification* pNotification) override;
    void applicationDidFinishLaunching(NS::Notification* pNotification) override;
    bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) override;

private:
    std::shared_ptr<MTL::Device> device;
    std::shared_ptr<NS::Window> window;
    std::shared_ptr<MTK::View> metalView;
    std::unique_ptr<MetalViewDelegate> metalViewDelegate;
};

#endif /* AppDelegate_hpp */
