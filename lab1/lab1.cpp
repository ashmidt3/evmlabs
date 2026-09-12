#include <iostream>
#include <vector>
#include <random>
#include <ctime>

//GetSystemTime(), GetTickCount(), time()
//GetThreadTimes(),GetProcessTimes()

class Bench {
private:
    std::vector<int> initial_array;
    std::vector<int> work_array;
    int size;
public:
    Bench(int N) {
        size = N;
        initial_array.resize(size);
        work_array.resize(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, size - 1);
        for (int i = 0; i < size; i++) {
            initial_array[i] = distribution(gen);
        }
        reset();
    }
    ~Bench() = default;

    void reset() {
        work_array = initial_array;
    }

    void boublesort() {
        int* p = work_array.data();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (p[j] > p[j + 1]) {
                    int temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << work_array[i] << " ";
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) { return 1; }

    int N = strtol(argv[1], nullptr, 10);
    Bench bench(N);

    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    bench.boublesort();
    clock_gettime(CLOCK_MONOTONIC, &end);
    std::cout << "Time taken: " << (double)(end.tv_sec-start.tv_sec) + 0.000000001*(end.tv_nsec-start.tv_nsec) << " sec.\n";

    return 0;
}