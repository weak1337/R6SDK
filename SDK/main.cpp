#include "includes.h"
R6* r6;
int main() {
	r6 = new R6();
	r6->mem = new Memory();
	r6->mem->setup();



	//b9 ? ? ? ? 48 03 0d ? ? ? ? e8 ? ? ? ? 48 8b 40 ? 48 85 c0 74 ? 48 8b 40 ? f6 80 ? ? ? ? ? 75 ? 80 be
	system("pause");
}