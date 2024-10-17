#ifndef STANDARDINCLUDES_H
#define STANDARDINCLUDES_H

#define SDL_MAIN_HANDLED

//include standard headers
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cinttypes>
#include <stdio.h>
#include <thread>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

//project headers
#include "Singleton.h"
#include "BasicStructs.h"

//OS Specific includes and defines 
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); }
#define GetCurrentDir _getcwd
#else 
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
using namespace std;

#endif // !1
