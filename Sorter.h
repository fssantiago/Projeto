#ifndef SORTER_H 
#define SORTER_H
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>

//Pior Caso: O(n²)
//Melhor Caso: O(n)
template <class object> void InsertionSort(object *content)
{
	int nrItens = size((*(content)));
	int j = 0;

	for (int i = 1; i < nrItens; i++)
	{
		j = i - 1;
		while (j >= 0 && (*(content))[j] >(*(content))[j + 1])
		{
			swap((*(content))[j], (*(content))[j + 1]);
			j--;
		}
	}
}

//Melhor Caso: O(n²)
//Pior Caso: O(n²)
template <class object> void SelectionSort(object *content)
{
	int nrItens = size((*(content)));
	int maxElemPos;

	for (int i = nrItens - 1; i >= 1; i--)
	{
		maxElemPos = 0;
		for (int j = 0; j <= i; j++)
			if ((*(content))[maxElemPos] < (*(content))[j])
				maxElemPos = j;

		swap((*(content))[i], (*(content))[maxElemPos]);
	}
}

//Melhor Caso: O(n)
//Pior Caso: O(n²)
template <class object> void BubbleSort(object *content)
{
	int nrItens = size((*(content)));

	for (int i = nrItens - 1; i >= 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if ((*(content))[j] >(*(content))[j + 1])
				swap((*(content))[j], (*(content))[j + 1]);
		}
	}
}

//Melhor Caso: O(n)
//Pior Caso: O(n²)
template <class object> void MergeSort(object *content)
{
	MergeSort(content, 0, size((*(content))) - 1);	
}
template <class object> void MergeSort(object *content, int low, int high)
{
	int middle;
	if (low < high)
	{
		middle = (low + high) / 2;

		MergeSort(content, low, middle);
		MergeSort(content, middle + 1, high);
		Merge(content, (*(content))[0], low, middle, high);
	}
}
template <class object, class type> void Merge(object *content, type value, int low, int middle, int high)
{
	map<int, type> aux;
	int i = low, k = low, j = middle + 1;

	while (i <= middle && j <= high)
	{
		if ((*(content))[i] < (*(content))[j])
		{
			aux[k] = (*(content))[i];
			k++;
			i++;
		}
		else
		{
			aux[k] = (*(content))[j];
			k++;
			j++;
		}
	}

	while (i <= middle)
	{
		aux[k] = (*(content))[i];
		k++;
		i++;
	}

	while (j <= high)
	{
		aux[k] = (*(content))[j];
		k++;
		j++;
	}

	for (i = low; i < k; i++)
	{
		(*(content))[i] = aux[i];
	}
}

//Melhor Caso: O(n log n)
//Pior Caso: O(n²)
template <class object> void QuickSort(object *content)
{
	QuickSort(content, (*(content))[0], 0, size((*(content))) - 1);
}
template <class object, class type> void QuickSort(object *content, type value, int begin, int end)
{
	type pivot;
	int inf, sup;
	if (begin < end)
	{
		pivot = (*(content))[(begin + end) / 2];
		Partition(content, begin, end, pivot, &inf, &sup);
		
		QuickSort(content, pivot, begin, sup);
		QuickSort(content, pivot, inf, end);
	}
}
template <class object, class type> void Partition(object *content, int begin, int end, type pivot, int *i, int *j)
{
	*i = begin;
	*j = end;
	
	while (*i <= *j)
	{
		while ((*(content))[*i] < pivot)
			(*i)++;
		while ((*(content))[*j] > pivot)
			(*j)--;
		if (*i <= *j)
		{
			swap((*(content))[*i], (*(content))[*j]);
			(*i)++;
			(*j)--;
		}
	}
}

//
template <class object> void TreeSort(object *content)
{
	int nrItens = size((*(content)));

	//Assume: |B| ? N
	//Garante: B[i] ? B[i+1] ? 1 ? i < N 
	var T: ArvoreBalanceada<Inteiro, Inteiro>     
		i, ProxPos: Inteiro 
		
	Constroi(T) 
	para i ? 1 até N faça
		Insere(T, B[i], B[i])

	ProxPos ? 1
	Escreve(T.Raiz, B, ProxPos)
	Destroi(T)
}

//Melhor Caso: O(n log n)
//Pior Caso: O(n log n)
template <class object> void HeapSort(object *content)
{
	int nrItens = size((*(content)));

	for (int i = ((nrItens / 2) - 1); i >= 0; i--)
		MaxHeapify(content, i, nrItens);

	for (int i = nrItens-1; i >= 0; i--)
	{
		swap((*(content))[i], (*(content))[0]);
		MaxHeapify(content, 0, --nrItens);
	}
}
template<class object> void MaxHeapify(object *content, int position, int nrItens)
{
	int max = (2 * position) + 1;

	if (max < nrItens)
	{
		if ((max + 1) < nrItens && (*(content))[max] < (*(content))[max + 1])
			++max;

		if ((*(content))[max] > (*(content))[position])
		{
			swap((*(content))[max], (*(content))[position]);
			MaxHeapify(content, max, nrItens);
		}
	}
}

//Melhor Caso: O(n + k)
//Pior Caso: O(n²)
template <class object> void BucketSort(object *content)
{
	BucketSort(content, (*(content))[0]);
}
template <class object, class type> void BucketSort(object *content, type value)
{
	int nrItens = size((*(content)));
	map<type, int> buckets;

	for (int i = 0; i < nrItens; i++)
		buckets[(*(content))[i]]++;

	int i = 0;
	for (int j = 0; j < buckets.size(); j++)
		for (int k = buckets[j]; k > 0; k--)
			(*(content))[i++] = j;
}

//Melhor Caso: O(n + k)
//Pior Caso: O(n + k)
//Obs.:k representa o maior item presente no vetor.
template <class object> void CountingSort(object *content)
{
	CountingSort(content, (*(content))[0]);
}
template <class object, class type> void CountingSort(object *content, type value)
{
	int nrItens = size((*(content)));
	map<int, type> output;
	map<type, int> count;

	for (int i = 0; i < nrItens; i++)
		count[(*(content))[i]]++;

	int aux = 0;
	for (map<type, int>::iterator it = count.begin(); it != count.end(); ++it)
	{
		count[it->first] += aux;
		aux = it->second;
	}

	for (int i = 0; i < nrItens; i++)
	{
		output[count[(*(content))[i]] - 1] = (*(content))[i];
		count[(*(content))[i]]--;
	}

	for (int i = 0; i < nrItens; i++)
		(*(content))[i] = output[i];
}

//
template <class object> void RadixSort(object *content)
{
	if(typeid((*(content))[0]) != typeid(string))
		RadixSort(content, (*(content))[0]);
	else
	{
		int x = 0;
	}
}
template <class object, class type> void RadixSort(object *content, type value)
{
	int nrItens = size((*(content)));
	type max = (*(content))[0];
	map<int, type> aux;
	int exp = 1;

	for (int i = 0; i < nrItens; i++)
	{
		if ((*(content))[i] > max)
			max = (*(content))[i];
	}

	while (max / exp > 0)
	{
		type bucket[30] = { 0 };
		for (int i = 0; i < nrItens; i++)
			bucket[((*(content))[i] / exp) % 10]++;
		for (int i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (int i = nrItens - 1; i >= 0; i--)
			aux[--bucket[((*(content))[i] / exp) % 10]] = (*(content))[i];
		for (int i = 0; i < nrItens; i++)
			(*(content))[i] = aux[i];
		exp *= 10;
	}
}

#endif 