#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vertUV;
uniform float iTime;
uniform vec2 iResolution;
uniform vec3 hillColor;
uniform vec3 sunColor;
uniform vec3 colorNight;
uniform vec3 colorDay;
out vec2 uv;
void main(){
	uv = vertUV;
	gl_Position = vec4(vPos,1.0);
}
