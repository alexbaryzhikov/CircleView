#include "AppDelegate.hpp"
#include "AutoRelease.hpp"

static constexpr CGRect frame = {.origin = {0, 0}, .size = {1000, 1000}};

AppDelegate::AppDelegate(std::shared_ptr<MTL::Device> device)
: device(device)
{}

NS::Menu* AppDelegate::createMainMenu() {
    using NS::StringEncoding::UTF8StringEncoding;
    
    auto mainMenu = NS::Menu::alloc()->init();
    auto appMenu = sharedPtr(NS::Menu::alloc()->init(NS::String::string("AppName", UTF8StringEncoding)));
    auto windowMenu = sharedPtr(NS::Menu::alloc()->init(NS::String::string("Window", UTF8StringEncoding)));

    auto appName = NS::RunningApplication::currentApplication()->localizedName();
    auto quitName = NS::String::string("Quit ", UTF8StringEncoding)->stringByAppendingString(appName);
    SEL quitCallback = NS::MenuItem::registerActionCallback("appQuit", [](void*, SEL, const NS::Object* sender) {
        NS::Application::sharedApplication()->terminate(sender);
    });
    auto quitItem = appMenu->addItem(quitName, quitCallback, NS::String::string("q", UTF8StringEncoding));
    quitItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

    auto closeWindowName = NS::String::string("Close Window", UTF8StringEncoding);
    SEL closeWindowCallback = NS::MenuItem::registerActionCallback("windowClose", [](void*, SEL, const NS::Object* sender) {
        NS::Application::sharedApplication()->windows()->object<NS::Window>(0)->close();
    } );
    auto closeWindowItem = windowMenu->addItem(closeWindowName, closeWindowCallback, NS::String::string("w", UTF8StringEncoding));
    closeWindowItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

    auto appMenuItem = sharedPtr(NS::MenuItem::alloc()->init());
    appMenuItem->setSubmenu(appMenu.get());
    mainMenu->addItem(appMenuItem.get());

    auto windowMenuItem = sharedPtr(NS::MenuItem::alloc()->init());
    windowMenuItem->setSubmenu(windowMenu.get());
    mainMenu->addItem(windowMenuItem.get());

    return mainMenu->autorelease();
}

void AppDelegate::applicationWillFinishLaunching(NS::Notification* notification) {
    auto app = static_cast<NS::Application*>(notification->object());
    app->setMainMenu(createMainMenu());
    app->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void AppDelegate::applicationDidFinishLaunching(NS::Notification* notification) {
    metalViewDelegate = std::make_unique<MetalViewDelegate>(device, frame.size);
    metalView = sharedPtr(MTK::View::alloc()->init(frame, device.get()));
    metalView->setDelegate(metalViewDelegate.get());
    metalView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    metalView->setClearColor(MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0));

    window = sharedPtr(NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled|NS::WindowStyleMaskResizable,
        NS::BackingStoreBuffered,
        false
    ));
    window->setContentView(metalView.get());
    window->setTitle(NS::String::string("CircleView", NS::StringEncoding::UTF8StringEncoding));
    window->makeKeyAndOrderFront(nullptr);

    auto app = static_cast<NS::Application*>(notification->object());
    app->activateIgnoringOtherApps(true);
}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* app) {
    return true;
}
