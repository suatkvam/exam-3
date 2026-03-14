#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void print_sol(int *queens, int n)
{
	int i = 0;
	while(i < n)
	{
		printf("%d",queens[i] + 1);
		if(i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

// önceki queen'lerle çakışıyor mu? aynı satır, sol-üst çapraz, sol-alt çapraz
int is_safe(int *queens, int col, int row)
{
	int i = 0;
	while(i < col)
	{
		if(queens[i] == row)                 // aynı satırda
			return 0;
		if((queens[i] - row) == (i - col))  // sol-üst çapraz
			return 0;
		if((queens[i] - row) == -(i - col)) // sol-alt çapraz
			return 0;
		i++;
	}
	return 1;
}

// col: hangi sütuna queen koyuyoruz (0'dan başlar)
void my_queen(int *queens, int col, int n)
{
	// BASE CASE: tüm sütunlar doldu → yazdır
	if(col == n)
	{
		print_sol(queens, n);
		return;
	}
	int row = 0;
	while(row < n)
	{
		if(is_safe(queens, col, row))
		{
			queens[col] = row;          // YERLEŞTİR
			my_queen(queens, col + 1, n);  // sonraki sütuna geç
			// geri alma implicit: queens[col] üzerine yazılacak
		}
		row++;
	}
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("+0\n");
		return 1;		
	}
	int n = atoi(argv[1]);
	if(n < 4)
	{
		printf("+0\n");
		return 1;
	}
	int queens[20];
	my_queen(queens,0,n);
	return 0;
}