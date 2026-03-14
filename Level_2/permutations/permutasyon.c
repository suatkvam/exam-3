#include <unistd.h>
#include <stdio.h>

int ft_len(char *s)
{
	int i = 0;
	while(s[i])
		i++;
	return i;
}

void swap(char *s1, char *s2)
{
	char s3 = *s1;
	*s1 = *s2;
	*s2 = s3;
}

void sort(char *s, int len)
{
	for(int i = 0; i < len - 1; i++)
		for(int  j = 0; j < len - i - 1; j++)
			if(s[j] > s[j + 1])
				swap(&s[j],&s[j + 1]);
}

// sonraki permütasyonu hesapla (alfabetik sırada)
// yoksa 0 döndür (en son permütasyona ulaştık)
int next(char *s, int len)
{
	int i = len - 2;
	int j = len - 1;
	// sağdan sola: ilk azalan yeri bul
	while(i >= 0 && s[i] >= s[i + 1])
		i--;
	if(i < 0)
		return 0; // tamamen azalan sıra = son permütasyon
	// s[i]'den büyük en sağdaki elemanı bul, swap yap
	while(s[j] <= s[i])
		j--;
	swap(&s[i], &s[j]);
	// i'nin sağını ters çevir (küçükten büyüğe sırala)
	int left = i + 1;
	int right = len - 1;
	while(left < right)
		swap(&s[left++], &s[right--]);
	return 1;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		return 1;
	int i = 0;
	char s[10000];
	// argv[1]'i kopyala
	while(argv[1][i])
	{
		s[i] = argv[1][i];
		i++;
	}
	s[i] = '\0';
	int len = ft_len(s);
	sort(s, len);   // alfabetik ilk permütasyondan başla
	puts(s);
	while(next(s, len))  // sonraki permütasyon var mı → yazdır
		puts(s);
	return 0;
}