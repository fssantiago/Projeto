#include "Sorts.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int nrItems;
	int sortType;

	cin >> nrItems;
	cin >> sortType;

	vector<int> list;

	switch (sortType)
	{
	//InsertionSort
	//Best Case -> Já ordenado
	//Worst Case -> Ordenado de forma decrescente
	case 0:
		for (int i = nrItems; i > 0; i--)
			list.push_back(i);
		InsertionSort(&list);
		break;
	//SelectionSort
	//Ordenação de entrada não afeta o algoritmo pois sempre olha todos os itens em busca do maior para colocar na ultima posicao
	case 1:
		break;
	//BubbleSort
	//Best Case -> Já ordenado
	//Worst Case -> Ordenado de forma decrescente
	case 2:
		for (int i = nrItems; i > 0; i--)
			list.push_back(i);
		BubbleSort(&list);
		break;
	//MergeSort
	//Ordenação de entrada não afeta o algoritmo pois divide o array e vai comparando um a um, até preencher um terceiro array --true???
	case 3:
		break;
	//QuickSort --(voltar aqui)
	//Best Case -> Pivô divide sempre a lista no meio
	//Worst Case -> Pivô é o maior ou menor elemento
	case 4:
		for (int i = 1; i <= nrItems; i++)
			list.push_back(i);
		QuickSort(&list);
		break;
	//TreeSort
	case 5:
		break;
	//HeapSort
	case 6:
		break;
	//BucketSort
	case 7:
		break;
	//CountingSort
	case 8:
		break;
	//RadixSort
	case 9:
		break;
	default:
		break;
	}

	return 1;
}