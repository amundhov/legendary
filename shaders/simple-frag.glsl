/* Fragment shader */

uniform sampler2D image;


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


void main()
{
    /*gl_FragColor[0] = gl_FragCoord[0] / 400.0;
    gl_FragColor[1] = gl_FragCoord[1] / 400.0;
    gl_FragColor[2] = 1.0;*/
    vec4 color = texture2D(image, gl_TexCoord[0].st);
//    color.xyz = color.xyz * (sin(gl_FragCoord.y) + 2);
    color.xyz = color.xyz * rand(gl_FragCoord.xy);
    gl_FragColor = color;
}
