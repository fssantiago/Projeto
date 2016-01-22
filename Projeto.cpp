#include <map>
#include <set>
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;

#pragma region Node

//Estrutura "Nó" que guarda o endereço de seu pai e seus filhos
struct Node {
	int Number = 0;
	Node* UpWard;
	vector<Node*> DownWard;
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
		Nodes[i].Number = i;
		Nodes[i].UpWard = &Nodes[upWard];
		Nodes[upWard].DownWard.push_back(&Nodes[i]);
	}

	Nodes[nrNodes].Number = nrNodes;
}
Tree Tree::GenerateIsomorphic()
{
	Tree newTree(Nodes.size());
	for (int i = 1; i <= Nodes.size(); i++)
	{
		if(i != Nodes.size())
			newTree.Nodes[i].UpWard = &newTree.Nodes[Nodes[i].UpWard->Number];

		newTree.Nodes[i].DownWard.clear();
		for each (Node* node in Nodes[i].DownWard)
			newTree.Nodes[i].DownWard.push_back(&newTree.Nodes[node->Number]);
	}

	vector<Node*> leaves;

	for (int i = 1; i <= newTree.Nodes.size(); i++)
	{
		if (newTree.Nodes[i].DownWard.size() == 0)
			leaves.push_back(&newTree.Nodes[i]);

		if (leaves.size() > 1)
			i = newTree.Nodes.size() + 1;
	}

	//Caso tenha achado mais de uma folha inverte as posições delas
	if (leaves.size() > 1)
	{
		int pos = 0;
		vector<Node*>::iterator it;
		
		//Guarda os pais das folhas
		Node* upOne = leaves[0]->UpWard;
		Node* upTwo = leaves[1]->UpWard;

		//Troca os pais
		leaves[0]->UpWard = upTwo;
		leaves[1]->UpWard = upOne;

		//Remove folha1 do seu pai antigo
		it = find(upOne->DownWard.begin(), upOne->DownWard.end(), leaves[0]);
		pos = distance(upOne->DownWard.begin(), it);
		upOne->DownWard.erase(upOne->DownWard.begin() + pos);

		//Remove folha2 do seu pai antigo
		it = find(upTwo->DownWard.begin(), upTwo->DownWard.end(), leaves[1]);
		pos = distance(upTwo->DownWard.begin(), it);
		upTwo->DownWard.erase(upTwo->DownWard.begin() + pos);

		//Realoca as folhas certas
		upOne->DownWard.push_back(leaves[1]);
		upTwo->DownWard.push_back(leaves[0]);

	}
	//Senão troca de lugar com o pai
	else
	{
		//Recebe o pai da folha
		Node* aux = leaves[0]->UpWard;
		
		//Aponta o filho para o avô e adiciona o pai na lista de filhos
		leaves[0]->UpWard = aux->UpWard;
		leaves[0]->DownWard.push_back(aux);
		
		//Aponta o ex-pai pro filho e limpa a lista de filhos dele
		aux->UpWard = leaves[0];
		aux->DownWard.clear();
	}

	return newTree;
}
Tree Tree::GenerateNonIsomorphic()
{
	if (Nodes.size() < 3)
		throw new exception("Impossible to create a non isomorphic tree.");

	Tree newTree(Nodes.size());
	for (int i = 1; i <= Nodes.size(); i++)
	{
		if (i != Nodes.size())
			newTree.Nodes[i].UpWard = &newTree.Nodes[Nodes[i].UpWard->Number];

		newTree.Nodes[i].DownWard.clear();
		for each (Node* node in Nodes[i].DownWard)
			newTree.Nodes[i].DownWard.push_back(&newTree.Nodes[node->Number]);
	}


	if (newTree.Nodes[1].UpWard != &newTree.Nodes[newTree.Nodes.size()])
	{
		//Posso remover o primeiro filho porque o nó 1 é o primeiro a ser criado e consequentemente será sempre o primeiro da lista
		newTree.Nodes[1].UpWard->DownWard.erase(newTree.Nodes[1].UpWard->DownWard.begin());
		newTree.Nodes[newTree.Nodes.size()].DownWard.push_back(&newTree.Nodes[1]);
		newTree.Nodes[1].UpWard = &newTree.Nodes[newTree.Nodes.size()];
	}
	else
	{
		//O primeiro nó sempre é folha
		Node* newUpWard = newTree.Nodes[1].UpWard;
		int newNode = 0;

		srand(time(NULL));
		while (newUpWard->Number == newTree.Nodes[1].UpWard->Number)
		{
			newNode = 2 + (rand() % (newTree.Nodes.size() - 1));
			newUpWard = &newTree.Nodes[newNode];
		}

		//Posso remover o primeiro filho porque o nó 1 é o primeiro a ser criado e consequentemente será sempre o primeiro da lista
		newTree.Nodes[1].UpWard->DownWard.erase(newTree.Nodes[1].UpWard->DownWard.begin());
		newUpWard->DownWard.push_back(&newTree.Nodes[1]);
		newTree.Nodes[1].UpWard = newUpWard;
	}

	return newTree;
}

#pragma endregion

//Define o level de cada nó a partir da raiz da arvore
void AssignLevels(Node* root, map<Node*, int>* levels)
{
	if (root->UpWard == NULL)
		levels->operator[](root) = 0;
	else
		levels->operator[](root) = levels->operator[](root->UpWard) + 1;
	
	for each (Node* node in root->DownWard)
		AssignLevels(node, levels);

	/*
	if (root->DownWard.size() > 0)
		for each (Node* node in root->DownWard)
			AssignLevels(node, levels);
	else
		levels->operator[](root) = 0;

	if (root->UpWard != NULL && levels->operator[](root->UpWard) < levels->operator[](root) + 1)
		levels->operator[](root->UpWard) = levels->operator[](root) + 1;
	*/
}

//Define para os valores para determinado nivel e compara pra ver se as duas arvores estão equivalentes
bool AssignValuesForLevel(vector<Node*>* l1, vector<Node*>* l2, map<Node*, int>* valuesOne, map<Node*, int>* valuesTwo)
{
	//SubTree gerada
	//map<Node*, vector<int>> s1, s2;
	map<Node*, multiset<int>> s1, s2;

	for each (Node* node in *l1)
		//s1[node->UpWard].push_back(valuesOne->operator[](node));
		s1[node->UpWard].insert(valuesOne->operator[](node));
	for each (Node* node in *l2)
		//s2[node->UpWard].push_back(valuesTwo->operator[](node));
		s2[node->UpWard].insert(valuesTwo->operator[](node));

	vector<multiset<int>> aux1, aux2;
	//vector<vector<int>> aux1, aux2;

	for (map<Node*, multiset<int>>::iterator it = s1.begin(); it != s1.end(); ++it)
	//for (map<Node*, vector<int>>::iterator it = s1.begin(); it != s1.end(); ++it)
		aux1.push_back(it->second);
	for (map<Node*, multiset<int>>::iterator it = s2.begin(); it != s2.end(); ++it)
	//for (map<Node*, vector<int>>::iterator it = s2.begin(); it != s2.end(); ++it)
		aux2.push_back(it->second);

	sort(aux1.begin(), aux1.end());
	sort(aux2.begin(), aux2.end());

	if (aux1 != aux2)
		return false;
	else
	{
		//Remove tuplas duplicadas
		aux1.erase(unique(aux1.begin(), aux1.end()), aux1.end());
		aux2.erase(unique(aux2.begin(), aux2.end()), aux2.end());

		//vector<vector<int>>::iterator aux;
		vector<multiset<int>>::iterator aux;
		for (map<Node*, multiset<int>>::iterator it = s1.begin(); it != s1.end(); ++it)
		//for (map<Node*, vector<int>>::iterator it = s1.begin(); it != s1.end(); ++it)
		{
			aux = find(aux1.begin(), aux1.end(), it->second);
			valuesOne->operator[](it->first) = distance(aux1.begin(), aux) + 1;
		}
		for (map<Node*, multiset<int>>::iterator it = s2.begin(); it != s2.end(); ++it)
		//for (map<Node*, vector<int>>::iterator it = s2.begin(); it != s2.end(); ++it)
		{
			aux = find(aux2.begin(), aux2.end(), it->second);
			valuesTwo->operator[](it->first) = distance(aux2.begin(), aux) + 1;
		}

		return true;
	}
}

//Verifica se as arvores são isomorfas
bool IsIsomorphic(Tree* treeOne, Tree* treeTwo)
{
	//Se o número de nós for diferente retorna falso logo
	if (treeOne->Nodes.size() != treeTwo->Nodes.size())
		return false;

	//Define o nivel de cada nó da arvore
	map<Node*, int> treeLevelsOne, treeLevelsTwo;
	AssignLevels(&treeOne->Nodes[treeOne->Nodes.size()], &treeLevelsOne);
	AssignLevels(&treeTwo->Nodes[treeTwo->Nodes.size()], &treeLevelsTwo);

	map<int, vector<Node*>> levelListOne, levelListTwo; //Recebe os nós arrumados por niveis.
	map<Node*, int> valuesOne, valuesTwo; //Estrutura lista Nó-Inteiros (0 para todas as folhas)
	for (map<Node*, int>::iterator it = treeLevelsOne.begin(); it != treeLevelsOne.end(); ++it)
	{
		levelListOne[it->second].push_back(it->first);

		if (it->first->DownWard.size() == 0)
			valuesOne[it->first] = 0;
	}
	for (map<Node*, int>::iterator it = treeLevelsTwo.begin(); it != treeLevelsTwo.end(); ++it)
	{
		levelListTwo[it->second].push_back(it->first);
		if (it->first->DownWard.size() == 0)
			valuesTwo[it->first] = 0;
	}

	//Se for diferente podemos retornar daqui mesmo
	if (levelListOne.size() != levelListTwo.size())
		return false;

	for (int i = (levelListOne.size() - 1); i > 0; --i)
	{
		if (!AssignValuesForLevel(&levelListOne[i], &levelListTwo[i], &valuesOne, &valuesTwo))
			return false;
	}
		

	if (valuesOne[&treeOne->Nodes[treeOne->Nodes.size()]] == valuesTwo[&treeTwo->Nodes[treeTwo->Nodes.size()]])
		return true;
	else
		return false;
}

int main()
{
	try
	{
		int nrNodes;
		bool isomorphic;
		cin >> nrNodes;
		cin >> isomorphic;

		Tree x = Tree(nrNodes);
		Tree y = isomorphic ? x.GenerateIsomorphic() : x.GenerateNonIsomorphic();

		if (IsIsomorphic(&x, &y))
			return 1;
		else
			return 0;
	}
	catch (exception e)
	{
		cout << e.what();
		return 404;//Page not found xD
	}
}