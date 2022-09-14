#include <iostream>
#include <cstdio>

int main() {
    int n = 5;
for (int y = 1; y <= n; y++) {
    int x = n;
    for (; x > y; x--) {
        printf("%d ", x);
    }
    printf("%d\n", x);
}
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
    return 0;
}
