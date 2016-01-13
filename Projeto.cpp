#include <map>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

#pragma region Node

//Estrutura "Nó" que guarda seu pai e seus filhos
struct Node {
	int UpWard;
	vector<int> DownWard;
};

#pragma endregion

#pragma region Tree

class Tree {
public:
	map<int, Node> Nodes;
public:
	Tree(int nrNodes);
	Tree GenerateIsomorphic();
	Tree GenerateNonIsomorphic();
};

Tree::Tree(int nrNodes)
{
	if (nrNodes < 2)
		throw new exception("Number of nodes minimum is 2.");

	//Cria arvore
	srand(time(NULL));
	for (int i = 1; i < nrNodes; i++)
	{
		//Gera um número aleatório maior que o atual e menor ou igual ao número de nós
		int upWard = (i + 1) + (rand() % (nrNodes - i));

		Nodes[i].UpWard = upWard;
		Nodes[upWard].DownWard.push_back(i);
	}
}
Tree Tree::GenerateIsomorphic()
{
	Tree newTree(Nodes.size());
	newTree.Nodes = Nodes;

	vector<int> leaves;

	for (int i = 1; i <= newTree.Nodes.size(); i++)
	{
		if (newTree.Nodes[i].DownWard.size() == 0)
			leaves.push_back(i);

		if (leaves.size() > 1)
			i = newTree.Nodes.size() + 1;
	}

	int aux = 0;
	//Caso tenha achado mais de uma folha inverte as posições delas
	if (leaves.size() > 1)
	{
		aux = newTree.Nodes[leaves[0]].UpWard;
		newTree.Nodes[leaves[0]].UpWard = newTree.Nodes[leaves[1]].UpWard;
		newTree.Nodes[leaves[1]].UpWard = aux;
	}
	//Senão troca de lugar com o pai
	else
	{
		aux = newTree.Nodes[leaves[0]].UpWard;
		
		//Aponta o filho para o avô e adiciona o pai na lista de filhos
		newTree.Nodes[leaves[0]].UpWard = newTree.Nodes[aux].UpWard;
		newTree.Nodes[leaves[0]].DownWard.push_back(aux);
		
		//Aponta o ex-pai pro filho e limpa a lista de filhos dele
		newTree.Nodes[aux].UpWard = leaves[0];
		newTree.Nodes[aux].DownWard.clear();
	}

	return newTree;
}
Tree Tree::GenerateNonIsomorphic()
{
	if (Nodes.size() < 3)
		throw new exception("Impossible to create a non isomorphic tree.");

	Tree newTree(Nodes.size());
	newTree.Nodes = Nodes;

	int newUpWard = newTree.Nodes[1].UpWard;
	
	srand(time(NULL));
	while (newUpWard == newTree.Nodes[1].UpWard)
		newUpWard = 2 + (rand() % (newTree.Nodes.size() - 1));
	 
	newTree.Nodes[1].UpWard = newUpWard;

	return newTree;
}

#pragma endregion

/*
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

*/

void AssignLeves(map<int, int> list) 
{
	for (map<int, int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		//it->second.Method();
	}
}

bool IsIsomorphic(Tree treeOne, Tree treeTwo)
{
	//Se o número de nós for diferente retorna falso logo
	if (treeOne.Nodes.size() != treeTwo.Nodes.size())
		return false;
	
	//Estrutura lista Nó/Level
	map<int, int> listOne;
	map<int, int> listTwo;

	for (int i = 1; i <= treeOne.Nodes.size(); i++)
	{
		//Definindo level 0 para todas as folhas
		if (treeOne.Nodes[i].DownWard.size() == 0)
			listOne[i] = 0;
		if(treeTwo.Nodes[i].DownWard.size() == 0)
			listTwo[i] = 0;
	}

	//for all leves
	//if (helper1[T1.root] == helper2[T2.root])
		return true;

	return false;
}

int main()
{
	try
	{
		Tree x(3);
		Tree y = x.GenerateNonIsomorphic();

		return 0;
	}
	catch (exception e)
	{
		cout << e.what();
		return 404;//Page not found xD
	}
}