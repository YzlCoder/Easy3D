#pragma once
#include "Vector.h"
#include <vector>

namespace easym
{
	//顶点信息 包括坐标，颜色，纹理坐标，法线等等
	class VertexIn
	{
	public:

		Vector3 pos;    //顶点位置
		Vector3 color;  //顶点颜色
		Vector2 tex;    //纹理坐标
		Vector3 normal; //法线

		VertexIn() = default;
		VertexIn(Vector3 _pos, Vector3 _color, Vector2 _tex, Vector3 _normal)
			:pos(_pos), color(_color), tex(_tex), normal(_normal) {}
		VertexIn(const VertexIn& rhs) :pos(rhs.pos), color(rhs.color), tex(rhs.tex), normal(rhs.normal) {}
	};

	//经过顶点着色器输出的结构
	class VertexOut
	{
	public:

		Vector3 posTrans;  //世界变换后的坐标
		Vector3 posH;      //投影变换后的坐标	
		Vector2 tex;       //纹理坐标
		Vector3 normal;	   //法线
		Vector3 color;	   //颜色
		real oneDivZ;     //1/z用于深度测试

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

