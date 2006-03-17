uniform sampler2D shadowMap;
uniform sampler2D oldFactorMap;
uniform float intensity;
uniform int firstRun;
uniform float counter;
varying vec4 projCoord;
varying vec4 texPos;

const mat4 bias = {0.5,0.0,0.0,0.0, 0.0,0.5,0.0,0.0, 0.0,0.0,0.5,0.0, 0.5,0.5,0.5,1.0};

float dither_Filter(vec4 projectiveBiased, float filterWidth, float factor)
{
	projectiveBiased.x -= filterWidth;
	projectiveBiased.y -= filterWidth;

      float blockerCount = 0.0;

	float random1;
	float random2;

	float FC0;
	float FC1;

	FC0 = gl_FragCoord[0];
	FC1 = gl_FragCoord[1];

	random1 = FC0 * factor;
	random2 = FC1 * factor;

	random1 -= floor(random1);
	random2 -= floor(random2);

	projectiveBiased.x += (filterWidth*random1);
	projectiveBiased.y += (filterWidth*random2);

      blockerCount = shadow2D(shadowMap, projectiveBiased.xyz).x;
	blockerCount *= intensity;
      
	return blockerCount;
}

void main(void)
{
	vec4 projectiveBiased = vec4((projCoord.xyz / projCoord.q),1.0);

	float shadowed;

	shadowed = dither_Filter(projectiveBiased, (1.0/1024.0)*3.0, 0.25);

	if(!firstRun) shadowed += texture2DProj(oldFactorMap,texPos.xyw).x;

	gl_FragColor = vec4(shadowed,0.0,0.0,1.0);
}




