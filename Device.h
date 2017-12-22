#pragma once
#include "Vector.h"
#include "Utils.h"
/*
  *  ‰≥ˆ…Ë±∏
  */
namespace easym
{
	class Device
	{
	public:
		Device(int width, int height);
		~Device();
		void DrawPixel(int x, int y, easym::Vector4 color);
		real GetZ(int x, int y) const;
		void SetZ(int x, int y, real z);
		inline UINT*& GetFrameBuffer() { return m_pFrameBuffer; }
		inline int GetClientWidth() { return m_width; }
		inline int getClientHeight() { return m_height; }
		void ClearBuffer(Vector3 color);

	private:
		int m_width, m_height;
		UINT* m_pFrameBuffer;
		real **m_zBuffer;
	};
}

