in lowp vec4 vs_color;

layout(location = 0) out lowp vec4 color;

void main()
{
	color = vs_color;
}
