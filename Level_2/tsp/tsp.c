#include<math.h>
#include<stdio.h>

// tüm veriyi tek struct'ta tutuyoruz — parametre sayısını azaltmak için
typedef struct s_tsp
{
	float cities[12][2]; // şehir koordinatları [x][y]
	int visited[12];     // hangi şehri ziyaret ettik
	int city_count;        // toplam şehir sayısı
	float min_distans;           // şu ana kadar bulunan en kısa yol
} t_tsp;

// iki şehir arası öklid mesafesi: √((x2-x1)² + (y2-y1)²)
float distance(float cities[][2],int a, int b)
{
	float dx = cities[a][0] - cities[b][0];
	float dy = cities[a][1] - cities[b][1];
	return sqrtf(dx * dx + dy * dy);
}

// idx: kaçıncı şehri seçiyoruz | last: bir önceki şehir | dist: şu anki toplam mesafe
void tsp(t_tsp *data, int idx, int last, float dist)
{
	// BASE CASE: tüm şehirleri ziyaret ettik
	if(idx == data->city_count)
	{
		dist += distance(data->cities, last, 0); // başlangıca (0. şehir) dön
		if(dist < data->min_distans)
			data->min_distans = dist; // daha kısa yol bulduk, güncelle
		return ;
	}
	int i = 0;
	while(i < data->city_count)
	{
		if(!data->visited[i])
		{
			data->visited[i] = 1;                                           // ZİYARET ET
			tsp(data, idx + 1, i, dist + distance(data->cities, last, i)); // İLERLE
			data->visited[i] = 0;                                           // GERİ AL (backtrack)
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_tsp data = {0};
	FILE *input = stdin;

	if (argc > 1)
	{
		input = fopen(argv[1], "r");
		if (!input)
		{
			fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
			return 1;
		}
	}
	// "x, y" formatında şehirleri oku
	while(fscanf(input, "%f, %f\n",
		&data.cities[data.city_count][0],
		&data.cities[data.city_count][1]) == 2)
	{
		data.city_count++;
	}

	if (argc > 1)
		fclose(input);
	if (data.city_count == 0)
	{
		printf("0.00\n");
		return 0;
	}
	
	data.min_distans = 1e9;      // başlangıç minimumu: çok büyük sayı
	data.visited[0] = 1; // 0. şehirden başlıyoruz, ziyaret ettik say
	tsp(&data, 1, 0, 0);
	printf("%.2f\n",data.min_distans);
	return 0;
} 
