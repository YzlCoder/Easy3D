#pragma once
#include "Texture2D.h"
#include "Light.h"
#include "Vector.h"
#include "Matrix.h"
#include "Mesh.h"

class BaseShader
{
public:
	BaseShader() {}
	virtual	~BaseShader() {}
	
public:
	virtual easym::VertexOut VS(const easym::VertexIn& vin) = 0;
	virtual easym::Vector4 PS (easym::VertexOut& vout) = 0;
	virtual void SetTexture(const easym::Texture2D& tex) = 0;
	virtual void SetWorld(const easym::Matrix& world) = 0;
	virtual void SetView(const easym::Matrix& view) = 0;
	virtual void SetProject(const easym::Matrix& project) = 0;
	virtual void SetEyePos(const easym::Vector3& eyePos) = 0;
	virtual void SetMaterial(const easym::light::Material& material) = 0;
	virtual void SetLight(const easym::light::Light& dirLight) = 0;
};

