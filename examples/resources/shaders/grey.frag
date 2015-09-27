uniform mat4 ModelViewProj;
uniform sampler2D Texture0;

in lowp vec4 vs_color;
in vec2 texCoord;

layout(location = 0) out lowp vec4 color;

void main()
{
	vec3 Const = vec3(0.30, 0.59, 0.11);
	
	vec3 Pix = texture(Texture0, texCoord).xyz;
	float c = dot(Const, Pix);
	color = vec4(c, c, c, 1.0);
}
