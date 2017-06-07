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

Texture2D diffuse_tex : register(t0);
SamplerState texture_sampler_linear_wrap : register(s0);

float4 main(VOut input) : SV_TARGET
{
	float4 texel = diffuse_tex.Sample(texture_sampler_linear_wrap, input.texcoord.xy);

	float4 final_color = diffuse * texel;
	final_color.a = diffuse.a;

	return final_color;
}
