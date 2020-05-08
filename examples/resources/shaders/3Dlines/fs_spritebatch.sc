$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = mul(v_color0, texture2D(s_texColor, v_texcoord0).xxxx);
	//gl_FragColor = color;
	gl_FragColor = texture2D(s_texColor, v_texcoord0);
}
