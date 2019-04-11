#version 150

const float offset = 1.0 / 512.0;

in vec2 uvCoord;

uniform sampler2D Texture;

out vec4 fragColor;

void main()
{
    //------kernel effects------
    vec2 offsets[9] = vec2[](   vec2(-offset,  offset), // top-left
                                vec2( 0.    ,  offset), // top-center
                                vec2( offset,  offset), // top-right
                                vec2(-offset,  0.    ), // center-left
                                vec2( 0.    ,  0.    ), // center-center
                                vec2( offset,  0.    ), // center-right
                                vec2(-offset, -offset), // bottom-left
                                vec2( 0.    , -offset), // bottom-center
                                vec2( offset, -offset)  // bottom-right
                            );

    //----edge detection
    float kernel[9]=float[](    1.0,  1.0, 1.0,
                                1.0, -8.0, 1.0,
                                1.0,  1.0, 1.0);
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
            sampleTex[i] = vec3(texture(Texture, uvCoord + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    fragColor = vec4(col, 1.0);
}
