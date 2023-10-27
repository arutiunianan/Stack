#include "hash.h"

//CRC32_function

// crc32_hash
int Hash( void *buf, unsigned long len )
{
	long crc_table[256] = {};
	long crc = 0;

	for ( int i = 0; i < 256; i++ )
	{
		crc = i;
		for ( int j = 0; j < 8; j++ )
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		crc_table[i] = crc;
	};
	
	crc = 0xFFFFFFFFUL;

	while ( len-- )	crc = crc_table[( crc ^ (*(char*)buf)++ ) & 0xFF] ^ ( crc >> 8 );
	return crc ^ 0xFFFFFFFFUL;
}