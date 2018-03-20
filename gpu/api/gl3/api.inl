#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>

namespace app::gpu::gl3 {

    using GLbitfield  = uint32_t;
    using GLboolean   = uint8_t;
    using GLbyte      = int8_t;
    using GLchar      = char;
    using GLclampd    = double;
    using GLclampf    = float;
    using GLdouble    = double;
    using GLfixed     = int32_t;
    using GLfloat     = float;
    using GLhalf      = uint16_t;
    using GLint       = int32_t;
    using GLintptr    = intptr_t;
    using GLshort     = int16_t;
    using GLsizei     = int32_t;
    using GLsizeiptr  = intptr_t;
    using GLubyte     = uint8_t;
    using GLuint      = uint32_t;
    using GLushort    = uint16_t;
    using GLvoid      = void;
    using GLstring    = const char*;

    //--------------------------------------------------------------------------

    enum GLenum : uint32_t {
        #define \
        app_gpu_gl3_enum(app_gpu_gl3_enum) \
        app_gpu_gl3_enum(GL_ACTIVE_ATTRIBUTES,              0x8B89)\
        app_gpu_gl3_enum(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,    0x8B8A)\
        app_gpu_gl3_enum(GL_ACTIVE_UNIFORMS,                0x8B86)\
        app_gpu_gl3_enum(GL_ACTIVE_UNIFORM_MAX_LENGTH,      0x8B87)\
        app_gpu_gl3_enum(GL_ALWAYS,                         0x0207)\
        app_gpu_gl3_enum(GL_ARRAY_BUFFER,                   0x8892)\
        app_gpu_gl3_enum(GL_BACK,                           0x0405)\
        app_gpu_gl3_enum(GL_BLEND,                          0x0BE2)\
        app_gpu_gl3_enum(GL_BOOL_VEC2,                      0x8B57)\
        app_gpu_gl3_enum(GL_BOOL_VEC3,                      0x8B58)\
        app_gpu_gl3_enum(GL_BOOL_VEC4,                      0x8B59)\
        app_gpu_gl3_enum(GL_BOOL,                           0x8B56)\
        app_gpu_gl3_enum(GL_BYTE,                           0x1400)\
        app_gpu_gl3_enum(GL_CCW,                            0x0901)\
        app_gpu_gl3_enum(GL_CLAMP_TO_EDGE,                  0x812F)\
        app_gpu_gl3_enum(GL_CLAMP,                          0x2900)\
        app_gpu_gl3_enum(GL_CLEAR,                          0x1500)\
        app_gpu_gl3_enum(GL_COLOR_ATTACHMENT0,              0x8CE0)\
        app_gpu_gl3_enum(GL_COLOR_ATTACHMENT1,              0x8CE1)\
        app_gpu_gl3_enum(GL_COLOR_ATTACHMENT2,              0x8CE2)\
        app_gpu_gl3_enum(GL_COLOR_ATTACHMENT3,              0x8CE3)\
        app_gpu_gl3_enum(GL_COLOR_BUFFER_BIT,               0x4000)\
        app_gpu_gl3_enum(GL_COLOR,                          0x1800)\
        app_gpu_gl3_enum(GL_COMPILE_STATUS,                 0x8B81)\
        app_gpu_gl3_enum(GL_CONSTANT_ALPHA,                 0x8003)\
        app_gpu_gl3_enum(GL_CONSTANT_COLOR,                 0x8001)\
        app_gpu_gl3_enum(GL_CULL_FACE,                      0x0B44)\
        app_gpu_gl3_enum(GL_CW,                             0x0900)\
        app_gpu_gl3_enum(GL_DECR_WRAP,                      0x8508)\
        app_gpu_gl3_enum(GL_DECR,                           0x1E03)\
        app_gpu_gl3_enum(GL_DEPTH_ATTACHMENT,               0x8D00)\
        app_gpu_gl3_enum(GL_DEPTH_BUFFER_BIT,               0x0100)\
        app_gpu_gl3_enum(GL_DEPTH_COMPONENT,                0x1902)\
        app_gpu_gl3_enum(GL_DEPTH_COMPONENT16,              0x81A5)\
        app_gpu_gl3_enum(GL_DEPTH_TEST,                     0x0B71)\
        app_gpu_gl3_enum(GL_DEPTH,                          0x1801)\
        app_gpu_gl3_enum(GL_DITHER,                         0x0BD0)\
        app_gpu_gl3_enum(GL_DRAW_FRAMEBUFFER,               0x8CA9)\
        app_gpu_gl3_enum(GL_DST_ALPHA,                      0x0304)\
        app_gpu_gl3_enum(GL_DST_COLOR,                      0x0306)\
        app_gpu_gl3_enum(GL_DYNAMIC_DRAW,                   0x88E8)\
        app_gpu_gl3_enum(GL_ELEMENT_ARRAY_BUFFER,           0x8893)\
        app_gpu_gl3_enum(GL_EQUAL,                          0x0202)\
        app_gpu_gl3_enum(GL_EXTENSIONS,                     0x1F03)\
        app_gpu_gl3_enum(GL_FALSE,                          0x0000)\
        app_gpu_gl3_enum(GL_FLOAT_MAT2,                     0x8B5A)\
        app_gpu_gl3_enum(GL_FLOAT_MAT3,                     0x8B5B)\
        app_gpu_gl3_enum(GL_FLOAT_MAT4,                     0x8B5C)\
        app_gpu_gl3_enum(GL_FLOAT_VEC2,                     0x8B50)\
        app_gpu_gl3_enum(GL_FLOAT_VEC3,                     0x8B51)\
        app_gpu_gl3_enum(GL_FLOAT_VEC4,                     0x8B52)\
        app_gpu_gl3_enum(GL_FLOAT,                          0x1406)\
        app_gpu_gl3_enum(GL_FRAGMENT_SHADER,                0x8B30)\
        app_gpu_gl3_enum(GL_FRAMEBUFFER_BINDING,            0x8CA6)\
        app_gpu_gl3_enum(GL_FRAMEBUFFER_COMPLETE,           0x8CD5)\
        app_gpu_gl3_enum(GL_FRAMEBUFFER,                    0x8D40)\
        app_gpu_gl3_enum(GL_FRONT,                          0x0404)\
        app_gpu_gl3_enum(GL_FUNC_ADD,                       0x8006)\
        app_gpu_gl3_enum(GL_FUNC_REVERSE_SUBTRACT,          0x800B)\
        app_gpu_gl3_enum(GL_FUNC_SUBTRACT,                  0x800A)\
        app_gpu_gl3_enum(GL_GEQUAL,                         0x0206)\
        app_gpu_gl3_enum(GL_GREATER,                        0x0204)\
        app_gpu_gl3_enum(GL_INCR_WRAP,                      0x8507)\
        app_gpu_gl3_enum(GL_INCR,                           0x1E02)\
        app_gpu_gl3_enum(GL_INFO_LOG_LENGTH,                0x8B84)\
        app_gpu_gl3_enum(GL_INT_VEC2,                       0x8B53)\
        app_gpu_gl3_enum(GL_INT_VEC3,                       0x8B54)\
        app_gpu_gl3_enum(GL_INT_VEC4,                       0x8B55)\
        app_gpu_gl3_enum(GL_INT,                            0x1404)\
        app_gpu_gl3_enum(GL_INVALID_ENUM,                   0x0500)\
        app_gpu_gl3_enum(GL_INVALID_FRAMEBUFFER_OPERATION,  0x0506)\
        app_gpu_gl3_enum(GL_INVALID_OPERATION,              0x0502)\
        app_gpu_gl3_enum(GL_INVALID_VALUE,                  0x0501)\
        app_gpu_gl3_enum(GL_INVERT,                         0x150A)\
        app_gpu_gl3_enum(GL_KEEP,                           0x1E00)\
        app_gpu_gl3_enum(GL_LEQUAL,                         0x0203)\
        app_gpu_gl3_enum(GL_LESS,                           0x0201)\
        app_gpu_gl3_enum(GL_LINE_STRIP,                     0x0003)\
        app_gpu_gl3_enum(GL_LINEAR_MIPMAP_LINEAR,           0x2703)\
        app_gpu_gl3_enum(GL_LINEAR_MIPMAP_NEAREST,          0x2701)\
        app_gpu_gl3_enum(GL_LINEAR,                         0x2601)\
        app_gpu_gl3_enum(GL_LINES,                          0x0001)\
        app_gpu_gl3_enum(GL_LINK_STATUS,                    0x8B82)\
        app_gpu_gl3_enum(GL_MIRRORED_REPEAT,                0x8370)\
        app_gpu_gl3_enum(GL_MULTISAMPLE,                    0x809D)\
        app_gpu_gl3_enum(GL_NEAREST_MIPMAP_LINEAR,          0x2702)\
        app_gpu_gl3_enum(GL_NEAREST_MIPMAP_NEAREST,         0x2700)\
        app_gpu_gl3_enum(GL_NEAREST,                        0x2600)\
        app_gpu_gl3_enum(GL_NEVER,                          0x0200)\
        app_gpu_gl3_enum(GL_NO_ERROR,                       0x0000)\
        app_gpu_gl3_enum(GL_NOTEQUAL,                       0x0205)\
        app_gpu_gl3_enum(GL_NUM_EXTENSIONS,                 0x821D)\
        app_gpu_gl3_enum(GL_ONE_MINUS_CONSTANT_ALPHA,       0x8004)\
        app_gpu_gl3_enum(GL_ONE_MINUS_CONSTANT_COLOR,       0x8002)\
        app_gpu_gl3_enum(GL_ONE_MINUS_DST_ALPHA,            0x0305)\
        app_gpu_gl3_enum(GL_ONE_MINUS_DST_COLOR,            0x0307)\
        app_gpu_gl3_enum(GL_ONE_MINUS_SRC_ALPHA,            0x0303)\
        app_gpu_gl3_enum(GL_ONE_MINUS_SRC_COLOR,            0x0301)\
        app_gpu_gl3_enum(GL_ONE,                            0x0001)\
        app_gpu_gl3_enum(GL_OUT_OF_MEMORY,                  0x0505)\
        app_gpu_gl3_enum(GL_POINTS,                         0x0000)\
        app_gpu_gl3_enum(GL_POLYGON_OFFSET_FILL,            0x8037)\
        app_gpu_gl3_enum(GL_PROGRAM_POINT_SIZE,             0x8642)\
        app_gpu_gl3_enum(GL_R16F,                           0x822D)\
        app_gpu_gl3_enum(GL_R32F,                           0x822E)\
        app_gpu_gl3_enum(GL_R8,                             0x8229)\
        app_gpu_gl3_enum(GL_READ_FRAMEBUFFER,               0x8CA8)\
        app_gpu_gl3_enum(GL_RED,                            0x1903)\
        app_gpu_gl3_enum(GL_RENDERBUFFER,                   0x8D41)\
        app_gpu_gl3_enum(GL_REPEAT,                         0x2901)\
        app_gpu_gl3_enum(GL_REPLACE,                        0x1E01)\
        app_gpu_gl3_enum(GL_RGB,                            0x1907)\
        app_gpu_gl3_enum(GL_RGB10_A2,                       0x8059)\
        app_gpu_gl3_enum(GL_RGB5_A1,                        0x8057)\
        app_gpu_gl3_enum(GL_RGB5,                           0x8050)\
        app_gpu_gl3_enum(GL_RGB8,                           0x8051)\
        app_gpu_gl3_enum(GL_RGBA,                           0x1908)\
        app_gpu_gl3_enum(GL_RGBA16F,                        0x881A)\
        app_gpu_gl3_enum(GL_RGBA32F,                        0x8814)\
        app_gpu_gl3_enum(GL_RGBA4,                          0x8056)\
        app_gpu_gl3_enum(GL_RGBA8,                          0x8058)\
        app_gpu_gl3_enum(GL_SAMPLE_ALPHA_TO_COVERAGE,       0x809E)\
        app_gpu_gl3_enum(GL_SAMPLER_1D_SHADOW,              0x8B61)\
        app_gpu_gl3_enum(GL_SAMPLER_1D,                     0x8B5D)\
        app_gpu_gl3_enum(GL_SAMPLER_2D_SHADOW,              0x8B62)\
        app_gpu_gl3_enum(GL_SAMPLER_2D,                     0x8B5E)\
        app_gpu_gl3_enum(GL_SAMPLER_3D,                     0x8B5F)\
        app_gpu_gl3_enum(GL_SAMPLER_CUBE,                   0x8B60)\
        app_gpu_gl3_enum(GL_SCISSOR_TEST,                   0x0C11)\
        app_gpu_gl3_enum(GL_SHORT,                          0x1402)\
        app_gpu_gl3_enum(GL_SRC_ALPHA_SATURATE,             0x0308)\
        app_gpu_gl3_enum(GL_SRC_ALPHA,                      0x0302)\
        app_gpu_gl3_enum(GL_SRC_COLOR,                      0x0300)\
        app_gpu_gl3_enum(GL_STACK_OVERFLOW,                 0x0503)\
        app_gpu_gl3_enum(GL_STACK_UNDERFLOW,                0x0504)\
        app_gpu_gl3_enum(GL_STATIC_DRAW,                    0x88E4)\
        app_gpu_gl3_enum(GL_STENCIL_ATTACHMENT,             0x8D20)\
        app_gpu_gl3_enum(GL_STENCIL_BUFFER_BIT,             0x0400)\
        app_gpu_gl3_enum(GL_STENCIL_TEST,                   0x0B90)\
        app_gpu_gl3_enum(GL_STENCIL,                        0x1802)\
        app_gpu_gl3_enum(GL_STREAM_DRAW,                    0x88E0)\
        app_gpu_gl3_enum(GL_TEXTURE_2D_ARRAY,               0x8C1A)\
        app_gpu_gl3_enum(GL_TEXTURE_2D,                     0x0DE1)\
        app_gpu_gl3_enum(GL_TEXTURE_3D,                     0x806F)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,    0x8516)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,    0x8518)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,    0x851A)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP_POSITIVE_X,    0x8515)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,    0x8517)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,    0x8519)\
        app_gpu_gl3_enum(GL_TEXTURE_CUBE_MAP,               0x8513)\
        app_gpu_gl3_enum(GL_TEXTURE_MAG_FILTER,             0x2800)\
        app_gpu_gl3_enum(GL_TEXTURE_MAX_LOD,                0x813B)\
        app_gpu_gl3_enum(GL_TEXTURE_MIN_FILTER,             0x2801)\
        app_gpu_gl3_enum(GL_TEXTURE_MIN_LOD,                0x813A)\
        app_gpu_gl3_enum(GL_TEXTURE_WRAP_R,                 0x8072)\
        app_gpu_gl3_enum(GL_TEXTURE_WRAP_S,                 0x2802)\
        app_gpu_gl3_enum(GL_TEXTURE_WRAP_T,                 0x2803)\
        app_gpu_gl3_enum(GL_TEXTURE0,                       0x84C0)\
        app_gpu_gl3_enum(GL_TRIANGLE_STRIP,                 0x0005)\
        app_gpu_gl3_enum(GL_TRIANGLES,                      0x0004)\
        app_gpu_gl3_enum(GL_TRUE,                           0x0001)\
        app_gpu_gl3_enum(GL_UNSIGNED_BYTE_2_3_3_REV,        0x8362)\
        app_gpu_gl3_enum(GL_UNSIGNED_BYTE_3_3_2,            0x8032)\
        app_gpu_gl3_enum(GL_UNSIGNED_BYTE,                  0x1401)\
        app_gpu_gl3_enum(GL_UNSIGNED_INT_10_10_10_2,        0x8036)\
        app_gpu_gl3_enum(GL_UNSIGNED_INT_2_10_10_10_REV,    0x8368)\
        app_gpu_gl3_enum(GL_UNSIGNED_INT_8_8_8_8_REV,       0x8367)\
        app_gpu_gl3_enum(GL_UNSIGNED_INT_8_8_8_8,           0x8035)\
        app_gpu_gl3_enum(GL_UNSIGNED_INT,                   0x1405)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT_1_5_5_5_REV,     0x8366)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT_4_4_4_4_REV,     0x8365)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT_4_4_4_4,         0x8033)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT_5_5_5_1,         0x8034)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT_5_6_5_REV,       0x8364)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT_5_6_5,           0x8363)\
        app_gpu_gl3_enum(GL_UNSIGNED_SHORT,                 0x1403)\
        app_gpu_gl3_enum(GL_VERTEX_SHADER,                  0x8B31)\
        app_gpu_gl3_enum(GL_ZERO,                           0x0000)\

        #define app_gpu_gl3_enum_definition(Name,Value) \
            Name = Value,
            app_gpu_gl3_enum(app_gpu_gl3_enum_definition)
        #undef app_gpu_gl3_enum_definition
    };

    inline
    std::ostream& operator<<(std::ostream& o, const GLenum e) {
        #define app_gpu_gl3_enum_string(Name,Value) \
            if (e == GLenum::Name) return o << #Name;
            app_gpu_gl3_enum(app_gpu_gl3_enum_string)
        #undef app_gpu_gl3_enum_string
        return o << "GLenum(" << std::underlying_type_t<GLenum>(e) << ")";
    }

    //--------------------------------------------------------------------------

    #define \
    app_gpu_gl3_function(app_gpu_gl3_function)\
    app_gpu_gl3_function(GLenum,    glGetError,(void))\
    app_gpu_gl3_function(GLstring,  glGetString,(GLenum name))\
    app_gpu_gl3_function(GLstring,  glGetStringi,(GLenum name, GLuint index))\
    app_gpu_gl3_function(void,      glGetBooleanv,(GLenum pname, GLboolean* params))\
    app_gpu_gl3_function(void,      glGetFloatv,(GLenum pname, GLfloat* params))\
    app_gpu_gl3_function(void,      glGetIntegerv,(GLenum pname, GLint* params))\
    /* State */\
    app_gpu_gl3_function(void,      glBlendColor,(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))\
    app_gpu_gl3_function(void,      glBlendEquationSeparate,(GLenum modeRGB, GLenum modeAlpha))\
    app_gpu_gl3_function(void,      glBlendFuncSeparate,(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha))\
    app_gpu_gl3_function(void,      glClear,(GLbitfield mask))\
    app_gpu_gl3_function(void,      glClearColor,(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))\
    app_gpu_gl3_function(void,      glClearDepth,(GLclampd depth))\
    app_gpu_gl3_function(void,      glClearStencil,(GLint stencil))\
    app_gpu_gl3_function(void,      glColorMask,(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha))\
    app_gpu_gl3_function(void,      glCullFace,(GLenum mode))\
    app_gpu_gl3_function(void,      glDepthFunc,(GLenum func))\
    app_gpu_gl3_function(void,      glDepthMask,(GLboolean flag))\
    app_gpu_gl3_function(void,      glDisable,(GLenum cap))\
    app_gpu_gl3_function(void,      glEnable,(GLenum cap))\
    app_gpu_gl3_function(void,      glFinish,(void))\
    app_gpu_gl3_function(void,      glFlush,(void))\
    app_gpu_gl3_function(void,      glFrontFace,(GLenum mode))\
    app_gpu_gl3_function(void,      glPolygonOffset,(GLfloat factor, GLfloat units))\
    app_gpu_gl3_function(void,      glScissor,(GLint x, GLint y, GLsizei width, GLsizei height))\
    app_gpu_gl3_function(void,      glStencilFunc,(GLenum func, GLint ref, GLuint mask))\
    app_gpu_gl3_function(void,      glStencilFuncSeparate,(GLenum face, GLenum func, GLint ref, GLuint mask))\
    app_gpu_gl3_function(void,      glStencilMask,(GLuint mask))\
    app_gpu_gl3_function(void,      glStencilOp,(GLenum fail, GLenum zfail, GLenum zpass))\
    app_gpu_gl3_function(void,      glStencilOpSeparate,(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass))\
    app_gpu_gl3_function(void,      glViewport,(GLint x, GLint y, GLsizei width, GLsizei height))\
    /* Drawing */\
    app_gpu_gl3_function(void,      glDrawArrays,(GLenum mode, GLint first, GLsizei count))\
    app_gpu_gl3_function(void,      glDrawArraysInstanced,(GLenum mode, GLint first, GLsizei count, GLsizei instancecount))\
    app_gpu_gl3_function(void,      glDrawBuffers,(GLsizei n, const GLenum* bufs))\
    app_gpu_gl3_function(void,      glDrawElements,(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices))\
    app_gpu_gl3_function(void,      glDrawElementsInstanced,(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instancecount))\
    /* Framebuffers */\
    app_gpu_gl3_function(void,      glBindFramebuffer,(GLenum target, GLuint framebuffer))\
    app_gpu_gl3_function(void,      glBindRenderbuffer,(GLenum target, GLuint renderbuffer))\
    app_gpu_gl3_function(void,      glBlitFramebuffer,(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))\
    app_gpu_gl3_function(GLenum,    glCheckFramebufferStatus,(GLenum target))\
    app_gpu_gl3_function(void,      glDeleteFramebuffers,(GLsizei n, const GLuint* framebuffers))\
    app_gpu_gl3_function(void,      glDeleteRenderbuffers,(GLsizei n, const GLuint* renderbuffers))\
    app_gpu_gl3_function(void,      glFramebufferRenderbuffer,(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer))\
    app_gpu_gl3_function(void,      glFramebufferTexture2D,(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))\
    app_gpu_gl3_function(void,      glFramebufferTextureLayer,(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer))\
    app_gpu_gl3_function(void,      glGenFramebuffers,(GLsizei n, GLuint* framebuffers))\
    app_gpu_gl3_function(void,      glGenRenderbuffers,(GLsizei n, GLuint* renderbuffers))\
    app_gpu_gl3_function(void,      glRenderbufferStorage,(GLenum target, GLenum internalformat, GLsizei width, GLsizei height))\
    app_gpu_gl3_function(void,      glRenderbufferStorageMultisample,(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height))\
    /* Buffers */\
    app_gpu_gl3_function(void,      glBindBuffer,(GLenum target, GLuint buffer))\
    app_gpu_gl3_function(void,      glBufferData,(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage))\
    app_gpu_gl3_function(void,      glBufferSubData,(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data))\
    app_gpu_gl3_function(void,      glClearBufferfi,(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil))\
    app_gpu_gl3_function(void,      glClearBufferfv,(GLenum buffer, GLint drawbuffer, const GLfloat* value))\
    app_gpu_gl3_function(void,      glClearBufferuiv,(GLenum buffer, GLint drawbuffer, const GLuint* value))\
    app_gpu_gl3_function(void,      glDeleteBuffers,(GLsizei n, GLuint* buffers))\
    app_gpu_gl3_function(void,      glGenBuffers,(GLsizei n, GLuint* buffers))\
    /* Vertex Arrays */\
    app_gpu_gl3_function(void,      glBindVertexArray,(GLuint array))\
    app_gpu_gl3_function(void,      glDeleteVertexArrays,(GLsizei n, const GLuint *arrays))\
    app_gpu_gl3_function(void,      glGenVertexArrays,(GLsizei n, GLuint* arrays))\
    /* Vertex Attributes */\
    app_gpu_gl3_function(void,      glDisableVertexAttribArray,(GLuint index))\
    app_gpu_gl3_function(void,      glEnableVertexAttribArray,(GLuint index))\
    app_gpu_gl3_function(void,      glVertexAttribDivisor,(GLuint index, GLuint divisor))\
    app_gpu_gl3_function(void,      glVertexAttribPointer,(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer))\
    /* Shaders */\
    app_gpu_gl3_function(void,      glCompileShader,(GLuint shader))\
    app_gpu_gl3_function(GLuint,    glCreateShader,(GLenum shaderType))\
    app_gpu_gl3_function(void,      glDeleteShader,(GLuint shader))\
    app_gpu_gl3_function(void,      glGetShaderInfoLog,(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog))\
    app_gpu_gl3_function(void,      glGetShaderiv,(GLuint shader, GLenum pname, GLint* params))\
    app_gpu_gl3_function(void,      glShaderSource,(GLuint shader, GLsizei count, const GLchar** string, const GLint* length))\
    /* Programs */\
    app_gpu_gl3_function(void,      glAttachShader,(GLuint program, GLuint shader))\
    app_gpu_gl3_function(void,      glBindAttribLocation,(GLuint program, GLuint index, const GLchar* name))\
    app_gpu_gl3_function(GLuint,    glCreateProgram,(void))\
    app_gpu_gl3_function(void,      glDeleteProgram,(GLuint program))\
    app_gpu_gl3_function(void,      glGetActiveAttrib,(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name))\
    app_gpu_gl3_function(void,      glGetActiveUniform,(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name))\
    app_gpu_gl3_function(GLint,     glGetAttribLocation,(GLuint program, const GLchar* name))\
    app_gpu_gl3_function(void,      glGetProgramInfoLog,(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog))\
    app_gpu_gl3_function(void,      glGetProgramiv,(GLuint program, GLenum pname, GLint* params))\
    app_gpu_gl3_function(GLint,     glGetUniformLocation,(GLuint program, const GLchar* name))\
    app_gpu_gl3_function(void,      glLinkProgram,(GLuint program))\
    app_gpu_gl3_function(void,      glUseProgram,(GLuint program))\
    app_gpu_gl3_function(void,      glValidateProgram,(GLuint program))\
    /* Uniforms */\
    app_gpu_gl3_function(void,      glUniform1f,(GLint location, const GLfloat value))\
    app_gpu_gl3_function(void,      glUniform1fv,(GLint location, GLsizei count, const GLfloat *value))\
    app_gpu_gl3_function(void,      glUniform1i,(GLint location, const GLint value))\
    app_gpu_gl3_function(void,      glUniform1iv,(GLint location, GLsizei count, const GLint *value))\
    app_gpu_gl3_function(void,      glUniform2fv,(GLint location, GLsizei count, const GLfloat *value))\
    app_gpu_gl3_function(void,      glUniform2iv,(GLint location, GLsizei count, const GLint *value))\
    app_gpu_gl3_function(void,      glUniform3fv,(GLint location, GLsizei count, const GLfloat *value))\
    app_gpu_gl3_function(void,      glUniform3iv,(GLint location, GLsizei count, const GLint *value))\
    app_gpu_gl3_function(void,      glUniform4fv,(GLint location, GLsizei count, const GLfloat *value))\
    app_gpu_gl3_function(void,      glUniform4iv,(GLint location, GLsizei count, const GLint *value))\
    app_gpu_gl3_function(void,      glUniformMatrix2fv,(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))\
    app_gpu_gl3_function(void,      glUniformMatrix3fv,(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))\
    app_gpu_gl3_function(void,      glUniformMatrix4fv,(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))\
    /* Textures */\
    app_gpu_gl3_function(void,      glActiveTexture,(GLenum texture))\
    app_gpu_gl3_function(void,      glBindTexture,(GLenum target, GLuint texture))\
    app_gpu_gl3_function(void,      glCompressedTexImage2D,(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data))\
    app_gpu_gl3_function(void,      glCompressedTexImage3D,(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data))\
    app_gpu_gl3_function(void,      glDeleteTextures,(GLsizei n, const GLuint * textures))\
    app_gpu_gl3_function(void,      glGenTextures,(GLsizei n, GLuint * textures))\
    app_gpu_gl3_function(void,      glGetTexParameterfv,(GLenum target, GLenum pname, GLfloat *params))\
    app_gpu_gl3_function(void,      glGetTexParameteriv,(GLenum target, GLenum pname, GLint *params))\
    app_gpu_gl3_function(void,      glTexImage2D,(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data))\
    app_gpu_gl3_function(void,      glTexImage3D,(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels))\
    app_gpu_gl3_function(void,      glTexParameterf,(GLenum target, GLenum pname, GLfloat param))\
    app_gpu_gl3_function(void,      glTexParameteri,(GLenum target, GLenum pname, GLint param))\
    app_gpu_gl3_function(void,      glTexSubImage2D,(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels))\
    app_gpu_gl3_function(void,      glTexSubImage3D,(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels))\

    //--------------------------------------------------------------------------

    #define app_gpu_gl3_function_pointer(ReturnType,Name,Parameters)\
        static ReturnType (*Name) Parameters = nullptr;
        app_gpu_gl3_function(app_gpu_gl3_function_pointer)
    #undef app_gpu_gl3_function_pointer

    //--------------------------------------------------------------------------

    struct GLcontext;
    extern GLcontext*  glCreateContext();
    extern void        glDestroyContext(GLcontext*);
    extern GLcontext*  glGetCurrentContext();
    extern void        glSetCurrentContext(GLcontext*);
    extern void        glSetCurrentWindow(GLcontext*, void*);
    extern GLint       glGetSwapInterval(GLcontext*);
    extern void        glSetSwapInterval(GLcontext*, GLint interval);
    extern void        glSwapBuffers(GLcontext*);
    extern void*       glGetProcAddress(const char* name);
    extern const char* glGetErrorString(GLenum);

} // namespace app::gpu::gl3

//------------------------------------------------------------------------------

#include "../../../detail/platform.hpp"
#if app_debug

    #include "../../../detail/assert.hpp"
    namespace app::gpu::gl3 {

        struct glCheckError {
            const char* file;
            const int   line;
            const char* call;
            ~glCheckError() {
                if (auto* error = glGetErrorString(glGetError())) {
                    app::assert::err({file,line,call,""}," error: ",error);
                }
                //app::assert::log({file,line,call,""});
            }
        };

    }

    #define glCheckError(call) [&](){\
        ::app::gpu::gl3::glCheckError _{__FILE__,__LINE__,#call};\
        return call;\
    }()

    #define glActiveTexture(...)                  glCheckError(glActiveTexture(__VA_ARGS__))
    #define glAttachShader(...)                   glCheckError(glAttachShader(__VA_ARGS__))
    #define glBindAttribLocation(...)             glCheckError(glBindAttribLocation(__VA_ARGS__))
    #define glBindBuffer(...)                     glCheckError(glBindBuffer(__VA_ARGS__))
    #define glBindFramebuffer(...)                glCheckError(glBindFramebuffer(__VA_ARGS__))
    #define glBindRenderbuffer(...)               glCheckError(glBindRenderbuffer(__VA_ARGS__))
    #define glBindTexture(...)                    glCheckError(glBindTexture(__VA_ARGS__))
    #define glBindVertexArray(...)                glCheckError(glBindVertexArray(__VA_ARGS__))
    #define glBlendColor(...)                     glCheckError(glBlendColor(__VA_ARGS__))
    #define glBlendEquationSeparate(...)          glCheckError(glBlendEquationSeparate(__VA_ARGS__))
    #define glBlendFuncSeparate(...)              glCheckError(glBlendFuncSeparate(__VA_ARGS__))
    #define glBlitFramebuffer(...)                glCheckError(glBlitFramebuffer(__VA_ARGS__))
    #define glBufferData(...)                     glCheckError(glBufferData(__VA_ARGS__))
    #define glBufferSubData(...)                  glCheckError(glBufferSubData(__VA_ARGS__))
    #define glCheckFramebufferStatus(...)         glCheckError(glCheckFramebufferStatus(__VA_ARGS__))
    #define glClear(...)                          glCheckError(glClear(__VA_ARGS__))
    #define glClearBufferfi(...)                  glCheckError(glClearBufferfi(__VA_ARGS__))
    #define glClearBufferfv(...)                  glCheckError(glClearBufferfv(__VA_ARGS__))
    #define glClearBufferuiv(...)                 glCheckError(glClearBufferuiv(__VA_ARGS__))
    #define glClearColor(...)                     glCheckError(glClearColor(__VA_ARGS__))
    #define glClearDepth(...)                     glCheckError(glClearDepth(__VA_ARGS__))
    #define glClearStencil(...)                   glCheckError(glClearStencil(__VA_ARGS__))
    #define glColorMask(...)                      glCheckError(glColorMask(__VA_ARGS__))
    #define glCompileShader(...)                  glCheckError(glCompileShader(__VA_ARGS__))
    #define glCompressedTexImage2D(...)           glCheckError(glCompressedTexImage2D(__VA_ARGS__))
    #define glCompressedTexImage3D(...)           glCheckError(glCompressedTexImage3D(__VA_ARGS__))
    #define glCreateProgram(...)                  glCheckError(glCreateProgram(__VA_ARGS__))
    #define glCreateShader(...)                   glCheckError(glCreateShader(__VA_ARGS__))
    #define glCullFace(...)                       glCheckError(glCullFace(__VA_ARGS__))
    #define glDeleteBuffers(...)                  glCheckError(glDeleteBuffers(__VA_ARGS__))
    #define glDeleteFramebuffers(...)             glCheckError(glDeleteFramebuffers(__VA_ARGS__))
    #define glDeleteProgram(...)                  glCheckError(glDeleteProgram(__VA_ARGS__))
    #define glDeleteRenderbuffers(...)            glCheckError(glDeleteRenderbuffers(__VA_ARGS__))
    #define glDeleteShader(...)                   glCheckError(glDeleteShader(__VA_ARGS__))
    #define glDeleteTextures(...)                 glCheckError(glDeleteTextures(__VA_ARGS__))
    #define glDeleteVertexArrays(...)             glCheckError(glDeleteVertexArrays(__VA_ARGS__))
    #define glDepthFunc(...)                      glCheckError(glDepthFunc(__VA_ARGS__))
    #define glDepthMask(...)                      glCheckError(glDepthMask(__VA_ARGS__))
    #define glDisable(...)                        glCheckError(glDisable(__VA_ARGS__))
    #define glDisableVertexAttribArray(...)       glCheckError(glDisableVertexAttribArray(__VA_ARGS__))
    #define glDrawArrays(...)                     glCheckError(glDrawArrays(__VA_ARGS__))
    #define glDrawArraysInstanced(...)            glCheckError(glDrawArraysInstanced(__VA_ARGS__))
    #define glDrawBuffers(...)                    glCheckError(glDrawBuffers(__VA_ARGS__))
    #define glDrawElements(...)                   glCheckError(glDrawElements(__VA_ARGS__))
    #define glDrawElementsInstanced(...)          glCheckError(glDrawElementsInstanced(__VA_ARGS__))
    #define glEnable(...)                         glCheckError(glEnable(__VA_ARGS__))
    #define glEnableVertexAttribArray(...)        glCheckError(glEnableVertexAttribArray(__VA_ARGS__))
    #define glFinish(...)                         glCheckError(glFinish(__VA_ARGS__))
    #define glFlush(...)                          glCheckError(glFlush(__VA_ARGS__))
    #define glFramebufferRenderbuffer(...)        glCheckError(glFramebufferRenderbuffer(__VA_ARGS__))
    #define glFramebufferTexture2D(...)           glCheckError(glFramebufferTexture2D(__VA_ARGS__))
    #define glFramebufferTextureLayer(...)        glCheckError(glFramebufferTextureLayer(__VA_ARGS__))
    #define glFrontFace(...)                      glCheckError(glFrontFace(__VA_ARGS__))
    #define glGenBuffers(...)                     glCheckError(glGenBuffers(__VA_ARGS__))
    #define glGenFramebuffers(...)                glCheckError(glGenFramebuffers(__VA_ARGS__))
    #define glGenRenderbuffers(...)               glCheckError(glGenRenderbuffers(__VA_ARGS__))
    #define glGenTextures(...)                    glCheckError(glGenTextures(__VA_ARGS__))
    #define glGenVertexArrays(...)                glCheckError(glGenVertexArrays(__VA_ARGS__))
    #define glGetActiveAttrib(...)               glCheckError(glGetActiveAttrib(__VA_ARGS__))
    #define glGetActiveUniform(...)               glCheckError(glGetActiveUniform(__VA_ARGS__))
    #define glGetAttribLocation(...)              glCheckError(glGetAttribLocation(__VA_ARGS__))
    #define glGetBooleanv(...)                    glCheckError(glGetBooleanv(__VA_ARGS__))
    #define glGetError(...)                       glCheckError(glGetError(__VA_ARGS__))
    #define glGetFloatv(...)                      glCheckError(glGetFloatv(__VA_ARGS__))
    #define glGetIntegerv(...)                    glCheckError(glGetIntegerv(__VA_ARGS__))
    #define glGetProgramInfoLog(...)              glCheckError(glGetProgramInfoLog(__VA_ARGS__))
    #define glGetProgramiv(...)                   glCheckError(glGetProgramiv(__VA_ARGS__))
    #define glGetShaderInfoLog(...)               glCheckError(glGetShaderInfoLog(__VA_ARGS__))
    #define glGetShaderiv(...)                    glCheckError(glGetShaderiv(__VA_ARGS__))
    #define glGetString(...)                      glCheckError(glGetString(__VA_ARGS__))
    #define glGetStringi(...)                     glCheckError(glGetStringi(__VA_ARGS__))
    #define glGetTexParameterfv(...)              glCheckError(glGetTexParameterfv(__VA_ARGS__))
    #define glGetTexParameteriv(...)              glCheckError(glGetTexParameteriv(__VA_ARGS__))
    #define glGetUniformLocation(...)             glCheckError(glGetUniformLocation(__VA_ARGS__))
    #define glLinkProgram(...)                    glCheckError(glLinkProgram(__VA_ARGS__))
    #define glPolygonOffset(...)                  glCheckError(glPolygonOffset(__VA_ARGS__))
    #define glRenderbufferStorage(...)            glCheckError(glRenderbufferStorage(__VA_ARGS__))
    #define glRenderbufferStorageMultisample(...) glCheckError(glRenderbufferStorageMultisample(__VA_ARGS__))
    #define glScissor(...)                        glCheckError(glScissor(__VA_ARGS__))
    #define glShaderSource(...)                   glCheckError(glShaderSource(__VA_ARGS__))
    #define glStencilFunc(...)                    glCheckError(glStencilFunc(__VA_ARGS__))
    #define glStencilFuncSeparate(...)            glCheckError(glStencilFuncSeparate(__VA_ARGS__))
    #define glStencilMask(...)                    glCheckError(glStencilMask(__VA_ARGS__))
    #define glStencilOp(...)                      glCheckError(glStencilOp(__VA_ARGS__))
    #define glStencilOpSeparate(...)              glCheckError(glStencilOpSeparate(__VA_ARGS__))
    #define glTexImage2D(...)                     glCheckError(glTexImage2D(__VA_ARGS__))
    #define glTexImage3D(...)                     glCheckError(glTexImage3D(__VA_ARGS__))
    #define glTexParameterf(...)                  glCheckError(glTexParameterf(__VA_ARGS__))
    #define glTexParameteri(...)                  glCheckError(glTexParameteri(__VA_ARGS__))
    #define glTexSubImage2D(...)                  glCheckError(glTexSubImage2D(__VA_ARGS__))
    #define glTexSubImage3D(...)                  glCheckError(glTexSubImage3D(__VA_ARGS__))
    #define glUniform1f(...)                      glCheckError(glUniform1f(__VA_ARGS__))
    #define glUniform1fv(...)                     glCheckError(glUniform1fv(__VA_ARGS__))
    #define glUniform1i(...)                      glCheckError(glUniform1i(__VA_ARGS__))
    #define glUniform1iv(...)                     glCheckError(glUniform1iv(__VA_ARGS__))
    #define glUniform2fv(...)                     glCheckError(glUniform2fv(__VA_ARGS__))
    #define glUniform2iv(...)                     glCheckError(glUniform2iv(__VA_ARGS__))
    #define glUniform3fv(...)                     glCheckError(glUniform3fv(__VA_ARGS__))
    #define glUniform3iv(...)                     glCheckError(glUniform3iv(__VA_ARGS__))
    #define glUniform4fv(...)                     glCheckError(glUniform4fv(__VA_ARGS__))
    #define glUniform4iv(...)                     glCheckError(glUniform4iv(__VA_ARGS__))
    #define glUniformMatrix2fv(...)               glCheckError(glUniformMatrix2fv(__VA_ARGS__))
    #define glUniformMatrix3fv(...)               glCheckError(glUniformMatrix3fv(__VA_ARGS__))
    #define glUniformMatrix4fv(...)               glCheckError(glUniformMatrix4fv(__VA_ARGS__))
    #define glUseProgram(...)                     glCheckError(glUseProgram(__VA_ARGS__))
    #define glValidateProgram(...)                glCheckError(glValidateProgram(__VA_ARGS__))
    #define glVertexAttribDivisor(...)            glCheckError(glVertexAttribDivisor(__VA_ARGS__))
    #define glVertexAttribPointer(...)            glCheckError(glVertexAttribPointer(__VA_ARGS__))
    #define glViewport(...)                       glCheckError(glViewport(__VA_ARGS__))

#endif // app_debug

//------------------------------------------------------------------------------

#include app_os_path(api.inl)