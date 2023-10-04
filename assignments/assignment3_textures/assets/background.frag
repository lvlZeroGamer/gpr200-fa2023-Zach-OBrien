#version 450
out vec4 FragColor;
in vec2 UV;

uniform float iTime;
uniform sampler2D _BrickTexture;
uniform sampler2D _NoiseTexture;

void main(){
	float noise = texture(_NoiseTexture, UV).r;
	vec2 uv = UV + noise * 0.1f;
	uv += iTime/4;
	FragColor = texture(_BrickTexture,uv);
}