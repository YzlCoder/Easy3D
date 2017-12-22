#pragma once
#include "easym.h"
#include <windows.h>
#include <memory>

class Scene
{
public:
	Scene();
	~Scene();
	bool Init(HINSTANCE hInstance, HWND hWnd);
	bool BeInit() { return m_bInit; }
	void Update();
	void Render();
	void Clear();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

	easym::UINT*& GetDeviceBuffer() { return m_pImmediateContext->GetDevice().GetFrameBuffer(); }

private:

	HINSTANCE	m_hInstance;
	HWND m_hWnd;
	int	m_width, m_height;
	POINT m_lastMousePos;
	bool m_bInit;


	easym::Matrix m_modelMat, m_viewMat, m_projMat;
	std::shared_ptr<easym::DeviceContext> m_pImmediateContext;
	easym::Mesh m_box;
	easym::Texture2D m_tex;
	std::shared_ptr<easym::light::Light> m_pLight;
	easym::light::Material	m_material;
};

