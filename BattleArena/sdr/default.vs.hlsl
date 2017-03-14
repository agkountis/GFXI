#include "light_utils.hlsl"

struct VInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texcoord : TEXCOORD0;
};

struct VOutput
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 t_viewDirection : VIEW_DIRECTION;
	float3 t_directionalLightDirections[MAX_DIRECTIONAL_LIGHTS] : DIR_LIGHT_DIRECTIONS;
	float3 t_pointLightDirections[MAX_POINT_LIGHTS] : POINT_LIGHT_DIRECTIONS;
	float3 t_spotlightDirections[MAX_SPOTLIGHTS] : SPOTLIGHT_DIRECTIONS;
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
	int pad;
};

StructuredBuffer<DirectionalLight> directionalLights : register(t0);
StructuredBuffer<PointLight> pointLights : register(t1);
StructuredBuffer<Spotlight> spotlights : register(t2);


VOutput main(VInput input)
{
	VOutput output;

	//Move the vertex to the clipspace.
	output.position = mul(float4(input.position, 1.0), MVP);
	
	//Calculate the texture tilling
	output.texcoord = mul(float4(input.texcoord, 1.0, 1.0), textureMatrix).xy;

	//Transform the normal.
	float3 normal = mul(input.normal, (float3x3)ITMV);
	
	//Transform the tangent.
	float3 tangent = normalize(mul(input.tangent, (float3x3)ITMV));
	
	//Compute the binormal.
	float3 binormal = normalize(cross(normal, tangent));

	//Create the TBN matrix. This matrix tranforms vectors to tangent space.
	float3x3 TBN = transpose(float3x3(tangent, 
									  binormal, 
									  normal));

	//Move the vertex to view space.
	float4 v_vertexPosition = mul(float4(input.position, 1.0), V);
	
	//Move the view direction to tangent space.
	output.t_viewDirection = mul(-v_vertexPosition.xyz, TBN);
	
	PopulateDirectionalLightDirections(directionalLights, 
									   V, 
									   TBN, 
									   output.t_directionalLightDirections);

	CalculatePointLightDirections(pointLights,
								  v_vertexPosition.xyz,
								  V,
								  TBN,
								  output.t_pointLightDirections);

	PopulateSpotlightDirections(spotlights,
								V,
								TBN,
								output.t_spotlightDirections);

	return output;
}
