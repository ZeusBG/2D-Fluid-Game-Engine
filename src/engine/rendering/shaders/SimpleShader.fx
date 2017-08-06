//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

struct VS_INPUT
{
    float4 Pos : POSITION;
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
};

PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(input.Pos, WorldMat);
	output.Pos = mul(output.Pos, ViewMat);
	output.Pos = mul(output.Pos, ProjMat);
	
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
    return float4( 1.0f, 1.0f, 0.0f, 1.0f );    // Yellow, with Alpha = 1
}
