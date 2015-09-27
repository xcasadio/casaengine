
uniform float4x4 ModelViewProj : WORLDVIEWPROJECTION;
//uniform sampler2D sampler0 : TEXTURE0;

uniform texture Texture0;
uniform sampler2D Texture0Sampler = sampler_state
{
	Texture = <Texture0>;
};
uniform float2 TexRepeat;

struct VS_INPUT
{
	float3 Position : POSITION;
	float3 Normal   : NORMAL;
	float2 Tex0     : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 Position : POSITION;
	float2 Tex0     : TEXCOORD0;
};


//
VS_OUTPUT VS(VS_INPUT VertIn)
{
	VS_OUTPUT VertOut = (VS_OUTPUT)0;
	VertOut.Position = mul( float4(VertIn.Position, 1.0), ModelViewProj);
	VertOut.Tex0     = VertIn.Tex0;

	return VertOut;
}

//
float4 PS(VS_OUTPUT ps_in) : COLOR
{
	return tex2D(Texture0Sampler, ps_in.Tex0 * TexRepeat);
}

technique Simple
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}
