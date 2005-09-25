
uniform sampler2D textureUnit;

// input variables from the vertex program.
varying vec3 vTexcoord;
varying vec3 vColor;

void main(void)
{
    
    gl_FragColor = gl_Color * texture2D(textureUnit, gl_TexCoord[0].st);
}

