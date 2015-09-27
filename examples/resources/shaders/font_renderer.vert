uniform highp mat4 ModelViewProj;

#ifdef GLES2

attribute highp vec3 vPositionIn;
attribute mediump vec2 vTextCoordIn;
attribute lowp vec4 vColorIn;

varying lowp vec4 vs_color;
varying mediump vec2 texCoord;

#else

layout(location = 0) in vec3 vPositionIn;
layout(location = 1) in vec2 vTextCoordIn;
layout(location = 2) in vec4 vColorIn;

out vec4 vs_color;
out vec2 texCoord;

#endif


void main()
{
	gl_Position = ModelViewProj * vec4(vPositionIn, 1.0);
	vs_color = vColorIn;
	texCoord = vTextCoordIn;
}
