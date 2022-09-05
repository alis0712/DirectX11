#include "DemoCube.h"

// Vertex Struct
struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

// Constructors
CDemoCube::CDemoCube()
{
	m_pVS = NULL;
	m_pPS = NULL;
	m_pInputLayout = NULL;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_pColorMap = NULL;
	m_pColorMapSampler = NULL;
	m_pViewCB = NULL;
	m_pProjCB = NULL;
	m_pWorldCB = NULL;

}

CDemoCube::~CDemoCube()
{
}

// Overrides

bool CDemoCube::LoadContent()
{
	// Compile Vertex Shader
	ID3DBlob* pVSBuffer = NULL;
	bool res = CompileShader(L"ShaderTexture.fx", "VS_Main", "vs_4_0", &pVSBuffer);
	if(res == false)
	{
		::MessageBox(m_hWnd, L"Unable to load vertex shader". L"ERROR", MB_OK);
		return false;
	}

	// Create vertex shader
	HRESULT hr;
	hr = m_pD3DDevice->CreateVertexShader(
		pVSBuffer->GetBufferPointer(),
		pVSBuffer->GetBufferSize(),
		0, &m_pVS);

	if (FAILED(hr))
	{
		if(pVSBuffer)
		{
			pVSBuffer->Release();
			return false;
		}
	}

	// Define Input Layout
	D3D11_INPUT_ELEMENT_DESC shaderInputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numLayoutElements = ARRAYSIZE(shaderInputLayout);

	// Create input Layout
	hr = m_pD3DDevice->CreateInputLayout(
		shaderInputLayout, numLayoutElements,
		pVSBuffer->GetBufferPointer(), 
		pVSBuffer->GetBufferSize(),
		&m_pInputLayout);

	if (FAILED(hr))
	{
		return false;
	}

	// Release VS buffer
	pVSBuffer->Release();
	pVSBuffer = NULL;

	// Compile pixel shader
	ID3DBlob* pPSBuffer = NULL;
	res = CompileShader(L"ShaderTexture.fx", "PS_Main", "ps_4_0", &pPSBuffer);

	if(res == false)
	{
		::MessageBox(m_hWnd, L"Unable to load pixel shader", L"ERROR", MB_OK);
		return false;
	}

	// Create Pixel Shader
	hr = m_pD3DDevice->CreatePixelShader(
		pPSBuffer->GetBufferPointer(),
		pPSBuffer->GetBufferSize(),
		0, &m_pPS);

	if (FAILED(hr))
	{
		return false;
	}

	// Cleanup PS Buffer
	pPSBuffer->Release();
	pPSBuffer = NULL;

	// Define Triangles
	Vertex vertices[] =
	{
		 { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };

	// Vertex Description
	D3D11_BUFFER_DESC vertexDesc;
	::ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(Vertex) * 24;