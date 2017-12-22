#include "Device.h"

namespace easym
{
	Device::Device(int width, int height) :m_width(width), m_height(height), m_pFrameBuffer(nullptr)
	{
		assert(width > 0 && height > 0);
		m_zBuffer = new real*[width];
		for (int i = 0; i < width; ++i)
		{
			m_zBuffer[i] = new real[height]{ 0 };
		}
	}


	Device::~Device()
	{
		if (m_zBuffer)
		{
			for (int i = 0; i < m_width; ++i)
			{
				delete[] m_zBuffer[i];
			}
			delete m_zBuffer;
			m_zBuffer = nullptr;
		}
	}

	void Device::DrawPixel(int x, int y, easym::Vector4 color)
	{
		assert(m_pFrameBuffer != nullptr);
		m_pFrameBuffer[y * m_width + x] = easym::color2Uint(color);
	}

	real Device::GetZ(int x, int y) const
	{
		assert(m_pFrameBuffer != nullptr);
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			return m_zBuffer[x][y];
		}
		else
		{
			return static_cast<real>(1);
		}
	}
	void Device::SetZ(int x, int y, real z)
	{
		assert(m_pFrameBuffer != nullptr);
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			m_zBuffer[x][y] = z;
		}
	}

	void Device::ClearBuffer(easym::Vector3 color)
	{
		assert(m_pFrameBuffer != nullptr && m_zBuffer != nullptr);
		for (int x = 0; x < m_width; ++x)
		{
			for (int y = 0; y < m_height; ++y)
			{
				m_pFrameBuffer[m_width * y + x] = easym::color2Uint(color);
				m_zBuffer[x][y] = 0;
			}
		}
	}
}