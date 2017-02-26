struct PInput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 t_lightDirection : LIGHT_DIRECTION;
	float3 t_viewDirection : VIEW_DIRECTION;
};

struct POutput
{
	float4 color : SV_TARGET;
};

cbuffer uniforms
{
	float4x4 MVP;
	float4x4 ITMV;
	float4x4 MV;
	float4x4 V;
	float4x4 textureMatrix;
	float4 diffuse;
	float4 specular;
};

Texture2D diffuse_tex : register(t0);
Texture2D specular_tex : register(t1);
Texture2D normalmap_tex : register(t2);

SamplerState texture_sampler : register(s0);

POutput main(PInput input)
{
	POutput output;

	//Sample the normalmap to get the normal value (already in tangent space)
	float4 normalmapTexel = normalmap_tex.Sample(texture_sampler, input.texcoord);
	
	//Move the texel value from [0,1] to [-1,1] so it can be used as an actual normal.
	float3 n = normalize(normalmapTexel.xyz * 2.0 - 1.0);

	//Normalize the light direction.
	float3 l = normalize(input.t_lightDirection);
	
	//Normalize the view direction.
	float3 v = normalize(input.t_viewDirection);
	
	//Compute the half vector
	float3 h = normalize(v + l);

	//Compute the required dot products.
	float n_dot_l = max(dot(n, l), 0.0);
	float n_dot_h = max(dot(n, h), 0.0);

	//Lighting calculation.
	float4 lightContribution = lit(n_dot_l, n_dot_h, specular.a);

	//Sample the diffuse texture.
	float4 diffuseTexel = diffuse_tex.Sample(texture_sampler, input.texcoord);
	
	//Sample the specular texture.
	float4 specularTexel = specular_tex.Sample(texture_sampler, input.texcoord);

	//Compute the final output color and return it.
	float4 finalColor = diffuse * diffuseTexel * lightContribution.y
		+ float4(specular.rgb, 1.0) * specularTexel * lightContribution.z;
	
	output.color = finalColor;

	return output;
}
