#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

void setcolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
int InvMatrix(int n, const double* A, double* b)  
{
	double m;
	register int i, j, k;
	double* a = new double[n * n];

	if (a == NULL)
		return 0;
	for (i = 0; i < n * n; i++)
		a[i] = A[i];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			b[i * n + j] = (i == j) ? 1. : 0.;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (a[i * n + i] == 0.)
		{
			if (i == n - 1)
			{
				delete[] a;
				return 0;
			}
			for (k = 1; i + k < n; k++)
			{
				if (a[i * n + i + k] != 0.)
					break;
			}
			if (i + k >= n)
			{
				delete[] a;
				return 0;
			}
			for (j = 0; j < n; j++)
			{
				m = a[i * n + j];
				a[i * n + j] = a[(i + k) * n + j];
				a[(i + k) * n + j] = m;
				m = b[i * n + j];
				b[i * n + j] = b[(i + k) * n + j];
				b[(i + k) * n + j] = m;
			}
		}
		m = a[i * n + i];
		for (j = 0; j < n; j++)
		{
			a[i * n + j] /= m;
			b[i * n + j] /= m;
		}
		for (j = 0; j < n; j++)
		{
			if (i == j)
				continue;

			m = a[j * n + i];
			for (k = 0; k < n; k++)
			{
				a[j * n + k] -= a[i * n + k] * m;
				b[j * n + k] -= b[i * n + k] * m;
			}
		}
	}
	delete[] a;
	return 1;
}
int Det(int(*a)[3]) {
	double det;
	det = a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])
		- a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])
		+ a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);

	return det;
}
void print_zero_one() {
	int i, cnt = 1;
	while (cnt++ <= 200) {
		cnt % 2 == 0 ? setcolor(2, 0) : setcolor(8, 0);
		i = rand() % 2;
		printf("%d", i);
		if (cnt == 101)
			printf("\n");
	}
	printf("\n");
}
void print_title_explain() {
	setcolor(10, 0);
	printf("       ###########    #############   ###       ############  ####         ####      ########               \n");
	printf("      ####           ###        ##   ###     ###             ### ##      ##  ###   ###      ##              \n");
	printf("       ####         ###        ##   ###    ###              ###  ##    ##   ###   ###       ##              \n");
	printf("         ####      ###        ##   ###   ###      ######   ###    ##  ##   ###   ############               \n");
	printf("      ####        ###        ##   ###   ###         ###   ###      ##     ###   ###        ##               \n");
	printf("    ####         ###        ##   ###    ###        ##    ###             ###   ###        ##                \n");
	printf("  ###########   ###        ##   ###     ###########     ###             ###   ###        ##                 \n");setcolor(10, 0);
	printf("* Ver. 1.0");
	printf("\n* 2017113356 Kim Min sung");
	printf("\n* 2017116965 Jun geon min\n");
}

int main() {
	print_zero_one();
	print_title_explain();
	print_zero_one();
	char input[100]; char encrypt[100]; char output[100];
	double input_digit[10][10] = { 0 };  double output_digit[10][10] = { 0 };
	double in_deter_digit[10][10] = { 0 };  double out_deter_digit[10][10] = { 0 };
	double encrypt_digit[10][10] = { 0 };
	double key[10][10] = { {0,2,4,6,8,10,12,14,16,18},{-2,-4,-6,-8,-10,-12,-14,-16,-18,0},{4,6,8,10,12,14,16,18,0,2},{6,8,10,12,14,16,18,0,2,4},
						   {8,10,12,14,16,18,0,2,4,6},{-10,-12,-14,-16,-18,0,-2,-4,-6,-8},{12,14,16,18,0,2,4,6,8,10},{14,16,18,0,2,4,6,8,10,12},
						   {16,18,0,2,4,6,8,10,12,14},{-18,0,-2,-4,-6,-8,-10,-12,-14,-16} };
	double inverse_key[10][10];
	int det_key[3][3] = { {1,3,5},{-5,3,-1},{3,-1,5} };
	int i, j, k = 0,

	det = Det(det_key);
	InvMatrix(10, (double*)key, (double*)inverse_key);

	setcolor(10, 0); printf("\n\t[ Press letters to encrypt ]\n\n"); setcolor(15, 0);
	scanf_s("%[^.]", input, sizeof(input));
	//fgets(input, sizeof(input), stdin);	setcolor(10, 0);

	setcolor(4, 0); printf("\n\t[ Phase 1 ..... Initial input ]\n\n"); Sleep(1000);  setcolor(2, 0);
	while (true) {
		for (int i = 0;i < 10;i++) {
			for (int j = 0;j < 10;j++) {
				input_digit[i][j] = input[k];
				k++;
			}
		}
		for (i = 0;i < 10;i++) {
			for (j = 0;j < 10;j++) {
				printf("\t%6.1f", input_digit[i][j]);
				Sleep(10);
			}
			Sleep(10);
			printf("\n\n");
		}
		printf("\n");
		break;
	}
	setcolor(4, 0); printf("\n\t[ Phase 2 ..... Using determine ]\n\n"); Sleep(1000); setcolor(2, 0);
	while (true) {
		for (int i = 0;i < 10;i++) {
			for (int j = 0;j < 10;j++) {
				in_deter_digit[i][j] = input_digit[i][j] - det;
			}
		}
		for (i = 0;i < 10;i++) {
			for (j = 0;j < 10;j++) {
				printf("\t%6.1f", in_deter_digit[i][j]);
				Sleep(10);
			}
			Sleep(10);
			printf("\n\n");
		}
		printf("\n");
		break;
	}
	setcolor(4, 0); printf("\n\t[ Phase 3 ..... Using key matrix ]\n\n"); Sleep(1000); setcolor(2, 0);
	while (true) {
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				for (k = 0; k < 10; k++) {
					encrypt_digit[i][j] += key[i][k] * in_deter_digit[k][j];
				}
			}
		}
		for (i = 0;i < 10;i++) {
			for (j = 0;j < 10;j++) {
				printf("\t%5.1f", encrypt_digit[i][j] + -1 *(rand() % 10000) + 5000);
				Sleep(10);
			}
			Sleep(10);
			printf("\n\n");
		}
		printf("\n");
		break;
	}
	setcolor(4, 0); printf("\n\t[ Phase 4 ..... Using inverse key matrix ]\n\n"); Sleep(1000); setcolor(2, 0);
	while (true) {
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				for (k = 0; k < 10; k++) {
					out_deter_digit[i][j] += inverse_key[i][k] * encrypt_digit[k][j];
				}
			}
		}
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				printf("\t%6.1f", out_deter_digit[i][j]);
				Sleep(10);
			}
			Sleep(10);
			printf("\n\n");
		}
		printf("\n");
		break;
	}
	setcolor(4, 0); printf("\n\t[ Phase 5 ..... Using determine ]\n\n"); Sleep(1000); setcolor(2, 0);
	while (true) {
		k = 0;
		for (int i = 0;i < 10;i++) {
			for (int j = 0;j < 10;j++) {
				output_digit[i][j] = (out_deter_digit[i][j] + det);
			}
		}
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				printf("\t%6.1f", output_digit[i][j]);
				Sleep(10);
			}
			Sleep(10);
			printf("\n\n");
		}
		break;
	}
	setcolor(4, 0); printf("\n\t[ Phase 6 ..... Decoded output ]\n\n"); Sleep(1000); setcolor(2, 0);
	while (true) {
		printf("\t");
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				output[k] = output_digit[i][j] + 0.5;
				k++;
				setcolor(8, 0);
				printf(".");
				Sleep(20);
			}
		}
		break;
	}
	printf("\n\n"); setcolor(10, 0);
	printf("\t[ Your initial letter ] \n\n", output); setcolor(10, 0);
	setcolor(15, 0); Sleep(1000);
	i = 0;
	while (output[i]) {
		printf("%c", output[i]);
		Sleep(150);
		i++;
	}
	printf("\n\n");

	return 0;
}
