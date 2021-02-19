typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

#define global_variable static;
#define internal static;

inline int
clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}


const char* letters[][7]{
	" 000 ",
	"0   0",
	"0   0",
	"00000",
	"0   0",
	"0   0",
	"0   0",

	"0000 ",
	"0   0",
	"0   0",
	"0000 ",
	"0   0",
	"0   0",
	"0000",

	" 000 ",
	"0   0",
	"0    ",
	"0    ",
	"0    ",
	"0   0",
	" 000 ",
	
	"000 ",
	"0  0",
	"0   0",
	"0   0",
	"0   0",
	"0  0",
	"000 ",

	"00000",
	"0   ",
	"0   ",
	"00000",
	"0   ",
	"0   ",
	"00000",

	"00000",
	"0   ",
	"0   ",
	"00000",
	"0   ",
	"0   ",
	"0   ",

	" 000 ",
	"0   0",
	"0   ",
	"0 000",
	"0   0",
	"0   0",
	" 000 ",

	"0   0",
	"0   0",
	"0   0",
	"00000",
	"0   0",
	"0   0",
	"0   0",

	"00000",
	"  0  ",
	"  0  ",
	"  0  ",
	"  0  ",
	"  0  ",
	"00000",

	"00000",
	"    0",
	"    0",
	"    0",
	"0   0",
	"0   0",
	" 000 ",

	"0    ",
	"0   0",
	"0  0 ",
	"0 0  ",
	"000  ",
	"0  0 ",
	"0   0",

	"0    ",
	"0    ",
	"0    ",
	"0    ",
	"0    ",
	"0    ",
	"00000",

	" 0 0 ",
	" 0 0 ",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",

	"0   0",
	"00  0",
	"00  0",
	"000 0",
	"0  00",
	"0  00",
	"0   0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 000 ",

	"0000 ",
	"0   0",
	"0   0",
	"0000 ",
	"0    ",
	"0    ",
	"0    ",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	" 000 ",
	"    0",

	"0000 ",
	"0   0",
	"0   0",
	"0000 ",
	"0   0",
	"0   0",
	"0   0",

	" 0000",
	"0    ",
	"0    ",
	" 000 ",
	"    0",
	"    0",
	"0000 ",

	"00000",
	"  0  ",
	"  0  ",
	"  0  ",
	"  0  ",
	"  0  ",
	"  0  ",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 000 ",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0 ",
	"  0  ",

	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",
	" 0 0 ",

	"0   0",
	" 0 0 ",
	"  0  ",
	"  0  ",
	"  0  ",
	" 0 0 ",
	"0   0",

	"0   0",
	"0   0",
	" 0 0 ",
	"  0  ",
	"  0  ",
	"  0  ",
	"  0  ",

	"00000",
	"    0",
	"   0 ",
	"  0  ",
	" 0   ",
	"0    ",
	"00000",

	"     ",
	"     ",
	"     ",
	"     ",
	"     ",
	"0  ",
	"0  ",

	"     ",
	"0   ",
	"0   ",
	"     ",
	"     ",
	"0   ",
	"0   ",

	"0   ",
	"0   ",
	"0   ",
	"0   ",
	"     ",
	"0   ",
	"0   ",

	"00000",
	"00000",
	"00000",
	"00000",
	"00000",
	"00000",
	"00000",


};