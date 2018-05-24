uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;

varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffuseMaterialColor = texture2D(u_texture, v_texcoord);
    vec3 eyeVector = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVector = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVector, v_normal));
    float len = length(v_position.xyz - eyePosition.xyz);
    float specularFactor = 50.0;
    float ambientFactor = 0.1;

    vec4 diffuseColor = diffuseMaterialColor * u_lightPower * max(0.0, dot(v_normal, -lightVector)) / (1.0 + 0.25 * len * len);
    resultColor += diffuseColor;

    vec4 ambientColor = ambientFactor * diffuseMaterialColor;
    resultColor += ambientColor;

    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower * pow(max(0.0, dot(reflectLight, -eyeVector)), specularFactor) / (1.0 + 0.25 * len * len);
    resultColor += specularColor;

    gl_FragColor = resultColor;
}
