#include "powerset.h"

void print_sol(int *arr, int n)
{
	int i = 0;
	while(i < n)
	{
		printf("%d", arr[i]);
		if(i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

// idx: dizide hangi elemana bakıyoruz
void power_set(t_power *set, int idx)
{
	// BASE CASE: tüm elemanları gezdik
	if(idx == set->size)
	{
		int i = 0;
		int sum = 0;
		while(i < set->sub_size) // subset'in toplamını hesapla
		{
			sum += set->subset[i];
			i++;
		}
		if(sum == set->total_sum) // toplam == hedef → yazdır
			print_sol(set->subset, set->sub_size);
		return;
	}
	set->subset[set->sub_size] = set->arr[idx];
	set->sub_size++;
	power_set(set,idx + 1); // SEÇİM 1: AL (sub_size arttı)
	set->sub_size--;
	power_set(set, idx + 1); // SEÇİM 2: ALMA (sub_size geri döndü = backtrack)
}

int main(int argc, char *argv[])
{
	if(argc < 2)
		return 1;
	int  i = 0;
	int arr[argc];
	t_power set;
	set.total_sum = atoi(argv[1]);
	set.size = argc - 2;
	set.sub_size = 0;
	while(i < set.size)
	{
		arr[i] = atoi(argv[i + 2]);
		i++;
	}
	set.arr = arr;
	power_set(&set, 0);
	return 0;
}
