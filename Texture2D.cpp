#include "Texture2D.h"
#include <string.h>
#include <windows.h>
#include <gdiplus.h>

#include <iostream>
#include <fstream>
#include <sstream>

#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

namespace easym
{
	Texture2D::Texture2D(UINT width, UINT height) : m_width(width), m_height(height), m_pixelBuffer(nullptr)
	{
		int nsize = width * height;
		if (nsize <= 0)
		{
			m_width = 0;
			m_height = 0;
			m_pixelBuffer = nullptr;
			return;
		}

		m_pixelBuffer = new Vector4[width * height];
		memset(m_pixelBuffer, 0, width * height * sizeof(Vector4));
	}

	Texture2D::Texture2D(UINT width, UINT height, void* data): m_width(width), m_height(height), m_pixelBuffer(nullptr)
	{
		int nsize = width * height;
		if (nsize <= 0)
		{
			m_width = 0;
			m_height = 0;
			m_pixelBuffer = nullptr;
			return;
		}

		m_pixelBuffer = new Vector4[width * height];
		memcpy(m_pixelBuffer, data, width * height * sizeof(Vector4));
	}

	Texture2D::~Texture2D()
	{
		delete[] m_pixelBuffer;
		m_pixelBuffer = nullptr;
	}


	Texture2D::Texture2D(Texture2D&& rhs) :m_width(rhs.m_width), m_height(rhs.m_height), m_pixelBuffer(rhs.m_pixelBuffer)
	{
		rhs.m_height = 0;
		rhs.m_width = 0;
		rhs.m_pixelBuffer = nullptr;
	}

	Texture2D::Texture2D(const Texture2D& rhs) :m_width(rhs.m_width), m_height(rhs.m_height), m_pixelBuffer(NULL)
	{
		//…ÓøΩ±¥
		int nsize = m_height * m_width;
		if (nsize == 0)
		{
			return;
		}
		m_pixelBuffer = new Vector4[m_width * m_height];
		int index = 0;
		for (UINT i = 0; i < m_width; ++i)
		{
			for (UINT j = 0; j < m_height; ++j)
			{
				m_pixelBuffer[index] = rhs.m_pixelBuffer[index];
				index++;
			}
		}
	}

	Vector4 Texture2D::Sample(const Vector2& tex)
	{
		if (!Invalid())
		{
			return Vector4();
		}
		if (tex.u >= 0 && tex.u <= 1 && tex.v >= 0 && tex.v <= 1)
		{
			UINT x = static_cast<UINT>(tex.u * (m_width - 1));
			UINT y = static_cast<UINT>(tex.v * (m_height - 1));
			return m_pixelBuffer[y * m_width + x];
		}
		else
		{
			real u, v;
			if (tex.u > 1)
				u = tex.u - static_cast<int>(tex.u);
			else if (tex.u < 0)
				u = (static_cast<int>(-tex.u) + 1) + tex.u;
			if (tex.v > 1)
				v = tex.v - static_cast<int>(tex.v);
			else if (tex.v < 0)
				v = (static_cast<int>(-tex.v) + 1) + tex.v;
			UINT x = static_cast<UINT>(u * (m_width - 1));
			UINT y = static_cast<UINT>(v * (m_height - 1));
			return m_pixelBuffer[y * m_width + x];
		}
	}

	Texture2D LoadTexture2D(wchar_t* filePath)
	{
		GdiplusStartupInput gdiplusstartupinput;
		ULONG_PTR gdiplustoken;
		GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

		Bitmap* bmp = new Bitmap(filePath);
		if (!bmp)
		{
			MessageBox(nullptr, "error", "picture path is null!", MB_OK);
			delete bmp;
			GdiplusShutdown(gdiplustoken);
			return Texture2D(0, 0);
		}
		else
		{
			UINT height = bmp->GetHeight();
			UINT width = bmp->GetWidth();
			//≥ı ºªØTexture2D
			Texture2D texture(width, height);

			Color color;
			UINT index = 0;
			for (UINT y = 0; y < height; y++)
			{
				for (UINT x = 0; x < width; x++)
				{
					bmp->GetPixel(x, y, &color);
					texture.m_pixelBuffer[index++] = Vector4(
						color.GetRed() / static_cast<real>(255),
						color.GetGreen() / static_cast<real>(255),
						color.GetBlue() / static_cast<real>(255),
						static_cast<real>(1)
					);
				}
			}
			delete bmp;
			GdiplusShutdown(gdiplustoken);
			return texture;
		}
	}
}

