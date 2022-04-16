#include "Propch.h"
#include "Font.h"

#define stbtt_tag4(p,c0,c1,c2,c3) ((p)[0] == (c0) && (p)[1] == (c1) && (p)[2] == (c2) && (p)[3] == (c3))
#define stbtt_tag(p,str)           stbtt_tag4(p,str[0],str[1],str[2],str[3])

namespace Pro
{
	
	// (4 bytes) Tipo de archivo
	// (2 bytes) num_tablas: Numero de tablas
	// (6 bytes)
	
	// (16 bytes) * (num_tablas) Informacion de tabla
		// (4 o mas hasta 8 byte) nombre | no lo tengo claro
		// ()


	bool IsFont(uint8_t* font) {
		if (stbtt_tag4(font, '1', 0, 0, 0))  return 1; // TrueType 1
		if (stbtt_tag(font, "typ1"))   return 1; // TrueType with type 1 font -- we don't support this!
		if (stbtt_tag(font, "OTTO"))   return 1; // OpenType with CFF
		if (stbtt_tag4(font, 0, 1, 0, 0)) return 1; // OpenType 1.0
		if (stbtt_tag(font, "true"))   return 1; // Apple specification for TrueType fonts
		return 0;
	}

	Ref<Font> Font::Load(const std::string& path)
	{
		return LoadFromSource(File::Load(path));
	}

	Ref<Font> Font::LoadFromSource(const std::string& source)
	{
		if (!IsFont((uint8_t*)&source))
			std::cout << "Error";
		return CreateRef<Font>();
	}



}