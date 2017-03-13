#ifndef LIGHT_UTILS_HLSL_
#define LIGHT_UTILS_HLSL_

struct DirectionalLight
{
	float4 ambientIntensity;
	float4 diffuseIntensity;
	float4 specularIntensity;
	float3 direction;
};

struct PointLight
{
	float4 ambientIntensity;
	float4 diffuseIntensity;
	float4 specularIntensity;
	float3 position;
};

struct Spotlight
{
	float4 ambientIntensity;
	float4 diffuseIntensity;
	float4 specularIntensity;
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
								 float shininess,
								 float3 t_dirLightDirections[MAX_DIRECTIONAL_LIGHTS],
								 inout float4 ambientLight,
								 inout float4 diffuseLight,
								 inout float4 specularLight)
{
	for (int i = 0; i < lightCount; i++)
	{
		//Normalize the light direction.
		float3 l = normalize(t_dirLightDirections[i]);

		//Compute the half vector
		float3 h = normalize(v_viewDirection + l);

		//Compute the required dot products.
		float n_dot_l = max(dot(normal, l), 0.0);
		float n_dot_h = max(dot(normal, h), 0.0);

		float4 litResult = lit(n_dot_l, n_dot_h, shininess);

		ambientLight += lights[i].ambientIntensity * litResult.x;
		diffuseLight += lights[i].diffuseIntensity * litResult.y;
		specularLight += lights[i].specularIntensity * litResult.z;
	}
}

void PopulateDirectionalLightDirections(StructuredBuffer<DirectionalLight> lights,
										float4x4 viewMatrix,
										float3x3 TBN,
										inout float3 directions[MAX_DIRECTIONAL_LIGHTS])
{
	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
	{
		directions[i] = mul(mul(lights[i].direction, (float3x3) viewMatrix), TBN);
	}
}

void CalculatePointLightDirections(StructuredBuffer<PointLight> lights,
								   float3 v_Vertex,
								   float4x4 viewMatrix,
								   float3x3 TBN,
								   inout float3 directions[MAX_POINT_LIGHTS])
{
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		directions[i] = mul(mul(float4(lights[i].position, 1.0), viewMatrix).xyz - v_Vertex, TBN);
	}
}

void PopulateSpotlightDirections(StructuredBuffer<Spotlight> lights,
								 inout float3 directions[MAX_SPOTLIGHTS])
{
	for (int i = 0; i < MAX_SPOTLIGHTS; i++)
	{
		directions[i] = float3(0.0, 0.0, 0.0);
	}
}

#endif //LIGHT_UTILS_HLSL_
