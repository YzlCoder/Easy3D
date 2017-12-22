#include "Scene.h"
#include "BoxShader.h"
using namespace easym;

Scene::Scene()
{

	m_lastMousePos.x = 0;
	m_lastMousePos.y = 0;

	light::DirectionalLight* light = new light::DirectionalLight();
	light->ambient = Vector3(0.2f, 0.2f, 0.2f);
	light->diffuse = Vector3(0.5f, 0.5f, 0.5f);
	light->specular = Vector3(0.5f, 0.5f, 0.5f);
	light->direction = Vector3(0, - 1, 0);
	m_pLight.reset(static_cast<light::Light*>(light));

	m_material.ambient = Vector3(0.7f, 0.85f, 0.7f);
	m_material.diffuse = Vector3(0.7f, 0.85f, 0.7f);
	m_material.specular = Vector3(0.8f, 0.8f, 0.8f);
	m_material.shininess = 16.0f;

	m_bInit = false;
}


Scene::~Scene()
{
	Clear();
}


bool Scene::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	RECT rc;
	GetClientRect(m_hWnd, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	m_pImmediateContext = std::make_shared<easym::DeviceContext>();
	m_pImmediateContext->Init(new easym::Device(m_width, m_height));
	m_box = easym::MeshGenerator::CreateBox(2, 2, 2);

	m_pImmediateContext->SetViewPort(0, 0, m_width, m_height);
	m_pImmediateContext->SetVertexBuffer(m_box.vertices);
	m_pImmediateContext->SetIndexBuffer(m_box.indices);

	m_tex = easym::LoadTexture2D(L"Texture/Wood.bmp");

	BaseShader* pShader = new BoxShader();
	pShader->SetTexture(m_tex);
	pShader->SetLight(*m_pLight);
	pShader->SetMaterial(m_material);
	m_pImmediateContext->SetShader(pShader);
	m_bInit = true;
	m_projMat = perspective(pi / 4, m_width / static_cast<float>(m_height), 1.f, 100.f);
	
	Vector4 pos(0, 2, -5, 1.f);
	Vector4 target(0.f, 0.f, 0.f, 1.f);
	Vector4 up(0.f, 1.f, 0.f, 0.f);
	m_viewMat = lookat(pos, target, up);
	m_pImmediateContext->GetShader().SetEyePos(pos);

	return true;
}

void Scene::Update()
{
}
void Scene::Render()
{
	m_pImmediateContext->ClearBuffer(Vector3(0.75f, 0.75f, 0.75f));

	m_pImmediateContext->SetRenderMode(FILL_SOLIDE);

	m_pImmediateContext->GetShader().SetWorld(m_modelMat);
	m_pImmediateContext->GetShader().SetView(m_viewMat);
	m_pImmediateContext->GetShader().SetProject(m_projMat);

	m_pImmediateContext->DrawIndexed(m_box.indices.size(), 0, 0);
}
void Scene::Clear()
{

}

void Scene::OnMouseDown(WPARAM btnState, int x, int y)
{
	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
	SetCapture(m_hWnd);
}
void Scene::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}
void Scene::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		//½Ç¶È×ª»¡¶È
		float dx = radians(0.25*static_cast<float>(x - m_lastMousePos.x));
		float dy = radians(0.25*static_cast<float>(y - m_lastMousePos.y));

		m_modelMat = m_modelMat * rotateX(-dy) * rotateY(-dx);

	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		float dx = 0.2f*static_cast<float>(x - m_lastMousePos.x);
		float dy = 0.2f*static_cast<float>(y - m_lastMousePos.y);

		m_modelMat = m_modelMat * rotateX(-dy) * rotateY(-dx);

	}

	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
}