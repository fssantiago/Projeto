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
	//Insertion
	case 0:
		for (int i = nrItems; i > 0; i--)
			list.push_back(i);
		InsertionSort(&list);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

	Tree x = Tree(nrNodes);
	Tree y = isomorphic ? x.GenerateIsomorphic() : x.GenerateNonIsomorphic();

	if (IsIsomorphic(&x, &y) != isomorphic)
		return 1;
	else
		return 0;
}