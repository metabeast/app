#line 1 "sample.gpuc"

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

struct fragment {
    float4 position;
    float4 normal;
    float4 color;
    float2 texcoord;
};

uniform transforms T;

fragment vsmain(uniform vertex v);

fragment vsmain(vertex v) {
    fragment f;
    int i = (1 + 2) * 3 / 4;
    i += 1 + 2 * 3 / 4;
    i = ++(++i);
    i = i++;
    f.position = T.mvp * float4(v.position,1);
    f.normal   = T.mvn * float4(v.normal,0);
    f.color    = v.color;
    f.texcoord = v.texcoord;
    return f;
}

struct targets {
    float4 color;
};

targets fsmain(fragment f) {
    targets t;
    t.color = f.color;
    return t;
    /*
    return {
        .color = f.color,
    };
    */
}