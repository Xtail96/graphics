//uniform sampler2D qt_Texture0;
//varying highp vec4 qt_TexCoord0;
uniform sampler2D u_texture;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;



void main(void)
{
    gl_FragColor = texture2D(u_texture, v_texcoord);


    //vec4 mv_matrix =
    //gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
    //gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}
