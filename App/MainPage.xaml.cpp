#include "pch.h"
#include "MainPage.xaml.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::XboxBrave::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
        LoadFilterLists();
    }

    MainPage::~MainPage()
    {
        if (m_adblockEngine)
        {
            engine_free(m_adblockEngine);
            m_adblockEngine = nullptr;
        }
    }

    void MainPage::LoadFilterLists()
    {
        const char* rules =
            "||doubleclick.net^\n"
            "||googlesyndication.com^\n"
            "||googleadservices.com^\n"
            "||adservice.google.com^\n";

        m_adblockEngine = engine_new(rules);
    }

    void MainPage::Browser_CoreWebView2Initialized(
        Microsoft::UI::Xaml::Controls::WebView2 const& /*sender*/,
        Microsoft::UI::Xaml::Controls::CoreWebView2InitializedEventArgs const& /*args*/)
    {
        // مكان مستقبلي: ربط WebResourceRequested بمحرك adblock
    }

    void MainPage::AddressBar_KeyDown(
        Windows::Foundation::IInspectable const& /*sender*/,
        Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
    {
        if (e.Key() == Windows::System::VirtualKey::Enter)
        {
            Navigate(AddressBar().Text());
        }
    }

    void MainPage::Navigate(winrt::hstring const& url)
    {
        std::wstring input{ url };
        std::wstring target;

        if (input.find(L"://") != std::wstring::npos)
        {
            target = input;
        }
        else if (input.find(L'.') != std::wstring::npos &&
                 input.find(L' ') == std::wstring::npos)
        {
            target = L"https://" + input;
        }
        else
        {
            target = L"https://www.google.com/search?q=" + input;
        }

        Browser().Source(Windows::Foundation::Uri{ target });
    }
}
