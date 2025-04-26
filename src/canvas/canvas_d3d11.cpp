//
// Created by Swung 0x48 on 2025-04-26.
//

#include "canvas_d3d11.h"

#include <cassert>
#include <cstdint>
#include <d3dcompiler.h>
#include <iostream>
#include <ostream>

canvas_d3d11::canvas_d3d11(ID3D11Device* device, ID3D11DeviceContext* devctx, ID3D11RenderTargetView* rtv, float x, float y):
    device_(device), dev_ctx_(devctx), rtv_(rtv), viewport_x_(x), viewport_y_(y) {
    HRESULT hr = S_OK;

    hr = D3DCompileFromFile(L"shader/vertex.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_4_0", D3DCOMPILE_DEBUG, 0, &vs_blob_, &error_);
    if (FAILED(hr)) {
        std::cerr << (const char*)error_->GetBufferPointer() << std::endl;
        assert(0);
    }
    hr = device_->CreateVertexShader(vs_blob_->GetBufferPointer(), vs_blob_->GetBufferSize(), nullptr, &vs_);
    assert(SUCCEEDED(hr));
    hr = D3DCompileFromFile(L"shader/pixel.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_4_0", D3DCOMPILE_DEBUG, 0, &ps_blob_, &error_);
    if (FAILED(hr)) {
        std::cerr << (const char*)error_->GetBufferPointer() << std::endl;
        assert(0);
    }
    hr = device_->CreatePixelShader(ps_blob_->GetBufferPointer(), ps_blob_->GetBufferSize(), nullptr, &ps_);
    assert(SUCCEEDED(hr));

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {
            .SemanticName = "SV_POSITION",
            .SemanticIndex = 0,
            .Format = DXGI_FORMAT_R32G32_FLOAT,
            .InputSlot = 0,
            .AlignedByteOffset = 0,
            .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
            .InstanceDataStepRate = 0
        }
    };
    hr = device_->CreateInputLayout(layout, 1, vs_blob_->GetBufferPointer(), vs_blob_->GetBufferSize(), &layout_);
    assert(SUCCEEDED(hr));

    /*
     * 1    2
     *
     * 0    3
     *
     */
    static float vb_data[] {
        -1., -1.,
        -1.,  1.,
         1.,  1.,
         1., -1.
    };
    static uint32_t ib_data[] = {
        0, 1, 2,
        0, 2, 3
    };

    D3D11_BUFFER_DESC vb_desc {
        .ByteWidth = sizeof(vb_data),
        .Usage = D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_VERTEX_BUFFER,
        .CPUAccessFlags = 0
    };
    D3D11_SUBRESOURCE_DATA vb_sd = {
        .pSysMem = vb_data,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };
    hr = device_->CreateBuffer(&vb_desc, &vb_sd, &vb_);
    assert(SUCCEEDED(hr));

    D3D11_BUFFER_DESC ib_desc {
        .ByteWidth = sizeof(ib_data),
        .Usage = D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_INDEX_BUFFER,
        .CPUAccessFlags = 0
    };
    D3D11_SUBRESOURCE_DATA ib_sd = {
        .pSysMem = ib_data,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };
    hr = device_->CreateBuffer(&ib_desc, &ib_sd, &ib_);
    assert(SUCCEEDED(hr));
}


void canvas_d3d11::draw() {
    // let's do a fullscreen pass here

    D3D11_VIEWPORT vp;
    memset(&vp, 0, sizeof(D3D11_VIEWPORT));
    vp.Width = viewport_x_;
    vp.Height = viewport_y_;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = vp.TopLeftY = 0;
    dev_ctx_->RSSetViewports(1, &vp);

    dev_ctx_->OMGetRenderTargets(1, &rtv_, nullptr);

    uint32_t vbstride = 2 * sizeof(float); // 2 * f32 per vtx
    uint32_t vboffset = 0;
    dev_ctx_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    dev_ctx_->IASetInputLayout(layout_);
    dev_ctx_->VSSetShader(vs_, nullptr, 0);
    dev_ctx_->PSSetShader(ps_, nullptr, 0);
    dev_ctx_->IASetVertexBuffers(0, 1, &vb_, &vbstride, &vboffset);
    dev_ctx_->IASetIndexBuffer(ib_, DXGI_FORMAT_R32_UINT, 0);
    dev_ctx_->DrawIndexed(6, 0, 0);
}

