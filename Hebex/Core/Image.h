#ifndef IMAGE_H
#define IMAGE_H

#include "Utils.h"
#include <string>
#include <vector>
#include "Color.h"

namespace Hebex 
{
	class Image {
	public :

		Image(float aResolutionX, float aResolutionY) : mResX((int)(aResolutionX)), mResY((int)(aResolutionY)) {}

		void Setup(float aResolutionX, float aResolutionY);

		void SetBuffer(const std::vector<Color> &aBuffer);

		void Clear();

		struct BmpHeader
		{
			uint32_t   mFileSize;        //!< Size of file in bytes.
			uint32_t   mReserved01;      //!< 2x 2 reserved bytes.
			uint32_t   mDataOffset;      //!< Offset in bytes where data can be found (54).

			uint32_t   mHeaderSize;      //!< 40B.
			int32_t    mWidth;           //!< Width in pixels.
			int32_t    mHeight;          //!< Height in pixels.

			int16_t  mColorPlates;     //!< Must be 1.
			int16_t  mBitsPerPixel;    //!< We use 24bpp.
			uint32_t   mCompression;     //!< We use BI_RGB ~ 0, uncompressed.
			uint32_t   mImageSize;       //!< mWidth x mHeight x 3B.
			uint32_t   mHorizRes;        //!< Pixels per meter (75dpi ~ 2953ppm).
			uint32_t   mVertRes;         //!< Pixels per meter (75dpi ~ 2953ppm).
			uint32_t   mPaletteColors;   //!< Not using palette - 0.
			uint32_t   mImportantColors; //!< 0 - all are important.
		};

		void Save(std::string & aFilename, float aGamma = 2.2f);

	private:
		void SaveBMP(const char *aFilename, float aGamma = 1.f);

		std::vector<Color> mColor;      //!< The color
		int mResX;       //!< Width of the framebuffer.
		int mResY;       //!< Height of the framebuffer.
	};
}

#endif