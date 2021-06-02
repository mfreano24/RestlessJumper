#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 MV_inv;

attribute vec4 aPos;
attribute vec4 aNor;
attribute vec2 aTex;


void main()
{
    gl_Position=(P*MV*aPos);
}