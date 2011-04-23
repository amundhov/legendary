/* Fragment shader */

uniform sampler2D image;

void main()
{
    /*gl_FragColor[0] = gl_FragCoord[0] / 400.0;
    gl_FragColor[1] = gl_FragCoord[1] / 400.0;
    gl_FragColor[2] = 1.0;*/
    vec4 color = texture2D(image, gl_texCoord[0].st);
}

