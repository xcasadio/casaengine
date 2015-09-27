uniform mediump mat4 ModelViewProj;

layout(location = 0) in vec3 vPositionIn;
layout(location = 1) in vec3 vNormalIn;
layout(location = 2) in vec2 vTextCoordIn;
layout(location = 3) in lowp vec4 vColorIn;

out lowp vec4 vs_color;
out vec2 texCoord;

//
void main()
{
	gl_Position = ModelViewProj * vec4(vPositionIn, 1.0);
	vs_color = vColorIn;
	texCoord = vTextCoordIn;
}
