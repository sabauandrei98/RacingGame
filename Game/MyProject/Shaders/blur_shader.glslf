#version 330

in vec2 uv;

out vec4 fragColor;

uniform sampler2D PREVIOUS_POSITION;
uniform sampler2D CURRENT_POSITION;
uniform sampler2D COLOR;
uniform sampler2D NORMAL;

uniform float EXPOSURE;
uniform float GAMMA;
uniform float INTENSITY;
uniform float SIZE;

float sampleNum = 5;

vec3 lightPos = vec3(0.0f, 25.0f, 0.0f);

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

	// lighting
	vec3 lighting = color * 0.1f;
	vec3 pos = currentPosition.xyz;
	vec3 normal = texture(NORMAL, uv).xyz;
	vec3 lightDir = normalize(lightPos - pos);
	vec3 diffuse = max(dot(normal, lightDir), 0.0) * color;
	color = diffuse + lighting;

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

