#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 MV_inv;

attribute vec4 aPos;


void main()
{
    gl_Position=(P*MV*aPos);
}