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
	case 0:
		for (int i = nrItems; i > 0; i--)
			list.push_back(i);
		InsertionSort(&list);
		break;
	//SelectionSort - (Tanto faz a arrumacao pois sempre olha todos os itens em busca do maior para colocar na ultima posicao)
	case 1:
		break;
	//BubbleSort
	case 2:
		for (int i = nrItems; i > 0; i--)
			list.push_back(i);
		BubbleSort(&list);
		break;
	//MergeSort - (Tanto faz pois divide o array e vai comparando um a u, até preencher um terceiro array)
	case 3:
		break;
	//QuickSort
	case 4:
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