#pragma once

namespace app::ios {

    struct UIResponder : NSObject {

        static struct API {

            objc::classid cls {"UIResponder"};

        } api;

    };

    UIResponder::API UIResponder::api {};

} // namespace app::ios