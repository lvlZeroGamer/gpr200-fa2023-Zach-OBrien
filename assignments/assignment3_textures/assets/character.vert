#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
out vec2 UV;

uniform float iTime;
uniform sampler2D _CharacterTexture;

void main(){
	UV = vUV;
	vec3 pos = vPos / 2.0;
	pos.x += sin(iTime);
	gl_Position = vec4(pos,1.0);
}