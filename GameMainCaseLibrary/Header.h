#pragma once
#ifdef GAME_EXPORTS
#define GAME_API __declspec(dllexport)	
#else
#define GAME_API __declspec(dllimport)	
#endif 

extern void Constructor(unsigned int* Vl,
	unsigned int k,
	unsigned int i,
	unsigned int** Rl,
	unsigned int** Wl);

extern void Do();