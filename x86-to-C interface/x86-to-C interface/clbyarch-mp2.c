#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX_CARS 10000

extern int lf_to_int(double lf);
extern double calc_accel(double in_v, double fin_v, double time);

int main() {
	double y = 0.0;
	double in_v[MAX_CARS] = { 0.0 };
	double fin_v[MAX_CARS] = { 0.0 };
	double time[MAX_CARS] = { 0.0 };

	printf("Enter the amount of cars: ");
	scanf_s("%lf", &y);

	printf("Enter the initial velocity, final velocity, and time of each car: \n");
	for (int i = 0; i < y; i++) {
		scanf_s("%lf, ", &in_v[i]);
		scanf_s("%lf, ", &fin_v[i]);
		scanf_s("%lf", &time[i]);
	}

	double result[MAX_CARS] = { 0.0 };
	for (int i = 0; i < y; i++) {
		result[i] = calc_accel(in_v[i], fin_v[i], time[i]);
	}

	int accel[MAX_CARS] = { 0 };

	printf("\nThe integer acceleration values (m/s^2) are: \n");
	for (int i = 0; i < y; i++) {
		accel[i] = lf_to_int(result[i]);
		printf("%d\n", accel[i]);

	}

	return 0;
}