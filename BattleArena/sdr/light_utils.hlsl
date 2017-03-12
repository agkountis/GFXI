#ifndef LIGHT_UTILS_HLSL_
#define LIGHT_UTILS_HLSL_

struct DirectionalLight
{
	float4x4 ambientIntensity;
	float4x4 diffuseIntensity;
	float4x4 specularIntensity;
	bool active;
	float3 direction;
};

struct PointLight
{
	float4x4 ambientIntensity;
	float4x4 diffuseIntensity;
	float4x4 specularIntensity;
	bool active;
	float3 position;
};

struct Spotlight
{
	float4x4 ambientIntensity;
	float4x4 diffuseIntensity;
	float4x4 specularIntensity;
	bool active;
	float3 position;
	float3 direction;
};

#define MAX_DIRECTIONAL_LIGHTS 5
#define MAX_POINT_LIGHTS 5
#define MAX_SPOTLIGHTS 5

void AccumulateDirectionalLights(StructuredBuffer<DirectionalLight> lights,
								 int lightCount,
								 float3 normal,
							     float3 v_viewDirection,
								 inout float4 ambientLight,
								 inout float4 diffuseLight,
								 inout float4 specularLight)
{
	for (int i = 0; i < lightCount; i++)
	{

	}
}

void PopulateDirectionalLightDirections(StructuredBuffer<DirectionalLight> lights,
									   int lightCount,
									   float4x4 viewMatrix,
									   float3x3 TBN,
	                                   inout float3 directions[MAX_DIRECTIONAL_LIGHTS])
{
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
	{
		if (i < lightCount)
		{
			directions[i] = mul(mul(lights[i].direction, (float3x3)viewMatrix), TBN);
		}
		else
		{
			directions[i] = float3(0.0, 0.0, 0.0);
		}
	}
}

void CalculatePointLightDirections(StructuredBuffer<PointLight> lights,
								   int lightCount,
								   float3 v_Vertex,
								   float4x4 viewMatrix,
								   float3x3 TBN,
								   inout float3 directions[MAX_POINT_LIGHTS])
{
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if (i < lightCount)
		{
			directions[i] = mul(mul(float4(lights[i].position, 1.0), viewMatrix).xyz - v_Vertex, TBN);
		}
		else
		{
			directions[i] = float3(0.0, 0.0, 0.0);
		}
	}
}

void PopulateSpotlightDirections(StructuredBuffer<Spotlight> lights,
								 int lightCount,
								 inout float3 directions[MAX_SPOTLIGHTS])
{
	for (int i = 0; i < MAX_SPOTLIGHTS; i++)
	{
		directions[i] = float3(0.0, 0.0, 0.0);
	}
}

#endif //LIGHT_UTILS_HLSL_
