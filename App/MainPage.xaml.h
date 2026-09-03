#pragma once

#include "MainPage.g.h"
#include "MainPage.xaml.g.h"
#include "AdblockEngine.h"

namespace winrt::XboxBrave::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        ~MainPage();

        void Browser_CoreWebView2Initialized(
            Microsoft::UI::Xaml::Controls::WebView2 const& sender,
            Microsoft::UI::Xaml::Controls::CoreWebView2InitializedEventArgs const& args);

        void AddressBar_KeyDown(
            Windows::Foundation::IInspectable const& sender,
            Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e);

    private:
        void* m_adblockEngine{ nullptr };
        int m_blockedCount{ 0 };

        void LoadFilterLists();
        void Navigate(winrt::hstring const& url);
    };
}

namespace winrt::XboxBrave::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
