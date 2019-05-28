#version 330

in vec4 col;
in vec2 uv;

out vec4 fragColor;

uniform sampler2D TEXTURE;
uniform sampler2D NORMAL;
uniform sampler2D POSITION;

uniform float EXPOSURE;
uniform float GAMMA;
uniform float INTENSITY;
uniform float SIZE;

vec3 lightPos = vec3(0.0f, 25.0f, 0.0f);

void main() {
	vec3 color = texture(TEXTURE, uv).rgb;

	// lighting
	vec3 lighting = color * 0.1f;
	vec3 pos = texture(POSITION, uv).rgb;
	vec3 normal = texture(NORMAL, uv).xyz;
	vec3 lightDir = normalize(lightPos - pos);
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * color;
	
    fragColor = vec4(diffuse + lighting, 1.0f);
}