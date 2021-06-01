#version 120

uniform vec3 kd;

void main(){
    gl_FragColor = vec4(kd, 1.0);
}