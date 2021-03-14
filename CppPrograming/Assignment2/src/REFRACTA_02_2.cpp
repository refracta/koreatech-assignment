#include <iostream>
#include <cstdio>

long double get_madhava_leibniz_series(int n, long double accumulator = 0) {
    accumulator == 0 && n % 2 == 0 ? n-- : 0;
    long double value = accumulator + 1.0L / (2 * n - 1) - 1.0L / (2 * n + 1);
    return n > 1 ? get_madhava_leibniz_series(n - 2, value) : value;
}

int main() {
    int n = 3000;
    printf("Pi = %lf", 4 * get_madhava_leibniz_series(n));
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
    return 0;
}