uniform highp mat4 ModelViewProj;

#ifdef GLES2

attribute highp vec3 vPositionIn;
attribute mediump vec2 vTextCoordIn;
attribute lowp vec4 vColorIn;

varying mediump vec2 texCoord;
varying mediump vec4 colorOut;

#else

layout(location = 0) in vec3 vPositionIn;
layout(location = 1) in vec2 vTextCoordIn;
layout(location = 2) in vec4 vColorIn;

out vec2 texCoord;
out vec4 colorOut;

#endif

void main()
{
	gl_Position = ModelViewProj * vec4(vPositionIn, 1.0);
	texCoord = vTextCoordIn;
	colorOut = vColorIn;
}
