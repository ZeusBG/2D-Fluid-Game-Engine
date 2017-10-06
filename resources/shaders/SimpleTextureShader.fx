//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float4 Pos : POSITION;
	float2 tex : TEXCOORD0;
};

cbuffer World
{
	matrix WorldMat;
	matrix ViewMat;
	matrix ProjMat;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(input.Pos, WorldMat);
	output.Pos = mul(output.Pos, ViewMat);
	output.Pos = mul(output.Pos, ProjMat);
	output.tex = input.tex;
    return output;
}
