#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

typedef struct {
    int* initial_array;
    int* work_array;
    double min_time_taken;
    int size;
} Bench;

void reset(Bench* b) {
    for (int i = 0; i < b->size; i++) {
        b->work_array[i] = b->initial_array[i];
    }
}

void bench_init(Bench* b, int N) {
    b->size = N;
    b->initial_array = (int*)malloc(sizeof(int) * N);
    b->work_array = (int*)malloc(sizeof(int) * N);
    b->min_time_taken = DBL_MAX;

    for (int i = 0; i < b->size; i++) {
        b->initial_array[i] = b->size - i - 1;
    }
    reset(b);
}

void bench_free(Bench* b) {
    free(b->initial_array);
    free(b->work_array);
}

void boublesort(Bench* b) {
    int* p = b->work_array;

    for (int i = 0; i < b->size; i++) {
        for (int j = 0; j < b->size - i - 1; j++) {
            if (p[j] > p[j + 1]) {
                int temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void print(Bench* b) {
    for (int i = 0; i < b->size; i++) {
        printf("%d ", b->work_array[i]);
    }
    printf("\n");
}

void measure_worktime(Bench* b, int it) {
    double fault_sec = 1.0 / (double)CLOCKS_PER_SEC;
    long long fault_nsec = (long long)(fault_sec * 1e9);

    for (int i = 0; i < it; i++) {
        clock_t start = clock();
        boublesort(b);
        clock_t end = clock();

        double time_taken = (double)(end - start) / (double)CLOCKS_PER_SEC;
        if (time_taken < b->min_time_taken) {
            b->min_time_taken = time_taken;
        }
        printf("Time taken: %f sec. Fault(it): %lld nsec.\n", time_taken, fault_nsec);
        reset(b);
    }
    printf("Min time taken: %f sec.\n", b->min_time_taken);
    printf("Fault taken: %e sec.\n", fault_sec / b->min_time_taken);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int N = (int)strtol(argv[1], NULL, 10);
    Bench bench;
    bench_init(&bench, N);

    measure_worktime(&bench, 5);

    bench_free(&bench);
    return 0;
}