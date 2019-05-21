#version 330

in vec2 uv;

out vec4 fragColor;

uniform sampler2D PREVIOUS_POSITION;
uniform sampler2D CURRENT_POSITION;
uniform sampler2D COLOR;

uniform float EXPOSURE;
uniform float GAMMA;
uniform float INTENSITY;
uniform float SIZE;

float sampleNum = 10;

void main() {
 	vec2 texCoord = uv;

 	vec4 currentPosition = texture(CURRENT_POSITION, texCoord);
 	vec4 prevPosition = texture(PREVIOUS_POSITION, texCoord);

	vec2 velocity = (prevPosition - currentPosition).xy / 400.f;
	vec3 color = texture(COLOR, texCoord).rgb;

	for (int i = 1; i < sampleNum; i++, texCoord += velocity) {
		color += texture(COLOR, texCoord).rgb;
	}

	color /= sampleNum;

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

