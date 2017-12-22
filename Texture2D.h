#pragma once
#include "MathDefine.h"
#include "Vector.h"

namespace easym
{
	class Texture2D
	{
	public:
		Texture2D() :m_width(0), m_height(0), m_pixelBuffer(nullptr) {}

		Texture2D(UINT width, UINT height);

		Texture2D(UINT width, UINT height, void* data);

		~Texture2D();

		Texture2D(Texture2D&& rhs);

		Texture2D(const Texture2D& rhs);

		Texture2D& operator=(const Texture2D& rhs)
		{
			if (this == &rhs)
				return *this;
			Texture2D clone(rhs);
			delete[] m_pixelBuffer;
			m_width = clone.m_width;
			m_height = clone.m_height;
			m_pixelBuffer = clone.m_pixelBuffer;
			clone.m_pixelBuffer = nullptr;
			return *this;
		}

		bool Invalid() { return m_pixelBuffer != nullptr; }

		Vector4 Sample(const Vector2& tex);

		UINT m_width;
		UINT m_height;
		Vector4* m_pixelBuffer;
	};

	Texture2D LoadTexture2D(wchar_t* filePath);
}
