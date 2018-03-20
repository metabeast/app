#pragma once
#include "../api.inl"
#include "../../../../dll.hpp"
#include "../../../../detail/assert.hpp"
#include "../../../../detail/objc/objc.inl"
#include "../../../../os/macos/api/NSWindow.inl"
#include "../../../../os/macos/api/NSView.inl"

namespace app::gpu::gl3 {

    using macos::NSWindow;
    using macos::NSView;
    using objc::NSInteger;

    //--------------------------------------------------------------------------

    const dll OpenGL {"OpenGL.framework/OpenGL"};

    //--------------------------------------------------------------------------

    enum NSOpenGLPixelFormatAttribute : uint32_t {
        // choose from all available renderers
        NSOpenGLPFAAllRenderers          = 1,
        // choose a triple buffered pixel format
        NSOpenGLPFATripleBuffer          = 3,
        // choose a double buffered pixel format
        NSOpenGLPFADoubleBuffer          = 5,
        // number of aux buffers
        NSOpenGLPFAAuxBuffers            = 7,
        // number of color buffer bits
        NSOpenGLPFAColorSize             = 8,
        // number of alpha component bits
        NSOpenGLPFAAlphaSize             = 11,
        // number of depth buffer bits
        NSOpenGLPFADepthSize             = 12,
        // number of stencil buffer bits
        NSOpenGLPFAStencilSize           = 13,
        // number of accum buffer bits
        NSOpenGLPFAAccumSize             = 14,
        // never choose smaller buffers than requested
        NSOpenGLPFAMinimumPolicy         = 51,
        // choose largest buffers of type requested
        NSOpenGLPFAMaximumPolicy         = 52,
        // number of multi sample buffers
        NSOpenGLPFASampleBuffers         = 55,
        // number of samples per multi sample buffer
        NSOpenGLPFASamples               = 56,
        // each aux buffer has its own depth stencil
        NSOpenGLPFAAuxDepthStencil       = 57,
        // color buffers store floating point pixels
        NSOpenGLPFAColorFloat            = 58,
        // choose multisampling
        NSOpenGLPFAMultisample           = 59,
        // choose supersampling
        NSOpenGLPFASupersample           = 60,
        // request alpha filtering
        NSOpenGLPFASampleAlpha           = 61,
        // request renderer by ID
        NSOpenGLPFARendererID            = 70,
        // disable all failure recovery systems
        NSOpenGLPFANoRecovery            = 72,
        // choose a hardware accelerated renderer
        NSOpenGLPFAAccelerated           = 73,
        // choose the closest color buffer to request
        NSOpenGLPFAClosestPolicy         = 74,
        // back buffer contents are valid after swap
        NSOpenGLPFABackingStore          = 76,
        // bit mask of supported physical screens
        NSOpenGLPFAScreenMask            = 84,
        // allow use of offline renderers
        NSOpenGLPFAAllowOfflineRenderers = 96,
        // choose a hardware accelerated compute device
        NSOpenGLPFAAcceleratedCompute    = 97,
        // number of virtual screens in this format
        NSOpenGLPFAVirtualScreenCount    = 128,

        // specify an OpenGL Profile to use
        NSOpenGLPFAOpenGLProfile         = 99,

        // choose a Legacy/Pre-OpenGL 3.0 Implementation
        NSOpenGLProfileVersionLegacy     = 0x1000,
        // choose an OpenGL 3.2 Core Implementation
        NSOpenGLProfileVersion3_2Core    = 0x3200,
        // choose an OpenGL 4.1 Core Implementation
        NSOpenGLProfileVersion4_1Core    = 0x4100,

        NSOpenGLPFAArrayTerminator       = 0,
    };

    //--------------------------------------------------------------------------

    enum NSOpenGLContextParameter : NSInteger {
        // 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace
        NSOpenGLContextParameterSwapInterval           = 222,
        // 1 param.  1 -> Above Window (default), -1 -> Below Window
        NSOpenGLContextParameterSurfaceOrder           = 235,
        // 1 param.  1-> Surface is opaque (default), 0 -> non-opaque
        NSOpenGLContextParameterSurfaceOpacity         = 236,
        // 2 params.  Width/height of surface backing size
        NSOpenGLContextParameterSurfaceBackingSize     = 304,
        // 0 params.
        NSOpenGLContextParameterReclaimResources       = 308,
        // 1 param.   Retrieves the current renderer ID
        NSOpenGLContextParameterCurrentRendererID      = 309,
        // 1 param.   Currently processing vertices with GPU (get)
        NSOpenGLContextParameterGPUVertexProcessing    = 310,
        // 1 param.   Currently processing fragments with GPU (get)
        NSOpenGLContextParameterGPUFragmentProcessing  = 311,
        // 1 param.   Boolean returned if drawable is attached
        NSOpenGLContextParameterHasDrawable            = 314,
        // 1 param.   Max number of swaps queued by the MP GL engine
        NSOpenGLContextParameterMPSwapsInFlight        = 315,
    };

    //--------------------------------------------------------------------------

    struct NSOpenGLPixelFormat : objc::NSObject {

        static struct API {

            objc::classid
            cls {"NSOpenGLPixelFormat"};

            objc::message<NSOpenGLPixelFormat*(NSOpenGLPixelFormatAttribute*)>
            initWithAttributes {"initWithAttributes:"};

        } api;

        static
        NSOpenGLPixelFormat*
        alloc() { return objc::NSObject::alloc<NSOpenGLPixelFormat>(); }

        NSOpenGLPixelFormat*
        init(NSOpenGLPixelFormatAttribute* attributes) {
            return api.initWithAttributes(this,attributes);
        }

        static
        NSOpenGLPixelFormat*
        newPixelFormat(NSOpenGLPixelFormatAttribute* attributes) {
            return alloc()->init(attributes);
        }

    };

    NSOpenGLPixelFormat::API NSOpenGLPixelFormat::api {};

    //--------------------------------------------------------------------------

    struct NSOpenGLContext : objc::NSObject {

        static struct API {

            objc::classid
            cls {"NSOpenGLContext"};

            objc::message<NSOpenGLContext*(NSOpenGLPixelFormat*,NSOpenGLContext*)>
            initWithFormat_shareContext {"initWithFormat:shareContext:"};

            objc::message<NSOpenGLContext*()>
            currentContext {"currentContext"};

            objc::message<void()>
            clearCurrentContext {"clearCurrentContext"};

            objc::message<void()>
            clearDrawable {"clearDrawable"};

            objc::message<void()>
            flushBuffer {"flushBuffer"};

            objc::message<void()>
            makeCurrentContext {"makeCurrentContext"};

            objc::message<void(NSView*)>
            setView {"setView:"};

            objc::message<void()>
            update {"update"};

            objc::message<void(GLint*,NSOpenGLContextParameter)>
            getValues_forParameter {"getValues:forParameter:"};

            objc::message<void(const GLint*,NSOpenGLContextParameter)>
            setValues_forParameter {"setValues:forParameter:"};

        } api;

        static
        NSOpenGLContext*
        alloc() { return objc::NSObject::alloc<NSOpenGLContext>(); }

        NSOpenGLContext*
        init(NSOpenGLPixelFormat* pixelFormat) {
            return api.initWithFormat_shareContext(this,pixelFormat,nullptr);
        }

        static
        NSOpenGLContext*
        newContext(NSOpenGLPixelFormat* pixelFormat) {
            return alloc()->init(pixelFormat);
        }

        static
        NSOpenGLContext*
        currentContext() { return api.currentContext(api.cls); }

        static
        void
        clearCurrentContext() { return api.clearCurrentContext(api.cls); }

        void
        clearDrawable() { return api.clearDrawable(this); }

        void
        flushBuffer() { return api.flushBuffer(this); }

        void
        makeCurrentContext() { return api.makeCurrentContext(this); }

        void
        setView(NSView* view) { return api.setView(this,view); }

        void
        update() { return api.update(this); }

        void
        getValues(GLint* val, NSOpenGLContextParameter param) {
            return api.getValues_forParameter(this,val,param);
        }

        void
        setValues(const GLint* val, NSOpenGLContextParameter param) {
            return api.setValues_forParameter(this,val,param);
        }

    };

    NSOpenGLContext::API NSOpenGLContext::api {};

    //==========================================================================

    #define NSOpenGLContext(GLcontext) ((NSOpenGLContext*)GLcontext)
    #define GLcontext(NSOpenGLContext) ((GLcontext*)NSOpenGLContext)

    inline
    GLcontext*
    glCreateContext() {
        objc::autoreleasepool autoreleasepool;
        NSOpenGLPixelFormatAttribute
        pixelFormatAttributes[] = {
            //NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
            NSOpenGLPFAColorSize,     NSOpenGLPixelFormatAttribute{24},
            NSOpenGLPFAAlphaSize,     NSOpenGLPixelFormatAttribute{ 8},
            NSOpenGLPFADepthSize,     NSOpenGLPixelFormatAttribute{24},
            NSOpenGLPFAStencilSize,   NSOpenGLPixelFormatAttribute{ 8},
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFANoRecovery,
            NSOpenGLPFAArrayTerminator,
        };

        NSOpenGLPixelFormat*
        pixelFormat = NSOpenGLPixelFormat::newPixelFormat(pixelFormatAttributes);

        NSOpenGLContext*
        context = NSOpenGLContext::newContext(pixelFormat);

        #define app_gpu_gl3_function_resolution(ReturnType,Name,Parameters) \
            Name = decltype(Name)(glGetProcAddress(#Name));
            app_gpu_gl3_function(app_gpu_gl3_function_resolution)
        #undef app_gpu_gl3_function_resolution

        app_assert(objc::CFGetRetainCount(context) == 1);
        return GLcontext(context);
    }

    inline
    void
    glDestroyContext(GLcontext* context) {
        app_assert(objc::CFGetRetainCount(context) == 1);
        {
            objc::autoreleasepool autoreleasepool;
            if (NSOpenGLContext::currentContext() == NSOpenGLContext(context)) {
                NSOpenGLContext::clearCurrentContext();
            }
            NSOpenGLContext(context)->clearDrawable();
        }
        app_assert(objc::CFGetRetainCount(context) == 1);
        objc::CFRelease(context);
    }

    //--------------------------------------------------------------------------

    inline
    GLcontext*
    glGetCurrentContext() {
        objc::autoreleasepool autoreleasepool;
        return GLcontext(NSOpenGLContext::currentContext());
    }

    inline
    void
    glSetCurrentContext(GLcontext* context) {
        objc::autoreleasepool autoreleasepool;
        NSOpenGLContext(context)->makeCurrentContext();
    }

    //--------------------------------------------------------------------------

    inline
    void
    glSetCurrentWindow(GLcontext* context, void* window) {
        objc::autoreleasepool autoreleasepool;
        auto* nsobject = (objc::NSObject*)window;
        auto* nswindow = nsobject->as<NSWindow>();
        auto* nsview =
            nswindow
            ? nswindow->contentView()
            : nsobject->as<NSView>();
        NSOpenGLContext(context)->setView(nsview);
        NSOpenGLContext(context)->update();
    }

    //--------------------------------------------------------------------------

    inline
    GLint
    glGetSwapInterval(GLcontext* context) {
        objc::autoreleasepool autoreleasepool;
        GLint interval = 0;
        NSOpenGLContext(context)->
            getValues(&interval,NSOpenGLContextParameterSwapInterval);
        return interval;
    }

    inline
    void
    glSetSwapInterval(GLcontext* context, GLint interval) {
        objc::autoreleasepool autoreleasepool;
        NSOpenGLContext(context)->
            setValues(&interval,NSOpenGLContextParameterSwapInterval);
    }

    //--------------------------------------------------------------------------

    inline
    void
    glSwapBuffers(GLcontext* context) {
        objc::autoreleasepool autoreleasepool;
        NSOpenGLContext(context)->flushBuffer();
        NSOpenGLContext(context)->update();
    }

    //--------------------------------------------------------------------------

    inline
    void*
    glGetProcAddress(GLstring name) {
        void* const address = OpenGL(name);
        //app_log(name, " @ ",address);
        return address;
    }

    //--------------------------------------------------------------------------

    inline
    const char*
    glGetErrorString(const GLenum err) {
        switch (err) {
            case GL_NO_ERROR:
                return nullptr;
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL_INVALID_FRAMEBUFFER_OPERATION";
            case GL_OUT_OF_MEMORY:
                return "GL_OUT_OF_MEMORY";
            case GL_STACK_OVERFLOW:
                return "GL_STACK_OVERFLOW";
            case GL_STACK_UNDERFLOW:
                return "GL_STACK_UNDERFLOW";
            default: {
                enum { BUFFER_SIZE = 16 };
                static char buffer[BUFFER_SIZE];
                snprintf(buffer, BUFFER_SIZE, "%X", err);
                return buffer;
            }
        };
    }

    //--------------------------------------------------------------------------

    #undef NSOpenGLContext
    #undef GLcontext

} // namespace app::gpu::gl3