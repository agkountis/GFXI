struct VInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

struct VOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

cbuffer uniforms
{
	float4x4 MVP;
	float4x4 ITMV;
	float4x4 textureMatrix;
	float4 diffuse;
	float4 specular;

};

VOutput main(VInput input)
{
	VOutput output;

	output.position = mul(float4(input.position, 1.0), MVP);
	output.normal = mul(input.normal, (float3x3)ITMV);
	output.texcoord = mul(float4(input.texcoord, 1.0, 1.0), textureMatrix).xy;

	return output;
}
