#pragma once
#include "gl3/api.inl"
#include "../../gpu.hpp"
#include "../../detail/subsystem.hpp"

namespace app::gpu {

    namespace gl3 {

        static GLcontext* context {};

        static detail::subsystem subsystem {
            []{ // startup
                using namespace gl3;
                context = glCreateContext();
                glSetCurrentContext(context);
                glSetSwapInterval(context,1);
                app_assert(context);
            },
            []{ // shutdown
                using namespace gl3;
                glDestroyContext(context);
                context = nullptr;
            },
        };

    }

    //--------------------------------------------------------------------------

    void
    set(window* w) {
        using namespace gl3;
        glSetCurrentWindow(context,w);
    }

    //--------------------------------------------------------------------------

    void
    present() {
        using namespace gl3;
        glSwapBuffers(context);
    }

} // namespace app::gpu

#include "gl3/buffer.inl"
#include "gl3/pipeline.inl"
#include "gl3/shader.inl"