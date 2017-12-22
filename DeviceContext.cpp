#include "DeviceContext.h"
#include <algorithm>

namespace easym
{
	DeviceContext::DeviceContext():
		m_pDevice(nullptr), 
		m_renderMode(FILL_SOLIDE),
		m_pShader(nullptr)
	{
	}


	DeviceContext::~DeviceContext()
	{

	}

	void DeviceContext::SetViewPort(int left, int top, int width, int height)
	{
		screenMat = viewport(left, top, width, height);
	}

	void DeviceContext::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation)
	{
		for (UINT i = startIndexLocation; i < indexCount / 3; ++i)
		{
			VertexIn p1 = m_vertices[startVertexLocation + m_indices[3 * i]];
			VertexIn p2 = m_vertices[startVertexLocation + m_indices[3 * i + 1]];
			VertexIn p3 = m_vertices[startVertexLocation + m_indices[3 * i + 2]];

			VertexOut v1 = TransofrmToProjection(p1);
			VertexOut v2 = TransofrmToProjection(p2);
			VertexOut v3 = TransofrmToProjection(p3);

			if (BackFaceCulling(p1, p2, p3) == false)
			{
				continue;
			}

			if (Clip(v1) == false && Clip(v2) == false && Clip(v3) == false)
			{
				continue;
			}

			ToCVV(v1);
			ToCVV(v2);
			ToCVV(v3);

			TransformToScreen(screenMat, v1);
			TransformToScreen(screenMat, v2);
			TransformToScreen(screenMat, v3);

			DrawTriangle(v1, v2, v3);
		}
	}

	/* 透视除法 */
	void DeviceContext::ToCVV(VertexOut & v)
	{
		v.posH.x /= v.posH.w;
		v.posH.y /= v.posH.w;
		v.posH.z /= v.posH.w;
		v.posH.w = 1;
	}

	bool DeviceContext::Clip(const VertexOut& v)
	{
		//cvv为 x-1,1  y-1,1  z0,1
		if (v.posH.x >= -v.posH.w && v.posH.x <= v.posH.w &&
			v.posH.y >= -v.posH.w && v.posH.y <= v.posH.w &&
			v.posH.z >= 0.f && v.posH.z <= v.posH.w)
		{
			return true;
		}
		return false;
	}

	VertexOut DeviceContext::TransofrmToProjection(const VertexIn& v)
	{
		assert(m_pShader);

		VertexOut out = m_pShader->VS(v);

		//由于1/z和x,y成线性关系
		//这里将需要插值的信息都乘以1/z 得到 s/z和t/z等，方便光栅化阶段进行插值
		out.oneDivZ = 1 / out.posH.w;

		out.posTrans *= out.oneDivZ;
		out.color *= out.oneDivZ;
		out.tex *= out.oneDivZ;

		return out;
	}

	void DeviceContext::TransformToScreen(const Matrix & m, VertexOut & v)
	{
		v.posH = v.posH * m;
	}

	bool DeviceContext::BackFaceCulling(const VertexIn & v1, const VertexIn & v2, const VertexIn & v3)
	{
		//线框模式不进行背面消隐
		if (m_renderMode == FILL_WIREFRAME)
		{
			return true;
		}
		else
		{
			Vector3 vector1 = v2.pos - v1.pos;
			Vector3 vector2 = v3.pos - v2.pos;
			Vector3 normal = Cross(vector1, vector2);
			Vector3 viewDir = v1.pos;
			if (Dot(normal, viewDir) > 0)
			{
				return true;
			}
			return false;
		}
	}

	/* bresenham画线 */
	void DeviceContext::BresenhamDrawLine(int x1, int y1, int x2, int y2, const Vector3& colorA, const Vector3& colorB)
	{

		assert(m_pDevice);

		int dx = x2 - x1;
		int dy = y2 - y1;

		int stepx = 1, stepy = 1;

		if (dx < 0)
		{
			stepx = -1;
			dx = abs(dx);
		}

		if (dy < 0)
		{
			stepy = -1;
			dy = abs(dy);
		}

		int deltaX = 2 * dx, deltaY = 2 * dy;
		int width = m_pDevice->GetClientWidth();
		int height = m_pDevice->getClientHeight();

		if (dx < dy)
		{
			int error = deltaY - dx;
			for (int i = 0; i <= dx; ++i)
			{
				if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
				{
					m_pDevice->DrawPixel(x1, y1, Lerp(colorA, colorB, (x2 - x1) * stepx / static_cast<real>(dx)));
				}
				if (error >= 0)
				{
					error -= deltaX;
					y1 += stepy;
				}
				error += deltaY;
				x1 += stepx;
			}
		}
		else
		{
			int error = deltaX - dy;
			for (int i = 0; i <= dy; i++)
			{
				if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
					m_pDevice->DrawPixel(x1, y1, Lerp(colorA, colorB, (y2 - y1) * stepy / static_cast<real>(dy)));
				if (error >= 0)
				{
					error -= deltaY;
					x1 += stepx;
				}
				error += deltaX;
				y1 += stepy;
			}
		}
	}

	void DeviceContext::DrawTriangle(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		if (m_renderMode == FILL_WIREFRAME)
		{
			BresenhamDrawLine(static_cast<int>(v1.posH.x), static_cast<int>(v1.posH.y), 
				static_cast<int>(v2.posH.x), static_cast<int>(v2.posH.y), v1.color, v2.color);
			BresenhamDrawLine(static_cast<int>(v1.posH.x), static_cast<int>(v1.posH.y),
				static_cast<int>(v3.posH.x), static_cast<int>(v3.posH.y), v1.color, v3.color);
			BresenhamDrawLine(static_cast<int>(v2.posH.x), static_cast<int>(v2.posH.y),
				static_cast<int>(v3.posH.x), static_cast<int>(v3.posH.y), v2.color, v3.color);
		}
		else if (m_renderMode == FILL_SOLIDE)
		{
			TriangleRasterization(v1, v2, v3);
		}
	}

	void DeviceContext::TriangleRasterization(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		if (v1.posH.y == v2.posH.y)
		{
			if (v1.posH.y < v3.posH.y)
			{
				DrawTriangleTop(v1, v2, v3);
			}
			else
			{
				DrawTriangleBottom(v3, v1, v2);
			}
		}
		else if (v1.posH.y == v3.posH.y)
		{
			if (v1.posH.y < v2.posH.y)
			{
				DrawTriangleTop(v1, v3, v2);
			}
			else
			{
				DrawTriangleBottom(v2, v1, v3);
			}
		}
		else if (v2.posH.y == v3.posH.y)
		{
			if (v2.posH.y < v1.posH.y)
			{
				DrawTriangleTop(v2, v3, v1);
			}
			else
			{
				DrawTriangleBottom(v1, v2, v3);
			}
		}
		else
		{
			std::vector<VertexOut> vertices{ v1,v2,v3 };
			std::sort(vertices.begin(), vertices.end(), [](VertexOut v1, VertexOut v2) {
				return v1.posH.y < v2.posH.y; });

			VertexOut top = vertices[0];
			VertexOut middle = vertices[1];
			VertexOut bottom = vertices[2];

			real t = (middle.posH.y - top.posH.y) / (bottom.posH.y - top.posH.y);
			
			VertexOut newMiddle = Lerp(top, bottom, t);

			DrawTriangleTop(middle, newMiddle, bottom);
			DrawTriangleBottom(top, middle, newMiddle);
		}
	}

	void DeviceContext::DrawTriangleTop(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		assert(m_pDevice);

		real dy = 0;
		int height = m_pDevice->getClientHeight();
		for (real y = v1.posH.y; y <= v3.posH.y; y += 1)
		{
			int yIndex = static_cast<int>(y + static_cast<real>(0.5));
			if (yIndex >= 0 && yIndex < height)
			{
				real t = 0;
				if (!equal(v3.posH.y,v1.posH.y))
				{
					t = dy / (v3.posH.y - v1.posH.y);
				}

				VertexOut new1 = Lerp(v1, v3, t);
				VertexOut new2 = Lerp(v2, v3, t);
				dy += static_cast<real>(1);
				if (new1.posH.x <= new2.posH.x)
				{
					ScanlineFill(new1, new2, yIndex);
				}
				else
				{
					ScanlineFill(new2, new1, yIndex);
				}
			}
		}

	}

	void DeviceContext::DrawTriangleBottom(const VertexOut & v1, const VertexOut & v2, const VertexOut & v3)
	{
		assert(m_pDevice);

		real dy = 0;
		int height = m_pDevice->getClientHeight();
		for (real y = v1.posH.y; y <= v2.posH.y; y += 1)
		{
			int yIndex = static_cast<int>(y + static_cast<real>(0.5));

			if (yIndex >= 0 && yIndex < height)
			{
				real t = 0;
				if (!equal(v2.posH.y, v1.posH.y))
				{
					t = dy / (v2.posH.y - v1.posH.y);
				}

				VertexOut new1 = Lerp(v1, v2, t);
				VertexOut new2 = Lerp(v1, v3, t);
				dy += static_cast<real>(1);
				if (new1.posH.x <= new2.posH.x)
				{
					ScanlineFill(new1, new2, yIndex);
				}
				else
				{
					ScanlineFill(new2, new1, yIndex);
				}
			}
		}
	}

	void DeviceContext::ScanlineFill(const VertexOut & left, const VertexOut & right, int yIndex)
	{
		assert(m_pDevice);
		assert(m_pShader);

		real dx = right.posH.x - left.posH.x;

		int width = m_pDevice->GetClientWidth();
		for (real x = left.posH.x; x <= right.posH.x; x += 1)
		{
			int xIndex = static_cast<int>(x + static_cast<real>(0.5));

			if (xIndex >= 0 && xIndex < width)
			{
				real lerpFactor = 0;
				if (!equal(dx, 0))
				{
					lerpFactor = (x - left.posH.x) / dx;
				}

				real oneDivZ = Lerp(left.oneDivZ, right.oneDivZ, lerpFactor);
				//depth test
				if (oneDivZ >= m_pDevice->GetZ(xIndex, yIndex))
				{
					m_pDevice->SetZ(xIndex, yIndex, oneDivZ);
					
					real w = 1 / oneDivZ;
					VertexOut out = Lerp(left, right, lerpFactor);

					out.posH.x = xIndex;
					out.posH.y = yIndex;

					out.posTrans *= w;
					out.tex *= w;
					out.color *= w;

					m_pDevice->DrawPixel(xIndex, yIndex, m_pShader->PS(out));
				}
			}

		}
	}
}