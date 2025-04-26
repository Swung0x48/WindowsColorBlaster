#include "common.hlsl"

struct VS_INPUT
{
    float2 position : SV_POSITION;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position.xy, 0., 1);
    return output;
}