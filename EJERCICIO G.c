#include <stdio.h>

int main() {
    int max = 0;
    int mayorx = 0, mayory = 0;

    for (int x = 0; x <= 120; x++) {
        for (int y = 0; y <= 120; y++) {
            if ((y - x) <= 5 && (x + 6 * y) <= 140 && (4 * x + y) <= 120) {
                if ((x + y) > max) {
                    max = x + y;
                    mayorx = x;
                    mayory = y;
                }
            }
        }
    }

    printf("%d\n", max);
    printf("%d\n", mayorx);
    printf("%d\n", mayory);

    return 0;
}
