uniform sampler2D Texture0;

in vec2 texCoord;
in vec4 spriteColor;

layout(location = 0) out lowp vec4 color;

void main()
{
	color = texture(Texture0, texCoord) * spriteColor;
}
