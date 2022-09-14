#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    LITTLE_ENDIAN_TYPE, BIG_ENDIAN_TYPE
};

void (*ce)(int *);
// Convert Endian FP

int get_system_endian() {
    unsigned int a = 0x00000001;
    unsigned char *p = &a;
    return *p == 0x00 ? BIG_ENDIAN_TYPE : LITTLE_ENDIAN_TYPE;
}

void print_system_env() {
    switch (get_system_endian()) {
        case LITTLE_ENDIAN_TYPE:
            printf("Current System: Little-Endian\n");
            printf("Reverse Endian Machine: Big-Endian\n");
            break;
        case BIG_ENDIAN_TYPE:
            printf("Current System: Big-Endian\n");
            printf("Reverse Endian Machine: Little-Endian\n");
            break;
    }
}

void print_data(int data) {
    int index = (data & 0xff000000) % 3;
    // Get index data
    int shift = 8 * index;
    char c = (data & (0xff << shift)) >> shift;
    // extract real character
    printf("%c", c);
}

void send_data(char c) {
    int ix = rand() % 3;
    char data_array[4];
    // [1 Byte]:PART1 [1 Byte]:PART2 [1 Byte]:PART3 [1 Byte]:PART4
    // [Character]:PART1 [Character]:PART2 [Character]:PART3 [Index Data (in ASCII range)]:PART4

    // Example)
    // If ix = 0
    // [Real Character(=c)] [Random Character] [Random Character] [ix + '0']

    // If ix = 1
    // [Random Character] [Real Character(=c)] [Random Character] [ix + '0']

    // If ix = 2
    // [Random Character] [Random Character] [Real Character(=c)] [ix + '0']
    data_array[ix] = c;
    // Real Character
    data_array[3] = ix + '0';
    // Index Data (in ASCII range)
    // '0' % 3 == 0 -> True ('0' is equals to 30)
    for (int i = 0; i < 3; i++) {
        if (i != ix) {
            int random_character = 32 + rand() % (126 - 32) + 1;
            // Random Character (ASCII Code: 33 ~ 126)
            data_array[i] = random_character;
        }
    }
    int data =
            (data_array[0] << (8 * 3)) + (data_array[1] << (8 * 2)) + (data_array[2] << (8 * 1)) +
            (data_array[3] << (8 * 0));

    ce(&data);
    print_data(data);
}

void init(void (*func_ce)(int *)) {
    ce = func_ce;
    srand(time(NULL));
    print_system_env();
    printf("Reverse Endian Machine Output: ");
}

