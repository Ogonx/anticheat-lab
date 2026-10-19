#include <cstdio>

__declspec(noinline) int add(int a, int b) {

	return a + b;
}

int main() {
	std::printf("%d\n", add(2, 3));
	return 0;
}