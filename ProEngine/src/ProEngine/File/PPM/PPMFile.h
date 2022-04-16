#pragma once
#include <string>
#include "ProEngine/Math/Vec2.h"
#include "ProEngine/Types/Color.h"
/*
    A "magic number" for identifying the file type. A ppm image's magic number is the two characters "P6".
    Whitespace (blanks, TABs, CRs, LFs).
    A width, formatted as ASCII characters in decimal.
    Whitespace.
    A height, again in ASCII decimal.
    Whitespace.
    The maximum color value (Maxval), again in ASCII decimal. Must be less than 65536 and more than zero.
    Newline or other single whitespace character.
    A raster of Height rows, in order from top to bottom. Each row consists of Width pixels, in order from left to right. Each pixel is a triplet of red, green, and blue samples, in that order. Each sample is represented in pure binary by either 1 or 2 bytes. If the Maxval is less than 256, it is 1 byte. Otherwise, it is 2 bytes. The most significant byte is first.

    A row of an image is horizontal. A column is vertical. The pixels in the image are square and contiguous.
    In the raster, the sample values are "nonlinear." They are proportional to the intensity of the ITU-R Recommendation BT.709 red, green, and blue in the pixel, adjusted by the BT.709 gamma transfer function. (That transfer function specifies a gamma number of 2.2 and has a linear section for small intensities). A value of Maxval for all three samples represents CIE D65 white and the most intense color in the color universe of which the image is part (the color universe is all the colors in all images to which this image might be compared).

    ITU-R Recommendation BT.709 is a renaming of the former CCIR Recommendation 709. When CCIR was absorbed into its parent organization, the ITU, ca. 2000, the standard was renamed. This document once referred to the standard as CIE Rec. 709, but it isn't clear now that CIE ever sponsored such a standard.

    Note that another popular color space is the newer sRGB. A common variation on PPM is to subsitute this color space for the one specified.
    Note that a common variation on the PPM format is to have the sample values be "linear," i.e. as specified above except without the gamma adjustment. pnmgamma takes such a PPM variant as input and produces a true PPM as output.
    Characters from a "#" to the next end-of-line, before the maxval line, are comments and are ignored. 
*/

namespace Pro 
{
    class PPMFile
    {
    public:
        PPMFile(const uint32_t& width, const uint32_t& height, Color* data);
        std::string GetFileAsText();

        void AddSquare(const Vec2& pos, const Vec2& size, Color* data);
    private:
        const char* m_magicNumber;
        uint32_t m_width, m_height;
        uint16_t m_maxVal; //65536 and more than zero.
        Color* m_data;
    };
}