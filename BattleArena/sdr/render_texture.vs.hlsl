struct VOut 
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

VOut main(uint vI : SV_VERTEXID)
{
	VOut output;

	float2 texcoord = float2(vI & 1,vI >> 1);

	output.position = float4((texcoord.x - 0.5f) * 2, -(texcoord.y - 0.5f) * 2, 0, 1);
	output.texcoord = texcoord;

	return output;
}
