varying vec4 projCoord;

void main(void)
{
  projCoord = gl_Vertex;
  gl_Position = ftransform();
}
