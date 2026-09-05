#include "pch.h"
#include "App.xaml.h"
#include "MainPage.xaml.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

void* winrt_make_XboxBrave_App()
{
    return winrt::detach_abi(winrt::make<winrt::XboxBrave::implementation::App>());
}

int __cdecl main()
{
    winrt::Windows::UI::Xaml::Application::Start(
        [](auto&&)
        {
            winrt::make<winrt::XboxBrave::implementation::App>();
        });
}

namespace winrt::XboxBrave::implementation
{
    App::App()
    {
        InitializeComponent();
    }

    void App::OnLaunched(LaunchActivatedEventArgs const&)
    {
        Frame rootFrame{ nullptr };
        auto content = Window::Current().Content();

        if (content)
        {
            rootFrame = content.try_as<Frame>();
        }

        if (!rootFrame)
        {
            rootFrame = Frame();

            rootFrame.NavigationFailed(
                [](IInspectable const&, NavigationFailedEventArgs const& e)
                {
                    throw hresult_error(
                        E_FAIL,
                        hstring(L"Failed to load Page ") +
                        e.SourcePageType().Name
                    );
                });

            Window::Current().Content(rootFrame);
        }

        if (rootFrame.Content() == nullptr)
        {
            rootFrame.Navigate(xaml_typename<XboxBrave::MainPage>());
        }

        Window::Current().Activate();
    }
}
