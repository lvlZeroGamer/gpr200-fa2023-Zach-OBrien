#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 uv;
out vec2 fragUV;
void main(){
	fragUV = uv;
	gl_Position = vec4(vPos,1.0);
}
