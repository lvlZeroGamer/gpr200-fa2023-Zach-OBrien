#version 450
out vec4 FragColor;

in Surface{
	vec2 UV;
	vec3 WorldPosition; //Per-fragment interpolated world position
	vec3 WorldNormal; //Per-fragment interpolated world normal
}fs_in;

struct Light
{
	vec3 position;
	vec3 color;
};
uniform Light _Light;


uniform sampler2D _Texture;

void main(){
	vec3 normal = normalize(fs_in.WorldNormal);
	//TODO: Lighting calculations using corrected normal
	vec3 w = normalize(_Light.position - fs_in.WorldPosition);
	vec3 I = _Light.color * max(dot(normal, w),0);
	vec3 C = texture(_Texture,fs_in.UV).rgb;
	C = C * I;
	FragColor = vec4(C, 1);
}