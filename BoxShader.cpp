#include "BoxShader.h"
#include "Utils.h"
using namespace easym;


BoxShader::BoxShader()
{
	m_pLight = nullptr;
}


BoxShader::~BoxShader()
{
}



easym::VertexOut BoxShader::VS(const easym::VertexIn& vin)
{
	VertexOut out;
	out.posTrans = vin.pos * m_worldMat;
	out.posH = out.posTrans * m_viewMat * m_projMat;
	out.normal = vin.normal * m_worldMat.inverse().transpose();
	out.color = vin.color;
	out.tex = vin.tex;
	return out;
}
easym::Vector4 BoxShader::PS(easym::VertexOut& vout)
{
	assert(m_pLight);
	vout.normal.Normalize();
	Vector4 texColor = m_tex.Sample(vout.tex);
	Vector3 toEye = (m_eyePos - vout.posTrans).normalize();
	Vector3 A, D, S;
	m_pLight->CalcLight(m_material, Vector3::zero, vout.normal, toEye, A, D, S);

	Vector4 litColor = texColor * (A + D);// +S;

	litColor.w = texColor.w;

	return litColor;
//	return(vout.normal + Vector4(1, 1, 1, 1)) / 2;
}

void BoxShader::SetTexture(const easym::Texture2D& tex)
{
	m_tex = tex;
}

void BoxShader::SetWorld(const easym::Matrix& world)
{
	m_worldMat = world;
}

void BoxShader::SetView(const easym::Matrix& view)
{
	m_viewMat = view;
}

void BoxShader::SetProject(const easym::Matrix& project)
{
	m_projMat = project;
}

void BoxShader::SetEyePos(const easym::Vector3& eyePos)
{
	m_eyePos = eyePos;
}

void BoxShader::SetMaterial(const easym::light::Material& material)
{
	m_material = material;
}

void BoxShader::SetLight(const easym::light::Light& dirLight)
{
	m_pLight = &dirLight;
}