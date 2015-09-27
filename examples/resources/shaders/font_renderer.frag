uniform sampler2D Texture0;

#ifdef GLES2

varying lowp vec4 vs_color;
varying mediump vec2 texCoord;

lowp vec4 color;

#else

in lowp vec4 vs_color;
in vec2 texCoord;

layout(location = 0) out lowp vec4 color;

#endif


void main()
{
	color = texture(Texture0, texCoord) * vs_color;

#ifdef GLES2
	gl_FragColor = color;
#endif
}
