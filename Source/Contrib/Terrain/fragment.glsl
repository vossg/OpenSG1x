uniform sampler2D texSampler;
uniform sampler2D nmapSampler;
uniform float offsetS;
uniform float offsetT;
uniform float scaleS;
uniform float scaleT;
uniform float specularExponent;
uniform float diffuseFactor;
uniform float specularFactor;
uniform vec3  basecolor;
varying vec3 lightDir;       // interpolated surface local coordinate light direction
varying vec3 viewDir;        // interpolated surface local coordinate view direction

void main (void)
{
    vec3 norm;
    vec3 r;
    vec3 color;
    vec3 texcolor;
    float intensity;
    float spec;
    float d;
    // Fetch normal from normal map
    vec2 nmapST = vec2 (gl_TexCoord[0])*vec2(scaleS, scaleT) + vec2(offsetS, offsetT);
    norm = vec3(texture2D(nmapSampler, nmapST));
    norm = (norm - 0.5) * 2.0;
    // Compute diffuse reflection
    d = dot(lightDir, norm);
    intensity = max(d, 0.0) * diffuseFactor;
    // Compute specular reflection
    d = 2.0 * d;
    r = d * norm;
    r = lightDir - r;
    spec = pow(max(dot(r, viewDir), 0.0), specularExponent) * specularFactor;
    intensity += min (spec, 1.0);
    // mix texture color and lighting color
    texcolor = vec3(texture2D(texSampler, vec2 (gl_TexCoord[0])));
    color = clamp(texcolor * basecolor * intensity, 0.0, 1.0);
    // Write out final fragment color
    gl_FragColor = vec4 (color, 1.0);

}
