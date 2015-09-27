$input v_normal, v_texcoord0 //in

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor,  0);
uniform vec4 u_texcoord0rep;

void main()
{
	gl_FragColor = texture2D(s_texColor, v_texcoord0 * u_texcoord0rep.xy);
}
