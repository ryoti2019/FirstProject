struct PSInput
{
    float4 pos : SV_Position;
    float4 dif : COLOR0;
    float2 uv : TEXCOORD0;
};

Texture2D tex : register(t0);
Texture2D dist : register(t1);
SamplerState smp : register(s0);

float4 main(PSInput input) : SV_TARGET
{
    float3 d = dist.Sample(smp, input.uv).xyz;
    d *= 2.0;
    d -= 1.0f;
    d /= 6.0f;
    
    float4 col = tex.Sample(smp, input.uv + d.xy);
    
    return col;
    
}