uniform sampler2D colorMap;
uniform sampler2D shadowFactorMap;
varying vec4 projCoord;

const mat4 bias = {0.5,0.0,0.0,0.0, 0.0,0.5,0.0,0.0, 0.0,0.0,0.5,0.0, 0.5,0.5,0.5,1.0};

void main(void)
{
	vec4 colorProj = bias * projCoord;

	vec3 color = texture2DProj(colorMap, colorProj.xyw).xyz;
	
	color *= texture2DProj(shadowFactorMap, colorProj.xyw).x;
	gl_FragColor = vec4(color, 1.0);
}
