const vec3   planenormal   = vec3 (0.0, 0.0, 1.0);
const vec3   planebinormal = vec3 (0.0, 1.0, 0.0);
const vec3   planetangent  = vec3 (1.0, 0.0, 0.0);
varying vec3 lightDir;    // interpolated surface local coordinate light direction
varying vec3 viewDir;     // interpolated surface local coordinate view direction

void main(void)
{
    // Do standard vertex stuff

    gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;

    // Compute the binormal
    vec3 n = normalize(gl_NormalMatrix * planenormal);
    vec3 t = normalize(gl_NormalMatrix * planetangent);
    vec3 b = cross(n, t);

    // Transform light position into surface local coordinates
    vec3 LightPosition = gl_LightSource[0].position.xyz;

    vec3 v;
    v.x = dot(LightPosition, t);
    v.y = dot(LightPosition, b);
    v.z = dot(LightPosition, n);

    lightDir = normalize(v);

    vec3 pos = vec3 (gl_ModelViewMatrix * gl_Vertex);
    v.x = dot(pos, t);
    v.y = dot(pos, b);
    v.z = dot(pos, n);

    viewDir = normalize(v);
}
