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
#define MAX_LIGHTS 4
uniform Light _Lights[MAX_LIGHTS];

uniform vec3 cameraPosition;
uniform float ambientK;
uniform float diffuseK;
uniform float specularK;
uniform float shininess;
uniform sampler2D _Texture;

void main(){
	vec3 normal = normalize(fs_in.WorldNormal);
	//TODO: Lighting calculations using corrected normal
	vec3 w = normalize(_Lights[0].position - fs_in.WorldPosition);
	vec3 v = normalize(cameraPosition - fs_in.WorldPosition);
	vec3 h = normalize(w + cameraPosition);
	vec3 ambient = (_Lights[0].color * ambientK);
	vec3 diffuse = ((_Lights[0].color * diffuseK) * max(dot(normal, w),0));
	vec3 specular = ((_Lights[0].color * specularK) * pow(max(dot(h, normal),0), shininess));

	vec3 I = ambient + diffuse + specular;
	vec3 C = texture(_Texture,fs_in.UV).rgb;
	C = C * I;
	FragColor = vec4(C, 1);
}