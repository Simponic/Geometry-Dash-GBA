//======================================================================
//
//	player, 16x16@4, 
//	+ palette 256 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 512 + 128 = 640
//
//	Time-stamp: 2020-08-07, 16:34:01
//	Exported by Cearn's Usenti v1.7.6
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __PLAYER__
#define __PLAYER__

#define playerPalLen 512
extern const unsigned short playerPal[256];

#define playerTilesLen 128
extern const unsigned short playerTiles[64];

#endif // __PLAYER__

