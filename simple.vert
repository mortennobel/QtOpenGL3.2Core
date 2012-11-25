#version 150

in vec3 vertex;
in vec3 color;
out vec3 vColor;

void main( void )
{
    gl_Position = vec4(vertex, 1.0);
    vColor = color;
}
