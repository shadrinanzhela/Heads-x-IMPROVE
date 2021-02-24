#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

 

int compare_even(int* a, int* b)//for even numbers
{
	return(*a - *b);
}
	
int compare_odd(int* a, int* b) //for odd numbers
{
	return(*b - *a);
}

int** func_random_arrays(int n) //функция возвращает массив указателей на отсортированные массивы, в первой ячейке которых хранится длины
{
	srand(time(NULL));

	if (n >= RAND_MAX) //не найдется n различных рандомных чисел, если n будет больше, чем максимально возможное рандомное число
	{
		return(NULL);
	}
	
	int** arr = (int**)malloc(sizeof(int*) * n);    
	int* ver = (int*)malloc(sizeof(int) * (RAND_MAX + 2)); //массив в котором будет храниться информация о уже использованных размерах массивов
	for (int i = 0; i < (RAND_MAX + 2); i++)
		ver[i] = 0;

	int size;
	for (int i = 0; i < n; i++)
	{
		size = rand() + 1; // генерация новой длины
		while (ver[size]) 
			size = rand() + 1; 
		ver[size] = 1; 

		arr[i] = (int*)malloc(sizeof(int) * (size + 1)); //выделение и заполнение массива
		arr[i][0] = size; //храним в arr[i][0] длинну массива, сам массив заполняется и сортируется с arr[i][1] элемента
		int* arr_el = arr[i] + 1; 
		for (int j = 0; j < size; j++) 
			arr_el[j] = rand();

		if (i & 1)//  сортировка в зависимотсти от четности
			qsort(arr_el, size, sizeof(int), compare_odd);
		else
			qsort(arr_el, size, sizeof(int), compare_even);
	}

	free(ver);
	return(arr);
}

int main()
{
	FILE* fw;
	fopen_s(&fw, "output.txt", "w");

	printf("Entrer n please\n");
	int n;
	scanf("%d", &n);
	int** arr = func_random_arrays(n);
	if (arr == NULL) //проверка на слишком большое n
		while (!arr)
		{
			printf("Value should not exceed, if you want exit program enter '-1'\n", RAND_MAX);
			scanf("%d", &n);
			if (n < 0)
				return(0);
			arr = func_random_arrays(n);
		}
	
	for (int i = 0; i < n; i++)//вывод массивов в output.txt
	{
		for (int j = 1; j < arr[i][0]; j++)
			fprintf(fw, "%d ", arr[i][j]);
		fprintf(fw, "\n");
	}
	
	//запрос на вывод и вывод массивов в консоль 
	printf("Look at the arrays in the file 'output.txt' please, if you want to output them to the console enter 'yes' else 'no'\n");
	char str[4];
	scanf("%s", str); 
	int flag = 1;
	while (flag)
	{
		if ((str[0] == 'y') || (str[0] == 'Y')) 
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 1; j < arr[i][0]; j++)
					printf("%d ", arr[i][j]);
				printf("\n");
			}
			flag = 0;
		}
		else
			if (!((str[0] == 'n') || (str[0] == 'N')))
			{
				printf("Sorry, I don't understud you, repeat please\n");
				scanf("%s", str);
			}
			else
				flag = 0;
	}

	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
	fclose(fw);
	return(0);
}