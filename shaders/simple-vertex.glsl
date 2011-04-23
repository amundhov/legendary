/* Vertex shader */
uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;
 
void main(void)
{
    vec4 v = vec4(gl_Vertex);
    gl_Position = gl_ModelViewProjectionMatrix * v;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
