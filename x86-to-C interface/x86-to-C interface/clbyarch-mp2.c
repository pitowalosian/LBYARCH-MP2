#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_CARS 9000
#define MAX_TEST 30

extern int lf_to_int(double lf);
extern double calc_accel(double in_v, double fin_v, double time);

void save_time(int calc_accel_ms[], int test_number) {
	FILE* file = fopen("9000_time.txt", "a"); // Open in append mode

	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}

	fprintf(file, "%d\n", calc_accel_ms[test_number]);

	fclose(file);
}

double calc_accel_c(double in_v, double fin_v, double time) {
	double diff = fin_v - in_v;
	double accel = diff * 1000.0 * 1 / 3600 / time; // Convert km/h to m/s and divide by time

	return accel;
}

int main() {
	srand((unsigned int)time(NULL)); // Seed the random number generator

	int k = 0;
	int calc_accel_ms[MAX_TEST];

	while (k != 30) {
		printf("\nTest %d:\n", k + 1);
		double y = 0.0;
		double in_v[MAX_CARS] = { 0.0 };
		double fin_v[MAX_CARS] = { 0.0 };
		double time_s[MAX_CARS] = { 0.0 };

		/*printf("Enter the amount of cars: ");
		scanf_s("%lf", &y);*/

		y = MAX_CARS;
		int int_y = lf_to_int(y); // Convert to integer

		//printf("Enter the initial velocity, final velocity, and time of each car: \n");
		for (int i = 0; i < int_y; i++) {
			/*scanf_s("%lf, ", &in_v[i]);
			scanf_s("%lf, ", &fin_v[i]);
			scanf_s("%lf", &time_s[i]);*/

			in_v[i] = (double)rand() / RAND_MAX * 100.0; // Random initial velocity between 0 and 100 km/h
			fin_v[i] = (double)rand() / RAND_MAX * 200.0; // Random final velocity between 0 and 200 km/h
			time_s[i] = (double)rand() / RAND_MAX * 15.0; // Random time between 0 and 15s
		}

		/*for (int i = 0; i < y; i++) {
			printf("Car %d: initial velocity: %.2lf, final velocity: %.2lf, time: %.2lf\n", i, in_v[i], fin_v[i], time_s[i]);
		}*/

		double result[MAX_CARS] = { 0.0 };

		// --- Timing starts here ---
		LARGE_INTEGER freq, start, end;
		QueryPerformanceFrequency(&freq);   // ticks per second
		QueryPerformanceCounter(&start);

		for (int i = 0; i < int_y; i++) {
			result[i] = calc_accel(in_v[i], fin_v[i], time_s[i]);
		}

		QueryPerformanceCounter(&end);

		int accel[MAX_CARS] = { 0 };

		printf("\nThe integer acceleration values (m/s^2) are: \n");
		for (int i = 0; i < int_y; i++) {
			printf("Car %d: ", i + 1);

			accel[i] = lf_to_int(result[i]);
			printf("%d m/s^2\n", accel[i]);
		}

		calc_accel_ms[k] = (end.QuadPart - start.QuadPart) * 1e9 / freq.QuadPart;
		printf("\nTime taken to calculate acceleration for %d cars: %d ns\n", int_y, calc_accel_ms[k]);

		save_time(calc_accel_ms, k);
		k++;
	}

	return 0;
}