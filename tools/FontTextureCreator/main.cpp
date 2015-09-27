
#include "stdafx.h"
#include "stb_truetype.h"

#include <stdlib.h>
#include <stdio.h>
#include "Core\Image.h"
#include "Maths\Vector2.h"
#include "Loaders\ImagesLoader.h"

#include <string>
#include <ostream>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace CasaEngine;
using namespace std;

bool createFontTexture(const char* fontpath, 
	float fontHeight_, int texWidth_, int texHeight_, 
	int first_char, int num_chars, float luminance_,const char* fileName_);

void getBakedQuad(stbtt_bakedchar *chardata, int pw, int ph, int char_index,
	float *xpos, float *ypos, stbtt_aligned_quad *q);


/**
 *
 */
int main(int argc, _TCHAR* argv[])
{
	createFontTexture("C:\\Windows\\Fonts\\verdana.ttf", 18.0f, 512, 512, 32, 255, 1.75f,"Verdana 18.png");
	createFontTexture("C:\\Windows\\Fonts\\Arial.ttf", 15.0f, 512, 512, 32, 255, 1.0f,"Arial.png");
	createFontTexture("C:\\Windows\\Fonts\\cour.ttf", 12.0f, 512, 512, 32, 255, 1.75f,"Courier New.png");
	createFontTexture("C:\\Windows\\Fonts\\consola.ttf", 15.0f, 512, 512, 32, 255, 1.0f,"consola.png");
	createFontTexture("C:\\Windows\\Fonts\\segoeui.ttf", 15.0f, 512, 512, 32, 255, 1.0f,"segoeui.png");

	printf("Press any keys to continue...\n");
	getchar();

	return 0;
}

/**
 * 
 */
bool createFontTexture(const char* fontpath, 
	float fontHeight_, int texWidth_, int texHeight_, 
	int firstChar_, int numChars_, float luminance_,
	const char* fileName_)
{
	bool res = true;

	// Load font.
	FILE* fp = fopen(fontpath, "rb");
	if (!fp) return false;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	unsigned char* ttfBuffer = (unsigned char*)malloc(size);
	if (!ttfBuffer)
	{
		fclose(fp);
		return false;
	}

	fread(ttfBuffer, 1, size, fp);
	fclose(fp);
	fp = 0;

	unsigned char* bmap = (unsigned char*)malloc(texWidth_ * texHeight_);
	if (!bmap)
	{
		free(ttfBuffer);
		return false;
	}

	// ASCII 32..126 is 95 glyphs
	stbtt_bakedchar *pCharData = (stbtt_bakedchar*)malloc(sizeof(stbtt_bakedchar) * numChars_);

	if (pCharData != NULL)
	{
		stbtt_BakeFontBitmap(ttfBuffer, 0, fontHeight_, bmap, texWidth_, texHeight_, firstChar_, numChars_, pCharData);

		// create png
		PixelFormat::TPixelFormat Format = PixelFormat::A8R8G8B8;
		//A8R8G8B8 R8G8B8 A4R4G4B4 L8
		CImage imgFont(Vector2I(texWidth_, texHeight_), Format); //Vector2I(texWidth_, texHeight_), Format, bmap);

		for (int y=0; y<texHeight_; y++)
		{
			for (int x=0; x<texWidth_; x++)
			{
				float l = static_cast<float>(bmap[y * texWidth_ + x]) * luminance_;
				if (l > 255)
				{
					l = 255.0f;
				}

				CColor c(255, 255, 255, static_cast<unsigned char>(l) );
				imgFont.SetPixel(x, y, c);
			}
		}

		CImagesLoader loader;
		loader.SaveToFile(&imgFont, fileName_);

		std::string xmlName = fileName_;
		size_t found = xmlName.find_last_of('.');

		if (found == string::npos)
		{
			xmlName += ".xml";
		}
		else
		{
			xmlName = xmlName.substr(0,found) + ".xml";
		}

		std::ofstream xmlOut;
		xmlOut.open(xmlName, std::ofstream::out);

		xmlOut << "<?xml version=\"1.0\"?>" << std::endl;
		xmlOut << "<Font version=\"1\" height=\"" << fontHeight_ << "\" >" << std::endl;
		
		//for (int i=firstChar_; i<firstChar_ + numChars_; i++)
		for (int i=0; i<numChars_; i++)
		{
			stbtt_aligned_quad q;
			float xpos = 0.0f, ypos= 0.0f;
			getBakedQuad(pCharData, texWidth_, texHeight_, i, &xpos, &ypos, &q); // i - firstChar_

			xmlOut << "\t<Char ";
			xmlOut << "c=\"" << (firstChar_ + i) << "\" ";
			xmlOut << "xadvance=\"" << xpos << "\" ";
			xmlOut << "s0=\"" << q.s0 << "\" ";
			xmlOut << "s1=\"" << q.s1 << "\" ";
			xmlOut << "t0=\"" << q.t0 << "\" ";
			xmlOut << "t1=\"" << q.t1 << "\" ";
			xmlOut << "x0=\"" << q.x0 << "\" ";
			xmlOut << "x1=\"" << q.x1 << "\" ";
			xmlOut << "y0=\"" << q.y0 << "\" ";
			xmlOut << "y1=\"" << q.y1 << "\" ";

			/*xmlOut << "xoff=\"" << pCharData->xoff << "\" ";
			xmlOut << "yoff=\"" << pCharData->yoff << "\" ";
			xmlOut << "bx0=\"" << pCharData->x0 << "\" ";
			xmlOut << "bx1=\"" << pCharData->x1 << "\" ";
			xmlOut << "by0=\"" << pCharData->y0 << "\" ";
			xmlOut << "by1=\"" << pCharData->y1 << "\" ";*/

			xmlOut << "/>" << std::endl;
			//printf("%c: %f %f  %f %f  %f %f  %f %f\n", firstChar_ + i, q.x0, q.y0, q.s0, q.t0, q.x1, q.y1, q.s1, q.t1);
		}

		xmlOut << "</Font>" << std::endl;
		xmlOut.close();
	}
	else
	{
		res = false;
	}

	free(pCharData);
	free(ttfBuffer);
	free(bmap);

	return res;
}

/**
 * 
 */
void getBakedQuad(stbtt_bakedchar *chardata, int pw, int ph, int char_index,
	float *xpos, float *ypos, stbtt_aligned_quad *q)
{
	stbtt_bakedchar *b = chardata + char_index;
	int round_x = STBTT_ifloor(*xpos + b->xoff);
	int round_y = STBTT_ifloor(*ypos - b->yoff);

	q->x0 = (float)round_x;
	q->y0 = (float)round_y;
	q->x1 = (float)round_x + b->x1 - b->x0;
	q->y1 = (float)round_y - b->y1 + b->y0;

	q->s0 = b->x0 / (float)pw;
	q->t0 = b->y0 / (float)pw;
	q->s1 = b->x1 / (float)ph;
	q->t1 = b->y1 / (float)ph;

	*xpos += b->xadvance;
}
