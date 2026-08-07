#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define MAX_CARS 10
#define MAX_TEST 30
#define MPS 0.27777778

extern int lf_to_int(double lf);
extern double calc_accel(double in_v, double fin_v, double time);

static void save_time(FILE* file, int calc_accel_ms[], int test_number) {
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < test_number; i++) {
        fprintf(file, "%d\n", calc_accel_ms[i]);
    }
    fclose(file);
}

static double calc_accel_c(double in_v, double fin_v, double time) {
    double diff = fin_v - in_v;
    double accel = diff * MPS / time;
    return accel;
}

int main() {
	srand((unsigned int)time(NULL)); // seed random generator with current time

    int k = 0; // main test loop 

    FILE* file = fopen("10_time.txt", "w");
	FILE* file_c = fopen("10_time_c.txt", "w");

    // per-test timing (one value per test)
    int calc_accel_ns[MAX_TEST] = { 0 };
    int calc_accel_ns_c[MAX_TEST] = { 0 };

    long long sum = 0;
    long long sum_c = 0;

    while (k != MAX_TEST) {     // main test loop
        printf("\nTest %d:\n", k + 1);
        double in_v[MAX_CARS] = { 0.0 };
        double fin_v[MAX_CARS] = { 0.0 };
        double time_s[MAX_CARS] = { 0.0 };
        LARGE_INTEGER freq, start, end, start_c, end_c;
        QueryPerformanceFrequency(&freq);

        //printf("Enter the amount of cars: ");
        //scanf_s("%lf", &y);

        double y = MAX_CARS;
        int int_y = lf_to_int(y);

        for (int i = 0; i < int_y; i++) {
            /*
			scanf_s("%lf, %lf, %lf", &in_v[i], &fin_v[i], &time_s[i]);
            get_char();
            */

            in_v[i] = (double)rand() / RAND_MAX * 100.0;
            fin_v[i] = (double)rand() / RAND_MAX * 200.0;
            time_s[i] = (double)rand() / RAND_MAX * 15.0;
        }

		// For correctness check, print the input values for each car
        /*for (int i = 0; i < int_y; i++) {
            printf("Car %d: Initial Velocity = %.2lf km/h, Final Velocity = %.2lf km/h, Time = %.2lf s\n", i + 1, in_v[i], fin_v[i], time_s[i]);
		}*/

        printf("\n--------------------------Output--------------------------\n");
        double result[MAX_CARS] = { 0.0 };
        double result_c[MAX_CARS] = { 0.0 };

        // per-car timings within this test (temporary, local)
        int car_ns[MAX_CARS] = { 0 };
        int car_ns_c[MAX_CARS] = { 0 };

        for (int i = 0; i < int_y; i++) {
            // time the ASM version
            QueryPerformanceCounter(&start);
			result[i] = calc_accel(in_v[i], fin_v[i], time_s[i]);       // calculate acceleration using ASM
            QueryPerformanceCounter(&end);
            car_ns[i] = (int)((end.QuadPart - start.QuadPart) * 1e9 / freq.QuadPart);
        }

        for (int i = 0; i < int_y; i++) {
            // time the C version
            QueryPerformanceCounter(&start_c);
			result_c[i] = calc_accel_c(in_v[i], fin_v[i], time_s[i]);   // calculate acceleration using C
            QueryPerformanceCounter(&end_c);   
            car_ns_c[i] = (int)((end_c.QuadPart - start_c.QuadPart) * 1e9 / freq.QuadPart);
        }

        int accel[MAX_CARS] = { 0 };
        int accel_c[MAX_CARS] = { 0 };
        printf("\nThe integer acceleration values (m/s^2) are: \n");
        printf("\t     ASM\t\t\tC\t\tCorrectness Check:\n");

        long long test_sum = 0, test_sum_c = 0;
        for (int i = 0; i < int_y; i++) {
			// print acceleration values and check correctness
            printf("Car %d: ", i + 1);
            accel[i] = lf_to_int(result[i]);
            printf("%5d m/s^2", accel[i]);
            accel_c[i] = lf_to_int(result_c[i]);
            printf("\t\t%5d m/s^2", accel_c[i]);
            if (accel[i] == accel_c[i]) {
                printf("\t\t    Correct\n");
            }
            else {
                printf("\t\t    Incorrect\n");
            }

			// sum the per-car times for this test
            test_sum += car_ns[i];
            test_sum_c += car_ns_c[i];
        }

        // store current test's average per-car time
        calc_accel_ns[k] = (int)(test_sum / int_y);
        calc_accel_ns_c[k] = (int)(test_sum_c / int_y);

		// add current test's average time to total sum for later averaging
        sum += calc_accel_ns[k];
        sum_c += calc_accel_ns_c[k];

        printf("\nTime taken for ASM to calculate acceleration for %d cars: %d ns\n", int_y, calc_accel_ns[k]);
        printf("Time taken for C to calculate acceleration for %d cars: %d ns\n\n", int_y, calc_accel_ns_c[k]);

        k++;
    }

    double avg_time = (double)sum / k;
    double avg_time_c = (double)sum_c / k;

    save_time(file, calc_accel_ns, k);
	save_time(file_c, calc_accel_ns_c, k);

    printf("----------------------------------------------------------\nAverage ASM execution time for %d tests: %.2lf ns\n", k, avg_time);
    printf("Average C execution time for %d tests: %.2lf ns\n", k, avg_time_c);
    return 0;
}