#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void ncc();

int main() {
	clock_t START, END;
	float total_time;
	START = clock();
	ncc();
	END = clock();
	total_time = (float)(END - START) / CLOCKS_PER_SEC;

	printf("Time : %f sec \n", total_time);
	system("PAUSE");
	return 0;
}

void ncc() {
	FILE *source, *target;
	source = fopen("source_block_1.txt", "rt");
	target = fopen("target_search_window.txt", "rt");
	int s[160][192];
	int t[480][640];
	int i, j, right = 0, down = 0, max, x = 0, y = 0;
	double sigma_s, sigma_t, sigma_s_t, sigma_t_t, s_bar, t_bar, NCC, n, num, den;

	for (i = 0; i <= 159; i++) {
		for (j = 0; j <= 191; j++) {
			fscanf(source, "%d", &s[i][j]);
		}
	}
	for (i = 0; i <= 479; i++) {
		for (j = 0; j <= 639; j++) {
			fscanf(target, "%d", &t[i][j]);
		}
	}
	n = 192 * 160;
	for (right = 0; right <= 320; right++) {
		for (down = 0; down <= 448; down++) {
			for (i = 0; i <= 159; i++) {
				for (j = 0; j <= 191; j++) {
					sigma_s_t = sigma_s_t + s[i][j] * t[i + right][j + down];
					sigma_s = sigma_s + s[i][j];
					sigma_t = sigma_t + t[i + right][j + down];
					sigma_t_t = sigma_t_t + t[i + right][j + down] * t[i + right][j + down];
				}
			}
			s_bar = sigma_s / n;
			t_bar = sigma_t / n;

			num = (sigma_s_t - n * s_bar * t_bar) * (sigma_s_t - n * s_bar * t_bar);
			den = sigma_t_t - n * t_bar * t_bar;
			NCC = num / den;
			sigma_s_t = 0; sigma_s = 0; sigma_t = 0; s_bar = 0; t_bar = 0; sigma_t_t = 0;

			if (NCC > max) {
				max = NCC;
				x = right;
				y = down;
			}

		}
	}
	printf("NCC max = ( %d , %d )\n", x, y);
}
