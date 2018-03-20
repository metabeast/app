////usr/bin/env \
    time -p \
    c++ -Werror \
        -std=c++1z \
        -I$(dirname $0)/../.. \
        -o${0%.*} \
        $0 && \
    ls -ho ${0%.*} && \
    ${0%.*}; \
    STATUS=$?; \
    rm ${0%.*}; \
    echo status: $STATUS; \
    exit $STATUS

#include <cstring>
#include "echo.hpp"
#include <app/app.inl>
#include <app/gpu.inl>

using namespace app::gpu;

struct transforms {
    float4x4 mvp;
    float4x4 mvn;
};

struct vertex {
    float3 position;
    float3 normal;
    float4 color;
    float2 texcoord;
};

//------------------------------------------------------------------------------

// template<typename T>
// struct offset_ptr {
//     const uint32_t offset;

//     offset_ptr()
// };

//------------------------------------------------------------------------------

int app::main(int argc, const char* argv[]) {

    using detail::capture;

    auto vb = capture(gpu::create<buffer>({
        buffer_access::STREAMING,
        buffer_size{1024},
        buffer_data{nullptr},
    }));
    echo(vb);

    auto vs = capture(gpu::create<shader>({
        shader_stage::VERTEX,
        shader_source{R"(
            #version 330

            struct transforms {
                mat4 mvp;
                mat4 mvn;
            };

            struct vertex {
                vec3 position;
                vec3 normal;
                vec4 color;
                vec2 texcoord;
            };

            struct fragment {
                vec4 position;
                vec4 normal;
                vec4 color;
                vec2 texcoord;
            };

            fragment vsmain(transforms T, vertex v) {
                fragment f;
                f.position = T.mvp * vec4(v.position,1);
                f.normal   = T.mvn * vec4(v.normal,0);
                f.color    = v.color;
                f.texcoord = v.texcoord;
                return f;
            }

            uniform transforms T;

            layout(location = 0) in vec3 v_position;
            layout(location = 1) in vec3 v_normal;
            layout(location = 2) in vec4 v_color;
            layout(location = 3) in vec2 v_texcoord;

            out vec4 fs_position;
            out vec4 fs_normal;
            out vec4 fs_color;
            out vec2 fs_texcoord;

            void main() {
                vertex v;
                v.position = v_position;
                v.normal   = v_normal;
                v.color    = v_color;
                v.texcoord = v_texcoord;

                fragment f = vsmain(T,v);

                gl_Position = f.position;
                fs_position = f.position;
                fs_normal   = f.normal;
                fs_color    = f.color;
                fs_texcoord = f.texcoord;
            }
        )"},
    }));
    echo(vs);

    auto fs = capture(gpu::create<shader>({
        shader_stage::FRAGMENT,
        shader_source{R"(
            #version 330

            uniform sampler2D diffuse;

            in vec4 fs_position;
            in vec4 fs_normal;
            in vec4 fs_color;
            in vec2 fs_texcoord;

            out vec4 color;

            void main() {
                vec4 tx_color = texture(diffuse, fs_texcoord);
                color = (fs_color + tx_color + fs_normal) / vec4(3.f);
            }
        )"},
    }));
    echo(fs);

    //auto T = gpu::create<uniform>({"T",sizeof(uniforms)});

    auto pl = capture(gpu::create<pipeline>({
        attribute_stream{
            attribute_stride_of<vertex>,
            attribute_location_of<&vertex::position>,
            attribute_location_of<&vertex::normal>,
            attribute_location_of<&vertex::color>,
            attribute_location_of<&vertex::texcoord>,
        },
        vertex_shader{vs},
        fragment_shader{fs},
        index_type::UINT16,
        primitive_type::TRIANGLES,
        raster_state{
            face_culling::BACK,
        },
        blend_state{},
        depth_stencil_state{},
    }));
    echo(pl);

    // auto window = app::window::main("hello world");
    // window->activate();
    // while (app::update(60) and !window->closed());

    return 0;
}