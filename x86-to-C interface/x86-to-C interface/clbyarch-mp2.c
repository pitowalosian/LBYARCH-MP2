#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_CARS 9000
#define MAX_TEST 30

extern int lf_to_int(double lf);
extern double calc_accel(double in_v, double fin_v, double time);

/* void save_time(double calc_accel_ms[], int test_number) {
	FILE* file = fopen("9000_time.txt", "a"); // Open in append mode

	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}

	fprintf(file, "%.6lf\n", calc_accel_ms[test_number]);

	fclose(file);
}
*/

int main() {
	srand((unsigned int)time(NULL)); // Seed the random number generator

	//int k = 0;
	double calc_accel_ms;

	/*while (k != 30) {
		printf("\nTest %d:\n", k + 1);*/
		double y = 0.0;
		double in_v[MAX_CARS] = { 0.0 };
		double fin_v[MAX_CARS] = { 0.0 };
		double time_s[MAX_CARS] = { 0.0 };

		printf("Enter the amount of cars: ");
		scanf_s("%lf", &y);

		/*y = MAX_CARS;*/

		//printf("Enter the initial velocity, final velocity, and time of each car: \n");
		for (int i = 0; i < y; i++) {
			scanf_s("%lf, ", &in_v[i]);
			scanf_s("%lf, ", &fin_v[i]);
			scanf_s("%lf", &time_s[i]);

			//in_v[i] = (double)rand() / RAND_MAX * 100.0; // Random initial velocity between 0 and 100 km/h
			//fin_v[i] = (double)rand() / RAND_MAX * 200.0; // Random final velocity between 0 and 200 km/h
			//time_s[i] = (double)rand() / RAND_MAX * 15.0; // Random time between 0 and 15s
		}

	/*	for (int i = 0; i < y; i++) {
			printf("Car %d: initial velocity: %.2lf, final velocity: %.2lf, time: %.2lf\n", i, in_v[i], fin_v[i], time_s[i]);
		}*/

		double result[MAX_CARS] = { 0.0 };

		// --- Timing starts here ---
		LARGE_INTEGER freq, start, end;
		QueryPerformanceFrequency(&freq);   // ticks per second
		QueryPerformanceCounter(&start);

		for (int i = 0; i < y; i++) {
			result[i] = calc_accel(in_v[i], fin_v[i], time_s[i]);
		}

		QueryPerformanceCounter(&end);

		int accel[MAX_CARS] = { 0 };

		printf("\nThe integer acceleration values (m/s^2) are: \n");
		for (int i = 0; i < y; i++) {
			printf("%d:", i + 1);
			printf("%.2lf, ", result[i]);

			accel[i] = lf_to_int(result[i]);
			printf("%d\n", accel[i]);
		}

		calc_accel_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
		printf("\nTime taken to calculate acceleration for %d cars: %.6lf ms\n", (int)y, calc_accel_ms);

		//save_time(calc_accel_ms, k);
		/*k++;
	}*/

	return 0;
}