struct PInput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

struct POutput
{
	float4 color : SV_TARGET;
};

cbuffer uniforms
{
	float4x4 MVP;
	float4x4 ITMV;
	float4x4 textureMatrix;
	float4 diffuse;
	float4 specular;
};

POutput main(PInput input)
{
	POutput output;

	output.color = diffuse;

	return output;
}
