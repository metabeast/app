#pragma once
#include "api.inl"

namespace app::gpu {

    namespace gl3 {

        GLint
        glGetProgrami(GLuint program, GLenum pname) {
            GLint pvalue = 0;
            glGetProgramiv(program, pname, &pvalue);
            return pvalue;
        }

        std::string
        glGetProgramInfoLogString(GLuint program) {
            if (const auto size = glGetProgrami(program,GL_INFO_LOG_LENGTH)) {
                std::string log(size, '\0');
                glGetProgramInfoLog(program, size, nullptr, &log[0]);
                return log;
            }
            return {};
        }

        bool
        glLinkShaderProgram(GLuint program, GLuint vshader, GLuint fshader) {
            app_assert(program);
            app_assert(vshader);
            app_assert(fshader);
            glAttachShader(program, vshader);
            glAttachShader(program, fshader);
            glLinkProgram(program);
            const auto linked = glGetProgrami(program, GL_LINK_STATUS);
            const auto log = glGetProgramInfoLogString(program);
            if (log.size()) {
                app::assert::write(log);
            }
            return linked ? true : false;
        }

        GLenum
        glIndexType(index_type i) {
            switch (i) {
                case index_type::DEFAULT:
                case index_type::NONE:
                    return GL_ZERO;
                case index_type::UINT16:
                    return GL_UNSIGNED_SHORT;
                case index_type::UINT32:
                    return GL_UNSIGNED_INT;
            }
        }

        // GLuint
        // glUniformSizeOf(GLenum type) {
        //     switch (type) {
        //         case GL_BOOL:              return sizeof(GLboolean);
        //         case GL_BOOL_VEC2:         return sizeof(GLboolean) * 2;
        //         case GL_BOOL_VEC3:         return sizeof(GLboolean) * 3;
        //         case GL_BOOL_VEC4:         return sizeof(GLboolean) * 4;
        //         case GL_FLOAT:             return sizeof(GLfloat);
        //         case GL_FLOAT_VEC2:        return sizeof(GLfloat) * 2;
        //         case GL_FLOAT_VEC3:        return sizeof(GLfloat) * 3;
        //         case GL_FLOAT_VEC4:        return sizeof(GLfloat) * 4;
        //         case GL_FLOAT_MAT2:        return sizeof(GLfloat) * 2 * 2;
        //         case GL_FLOAT_MAT3:        return sizeof(GLfloat) * 3 * 3;
        //         case GL_FLOAT_MAT4:        return sizeof(GLfloat) * 4 * 4;
        //         case GL_INT:               return sizeof(GLint);
        //         case GL_INT_VEC2:          return sizeof(GLint) * 2;
        //         case GL_INT_VEC3:          return sizeof(GLint) * 3;
        //         case GL_INT_VEC4:          return sizeof(GLint) * 4;
        //         case GL_SAMPLER_1D_SHADOW: return sizeof(GLint);
        //         case GL_SAMPLER_1D:        return sizeof(GLint);
        //         case GL_SAMPLER_2D_SHADOW: return sizeof(GLint);
        //         case GL_SAMPLER_2D:        return sizeof(GLint);
        //         case GL_SAMPLER_3D:        return sizeof(GLint);
        //         case GL_SAMPLER_CUBE:      return sizeof(GLint);
        //     }
        // }

        struct GLpipeline {
            GLuint program;
            attribute_streams attribute_streams;
        };

    } // namespace gl3

    //--------------------------------------------------------------------------

    pipeline*
    create(const pipeline_options& o) {
        using namespace gl3;

        GLuint vshader = GLuint(size_t(o.vertex_shader));
        if (not vshader) return nullptr;

        GLuint fshader = GLuint(size_t(o.fragment_shader));
        if (not fshader) return nullptr;

        GLuint program = glCreateProgram();
        app_assert(program);

        // bind attribute locations
        // GLuint attribute_index = ~GLuint(0);
        // bool bound_attribute_indices[MAX_VERTEX_ATTRIBUTES] {};
        // for (auto& stream : o.attribute_streams) {
        //     for (auto& location : stream.attribute_locations) {
        //         auto name = location.attribute_name;
        //         auto index = location.attribute_index;
        //         attribute_index = index ? index : attribute_index + 1;
        //         app_assert(bound_attribute_indices[attribute_index] == false);
        //         app_log(name,":",attribute_index);
        //         glBindAttribLocation(program,attribute_index,name);
        //         bound_attribute_indices[attribute_index] = true;
        //     }
        // }

        if (not glLinkShaderProgram(program, vshader, fshader)) {
            glDeleteProgram(program);
            return nullptr;
        }

        GLchar buffer[32];

        const auto uniform_count = glGetProgrami(program,GL_ACTIVE_UNIFORMS);
        for (auto index = 0;index < uniform_count;++index) {
            GLsizei buffer_size = sizeof(buffer);
            GLint   array_length = 0;
            GLenum  uniform_type = GL_ZERO;
            glGetActiveUniform(
                program,index,
                buffer_size,
                &buffer_size,
                &array_length,
                &uniform_type,
                buffer);
            if (array_length > 1)
                app_log("uniform ",
                    uniform_type," ",buffer,"[",array_length,"]");
            else
                app_log("uniform ",
                    uniform_type," ",buffer);
        }

        const auto attribute_count = glGetProgrami(program,GL_ACTIVE_ATTRIBUTES);
        for (auto index = 0;index < attribute_count;++index) {
            GLsizei buffer_size = sizeof(buffer);
            GLint   array_length = 0;
            GLenum  attribute_type = GL_ZERO;
            glGetActiveAttrib(
                program,index,
                buffer_size,
                &buffer_size,
                &array_length,
                &attribute_type,
                buffer);
            GLint location = glGetAttribLocation(program,buffer);
            if (array_length > 1)
                app_log(
                    "attribute(",location,") ",
                    attribute_type," ",buffer,"[",array_length,"]"
                );
            else
                app_log(
                    "attribute(",location,") ",
                    attribute_type," ",buffer
                );
        }
        

        GLpipeline* glpipeline = new GLpipeline {
            program,
        };
        return (pipeline*)glpipeline;
        // glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE)
        // glEnable(GL_CULL_FACE)
        // glCullFace(GL_FRONT/GL_BACK)
        // glFrontFace(GL_CW/GL_CCW)
        // glEnable(GL_MULTISAMPLE)
        // glPolygonOffset(depth_bias_slope_scale, depth_bias);
        // glEnable(GL_POLYGON_OFFSET_FILL)
        // glEnable(GL_BLEND)
        // glUseProgram(program)
    }

    void
    destroy(pipeline* p) {
        using namespace gl3;
        GLpipeline* glpipeline = (GLpipeline*)p;
        glDeleteProgram(glpipeline->program);
        delete glpipeline;
    }

} // namespace app::gpu