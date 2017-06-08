struct VIn 
{
	float4 position : POSITION;
	float4 texcoord : TEXCOORD0;
};


struct VOut 
{
	float4 position : SV_POSITION;
	float4 texcoord : TEXCOORD0;
};

cbuffer uniforms 
{
	float4x4 MVP;
	float4 diffuse;
};

VOut main(VIn input)
{
	VOut output;
	output.position = mul(input.position, MVP);
	output.texcoord = input.texcoord;

	return output;
}
