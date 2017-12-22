#pragma once
#include "BaseShader.h"

class BoxShader : public BaseShader
{
public:
	BoxShader();
	~BoxShader();

	virtual easym::VertexOut VS(const easym::VertexIn& vin) ;
	virtual easym::Vector4 PS(easym::VertexOut& vout) ;
	virtual void SetTexture(const easym::Texture2D& tex) ;
	virtual void SetWorld(const easym::Matrix& world) ;
	virtual void SetView(const easym::Matrix& view) ;
	virtual void SetProject(const easym::Matrix& project) ;
	virtual void SetEyePos(const easym::Vector3& eyePos) ;
	virtual void SetMaterial(const easym::light::Material& material) ;
	virtual void SetLight(const easym::light::Light& dirLight) ;
private:
	easym::Vector3               m_eyePos;
	easym::Matrix				     m_worldMat;
	easym::Matrix                 m_viewMat;
	easym::Matrix                 m_projMat;
	easym::Texture2D		    m_tex;				//纹理
	easym::light::Material	m_material;	  //材质
	const easym::light::Light*		m_pLight;			     //平行光
};

