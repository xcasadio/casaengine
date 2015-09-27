
uniform float4x4 ModelViewProj : WORLDVIEWPROJECTION;
//uniform sampler2D sampler0 : TEXTURE0;

uniform texture Texture0;
uniform sampler2D Texture0Sampler = sampler_state
{
	Texture = <Texture0>;
};

struct VS_INPUT
{
	float3 Position : POSITION;
	float2 Tex0     : TEXCOORD0;
	float4 Diffuse  : COLOR;
};
struct VS_OUTPUT
{
	float4 Position : POSITION;
	float2 Tex0     : TEXCOORD0;
	float4 Diffuse  : COLOR;
};


//
VS_OUTPUT VS(VS_INPUT VertIn)
{
	VS_OUTPUT VertOut = (VS_OUTPUT)0;
	VertOut.Position = mul( float4(VertIn.Position, 1.0), ModelViewProj);
	VertOut.Tex0     = VertIn.Tex0;
	VertOut.Diffuse  = VertIn.Diffuse;

	return VertOut;
}

//
float4 PS(VS_OUTPUT ps_in) : COLOR
{
	return tex2D(Texture0Sampler, ps_in.Tex0) * ps_in.Diffuse;
}

technique Simple
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}
