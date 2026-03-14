#include <unistd.h>
#include <stdio.h>

// minimum kaç parantez silmem gerekiyor?
// eşleşmeyen ')' → count, açık kalan '(' → balance
// örnek: "( ( )" → balance=1, count=0 → 1 silmek yeterli
int min_remove(char *s)
{
	int balance = 0;
	int count = 0;
	int i = 0;
	while(s[i])
	{
		if(s[i] == '(') 
			balance++;
		if(s[i] == ')') 
			balance--;
		if(balance < 0)       // eşleşmeyen ')' bulduk
		{
			count++;
			balance = 0;
		}
		i++;
	}
	return count + balance;   // count: fazla ')' | balance: açık kalan '('
}

// i: string'de hangi karakterdeyiz
// balance: şu ana kadar açık olan '(' sayısı
// removed: kaç tane sildik | min: minimum silmemiz gereken sayı
void rip(char *s, int i, int balance, int removed, int min)
{
	// BASE CASE: string bitti
	if(!s[i])
	{
		if(balance == 0 && removed == min) // dengeli + minimum silindi
			puts(s);
		return;
	}
	char c = s[i];
	if(c == '(' || c == ')')
	{
		// SEÇİM 1: SİL → space yaz, removed+1, balance değişmez
		s[i] = ' ';
		rip(s, i + 1, balance, removed + 1, min);

		// SEÇİM 2: KORU → orijinal char'ı geri al (backtrack), balance güncelle
		s[i] = c;
		if(c == '(')
			rip(s, i + 1, balance + 1, removed, min);
		else if(balance > 0)              // ')' tutmak için balance > 0 şart
			rip(s, i + 1, balance - 1, removed, min);
	}
	else
		rip(s, i + 1, balance, removed, min); // space → olduğu gibi geç
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		return 1;
	int min = min_remove(argv[1]); // önce minimum silme sayısını hesapla
	rip(argv[1], 0, 0, 0, min);
	return 0;
}