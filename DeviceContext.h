#pragma once
#include "Device.h"
#include "BaseShader.h"
#include <memory>

namespace easym
{
	enum FILL_MODE//渲染模式
	{
		FILL_WIREFRAME,//线框模式
		FILL_SOLIDE	  //实体模式
	};

	class DeviceContext
	{
	public:
		DeviceContext();
		~DeviceContext();

		void Init(Device* pDevice)
		{
			m_pDevice.reset(pDevice);
		}
		void SetRenderMode(FILL_MODE mode)
		{
			m_renderMode = mode;
		}
		void SetVertexBuffer(const std::vector<VertexIn>& vertices)
		{
			m_vertices = vertices;
		}
		void SetVertexBuffer(std::vector<VertexIn>&& vertices)
		{
			swap(m_vertices, std::move(vertices));
		}
		void SetIndexBuffer(const std::vector<UINT>& indices)
		{
			m_indices = indices;
		}
		void SetIndexBuffer(std::vector<UINT>&& indices)
		{
			swap(m_indices, std::move(indices));
		}
		void SetShader(BaseShader* shader)
		{
			m_pShader.reset(shader);
		}
		BaseShader& GetShader()
		{
			assert(m_pShader);
			return *m_pShader;
		}
		Device& GetDevice()
		{
			assert(m_pDevice);
			return *m_pDevice;
		}
		void ClearBuffer(Vector3 color)
		{
			assert(m_pDevice);
			m_pDevice->ClearBuffer(color);
		}
		void SetViewPort(int left, int top, int width, int height);
		void DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation);
	
	private:

		void ToCVV(VertexOut& v);
		bool Clip(const VertexOut& v);
		VertexOut TransofrmToProjection(const VertexIn& v);
		void TransformToScreen(const Matrix& m, VertexOut& v);
		bool BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3);
		void BresenhamDrawLine(int x1, int y1, int x2, int y2,const Vector3& colorA, const Vector3& colorB);
		void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
		void TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);	
		void DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
		void DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
		void ScanlineFill(const VertexOut& left, const VertexOut& right, int yIndex);

	private:
		std::shared_ptr<Device> m_pDevice;
		FILL_MODE m_renderMode; 
		std::vector<VertexIn> m_vertices;
		std::vector<UINT> m_indices;
		std::shared_ptr<BaseShader> m_pShader;
		Matrix screenMat;
	};

}