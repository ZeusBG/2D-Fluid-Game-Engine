//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
Texture2D shaderTexture;
SamplerState SampleType;

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 PS( PS_INPUT input ) : SV_Target
{
	float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.tex);
    return textureColor;
}
