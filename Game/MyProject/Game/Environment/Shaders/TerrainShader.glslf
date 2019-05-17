#version 150

in vec2 uv;
in vec3 normal;
in float height;

out vec4 fragColor;


void main()
{
    const vec3 lightPos = vec3(-10.0, 10.3, 3.0);
    
    float diff = clamp(dot(normal, normalize(-lightPos)), 0.0, 1.0);
    vec3 baseColor = vec3(0.7 * height, 0.2, 0.1);

    fragColor = vec4(baseColor * diff + vec3(0.1, 0.1, 0.1), 1.0);
}
