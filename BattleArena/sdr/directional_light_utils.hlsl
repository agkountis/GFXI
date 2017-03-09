struct DirectionalLight
{
	float4x4 ambientIntensity;
	float4x4 diffuseIntensity;
	float4x4 specularIntensity;
	bool active;
	float4x4 direction;
};

void AccumulateDirectionalLights(StructuredBuffer<DirectionalLight> lights,
								 int lightCount,
								 float3 normal,
							     float3 viewDirection,
								 inout float4 ambientLight,
								 inout float4 diffuseLight,
								 inout float4 specularLight)
{
	for (int i = 0; i < lightCount; i++)
	{

	}
}
