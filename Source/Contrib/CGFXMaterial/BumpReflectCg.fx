/*********************************************************************NVMH3****
Path:  NVSDK\Common\media\cgfx
File:  bumpreflectcg.fx

Copyright NVIDIA Corporation 2002
TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED
*AS IS* AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS
BE LIABLE FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES
WHATSOEVER (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.


Comments:
	$Id: BumpReflectCg.fx,v 1.1 2005/06/09 14:53:40 a-m-z Exp $

******************************************************************************/

string Category = "Effects\\Cg\\Bump";
string keywords = "dx8,assembler,bumpmap,texture";
string description = "Dx8 bumpy-shiny with or without asm pixel shader";

// un-tweakables

float4x4 worldMatrix : World;	// World or Model matrix
float4x4 wvpMatrix : WorldViewProjection;	// Model*View*Projection
float4x4 worldViewMatrix : WorldView;
float4x4 worldViewMatrixI : WorldViewI;
float4x4 viewInverseMatrix : ViewIT;
float4x4 viewMatrix : View;

// tweakables

texture normalMap : NormalMap
<
	string File = "default_bump_normal.dds";
    string TextureType = "2D";
>;

texture cubeMap : EnvMap
<
	string File = "default_reflection.dds";
	string TextureType = "Cube";
>;

float bumpHeight
<
	string gui = "slider";
	float uimin = 0.0;
	float uimax = 2.0;
	float uistep = 0.1;
> = 0.5;

////////////////////

struct a2v {
	float4 Position : POSITION; //in object space
	float2 TexCoord : TEXCOORD0;
	float3 Tangent : TEXCOORD1; //in object space
	float3 Binormal : TEXCOORD2; //in object space
	float3 Normal : NORMAL; //in object space
};

struct v2f {
	float4 Position : POSITION; //in projection space
	float4 TexCoord : TEXCOORD0;
	float4 TexCoord1 : TEXCOORD1; //first row of the 3x3 transform from tangent to cube space
	float4 TexCoord2 : TEXCOORD2; //second row of the 3x3 transform from tangent to cube space
	float4 TexCoord3 : TEXCOORD3; //third row of the 3x3 transform from tangent to cube space
};

v2f BumpReflectVS(a2v IN,
		uniform float4x4 WorldViewProj,
		uniform float4x4 World,
		uniform float4x4 ViewIT,
		uniform float BumpScale)
{
	v2f OUT;

	// Position in screen space.
	OUT.Position = mul(WorldViewProj, IN.Position);
	
	// pass texture coordinates for fetching the normal map
	OUT.TexCoord.xy = IN.TexCoord;

	// compute the 3x3 tranform from tangent space to object space
	float3x3 objToTangentSpace;
	// first rows are the tangent and binormal scaled by the bump scale
	objToTangentSpace[0] = BumpScale * normalize(IN.Tangent);
	objToTangentSpace[1] = BumpScale * normalize(IN.Binormal);
	objToTangentSpace[2] = normalize(IN.Normal);

	OUT.TexCoord1.xyz = mul(objToTangentSpace, World[0].xyz);
	OUT.TexCoord2.xyz = mul(objToTangentSpace, World[1].xyz);
	OUT.TexCoord3.xyz = mul(objToTangentSpace, World[2].xyz);

	float4 worldPos = mul(World,IN.Position);
	// compute the eye vector (going from shaded point to eye) in cube space
	float4 eyeVector = worldPos - ViewIT[3]; // view inv. transpose contains eye position in world space in last row.
	OUT.TexCoord1.w = eyeVector.x;
	OUT.TexCoord2.w = eyeVector.y;
	OUT.TexCoord3.w = eyeVector.z;

	return OUT;
}

struct f2fb
{
	float4 col : COLOR;
};

f2fb BumpReflectPS(v2f IN,
				uniform sampler2D NormalMap,
				uniform samplerCUBE EnvironmentMap) 
{
	f2fb OUT;

	// fetch the bump normal from the normal map
	float4 normal = expand(tex2D(NormalMap));

	// transform the bump normal into cube space
	// then use the transformed normal and eye vector to compute a reflection vector
	// used to fetch the cube map
	// (we multiply by 2 only to increase brightness)
	OUT.col = texCUBE_reflect_dp3x3(EnvironmentMap, IN.TexCoord1, IN.TexCoord2, normal);
	return OUT;
}

sampler2D normalMapSampler = sampler_state
{
	Texture = <normalMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

samplerCUBE envMapSampler = sampler_state
{
	Texture = <cubeMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

////////////////////

technique BumpReflect0
{
	pass p0
	{
		VertexShader = compile vs_1_1 BumpReflectVS(wvpMatrix,worldMatrix,viewInverseMatrix,bumpHeight);
		
		Zenable = true;
		ZWriteEnable = true;
		CullMode = None;
		NormalizeNormals = true;

		PixelShader = compile ps_1_1 BumpReflectPS(normalMapSampler,envMapSampler);
		/*
		Texture[0] = <normalMap>;
		Target[0] = Texture2D;
		MinFilter[0] = Linear;
		MagFilter[0] = Linear;
		MipFilter[0] = Linear;

		Texture[3] = <cubeMap>;
		Target[3] = TextureCube;
		MinFilter[3] = Linear;
		MagFilter[3] = Linear;
		MipFilter[3] = Linear;

		ColorOp[0] = Modulate;		// Here for now to force GL to use D3D defaults.
		ColorArg1[0] = Texture;
		ColorArg2[0] = Current;
		AlphaOp[0] = SelectArg1;
		AlphaArg1[0] = Texture;
		AlphaArg2[0] = Current;

		ColorOp[1] = Disable;
		AlphaOp[1] = Disable;

		PixelShader = 
		asm
		{
			ps.1.1
			tex t0
			texm3x3pad t1, t0_bx2
			texm3x3pad t2, t0_bx2		
			texm3x3vspec t3, t0_bx2
			mov r0, t3
		};
		*/
	}
}

technique ReflectNoPixelShader
{
    pass p0
    {
		Zenable = true;
		ZWriteEnable = true;
		CullMode = None;
		NormalizeNormals = true;
		LocalViewer = true;

        TextureFactor = 0x008080ff; // 808080FF == 0,0,0,1

        TexCoordIndex[ 1 ] = 1 | CameraSpaceReflectionVector;

        TextureTransform[ 1 ] = <worldViewMatrix>;

        TextureTransformFlags[1] = Count3;

		Texture[1] = <cubeMap>;
		Target[1] = TextureCube;
		MinFilter[1] = Linear;
		MagFilter[1] = Linear;
		MipFilter[1] = Point;

		Texture[0] = <normalMap>;
		Target[0] = Texture2D;
		MinFilter[0] = Linear;
		MagFilter[0] = Linear;
		MipFilter[0] = Point;

		ColorOp[0] = DotProduct3; 
		ColorArg1[0] = Texture;
		ColorArg2[0] = TFactor;
		AlphaOp[0] = SelectArg1;
		AlphaArg1[0] = Texture;
		AlphaArg2[0] = Current;

		ColorOp[1] = Modulate;
		ColorArg1[1] = Texture;
		ColorArg2[1] = Current;
		AlphaOp[1] = SelectArg1;
		AlphaArg1[1] = Current;
		AlphaArg2[1] = Current;
    }

    pass p1
    {
		Zenable = true;
		ZWriteEnable = false;
		CullMode = None;
		NormalizeNormals = true;
		LocalViewer = true;

        TextureFactor = 0x0000ff80;

        TextureTransform[ 1 ] = <worldViewMatrixI>;
        TexCoordIndex[ 1 ] = 1 | CameraSpaceReflectionVector;

        TextureTransformFlags[1] = Count3;

		Texture[1] = <cubeMap>;
		Target[1] = TextureCube;
		MinFilter[1] = Linear;
		MagFilter[1] = Linear;
		MipFilter[1] = Point;

		Texture[0] = <normalMap>;
		Target[0] = Texture2D;
		MinFilter[0] = Linear;
		MagFilter[0] = Linear;
		MipFilter[0] = Point;

		ColorOp[0] = DotProduct3; 
		ColorArg1[0] = Texture;
		ColorArg2[0] = TFactor;
		AlphaOp[0] = SelectArg1;
		AlphaArg1[0] = Texture;
		AlphaArg2[0] = Current;

		ColorOp[1] = Modulate;
		ColorArg1[1] = Texture;
		ColorArg2[1] = Current;
		AlphaOp[1] = SelectArg2;
		AlphaArg1[1] = Texture;
		AlphaArg2[1] = Current;

        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        AlphaBlendEnable = true;
    }

    pass p2
    {
		Zenable = true;
		ZWriteEnable = false;
		CullMode = None;
		NormalizeNormals = true;
		LocalViewer = true;

        TextureFactor = 0x00ff0080; 

        TextureTransform[ 1 ] = <worldViewMatrixI>;
        TexCoordIndex[ 1 ] = 1 | CameraSpaceReflectionVector;

        TextureTransformFlags[1] = Count3;

		Texture[1] = <cubeMap>;
		Target[1] = TextureCube;
		MinFilter[1] = Linear;
		MagFilter[1] = Linear;
		MipFilter[1] = Point;

		Texture[0] = <normalMap>;
		Target[0] = Texture2D;
		MinFilter[0] = Linear;
		MagFilter[0] = Linear;
		MipFilter[0] = Point;

		ColorOp[0] = DotProduct3; 
		ColorArg1[0] = Texture;
		ColorArg2[0] = TFactor;
		AlphaOp[0] = SelectArg1;
		AlphaArg1[0] = Texture;
		AlphaArg2[0] = Current;

		ColorOp[1] = Modulate;
		ColorArg1[1] = Texture;
		ColorArg2[1] = Current;
		AlphaOp[1] = SelectArg2;
		AlphaArg1[1] = Texture;
		AlphaArg2[1] = Current;

         SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
       AlphaBlendEnable = true;
    }


}
