// malloc/malloc.h, I'm compiling on OS X
#include <malloc/malloc.h>
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <limits.h>

//////////
// vars used for timing
uint64_t start, end;
unsigned cycles_high, cycles_low, cycles_high1, cycles_low1, ellapsed_cycles;

#define CYCLE_COUNT_START \
	asm volatile ("CPUID\n\t" \
	"RDTSC\n\t" \
	"mov %%edx, %0\n\t" \
	"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: \
	"%rax", "%rbx", "%rcx", "%rdx");

#define CYCLE_COUNT_END \
	asm volatile("RDTSCP\n\t" \
	"mov %%edx, %0\n\t" \
	"mov %%eax, %1\n\t" \
	"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1):: \
	"%rax", "%rbx", "%rcx", "%rdx"); \
	start = ( ((uint64_t)cycles_high << 32) | cycles_low ); \
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 ); \
	ellapsed_cycles = end - start;
//////////

int main(int argc, char* argv[]) {

	srand(time(NULL));

	//volatile size_t size = 4000;
	volatile size_t size = ARRAY_SIZE;

	CYCLE_COUNT_START
	volatile char* numbers = (char*)malloc(sizeof(char)*size);
	CYCLE_COUNT_END
	printf("memory allocatoin, cycles  %*ld\n", 12, ellapsed_cycles);

	// Everything below this is a hack to force optimizing compilers to actually
	// create the array.
	//
	// Print to stdout an operation that depends on all elements of the array.
	// Anyone reading this from stackoverflow, please feel free to offer suggestions
	// for better ways to achieve this.

	constexpr const unsigned int charmax_over_randmax = CHAR_MAX / RAND_MAX;

	for (size_t i=0; i<size; i++) {
		numbers[i] = rand() * charmax_over_randmax;
	}

	char sum=0;
	for (size_t i=0; i<size; i++) {
		sum += numbers[i] * 1e-4;
	}
	std::cout << "sum " << sum << std::endl;

	free((void*)numbers);
}
