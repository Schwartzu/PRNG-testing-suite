#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <lmcons.h>
#include <math.h>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

#include "functions.h"

#define MAXWIEDERHOLUNG 10000//8388607
#define MTTEST true

//MT
	//#define INITSEED 19660809UL
	#define P 624
	#define Q 397
	#define MATRIX_A   0x9908b0dfUL 
	#define UPPER_MASK 0x80000000UL 
	#define LOWER_MASK 0x7fffffffUL 
	static unsigned long mt[P]; 
	static int mti = P + 1;     
//MT END

