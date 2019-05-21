#version 330

in vec4 col;
in vec2 uv;

out vec4 fragColor;

uniform sampler2D TEXTURE;

uniform float EXPOSURE;
uniform float GAMMA;
uniform float INTENSITY;
uniform float SIZE;

void main() {
	vec3 color = texture(TEXTURE, uv).rgb;

	// vignette
    vec2 flipped_uv = uv * (1.0f - uv.yx);
    float vignette = flipped_uv.x * flipped_uv.y * INTENSITY;
    vignette = pow(vignette, SIZE);
    color = min(color, vec3(vignette));

	// tone mapping
	vec3 mapped = vec3(1.0f) - exp(-color * EXPOSURE);

	// gamma correction
	mapped = pow(mapped, vec3(1.0f / GAMMA));

    fragColor = vec4(mapped, 1.0f);
}