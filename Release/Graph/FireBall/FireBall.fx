//�X�N���[�����x
float2 ScrSpd = float2(1,1);






// ���@�ϊ��s��
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
float4x4 WorldMatrix              : WORLD;
float4x4 ViewMatrix               : VIEW;
float4x4 LightWorldViewProjMatrix : WORLDVIEWPROJECTION < string Object = "Light"; >;

// �I�u�W�F�N�g�̃e�N�X�`��
texture ObjectTexture: MATERIALTEXTURE;
sampler ObjTexSampler = sampler_state {
    texture = <ObjectTexture>;
    MINFILTER = ANISOTROPIC;
    MAGFILTER = ANISOTROPIC;
    MIPFILTER = LINEAR;
    MAXANISOTROPY = 16;
};
texture Pallet<
    string ResourceName = "Pallet.png";
>;
sampler PalletSamp = sampler_state {
    texture = <Pallet>;
    Filter = LINEAR;
    AddressU  = CLAMP;
    AddressV  = CLAMP;
};


// MMD�{����sampler���㏑�����Ȃ����߂̋L�q�ł��B�폜�s�B
sampler MMDSamp0 : register(s0);
sampler MMDSamp1 : register(s1);
sampler MMDSamp2 : register(s2);

// �֊s�`��p�e�N�j�b�N
technique EdgeTec < string MMDPass = "edge"; > {

}


///////////////////////////////////////////////////////////////////////////////////////////////
// �e�i��Z���t�V���h�E�j�`��
technique ShadowTec < string MMDPass = "shadow"; > {

}


float time : TIME;

///////////////////////////////////////////////////////////////////////////////////////////////
// �I�u�W�F�N�g�`��i�Z���t�V���h�EOFF�j

struct VS_OUTPUT {
    float4 Pos        : POSITION;    // �ˉe�ϊ����W
    float3 Normal     : TEXCOORD2;   // �@��
    float4 ScreenTex  : TEXCOORD5;   // �X�N���[�����W
};

// ���_�V�F�[�_
VS_OUTPUT Basic_VS(float4 Pos : POSITION, float3 Normal : NORMAL)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    // ���_�@��
    Out.Normal = normalize( mul( Normal, (float3x3)WorldMatrix ) );
	
	float4 sctex = mul(Pos,WorldViewProjMatrix);
    sctex.xyz /= sctex.w;
    float2 TransScreenTex;
    TransScreenTex.x = (1.0f + sctex.x) * 0.5f;
    TransScreenTex.y = (1.0f - sctex.y) * 0.5f;
    TransScreenTex *= saturate(sctex.w*0.01);
    
    float height = tex2Dlod(ObjTexSampler,float4(TransScreenTex*4+float2(0.25,-1)*time*0.1,0,0)).r*1.01;
    //height *= tex2Dlod(ObjTexSampler,float4(TransScreenTex*4+float2(-0.1,-0.5)*time*0.1,0,0)).r*1.01;
    height = max(0,height-0.9)*10;
    
    Pos.xyz += Out.Normal*height;
    
    
    Out.Pos = mul(Pos,WorldViewProjMatrix);
    Out.ScreenTex = Out.Pos;
    
    return Out;
}

// �s�N�Z���V�F�[�_
float4 Basic_PS(VS_OUTPUT IN) : COLOR0
{
    IN.ScreenTex.xyz /= IN.ScreenTex.w;
    float2 TransScreenTex;
    TransScreenTex.x = (1.0f + IN.ScreenTex.x) * 0.5f;
    TransScreenTex.y = (1.0f - IN.ScreenTex.y) * 0.5f;
    TransScreenTex *= (IN.ScreenTex.w*0.01);

    float4 Color = 1;
    // �e�N�X�`���K�p
    float height = tex2D( ObjTexSampler, TransScreenTex*4+ScrSpd*float2(0.25,-1)*time*0.1 ).r;
    //height *= tex2D(ObjTexSampler,float4(TransScreenTex*4+ScrSpd*float2(-0.1,-0.5)*time*0.1,0,0)).r*2;
    Color.rgb = tex2D(PalletSamp,float2(1-height,0));
    float light = 1-height;
    height = pow(height,4);
    
    Color.rgb += pow(light*1,2)*float3(2,1,0);
    
    return Color;
}

technique MainTec0 < string MMDPass = "object"; > {
    pass DrawObject {
        VertexShader = compile vs_3_0 Basic_VS();
        PixelShader  = compile ps_3_0 Basic_PS();
    }
}
technique MainTec0ss < string MMDPass = "object_ss"; > {
    pass DrawObject {
        VertexShader = compile vs_3_0 Basic_VS();
        PixelShader  = compile ps_3_0 Basic_PS();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// �Z���t�V���h�E�pZ�l�v���b�g

struct VS_ZValuePlot_OUTPUT {
    float4 Pos : POSITION;              // �ˉe�ϊ����W
    float4 ShadowMapTex : TEXCOORD0;    // Z�o�b�t�@�e�N�X�`��
};

// ���_�V�F�[�_
VS_ZValuePlot_OUTPUT ZValuePlot_VS( float4 Pos : POSITION )
{
    VS_ZValuePlot_OUTPUT Out = (VS_ZValuePlot_OUTPUT)0;
    
    // ���C�g�̖ڐ��ɂ�郏�[���h�r���[�ˉe�ϊ�������
    Out.Pos = mul( Pos, LightWorldViewProjMatrix );
    
    // �e�N�X�`�����W�𒸓_�ɍ��킹��
    Out.ShadowMapTex = Out.Pos;
    
    return Out;
}

// �s�N�Z���V�F�[�_
float4 ZValuePlot_PS( float4 ShadowMapTex : TEXCOORD0 ) : COLOR
{
    // R�F������Z�l���L�^����
    return float4(ShadowMapTex.z/ShadowMapTex.w,0,0,1);
}

// Z�l�v���b�g�p�e�N�j�b�N
technique ZplotTec < string MMDPass = "zplot"; > {
    pass ZValuePlot {
        AlphaBlendEnable = FALSE;
        VertexShader = compile vs_2_0 ZValuePlot_VS();
        PixelShader  = compile ps_2_0 ZValuePlot_PS();
    }
}