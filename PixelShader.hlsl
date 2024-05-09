
struct PSInput
{
    float4 pos : SV_Position;
    float4 dif : COLOR0;
    float2 uv : TEXCOORD0;
};

Texture2D tex : register(t0);
Texture2D norm : register(t1);
SamplerState smp : register(s0);

float4 main(PSInput input) : SV_TARGET
{
    float4 col = tex.Sample(smp, input.uv);
    
    float3 n = norm.Sample(smp, input.uv).xyz;
    n *= 2;
    n -= 1;
    n.z = -n.z;
    
    float3 light = float3(1, -1, 1);
    light = normalize(light);
    float diffuse = dot(-light, n);
    float ambient = 0.2;
    ambient = max(diffuse, ambient);
    
    float3 V = float3(0, 0, 1);
    V = normalize(V);
    float3 R = reflect(light, n);
    
    float spec = pow(saturate(dot(R, -V)), 20);
    
    return float4(col.rgb * diffuse + spec, col.a);
    
}