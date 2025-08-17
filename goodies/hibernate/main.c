#include <stdio.h>

int main(int argc, char **argv)
{
	asm volatile("csrrw x0, 0x170, %0\n" : : "r"(0xf0cacc1a));
	return 0;
}
