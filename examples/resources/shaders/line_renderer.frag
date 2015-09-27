#ifdef GLES2

varying lowp vec4 vs_color;

lowp vec4 color;

#else

in lowp vec4 vs_color;

layout(location = 0) out lowp vec4 color;

#endif


void main()
{
	color = vs_color;

#ifdef GLES2
	gl_FragColor = color;
#endif
}
