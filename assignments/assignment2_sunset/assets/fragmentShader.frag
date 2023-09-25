#version 450
out vec4 FragColor;
uniform vec3 _Color;
uniform float _Brightness;
uniform float iTime;
uniform vec2 iResolution;
uniform vec3 hillColor;
uniform vec3 sunColor;
uniform vec3 colorNight;
uniform vec3 colorDay;
in vec2 uv;
vec2 UV = uv;
float circleSDF(vec2 p, float r){
    return length(p)-r;
}

void main(){
	//FragColor = vec4(_Color * _Brightness,1.0);
	UV.x*=iResolution.x / iResolution.y;
	float t = distance(UV,vec2(0.5));

	vec2 circlePos = vec2(0.5,sin(iTime));
	float circleRadius = 0.2;
	float d = circleSDF(UV - circlePos,circleRadius);

	vec3 colorDay = mix(colorDay, colorNight, UV.y);
	vec3 colorNight = mix(colorNight, vec3(0.0, 0.0, 0.0), UV.y);

	//Get 0-1 T value for hill shape
	//float hills = 1.0 - step(sin(uv.x*6.0) * 0.2 + 0.3,uv.y);
	float wave = sin(uv.x*6.0) * 0.2 + 0.3;
    float hills = 1.0 - step(wave, uv.y);

	//BG gradient
	vec3 color = mix(colorNight,colorDay,sin(iTime));
	
	color = mix(color, sunColor, 1.0 - step(0,d));

	//Blend dark grey hills
	color = mix(color,hillColor,hills);

	FragColor = vec4(color,1.0);
}
