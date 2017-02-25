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
	float3 t_lightDirection : LIGHT_DIRECTION;
	float3 t_viewDirection : VIEW_DIRECTION;
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

	//Temporary hardcoded light direction.
	float3 lightDirection = float3(10.0, 10.0, -10.0);

	//Move the vertex to view space.
	float4 v_vertexPosition = mul(float4(input.position, 1.0), V);
	
	//Move the view direction to tangent space.
	output.t_viewDirection = mul(-v_vertexPosition.xyz, TBN);
	
	//Move the light direction to tangent space.
	output.t_lightDirection = mul(mul(lightDirection, (float3x3)V), TBN);

	return output;
}
