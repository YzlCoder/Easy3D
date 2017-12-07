#pragma once
#include "Vector.h"
#include <vector>

namespace easym
{
	//������Ϣ �������꣬��ɫ���������꣬���ߵȵ�
	class VertexIn
	{
	public:

		Vector3 pos;    //����λ��
		Vector3 color;  //������ɫ
		Vector2 tex;    //��������
		Vector3 normal; //����

		VertexIn() = default;
		VertexIn(Vector3 _pos, Vector3 _color, Vector2 _tex, Vector3 _normal)
			:pos(_pos), color(_color), tex(_tex), normal(_normal) {}
		VertexIn(const VertexIn& rhs) :pos(rhs.pos), color(rhs.color), tex(rhs.tex), normal(rhs.normal) {}
	};

	//����������ɫ������Ľṹ
	class VertexOut
	{
	public:

		Vector3 posTrans;  //����任�������
		Vector3 posH;      //ͶӰ�任�������	
		Vector2 tex;       //��������
		Vector3 normal;	   //����
		Vector3 color;	   //��ɫ
		real oneDivZ;     //1/z������Ȳ���

		VertexOut() = default;
		VertexOut(Vector3 _posT, Vector3 _posH, Vector2 _tex, Vector3 _normal, Vector3 _color, real _oneDivZ)
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

	class Mesh
	{
	public:
		Mesh() {}

		void SetVertexs(VertexIn* _vs, int count)
		{
			vertexs.resize(count);
			new(&vertexs[0])std::vector<VertexIn>(_vs, _vs + count);  //vertexs.std::vector<VertexIn>::vector(_vs, _vs + count);
		}

		void SetIndices(int* _es, int count)
		{
			indices.resize(count);
			new(&indices)std::vector<int>(_es, _es + count); //indices.std::vector<int>::vector(_es, _es + count);
		}

		std::vector<VertexIn> vertexs;
		std::vector<int>  indices;
	};
}

