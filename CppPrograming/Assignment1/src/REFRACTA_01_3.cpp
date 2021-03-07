#include <iostream>
#include <cstdio>
#define D_CEIL(x, y) ((x) / (y) + (((x) % (y)) != 0))

void print_mt(int from, int to, int dan) {
    for (int i = from; i <= to; i++) {
        printf("%2d x %2d = %2d\n", dan, i, dan * i);
    }
}

void print_mt_range(int danStart, int danEnd, int from, int to) {
    for (int dan = danStart; dan <= danEnd; dan++) {
        print_mt(from, to, dan);
    }
}

class MultiplicationTable {
private:
    int dan_start;
    int dan_end;
    int from;
    int to;
    int rows;
public:
    MultiplicationTable(int dan_start, int dan_end, int from, int to, int rows) {
        this->dan_start = dan_start;
        this->dan_end = dan_end;
        this->from = from;
        this->to = to;
        this->rows = rows;
    }
    ~MultiplicationTable() {}
    void print() {
        std::cout << "[객체지향 프로그래밍]" << std::endl;
        std::cout << " 구구단 " << dan_start << "~" << dan_end << "단" << std::endl;
        for (int l = 0; l < D_CEIL(dan_end - dan_start + 1, rows); l++) {
            for (int i = from; i <= to; i++) {
                for (int d = 0, dan = dan_start + l * rows + d;
                     d < rows && dan <= dan_end; d++, dan = dan_start + l * rows + d) {
                    printf("%2d x %2d = %2d\t", dan, i, dan * i);
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

void run_procedural_mt(int dan_start, int dan_end, int from, int to) {
    std::cout << "[절차적 프로그래밍]" << std::endl;
    int dan = dan_start, i = from;
    std::cout << " 구구단 " << dan_start << "~" << dan_end << "단" << std::endl;
    loop:
    printf("%2d x %2d = %2d\n", dan, i, dan * i);
    i++;
    if (i <= to) {
        goto loop;
    } else if (dan < dan_end) {
        i = from;
        dan++;
        goto loop;
    }
}

void run_structured_mt(int dan_start, int dan_end, int from, int to) {
    std::cout << "[구조적 프로그래밍]" << std::endl;
    std::cout << " 구구단 " << dan_start << "~" << dan_end << "단" << std::endl;
    print_mt_range(dan_start, dan_end, from, to);
}

void run_object_oriented_mt(int dan_start, int dan_end, int from, int to, int rows) {
    MultiplicationTable table(dan_start, dan_end, from, to, rows);
    table.print();
}

int main() {
    int dan_start = 2, dan_end = 9, from = 1, to = 9, rows = 4;
    run_procedural_mt(dan_start, dan_end, from, to);
    run_structured_mt(dan_start, dan_end, from, to);
    run_object_oriented_mt(dan_start, dan_end, from, to, rows);
    std::cout << std::endl << "Press ENTER to exit..."; fflush(stdin); getchar();
    return 0;
}