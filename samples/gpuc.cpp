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
    exit $STATUS;

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include "../gpuc/writers/glsl_writer.hpp"
#include "echo.hpp"

//------------------------------------------------------------------------------

static
std::string readfile(const char* path) {
    std::string s;
    std::ifstream f(path);
    if (f.is_open()) {
        f.seekg(0, std::ios::end);
        const size_t size = f.tellg();
        s.resize(size);
        f.seekg(0, std::ios::beg);
        f.read(&s[0], size);
    }
    return s;
}

//------------------------------------------------------------------------------

const char* const source = R"(
    struct camera {
        float4x4 mvp;
        float4x4 mvn;
    };

    struct vertex {
        float3 position;
        float3 normal;
        float4 color;
        float2 texcoord;
    };

    struct fragment {
        float4 position;
        float4 normal;
        float4 color;
        float2 texcoord;
    };

    fragment vsmain(
        vertex v,
        uniform camera cam)
    {
        fragment f;
        f.position = cam.mvp * float4(v.position,1);
        f.normal   = cam.mvn * float4(v.normal,0);
        f.color    = v.color;
        f.texcoord = v.texcoord;
        return f;
    }

    struct sample {
        float4 color;
    };

    sample fsmain(
        fragment f,
        uniform texture_2d diffuse)
    {
        float4 texel;// = diffuse[f.texcoord];
        sample s;
        s.color = (f.color + texel + f.normal) / float4(3.f);
        return s;
    }
)";

int main(int argc, const char* argv[]) {
    using namespace app::gpuc;
    tree ast{source};
    std::cout << "\n----------------\n";
    std::cout << glsl_writer(ast,shader_stage::VERTEX);
    std::cout << "\n----------------\n";
    std::cout << glsl_writer(ast,shader_stage::FRAGMENT);
    std::cout << "\n----------------\n";
    std::cout << ast.root();
    size_t errors = 0;
    for (auto& d : ast.diagnostics()) {
        errors += d.level == diagnostic_level::ERROR;
        std::cout << d << "\n";
    }
    if (errors) return 1;
    // echo(strlen(source));
    // echo(ast.lexemes.size());
    // for (auto x : ast.lexemes) {
    //     std::cout << std::setw(16) << x.token << ": '" << x << "'\n";
    // }
    return 0;
}
