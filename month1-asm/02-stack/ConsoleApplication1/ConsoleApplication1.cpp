#include <cstdio>

__declspec(noinline) int square(int x)
{
    return x * x;
}

__declspec(noinline) int sum_of_squares(int a, int b)
{
    int sa = square(a);
    int sb = square(b);
    return sa + sb;
}

int main()
{
    int result = sum_of_squares(3, 4);
    std::printf("%d\n", result);
    return 0;
}