#pragma once
#include <cstdint>
#include <corecrt_malloc.h>

/*
typedef unsigned char Byte;
typedef Byte* voidp;

typedef voidp(*alloc_func) (voidp opaque, uint32_t items, uint32_t size);
typedef void(*free_func)  (voidp opaque, voidp address);


struct z_stream {
	const char* next_in;				// next input byte 
	uint32_t     avail_in;				// number of bytes available at next_in 
	uint64_t    total_in;				// total number of input bytes read so far 

	char* next_out;						// next output byte will go here
	uint32_t     avail_out;				// remaining free space at next_out
	uint64_t    total_out;				// total number of bytes output so far 

	const char* msg;					// last error message, NULL if no error 
	struct internal_state* state;		// not visible by applications

	alloc_func zalloc;					// used to allocate the internal state 
	free_func  zfree;					// used to free the internal state 
	voidp     opaque;					// private data object passed to zalloc and zfree 
		
	int     data_type;					// best guess about the data type: binary or text for deflate, or the decoding state for inflate
	uint64_t   adler;					// Adler-32 or CRC-32 value of the uncompressed data
	uint64_t   reserved;				// reserved for future use
};


#define MAX_WBITS   15 // 32K LZ77 window

#define DEF_WBITS MAX_WBITS

#define ZLIB_VERSION "1.2.11"

#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)

#define ZALLOC(strm, items, size) (*(strm.zalloc))(strm.opaque, (items), (size))
#define ZFREE(strm, addr)  (*((strm)->zfree))((strm)->opaque, (voidpf)(addr))
#define TRY_FREE(s, p) {if (p) ZFREE(s, p);}

// Reverse the bytes in a 32-bit value
#define ZSWAP32(q) ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + (((q) & 0xff00) << 8) + (((q) & 0xff) << 24))






voidp zcalloc(voidp opaque, unsigned int items, unsigned int size)
{
	voidp buf;
	unsigned long bsize = (unsigned long)items * size;

	(void)opaque;

	// If we allocate less than 65520 bytes, we assume that farmalloc
	// will return a usable pointer which doesn't have to be normalized.
	 
	if (bsize < 65520L) {
		buf = malloc(bsize);
		if (*(unsigned short*)&buf != 0) return buf;
	}
	else {
		buf = malloc(bsize + 16L);
	}
	if (buf == NULL || next_ptr >= MAX_PTR) return NULL;
	table[next_ptr].org_ptr = buf;

	// Normalize the pointer to seg:0
	*((unsigned short*)&buf + 1) += ((unsigned short)((unsigned char*)buf - 0) + 15) >> 4;
	*(unsigned short*)&buf = 0;
	table[next_ptr++].new_ptr = buf;
	return buf;
}
void zcfree (voidp opaque, voidp ptr);

int inflateInit(z_stream strm, int windowBits, const char* version, int stream_size)
{
	int ret;
	struct inflate_state* state;

	if (version == NULL || version[0] != ZLIB_VERSION[0] ||
		stream_size != (int)(sizeof(z_stream)))
		return Z_VERSION_ERROR;
	
	if (&strm == NULL) return Z_STREAM_ERROR;
	
	strm.msg = NULL;                 // in case we return an error
	
	if (strm.zalloc == (alloc_func)0) {
		strm.zalloc = zcalloc;
		strm.opaque = (voidp)0;
	}
	
	if (strm.zfree == (free_func)0)
		strm.zfree = zcfree;

	state = (struct inflate_state*)
		ZALLOC(strm, 1, sizeof(struct inflate_state));
	if (state == NULL) return Z_MEM_ERROR;
	//Tracev((stderr, "inflate: allocated\n"));
	strm.state = (struct internal_state*)state;
	state.strm = strm;
	state.window = NULL;
	state.mode = HEAD;     // to pass state test in inflateReset2()
	ret = inflateReset2(strm, windowBits);
	if (ret != Z_OK) {
		ZFREE(strm, state);
		strm->state = NULL;
	}
	return ret;
}


int inflateInit(z_stream strm, const char* version, int stream_size)
{
	return inflateInit(strm, DEF_WBITS, version, stream_size);
}

int inflateInit(z_stream strm)
{
	return inflateInit(strm, ZLIB_VERSION, (int)sizeof(z_stream));
}
*/