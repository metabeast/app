#pragma once
#include "api.inl"

namespace app::gpu {

    namespace gl3 {

        GLenum glBufferUsage(buffer_access a) {
            switch (a) {
                case buffer_access::DEFAULT:
                case buffer_access::IMMUTABLE:
                    return GL_STATIC_DRAW;
                case buffer_access::DYNAMIC:
                    return GL_DYNAMIC_DRAW;
                case buffer_access::STREAMING:
                    return GL_STREAM_DRAW;
            }
        }

        struct GLbuffer {
            const GLuint id  {};
            const GLuint vao {};

            GLbuffer(GLuint id):id(id){}

            ~GLbuffer() {
                auto vao = GLbuffer::vao;
                if (vao) glDeleteVertexArrays(1,&vao);
                auto id = GLbuffer::id;
                glDeleteBuffers(1,&id);
            }
        };

    } // namespace gl3

    //--------------------------------------------------------------------------

    buffer*
    create(const buffer_options& o) {
        using namespace gl3;
        GLuint id;
        glGenBuffers(1,&id);
        if (o.buffer_size and o.buffer_data) {
            glBindBuffer(GL_ARRAY_BUFFER,id);
            glBufferData(GL_ARRAY_BUFFER,
                o.buffer_size,
                o.buffer_data,
                glBufferUsage(o.buffer_access));
            glBindBuffer(GL_ARRAY_BUFFER,0);
        }
        return (buffer*)new GLbuffer(id);
    }

    void
    destroy(buffer* b) {
        using namespace gl3;
        delete (GLbuffer*)b;
    }

} // namespace app::gpu