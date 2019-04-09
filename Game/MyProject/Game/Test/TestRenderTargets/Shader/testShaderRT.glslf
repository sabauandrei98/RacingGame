#version 150

in vec3 color;
in vec2 uvCoord;

uniform sampler2D Texture;
//uniform vec4 MyColor;

out vec4 fragColor;

const float offset = 1.0 / 300.0;

void main()
{
    //fragColor=vec4(color,1.);

    //fragColor=vec4(1.-vec3(texture(Texture,uvCoord)*MyColor),1.);

    //vec4 FragColor = texture(Texture, uvCoord);

    //float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;

    //float average=0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;

    // fragColor = vec4(average, average, average, 1.0);


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
    /*
    float kernel[9] = float[](-1, -1, -1,
                              -1,  9, -1,
                              -1, -1, -1);
    */

    /*
    //-----blur
    float kernel[9] = float[](  1.0 / 20, 3.0 / 16, 1.0 / 20,
                                3.0 / 20, 4.0 / 16, 3.0 / 20,
                                1.0 / 20, 3.0 / 16, 1.0 / 20);
    */
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
