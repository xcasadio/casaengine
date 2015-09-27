
uniform float4x4 ModelViewProj : WORLDVIEWPROJECTION;

struct VS_INPUT
{
	float3 Position : POSITION;
	float4 Diffuse  : COLOR;
};
struct VS_OUTPUT
{
	float4 Position : POSITION;
	float4 Diffuse  : COLOR;
};


//
VS_OUTPUT VS(VS_INPUT VertIn)
{
	VS_OUTPUT VertOut = (VS_OUTPUT)0;
	VertOut.Position = mul( float4(VertIn.Position, 1.0), ModelViewProj);
	VertOut.Diffuse  = VertIn.Diffuse;

	return VertOut;
}

//
float4 PS(VS_OUTPUT ps_in) : COLOR
{
	return ps_in.Diffuse;
}

technique Simple
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}
