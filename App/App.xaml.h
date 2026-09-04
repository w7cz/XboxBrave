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
