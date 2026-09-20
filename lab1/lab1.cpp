#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <float.h>

//GetSystemTime(), GetTickCount(), time()
//GetThreadTimes(),GetProcessTimes()

class Bench {
private:
    std::vector<int> initial_array;
    std::vector<int> work_array;
    double min_time_taken;
    int size;
public:
    Bench(int N) {
        size = N;
        initial_array.resize(size);
        work_array.resize(size);
        min_time_taken = DBL_MAX;

        for (int i = 0; i < size; i++) {
            initial_array[i] = size-i-1;
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

    void measure_worktime(int it) {
        timespec start, end, fault;

        for (int i = 0; i < it; i++) {
            clock_getres(CLOCK_MONOTONIC, &fault);
            clock_gettime(CLOCK_MONOTONIC, &start);
            boublesort();
            clock_gettime(CLOCK_MONOTONIC, &end);


            double time_taken = (double)(end.tv_sec-start.tv_sec) + 0.000000001*(end.tv_nsec-start.tv_nsec);
            if (time_taken < min_time_taken) {
                min_time_taken = time_taken;
            }
            std::cout << "Time taken: " << time_taken << " sec. Fault(it): " << fault.tv_nsec << " nsec.\n";
            reset();
        }
        std::cout << "Min time taken: " << min_time_taken <<  " sec.\n";
        std::cout << "Fault taken: " << (fault.tv_nsec/1e9)/min_time_taken << " sec.\n";
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) { return 1; }

    int N = strtol(argv[1], nullptr, 10);
    Bench bench(N);

    bench.measure_worktime(5);

    return 0;
}