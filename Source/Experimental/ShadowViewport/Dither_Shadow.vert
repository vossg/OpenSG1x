uniform float shadowBias;
uniform mat4 lightPM;
varying vec4 projCoord;
varying vec4 texPos;

const mat4 bias = {0.5,0.0,0.0,0.0, 0.0,0.5,0.0,0.0, 0.0,0.0,0.5,0.0, 0.5,0.5,0.5,1.0};

void main(void)
{
  vec4 realPos = gl_ModelViewMatrix * gl_Vertex;
  projCoord = lightPM * realPos;
  texPos = gl_ModelViewProjectionMatrix * gl_Vertex;

  //projCoord.z -= shadowBias;
  projCoord = bias * projCoord;
  texPos = bias * texPos;
  gl_Position = ftransform();
}
