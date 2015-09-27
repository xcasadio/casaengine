uniform highp mat4 ModelViewProj;

#ifdef GLES2

attribute vec3 vPositionIn;
attribute lowp vec4 vColorIn;

varying lowp vec4 vs_color;

#else

layout(location = 0) in vec3 vPositionIn;
layout(location = 1) in vec4 vColorIn;

out vec4 vs_color;

#endif

void main()
{
	gl_Position = ModelViewProj * vec4(vPositionIn, 1.0);
	vs_color = vColorIn;
}
