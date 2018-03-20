#pragma once
#include "api.inl"

namespace app::gpu {

    namespace gl3 {

        GLint
        glGetShaderi(GLuint shader, GLenum pname) {
            GLint pvalue = 0;
            glGetShaderiv(shader,pname,&pvalue);
            return pvalue;
        }

        std::string
        glGetShaderInfoLogString(GLuint shader) {
            if (const GLint length = glGetShaderi(shader,GL_INFO_LOG_LENGTH)) {
                std::string log(length,'\0');
                glGetShaderInfoLog(shader,length,nullptr,log.data());
                return log;
            }
            return {};
        }

        GLuint
        glCompileShaderSource(GLenum type, const char* source, GLint length) {
            GLuint shader = glCreateShader(type);
            app_assert(shader);
            glShaderSource(shader,1,&source,&length);
            glCompileShader(shader);
            const auto compiled = glGetShaderi(shader,GL_COMPILE_STATUS);
            const auto log = glGetShaderInfoLogString(shader);
            if (log.size()) {
                app::assert::write(log);
            }
            if (not compiled) {
                glDeleteShader(shader);
                shader = 0;
            }
            return shader;
        }

        GLenum
        glShaderStage(shader_stage s) {
            switch (s) {
                case shader_stage::DEFAULT:
                    return GL_ZERO;
                case shader_stage::VERTEX:
                    return GL_VERTEX_SHADER;
                case shader_stage::FRAGMENT:
                    return GL_FRAGMENT_SHADER;
            }
        }

    } // namespace gl3

    //--------------------------------------------------------------------------

    shader*
    create(const shader_options& o) {
        using namespace gl3;
        GLuint glshader =
            glCompileShaderSource(
                glShaderStage(o.shader_stage),
                (const char*)
                o.shader_source.data,
                o.shader_source.size);
        return (shader*)size_t(glshader);
    }

    void
    destroy(shader* s) {
        using namespace gl3;
        GLuint glshader = GLuint(size_t(s));
        glDeleteShader(glshader);
    }

} // namespace app::gpu