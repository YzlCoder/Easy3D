#pragma once
#include "Vector.h"
#include <windows.h>

namespace easym
{
	namespace light
	{

		struct Material
		{
			Material() { ZeroMemory(this, sizeof(this)); }
			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 reflect;
			real shininess;
		};


		/*
		* ambient 环境光
		* diffuse 漫反射光
		* specular 高光
		*/
		class Light
		{
		public:
			virtual void CalcLight(
				/*  in    */Material mat,
				/*  in  */const Vector3& pos,
				/*  in  */const Vector3& normal,
				/*  in   */Vector3 toEye,
				/* out */Vector3& ambient,
				/* out */Vector3& diffuse,
				/* out */Vector3& spec) const = 0;
		};
		class DirectionalLight : public Light
		{
		public:
			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 direction;
			virtual void CalcLight(
				/*  in    */Material mat,
				/*  in  */const Vector3& pos,
				/*  in  */const Vector3& normal,
				/*  in   */Vector3 toEye,
				/* out */Vector3& ambient,
				/* out */Vector3& diffuse,
				/* out */Vector3& spec) const
			{
				ambient = mat.ambient * this->ambient;

				Vector3 lightVec = - this->direction;
				lightVec.Normalize();
				diffuse = mat.diffuse *  this->diffuse * max(Dot(lightVec, normal), 0);

				spec = mat.specular *  this->specular *
					pow(max(Dot(Reflect(-lightVec, normal), toEye), 0.0f), mat.shininess);
			}
		};

		class PointLight : public Light
		{
		public:
			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 position;
			Vector3 att;     //衰减系数
			real range;      //光照范围
			virtual void CalcLight(
				/*  in    */Material mat,
				/*  in  */const Vector3& pos,
				/*  in  */const Vector3& normal,
				/*  in   */Vector3 toEye,
				/* out */Vector3& ambient,
				/* out */Vector3& diffuse,
				/* out */Vector3& spec) const
			{
				ambient = mat.ambient * this->ambient;

				Vector3 lightVec = this->position - pos;
				real d = lightVec.magnitude();
				if (d > this->range)
				{
					diffuse = Vector3::zero;
					spec = Vector3::zero;
					return;
				}
				real att = 1.f / Dot(this->att, Vector3(1.f, d, d*d));

				lightVec.Normalize();
				diffuse = mat.diffuse *  this->diffuse *  max(Dot(lightVec, normal), 0) * att;

				spec = mat.specular *  this->specular *
					pow(max(Dot(Reflect(-lightVec, normal), toEye), 0.0f), mat.shininess);
			}
		};
		 
		struct SpotLight : public Light
		{
			Vector3 ambient;
			Vector3 diffuse;
			Vector3 specular;
			Vector3 position;
			Vector3 direction;	
			Vector3 att;
			real range;
			real spot;
			virtual void CalcLight(
				/*  in    */Material mat,
				/*  in  */const Vector3& pos,
				/*  in  */const Vector3& normal,
				/*  in   */Vector3 toEye,
				/* out */Vector3& ambient,
				/* out */Vector3& diffuse,
				/* out */Vector3& spec)const
			{
				ambient = mat.ambient * this->ambient;

				Vector3 lightVec = this->position - pos;
				real d = lightVec.magnitude();

				if (d > this->range)
				{
					diffuse = Vector3::zero;
					spec = Vector3::zero;
					return;
				}

				lightVec.Normalize();
				diffuse = mat.diffuse * this->diffuse * (Dot(lightVec, normal), 0);

				spec = mat.specular * this->specular *
					pow(max(Dot(Reflect(-lightVec, normal), toEye), 0.0f), mat.shininess) * this->att;

				//聚光衰减系数
				real spot = pow(max(Dot(-lightVec, this->direction), 0.0f), this->spot);
				//衰减系数
				real att = spot / Dot(this->att, Vector3(1.0f, d, d*d));
				ambient = ambient * spot;
				diffuse = diffuse * att;
				spec = spec * att;
			}
		};

	

	}
}