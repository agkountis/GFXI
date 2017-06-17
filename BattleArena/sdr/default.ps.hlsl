#include "light_utils.hlsl"

struct PInput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 t_viewDirection : VIEW_DIRECTION;
	float3 t_directionalLightDirections[MAX_DIRECTIONAL_LIGHTS] : DIR_LIGHT_DIRECTIONS;
	float3 t_pointLightDirections[MAX_POINT_LIGHTS] : POINT_LIGHT_DIRECTIONS;
	float3 t_spotlightDirections[MAX_SPOTLIGHTS] : SPOTLIGHT_DIRECTIONS;
};

struct POutput
{
	float4 color : SV_TARGET;
};

cbuffer uniforms : register(c0)
{
	float4x4 MVP;
	float4x4 ITMV;
	float4x4 MV;
	float4x4 V;
	float4x4 textureMatrix;
	float4 diffuse;
	float4 specular;
	int pointLightCount;
	int directionalLightCount;
	int spotlightCount;
	float pad;
};

SamplerState textureSamplerLinear : register(s0);

Texture2D diffuse_tex : register(t0);
Texture2D specular_tex : register(t1);
Texture2D normalmap_tex : register(t2);

StructuredBuffer<DirectionalLight> directionalLights : register(t3);
StructuredBuffer<PointLight> pointLights : register(t4);
StructuredBuffer<Spotlight> spotlights : register(t5);

POutput main(PInput input)
{
	POutput output;

	//Sample the normalmap to get the normal value (already in tangent space)
	float4 normalmapTexel = normalmap_tex.Sample(textureSamplerLinear, input.texcoord);
	
	//Move the texel value from [0,1] to [-1,1] so it can be used as an actual normal.
	float3 n = normalize(normalmapTexel.xyz * 2.0 - 1.0);
	
	//Normalize the view direction.
	float3 v = normalize(input.t_viewDirection);

	float4 ambientLight = float4(0.0, 0.0, 0.0, 0.0);
	float4 diffuseLight = float4(0.0, 0.0, 0.0, 0.0);
	float4 specularLight = float4(0.0, 0.0, 0.0, 0.0);

	AccumulateDirectionalLights(directionalLights,
								directionalLightCount,
								n,
								v,
								specular.a,
								input.t_directionalLightDirections,
								ambientLight,
								diffuseLight,
								specularLight);

	//Sample the diffuse texture.
	float4 diffuseTexel = diffuse_tex.Sample(textureSamplerLinear, input.texcoord);
	
	//Sample the specular texture.
	float4 specularTexel = specular_tex.Sample(textureSamplerLinear, input.texcoord);

	//Compute the final output color and return it.
	float4 finalColor = ambientLight +
					    diffuseTexel * diffuse * diffuseLight +
						specularTexel * float4(specular.xyz, 1.0) * specularLight;

	finalColor.a = diffuse.a;
	
	output.color = finalColor*pad;

	return output;
}
