#version 420

uniform mat4 projMatrix; 
uniform mat4 modelViewMatrix; 

in vec3 position;
in vec4 color;
in vec3 normal;

out vec4 Color;
 
void main(void)
{
    gl_Position = projMatrix * modelViewMatrix * vec4(position, 1.0f);
    Color = vec4(color.rgb, 1.0f);

    //gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0f);
    //gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(position, 1.0f);
	//gl_Position = projMatrix * viewMatrix * transMatrix * vec4(position, 1.0f);
    //gl_FrontColor = vec4(1.0f, 0.0f, 0.0f, 0.0f); //color;
}