//#version 150
//
//in vec2 uv;
//in vec4 pos;
//in vec3 normal;
//in float height;
//
//out vec4 fragColor;
//
//
//void main()
//{
//    const vec3 lightPos = vec3(-10.0, 10.3, 3.0);
//
//    vec3 ld = normalize(lightPos - pos.xyz);
//    float diff = max(dot(normal, ld), 0.0);
//
//    vec3 baseColor = vec3(0.3, 0.72, 0.1);
//
//    fragColor = vec4(baseColor * diff + baseColor * vec3(0.1, 0.1, 0.1), 1.0);
//}

#version 330

layout(location = 0) out vec4 position;
layout(location = 1) out vec4 normal;
layout(location = 2) out vec4 color;

in vec3 pos;
in vec3 norm;
in vec2 uv;

uniform sampler2D TEXTURE;

void main()
{
    position = vec4(pos, 1.f);
    normal = vec4(normalize(norm), 1.f);
    color = vec4(0.3, 0.72, 0.1, 1.);
}
