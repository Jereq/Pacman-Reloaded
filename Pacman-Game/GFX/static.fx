//transformation matrices
matrix World;
matrix View;
matrix Projection;

tbuffer morphIndexBuffer
{
	int index;
};

tbuffer morphVertexBuffer
{
	float3 pos;
	float3 norm;
	float2 tex;
};

//TEXTURE VARIABLES
//--------------------------------------------------------------------------------------

//color map texture
Texture2D colorMap;

//texture sampler state
SamplerState linearSampler
{
    Filter = min_mag_mip_linear;
    AddressU = Clamp;
    AddressV = Clamp;
    MaxAnisotropy = 16;
};

//LIGHTING STRUCTURES AND VARIABLES
//--------------------------------------------------------------------------------------
struct DirectionalLight
{
	float4 color;
	float3 dir;
};

struct Material
{
	float Ka, Kd, Ks, A;
};

//lighting vars
DirectionalLight light;
Material material;
float4 ambientLight;
float3 eye;

//RASTERIZER STATES
//--------------------------------------------------------------------------------------
RasterizerState rsSolid
{
	  FillMode = Solid;
	  CullMode = FRONT;
	  FrontCounterClockwise = false;
};

//VERTEX AND PIXEL SHADER INPUTS
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 p : POSITION;
	float2 t : TEXCOORD; 
	float3 n : NORMAL;  
};

struct PS_INPUT
{
	float4 p : SV_POSITION;  
	float2 t : TEXCOORD;	
	float3 n : TEXCOORD1;
	float3 h : TEXCOORD2;	
};

//--------------------------------------------------------------------------------------
// Blinn-Phong Lighting Reflection Model
//--------------------------------------------------------------------------------------
float4 calcBlinnPhongLighting( Material M, float4 LColor, float3 N, float3 L, float3 H )
{	
	float4 Ia = M.Ka * ambientLight;
	float4 Id = M.Kd * saturate( dot(N,L) );
	float4 Is = M.Ks * pow( saturate(dot(N,H)), M.A );
	
	return Ia + (Id + Is) * LColor;
}

//--------------------------------------------------------------------------------------
// PER PIXEL LIGHTING 
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	
	//set position into clip space
	input.p = mul( input.p, World );
	output.p = mul( input.p, View );
	output.p = mul( output.p, Projection );
	
	//set texture coords
	output.t = input.t;
	
	//set required lighting vectors for interpolation
	float3 V = normalize( eye - (float3) input.p );
	output.n = normalize( mul(input.n, (float3x3)World) );
	output.h = normalize( -light.dir + V );
    
	return output;
}

float4 PS( PS_INPUT input ) : SV_Target
{
	//renormalize interpolated vectors
	input.n = normalize( input.n );
	input.h = normalize( input.h );
	
	//calculate lighting	
	float4 I = calcBlinnPhongLighting( material, light.color, input.n, -light.dir, input.h );
	
	//with texturing
	return I * colorMap.Sample(linearSampler, input.t);
	
	//no texturing pure lighting
	//return I;
}
//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------

technique10 RENDER
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
        SetRasterizerState( rsSolid );
    }    
}