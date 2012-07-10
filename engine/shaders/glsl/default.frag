#version 420
 
in vec4 Color;

void main(void)
{
    //gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f); //gl_Color;
    gl_FragColor = Color;
}