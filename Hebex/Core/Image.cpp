#include "Image.h"

namespace Hebex
{
	void Image::Setup(float aResolutionX, float aResolutionY)
	{

		mResX = int(aResolutionX);
		mResY = int(aResolutionY);
		mColor.resize(mResX * mResY);
		Clear();
	}

	void Image::SetBuffer(const std::vector<Color> &aBuffer) {
		mColor = std::move(aBuffer);
	}

	/**
	 * @brief	Clears the framebuffer.
	 */
	void Image::Clear()
	{
		memset(&mColor[0], 0, sizeof(Color) * mColor.size());
	}


	void Image::SaveBMP(const char *aFilename, float aGamma) {
		std::ofstream bmp(aFilename, std::ios::binary);
		BmpHeader header;
		bmp.write("BM", 2);
		header.mFileSize = uint32_t(sizeof(BmpHeader) + 2) + mResX * mResX * 3;
		header.mReserved01 = 0;
		header.mDataOffset = uint32_t(sizeof(BmpHeader) + 2);
		header.mHeaderSize = 40;
		header.mWidth = mResX;
		header.mHeight = mResY;
		header.mColorPlates = 1;
		header.mBitsPerPixel = 24;
		header.mCompression = 0;
		header.mImageSize = mResX * mResY * 3;
		header.mHorizRes = 2953;
		header.mVertRes = 2953;
		header.mPaletteColors = 0;
		header.mImportantColors = 0;

		bmp.write((char*)&header, sizeof(header));

		const float invGamma = 1.f / aGamma;
		for (int y = 0; y < mResY; y++)
		{
			for (int x = 0; x < mResX; x++)
			{
				// BMP is stored from bottom up.
				const Color &rgbF = mColor[x + (mResY - y - 1)*mResX];
				typedef unsigned char byte;
				float gammaBgr[3];
				gammaBgr[0] = std::pow(rgbF.b, invGamma) * 255.f;
				gammaBgr[1] = std::pow(rgbF.g, invGamma) * 255.f;
				gammaBgr[2] = std::pow(rgbF.r, invGamma) * 255.f;

				byte bgrB[3];
				bgrB[0] = byte(std::min(255.f, std::max(0.f, gammaBgr[0])));
				bgrB[1] = byte(std::min(255.f, std::max(0.f, gammaBgr[1])));
				bgrB[2] = byte(std::min(255.f, std::max(0.f, gammaBgr[2])));

				bmp.write((char*)&bgrB, sizeof(bgrB));
			}
		}
	}

	void Image::Save(std::string & aFilename, float aGamma) {
		std::string extension = aFilename.substr(aFilename.length() - 3, 3);
		if (extension == "bmp")
			SaveBMP(aFilename.c_str(), aGamma /*gamma*/);
		else
		{
			std::cerr << "Error: used unknown extension " << extension << std::endl;
			exit(2);
		}
	}
}