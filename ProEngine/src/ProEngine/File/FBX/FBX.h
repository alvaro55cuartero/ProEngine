#pragma once

#include <string>
#include "ProEngine/File/Stream.h"
#include "ProEngine/File/FBX/Node.h"


#include <iostream>


namespace Pro
{
	class FBX
	{
	public:
		FBX(std::string path);

		static FBX Import(std::string path);
	private:
		
		bool ReadNode(Node& node);
		void ReadNodeProperties(Node& node);
		

		template<class T>
		std::vector<T> ReadArray() {
			size_t arraySize = stream.Read<uint32_t>();
			size_t encoding = stream.Read<uint32_t>();
			size_t completeLength = stream.Read<uint32_t>();

			std::vector<T> data;
			if (encoding == 1)
			{ 
				data = stream.ReadArray<T>(completeLength);
				//buffer = decompress<T>(stream.read<char>(completeLength));
			}
			else 
			{
				data = stream.ReadArray<T>(completeLength);
			}

			return data;
		}

		int tabs = 0;
		Stream stream;
	};

	/*
	template<class T>
	std::vector<T> decompress(const Span<char>& source) const {
		std::vector<T> buffer;
		std::vector<char> out(FBX_CHUNK);

		z_stream infstream;
		infstream.zalloc = Z_NULL;
		infstream.zfree = Z_NULL;
		infstream.opaque = Z_NULL;
		infstream.avail_in = 0;
		infstream.next_in = Z_NULL;

		if (inflateInit(&infstream) != Z_OK) {
			throw std::runtime_error("Failed to initialize inflate");
		}

		int ret;
		size_t consumed = 0;
		do {
			size_t toConsume;
			if (consumed + FBX_CHUNK > source.size())
				toConsume = source.size() - consumed;
			else
				toConsume = FBX_CHUNK;

			infstream.avail_in = toConsume;
			infstream.next_in = (Bytef*)source.begin + consumed;
			consumed += toConsume;

			do {
				infstream.avail_out = FBX_CHUNK;
				infstream.next_out = (Bytef*)out.data();

				ret = inflate(&infstream, Z_NO_FLUSH);

				size_t have = FBX_CHUNK - infstream.avail_out;
				size_t size = buffer.size() * sizeof(T);

				assert(toConsume <= have); // TODO: Fix buffer overflow for large chunks to inflate

				buffer.resize(buffer.size() + have / sizeof(T));
				std::memcpy(buffer.data() + size, out.data(), have);
			} while (infstream.avail_out == 0);
		} while (ret != Z_STREAM_END);
		inflateEnd(&infstream);
		return buffer;
	}
	*/
}