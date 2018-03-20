#pragma once
#include "../writer.hpp"

namespace app::gpuc {

    struct glsl_writer : writer {

        using writer::writer;
        using writer::write;

        //----------------------------------------------------------------------

        void write(const lexeme& l) override {
            switch (l.token) {
                case BOOL2:        return writer::write("bvec2");
                case BOOL3:        return writer::write("bvec3");
                case BOOL4:        return writer::write("bvec4");

                case FLOAT2:       return writer::write("vec2");
                case FLOAT3:       return writer::write("vec3");
                case FLOAT4:       return writer::write("vec4");

                case FLOAT2X2:     return writer::write("mat2x2");
                case FLOAT2X3:     return writer::write("mat2x3");
                case FLOAT2X4:     return writer::write("mat2x4");

                case FLOAT3X2:     return writer::write("mat3x2");
                case FLOAT3X3:     return writer::write("mat3x3");
                case FLOAT3X4:     return writer::write("mat3x4");

                case FLOAT4X2:     return writer::write("mat4x2");
                case FLOAT4X3:     return writer::write("mat4x3");
                case FLOAT4X4:     return writer::write("mat4x4");

                case INT2:         return writer::write("ivec2");
                case INT3:         return writer::write("ivec3");
                case INT4:         return writer::write("ivec4");

                case UINT2:        return writer::write("uvec2");
                case UINT3:        return writer::write("uvec3");
                case UINT4:        return writer::write("uvec4");

                case TEXTURE_1D:   return writer::write("sampler1D");
                case TEXTURE_2D:   return writer::write("sampler2D");
                case TEXTURE_3D:   return writer::write("sampler3D");
                case TEXTURE_CUBE: return writer::write("samplerCube");

                default:           return writer::write(l);
            }
        }

        //----------------------------------------------------------------------

        unsigned attribute_index = 0;
        unsigned output_count = 0;

        const node* main = nullptr;

        std::vector<const lexeme*> prefixes;

        void prefix(const lexeme* l,const char* separator = "_") {
            for (auto prefix : prefixes) write(prefix,separator);
            write(l);
        }

        //----------------------------------------------------------------------

        void declare_uniform(const node& node) {
            write("uniform ",node.type_name()," ");
            prefix(node.lexeme);
            write(";\n");
        }

        void declare_uniforms(const node& node) {
            unsigned uniform_count = 0;
            for (auto& input : node.children()) {
                app_assert(input);
                if (input->semantic == UNIFORM_DEFINITION) {
                    uniform_count += 1;
                    declare_uniform(*input);
                }
            }
            if (uniform_count) write("\n");
        }

        //----------------------------------------------------------------------

        void declare_attribute(const node& node) {
            auto type = node.type;
            app_assert(type);
            if (type->semantic == STRUCT_DEFINITION) {
                prefixes.push_back(node.lexeme);
                for (auto& child : type->children()) {
                    declare_attribute(*child);
                }
                prefixes.pop_back();
                return;
            }
            if (shader_stage == gpuc::shader_stage::VERTEX) {
                write("layout(location = ",attribute_index++,") ");
                
            }
            write("in ",node.type_name()," ");
            prefix(node.lexeme);
            write(";\n");
        }

        void declare_attributes(const node& node) {
            unsigned attribute_count = 0;
            for (auto& input : node.children()) {
                app_assert(input);
                if (input->semantic == VARIABLE_DEFINITION) {
                    attribute_count += 1;
                    declare_attribute(*input);
                }
            }
            if (attribute_count) write("\n");
        }

        //----------------------------------------------------------------------

        void declare_outputs(const node& outputs) {
            auto type = outputs.type;
            app_assert(type);
            if (type->semantic == STRUCT_DEFINITION) {
                prefixes.push_back(outputs.lexeme);
                for (auto& child : type->children()) {
                    declare_outputs(*child);
                }
                prefixes.pop_back();
                if (output_count) write("\n");
                return;
            }
            output_count += 1;
            write("out ",outputs.type_name()," ");
            prefix(outputs.lexeme);
            write(";\n");
        }

        //----------------------------------------------------------------------

        void assign_attribute(const node& input) {
            auto type = input.type;
            app_assert(type);
            if (type->semantic == STRUCT_DEFINITION) {
                write(input.type_name()," ",input.lexeme,";\n");
                prefixes.push_back(input.lexeme);
                for (auto& child : type->children()) {
                    assign_attribute(*child);
                }
                prefixes.pop_back();
                return;
            }
            prefix(input.lexeme,".");
            write(" = ");
            prefix(input.lexeme,"_");
            write(";\n");
        }

        void assign_attributes(const node& inputs) {
            unsigned attribute_count = 0;
            for (auto& input : inputs.children()) {
                app_assert(input);
                if (input->semantic == VARIABLE_DEFINITION) {
                    attribute_count += 1;
                    assign_attribute(*input);
                }
            }
            if (attribute_count) write("\n");
        }

        //----------------------------------------------------------------------

        void invoke_gpuc_main(const node& inputs) {
            write(main->type_name()," ",main->lexeme,"_result = ");
            write(main->lexeme,"(");
            unsigned argument_count = 0;
            for (auto& input : inputs.children()) {
                app_assert(input);
                if (argument_count++) write(", ");
                write(input->lexeme);
            }
            write(");\n\n");
        }

        //----------------------------------------------------------------------

        void assign_outputs(const node& outputs) {
            auto type = outputs.type;
            app_assert(type);
            if (type->semantic == STRUCT_DEFINITION) {
                prefixes.push_back(outputs.lexeme);
                for (auto& child : type->children()) {
                    assign_outputs(*child);
                }
                prefixes.pop_back();
                return;
            }
            if (output_count++ == 0) {
                if (shader_stage == gpuc::shader_stage::VERTEX) {
                    // first output is gl_Position
                    write("gl_Position = ");
                    write(main->lexeme,"_result.",outputs.lexeme,";\n");
                }
            }
            prefix(outputs.lexeme);
            write(" = ",main->lexeme,"_result.",outputs.lexeme,";\n");
        }

        //----------------------------------------------------------------------

        void write_glsl_main(const node& node) {
            auto inputs = node.child(0);
            app_assert(inputs);
            declare_uniforms(*inputs);
            declare_attributes(*inputs);

            auto outputs = node.type;
            app_assert(outputs);
            declare_outputs(*outputs);

            write("void main() {\n");
            indent([&]{
                assign_attributes(*inputs);
                invoke_gpuc_main(*inputs);

                output_count = 0;
                assign_outputs(*outputs);
            });
            write("}\n");
        }

        //----------------------------------------------------------------------

        app_gpuc_writer_write(TRANSLATION_UNIT) {
            write("/*GLSL*/\n");
            write("#version 330\n\n");
            write(node.children());

            if (main) write_glsl_main(*main);
        }

        app_gpuc_writer_write(UNIFORM_DEFINITION) {
            write(node.type_name()," ",node.lexeme);
        }

        app_gpuc_writer_write(FUNCTION_DEFINITION) {
            auto& function_name = *node.lexeme;
            if (function_name == lexeme("vsmain",IDENTIFIER)) {
                if (shader_stage == gpuc::shader_stage::VERTEX) {
                    app_assert(main == nullptr);
                    main = &node;
                    writer::write_FUNCTION_DEFINITION(node);
                }
                return;
            }
            if (function_name == lexeme("fsmain",IDENTIFIER)) {
                if (shader_stage == gpuc::shader_stage::FRAGMENT) {
                    app_assert(main == nullptr);
                    main = &node;
                    writer::write_FUNCTION_DEFINITION(node);
                }
                return;
            }
            writer::write_FUNCTION_DEFINITION(node);
        }

    };

} // namespace app::gpuc