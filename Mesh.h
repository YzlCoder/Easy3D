#pragma once
#include "Vector.h"
#include <vector>

namespace easym
{
	//������Ϣ �������꣬��ɫ���������꣬���ߵȵ�
	class VertexIn
	{
	public:

		Vector4 pos;    //����λ��
		Vector4 color;  //������ɫ
		Vector2 tex;    //��������
		Vector3 normal; //����

		VertexIn() = default;
		VertexIn(Vector4 _pos, Vector4 _color, Vector2 _tex, Vector3 _normal)
			:pos(_pos), color(_color), tex(_tex), normal(_normal) {}
		VertexIn(const VertexIn& rhs) :pos(rhs.pos), color(rhs.color), tex(rhs.tex), normal(rhs.normal) {}
	};

	//����������ɫ������Ľṹ
	class VertexOut
	{
	public:

		Vector4 posTrans;  //����任�������
		Vector4 posH;      //ͶӰ�任�������	
		Vector2 tex;       //��������
		Vector3 normal;	   //����
		Vector4 color;	   //��ɫ
		real oneDivZ;     //1/z������Ȳ���

		VertexOut() = default;
		VertexOut(Vector4 _posT, Vector4 _posH, Vector2 _tex, Vector3 _normal, Vector4 _color, real _oneDivZ)
			:posTrans(_posT), posH(_posH), tex(_tex), normal(_normal), color(_color), oneDivZ(_oneDivZ) {}

		VertexOut(const VertexOut& rhs) :posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal),
			color(rhs.color), oneDivZ(rhs.oneDivZ) {}

		VertexOut& operator= (const VertexOut& rhs)
		{
			if (this == &rhs)
				return *this;
			this->normal = rhs.normal;
			this->posH = rhs.posH;
			this->posTrans = rhs.posTrans;
			this->tex = rhs.tex;
			this->color = rhs.color;
			this->oneDivZ = rhs.oneDivZ;
			return *this;
		}
	};

	inline VertexOut Lerp(const VertexOut& a, const VertexOut& b, real t)
	{
		return VertexOut(
			easym::Lerp(a.posTrans, b.posTrans, t),
			easym::Lerp(a.posH, b.posH, t),
			easym::Lerp(a.tex, b.tex, t),
			easym::Lerp(a.normal, b.normal, t),
			easym::Lerp(a.color, b.color, t),
			easym::Lerp(a.oneDivZ, b.oneDivZ, t)
		);
	}

	class Mesh
	{
	public:
		Mesh() {}
		
		Mesh(const Mesh& mesh):vertices(mesh.vertices), indices(mesh.indices){}
		
		Mesh(Mesh&& mesh)
		{
			swap(vertices, std::move(mesh.vertices));
			swap(indices, std::move(mesh.indices));
		}

		Mesh& operator=(const Mesh& mesh)
		{
			if (&mesh == this)
			{
				return *this;
			}
			vertices = mesh.vertices;
			indices = mesh.indices;
			return *this;
		}

		Mesh& operator=(Mesh&& mesh)
		{
			swap(vertices, std::move(mesh.vertices));
			swap(indices, std::move(mesh.indices));
			return *this;
		}

		void SetVertexs(VertexIn* _vs, int count)
		{
			vertices.resize(count);
			new(&vertices[0])std::vector<VertexIn>(_vs, _vs + count);  //vertexs.std::vector<VertexIn>::vector(_vs, _vs + count);
		}

		void SetIndices(int* _es, int count)
		{
			indices.resize(count);
			new(&indices)std::vector<UINT>(_es, _es + count); //indices.std::vector<int>::vector(_es, _es + count);
		}

		std::vector<VertexIn> vertices;
		std::vector<UINT>  indices;
	};
}

