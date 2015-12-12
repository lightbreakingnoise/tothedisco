#include <windows.h>
#include "bass.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>

#define DP 6.283185307179586476925286766559
#define OP 3.1415926535897932384626433832795
#define SR 44100.0
#define HSR 22050.0
#define HN 0.94387431268

typedef struct {
	float tones[100];
	float table[5000];
} ITABLE, *PTABLE;

#include "wavetable.h"
#include "class-CodingSong.h"
#include "class-UltraSaw.h"
#include "class-UltraPulse.h"
#include "class-UltraHat.h"
#include "class-Piano.h"
#include "class-UltraSinus.h"
#include "xdrum.h"
#include "xpisaw.h"
#include "xgeiger.h"
#include "fromfile.h"
