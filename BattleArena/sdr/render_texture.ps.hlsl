Texture2D color_tex : register(t0);

SamplerState texture_sampler : register(s0);

struct VOut {
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
};

float4 main(VOut input) : SV_TARGET
{
	float4 color = color_tex.Sample(texture_sampler, input.texcoord);
	return color;
}
