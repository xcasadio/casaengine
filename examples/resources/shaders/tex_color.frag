uniform sampler2D Texture0;

#ifdef GLES2

varying mediump vec2 texCoord;
varying mediump vec4 colorOut;

lowp vec4 color;

#else

in vec2 texCoord;
in vec4 colorOut;

layout(location = 0) out vec4 color;

#endif


void main()
{
	color = texture(Texture0, texCoord) * colorOut;

#ifdef GLES2
	gl_FragColor = color;
#endif
}
