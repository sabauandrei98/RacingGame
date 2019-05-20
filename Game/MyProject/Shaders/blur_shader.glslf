#version 330

in vec2 uv;

out vec4 fragColor;

uniform sampler2D PREVIOUS_POSITION;
uniform sampler2D CURRENT_POSITION;
uniform sampler2D COLOR;

float sampleNum = 10;

void main() {
 	vec2 texCoord = uv;

 	vec4 currentPosition = texture(CURRENT_POSITION, texCoord);
 	vec4 prevPosition = texture(PREVIOUS_POSITION, texCoord);

	vec2 velocity = (prevPosition - currentPosition).xy / 500.f;
	vec3 color = texture(COLOR, texCoord).rgb;

	for (int i = 1; i < sampleNum; i++, texCoord += velocity) {
		
		color += texture(COLOR, texCoord).rgb;
	}

	fragColor = vec4(color / sampleNum, 1.f);
 	// fragColor = vec4(velocity, 0.0f, 1.);
}

