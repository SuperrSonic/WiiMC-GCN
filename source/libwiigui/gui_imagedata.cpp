/****************************************************************************
 * libwiigui
 *
 * Tantric 2009-2012
 *
 * gui_imagedata.cpp
 *
 * GUI class definitions
 ***************************************************************************/

#include "../utils/pngu.h"
#include "../utils/jmemsrc.h"
#include "gui.h"

/**
 * Constructor for the GuiImageData class.
 */
GuiImageData::GuiImageData(const u8 * i)
{
	data = NULL;
	width = 0;
	height = 0;
	format = GX_TF_RGBA8;

	if(i)
		LoadPNG(i);
}

GuiImageData::GuiImageData(const u8 * i, int s, u8 f)
{
	data = NULL;
	width = 0;
	height = 0;
	format = f;

	if(!i || s < 8)
		return;

	if (i[0] == 0xFF && i[1] == 0xD8)
		LoadJPEG(i, s);
	else if (i[0] == 0x89 && i[1] == 'P' && i[2] == 'N' && i[3] == 'G')
		LoadPNG(i);
	else
		LoadTex(i);
}

/**
 * Destructor for the GuiImageData class.
 */
GuiImageData::~GuiImageData()
{
	if(data)
	{
		gui_free(data);
		data = NULL;
	}
}

// overloaded new operator
void *GuiImageData::operator new(size_t size)
{
	void *p = gui_malloc(size);

	if (!p)
	{
		bad_alloc ba;
		throw ba;
	}
	return p;
}

// overloaded delete operator
void GuiImageData::operator delete(void *p)
{
	gui_free(p);
}

// overloaded new operator for arrays
void *GuiImageData::operator new[](size_t size)
{
	void *p = gui_malloc(size);

	if (!p)
	{
		bad_alloc ba;
		throw ba;
	}
	return p;
}

// overloaded delete operator for arrays
void GuiImageData::operator delete[](void *p)
{
	gui_free(p);
}

void GuiImageData::SetData(u8 * i)
{
	data = i;
}

void GuiImageData::SetImage(const u8 * i, int s)
{
	if(!i)
		return;

	width = 0;
	height = 0;

	if (i[0] == 0xFF && i[1] == 0xD8)
		LoadJPEG(i, s);
	else if (i[0] == 0x89 && i[1] == 'P' && i[2] == 'N' && i[3] == 'G')
		LoadPNG(i);
	else
		LoadTex(i);
}

void GuiImageData::LoadPNG(const u8 *i)
{
	data = DecodePNG(i, &width, &height, data);
}

void GuiImageData::LoadJPEG(const u8 *i, int s)
{
	format = GX_TF_RGB565;
	data = DecodeJPEG(i, s, &width, &height, data);
}

void GuiImageData::LoadTex(const u8 *i)
{
#if 0
	format = GX_TF_CMPR;
	width = *(uint16_t*)i;
	height = *(uint16_t*)(i+2);
	printf("SHOWME X: %d, %d,,", width, height);
	data = (u8 *)i+0x10;
#else
	format = GX_TF_CMPR;
	width = 320;
	height = 240;
	data = (u8 *)i;
#endif
}

u8 * GuiImageData::GetImage()
{
	return data;
}

int GuiImageData::GetWidth()
{
	return width;
}

int GuiImageData::GetHeight()
{
	return height;
}

u8 GuiImageData::GetFormat()
{
	return format;
}
