#ifndef _GXDX11BASE_H_
#define _GXDX11BASE_H_


class CGxDx11Base
{
// Constructors
public:
    CGxDx11Base();
    virtual ~CGxDx11Base();

// Methods
public:
    bool Initialize(HWND hWnd, HINSTANCE hInst);
    void Terminate();
    bool InitializeRTV(UINT nWidth, UINT nHeight);
    // bool ResizeSC(UINT nWidth, UINT nHeight);
    bool CompileShader(LPCWSTR szFilePath, LPCSTR szFunc, LPCSTR szShaderModel, ID3DBlob** buffer);

// Overrides
public:
    virtual bool LoadContent() = 0;
    virtual void UnloadContent() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

// Attributes
public:
    HWND m_hWnd;
    HINSTANCE m_hInst;
    ID3D11Device* m_pD3DDevice;
    ID3D11DeviceContext* m_pD3DContext;
    ID3D11RenderTargetView*	m_pD3DRenderTargetView;
    IDXGISwapChain* m_pSwapChain;
    ID3D11Texture2D* m_pDepthTexture;
    ID3D11DepthStencilView* m_pDepthStencilView;
};


#endif // _GXDX11BASE_H_