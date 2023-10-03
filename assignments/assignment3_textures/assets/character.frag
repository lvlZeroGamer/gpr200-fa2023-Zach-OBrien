#version 450
out vec4 FragColor;
in vec2 UV;

uniform float iTime;
uniform sampler2D _CharacterTexture;

void main(){
	FragColor = texture(_CharacterTexture,UV);
}