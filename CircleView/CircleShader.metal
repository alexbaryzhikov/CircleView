#include <metal_stdlib>
using namespace metal;

struct VertexOut {
    float4 position [[position]];
    float4 color;
};

vertex VertexOut vertexShader(const device float2* vertexData [[buffer(0)]],
                              const device float2* viewSizeData [[buffer(1)]],
                              uint vertexId [[vertex_id]]) {
    float2 vertexPos = vertexData[vertexId];
    float2 viewSize = viewSizeData[0];
    float2 aspect = {viewSize[1] / viewSize[0], 1};
    return {
        .position = float4(vertexPos * aspect, 0, 1),
        .color = float4(189, 47, 36, 255) / 255
    };
}

fragment float4 fragmentShader(VertexOut in [[stage_in]]) {
    return in.color;
}
