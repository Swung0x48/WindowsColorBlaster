//
// Created by Swung 0x48 on 2025-04-26.
//

#ifndef CANVAS_D3D11_H
#define CANVAS_D3D11_H

#include <d3d11.h>

class canvas_d3d11 {
public:
    explicit canvas_d3d11(ID3D11Device* device, ID3D11DeviceContext* devctx, ID3D11RenderTargetView* rtv, float x, float y);
    void draw();
private:
    ID3D11Device* device_ = nullptr;
    ID3D11DeviceContext* dev_ctx_ = nullptr;
    ID3D11RenderTargetView* rtv_ = nullptr;
    ID3D11Buffer* vb_ = nullptr;
    ID3D11Buffer* ib_ = nullptr;

    ID3DBlob* error_ = nullptr;
    ID3DBlob* vs_blob_ = nullptr;
    ID3DBlob* ps_blob_ = nullptr;

    ID3D11InputLayout* layout_ = nullptr;
    ID3D11VertexShader* vs_ = nullptr;
    ID3D11PixelShader* ps_ = nullptr;

    float viewport_x_ = 0.0f;
    float viewport_y_ = 0.0f;
};



#endif //CANVAS_D3D11_H
