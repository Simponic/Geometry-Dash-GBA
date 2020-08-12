//======================================================================
//
//	block, 16x16@4, 
//	+ palette 256 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 512 + 128 = 640
//
//	Time-stamp: 2020-08-11, 20:45:09
//	Exported by Cearn's Usenti v1.7.6
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __BLOCK__
#define __BLOCK__

#define blockPalLen 512
extern const unsigned short blockPal[256];

#define blockTilesLen 128
extern const unsigned short blockTiles[64];

#endif // __BLOCK__

