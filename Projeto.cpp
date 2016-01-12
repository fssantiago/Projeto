#include <vector>
#include <numeric>
#include <ctime>
#include <iterator>

#include <map>
#include <cstdlib>
#include <iostream>

using namespace std;

void ShowTree(vector<vector<bool>> tree)
{
	for each (vector<bool> row in tree)
	{
		for each (bool cell in row)
		{
			cout << (int)cell << " ";
		}
		cout << "\n";
	}
}

void GenerateTrees(int nrNodes, bool isomophic)
{
	if (nrNodes < 2)
		throw new exception("Number of nodes minimum is 2.");

	//Estrutura de arvore
	vector<vector<bool>> treeOne(nrNodes, vector<bool>(nrNodes)), treeTwo(nrNodes, vector<bool>(nrNodes));

	//Cria arvore
	//nrNodes-1 pq o último vértice é a raiz e não aponta pra ninguem
	srand(time(NULL));
	for (int i = 0; i < nrNodes - 1; i++)
	{
		int row = (i + 1) + (rand() % (nrNodes - (i + 1)));
		treeOne[row][i] = 1;
	}

	//Cria o segundo grafo igual ao primeiro
	treeTwo = treeOne;

	//Move uma folha da segunda arvore caso não sejam isomorfas
	if (!isomophic)
	{
		for (int i = 0; i < nrNodes; i++)
		{
			//Se a linha é vazia então é folha
			if (!accumulate(treeOne[i].begin(), treeOne[i].end(), 0))
			{
				for (int j = 0; j < nrNodes; j++)
				{
					//Altera o pai da folha
					if (treeTwo[j][i] == 1)
					{
						treeTwo[j][i] = 0;
						int newLine = nrNodes - j != j ? nrNodes - j : j + 1;
						treeTwo[newLine][i] = 1;
						
						j = nrNodes;
					}
				}
				i = nrNodes;
			}
		}
	}
	else
	{
		vector<int> leaves;
		for (int i = 0; i < nrNodes; i++)
		{
			if (!accumulate(treeOne[i].begin(), treeOne[i].end(), 0))
				leaves.push_back(i);
		}

		//Caso tenha achado mais de uma folha inverte as posições delas
		if (leaves.size() > 1)
		{
			for (int i = 0; i < nrNodes; i++)
				swap(treeTwo[i][leaves[0]], treeTwo[i][leaves[1]]);
		}
		//Senão troca de lugar com o pai
		else
		{
			int up = -1;

			//Encontra o pai da folha
			for (int i = 0; i < nrNodes; i++)
			{
				if (treeTwo[i][leaves[0]] == 1)
				{
					up = i;
					i = nrNodes;
				}
			}

			//Encontra o pai do pai da folha e faz as alterações
			for (int i = 0; i < nrNodes; i++)
			{
				if (treeTwo[i][up] == 1)
				{
					treeTwo[i][leaves[0]] = 1;
					treeTwo[i][up] = 0;

					treeTwo[leaves[0]][up] = 1;
					treeTwo[up][leaves[0]] = 0;

					i = nrNodes;
				}
			}
		}
	}
	ShowTree(treeOne);
	cout << "\n\n";
	ShowTree(treeTwo);
}



/*bool isIsomorphic(vector<dynamic_bitset<>> T1, vector<dynamic_bitset<>> T2)
{
	//Estrutura lista Nó/Level
	map<int, int> helper1;
	map<int, int> helper2;

	if (T1.size() != T2.size())
		return false;

	for (int i = 0; i < T1.size(); i++)
	{
		//Se ninguem aponta pra esse nó então é folha
		if (!T1[i].any())
			helper1[i] = 0;
		if(!T2[i].any())
			helper2[i] = 0;
	}

	//for all leves
	//if (helper1[T1.root] == helper2[T2.root])
		return true;

	return false;
}*/

int main()
{
	GenerateTrees(6, true);

    return 0;
}