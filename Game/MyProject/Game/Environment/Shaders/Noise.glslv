uniform mat4 IvModelViewProjectionMatrix;

layout(location = POSITION) in vec3 Position;
layout(location = TEXCOORD0) in vec2 texCoord;

out vec2 uv;

float hash(float n)
{
	return fract(sin(n) * 753.5453123);
}

float snoise(vec3 x)
{
	vec3 p = floor(x);
	vec3 f = fract(x);
	f = f * f * (3.0f - (2.0f * f));

	float n = p.x + p.y * 157.0f + 113.0f * p.z;
	return mix(mix(mix(hash(n + 0.0f), 
					   hash(n + 1.0f),
					   f.x),
				   mix(hash(n + 157.0f), 
					   hash(n + 158.0f), 
					   f.x), 
				   f.y),
			   mix(mix(hash(n + 113.0f), 
			   	       hash(n + 114.0f), 
			   	       f.x),
			   	   mix(hash(n + 270.0f), 
			   	       hash(n + 271.0f), 
			   	       f.x), 
			   	   f.y),
			   f.z);
}

float noise(vec3 position, int octaves, float frequency, float persistence) {
	float total = 0.0f;
	float maxAmplitude = 0.0f;
	float amplitude = 1.0f;
	for (int i = 0; i < octaves; i++) {
		total += snoise(position * frequency) * amplitude;
		frequency *= 2.0f;
		maxAmplitude += amplitude;
		amplitude *= persistence;
	}
	return total / maxAmplitude;
}

void main() {
	float height = noise(Position.xyz, 10, 0.002, 0.3);
	Position.y = height;
	//vertex_pos = Position.xyz;
	gl_Position = IvModelViewProjectionMatrix * vec4(Position,1.0);
}