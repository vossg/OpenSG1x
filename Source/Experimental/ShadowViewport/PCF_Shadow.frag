uniform sampler2D shadowMap;
uniform sampler2D oldFactorMap;
uniform float intensity;
uniform int firstRun;
uniform float shadowRange;
varying vec4 projCoord;
varying vec4 texPos;

float PCF_Filter(vec4 projectiveBiased, float filterWidth, float samples)
{
	float stepSize = 2.0 * filterWidth / samples;

	projectiveBiased.x -= filterWidth;
	projectiveBiased.y -= filterWidth;

      float blockerCount = 0.0;

	for (float i=0.0; i<samples; i++) 
	{
            for (float j=0.0; j<samples; j++) 
		{
			projectiveBiased.x += (j*stepSize);
			projectiveBiased.y += (i*stepSize);

			blockerCount += shadow2D(shadowMap, projectiveBiased.xyz).x ;

			projectiveBiased.x -= (j*stepSize);
			projectiveBiased.y -= (i*stepSize);
             }
	}

	float result = ((blockerCount)/(samples*samples)) * intensity;
	return result;
}

void main(void)
{
	vec4 projectiveBiased = vec4((projCoord.xyz / projCoord.q),1.0);

	float shadowed;
	
	shadowed = PCF_Filter(projectiveBiased, shadowRange, 4.0);

	if(!firstRun) shadowed += texture2DProj(oldFactorMap,texPos.xyw).x;

	gl_FragColor = vec4(shadowed,0.0,0.0,1.0);
}




