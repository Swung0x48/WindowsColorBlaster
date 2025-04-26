#include "common.hlsl"

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float4 color_l = float4(10.0, 0.0, 0.0, 1.0);
    float4 color_r = float4(0.0, 10.0, 0.0, 1.0);
    float norm_x = (input.position.x + 1.) / 2.;
    return lerp(color_l, color_r, norm_x);
}