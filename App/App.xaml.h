#pragma once
#include "App.xaml.g.h"

namespace winrt::XboxBrave::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(
            Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
    };
}

namespace winrt::XboxBrave::factory_implementation
{
    struct App : AppT<App, implementation::App>
    {
    };
}
