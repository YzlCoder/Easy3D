#pragma once
#include "Vector.h"
#include <windows.h>

namespace easym
{
	namespace light
	{
		/*
		* ambient ������
		* diffuse �������
		* specular �߹�
		*/

		struct DirectionalLight
		{
			DirectionalLight() { ZeroMemory(this, sizeof(this)); }

			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 direction;
		};

		struct PointLight
		{
			PointLight() { ZeroMemory(this, sizeof(this)); }

			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 position;
			Vector3 att;     //˥��ϵ��
			float range;      //���շ�Χ
		};
		 
		struct SpotLight
		{
			SpotLight() { ZeroMemory(this, sizeof(this)); }

			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 position;
			Vector3 direction;	
			Vector3 att;
			float range;			
			float spot;		
		};

		struct Material
		{
			Material() { ZeroMemory(this, sizeof(this)); }

			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular; 
			Vector3 reflect;
			real shininess;
		};

		inline void ComputeDirectionalLight(
			/* in */const Material& mat,				
			/* in */const DirectionalLight& L,
			/* in */const Vector3& normal,
			/* in */const Vector3& toEye,
			/* in */Vector3& ambient,
			/* out */Vector3& diffuse,
			/* out */Vector3& spec)
		{
			ambient = mat.ambient * L.ambient;

			Vector3 lightVec = - L.direction;
			lightVec.Normalize();
			diffuse = mat.diffuse * L.diffuse * max(Dot(lightVec, normal), 0);

			spec = mat.specular * L.specular * 
				pow(max(Dot(Reflect(-lightVec, normal), toEye), 0.0f), mat.shininess);
		}

		//������Դ
		inline void ComputePointLight(
			/* in */const Material& mat,
			/* in */const PointLight& L,
			/* in */const Vector3& pos,
			/* in */const Vector3& normal,
			/* in */const Vector3& toEye,
			/* out */Vector3& ambient,
			/* out */Vector3& diffuse,
			/* out */Vector3& spec)
		{

			ambient = mat.ambient * L.ambient;

			Vector3 lightVec = L.position - pos;
			float d = lightVec.magnitude();
			if (d > L.range)
			{
				diffuse = Vector3::zero;
				spec = Vector3::zero;
				return;
			}
			float att = 1.f / Dot(L.att, Vector3(1.f, d, d*d));

			lightVec.Normalize();
			diffuse = mat.diffuse * L.diffuse *  max(Dot(lightVec, normal), 0) * att;

			spec = mat.specular * L.specular *
				pow(max(Dot(Reflect(-lightVec, normal), toEye), 0.0f), mat.shininess) * att;
		}

		//����۹��
		inline void  ComputeSpotLight(
			/* in */const Material& mat,
			/* in */const SpotLight& L,
			/* in */const Vector3& pos,
			/* in */const Vector3& normal,
			/* in */const Vector3& toEye,
			/* out */Vector3& ambient,
			/* out */Vector3& diffuse,
			/* out */Vector3& spec)
		{

			ambient = mat.ambient * L.ambient;

			Vector3 lightVec = L.position - pos;
			float d = lightVec.magnitude();

			if (d > L.range)
			{
				diffuse = Vector3::zero;
				spec = Vector3::zero;
				return;
			}

			lightVec.Normalize();
			diffuse = mat.diffuse * L.diffuse * (Dot(lightVec, normal), 0);
			
			spec = mat.specular * L.specular *
				pow(max(Dot(Reflect(-lightVec, normal), toEye), 0.0f), mat.shininess) * att;

			//�۹�˥��ϵ��
			float spot = pow(max(Dot(-lightVec, L.direction), 0.0f), L.spot);
			//˥��ϵ��
			float att = spot / Dot(L.att, Vector3(1.0f, d, d*d));
			ambient = ambient * spot;
			diffuse = diffuse * att;
			spec = spec * att;
		}

	}
}