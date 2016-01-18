#include <map>
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
	~Tree();
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
Tree::~Tree() 
{
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

	return newTree;
}

#pragma endregion

//Define o level de cada nó a partir da raiz da arvore
void AssignLevels(Node* root, map<Node*, int>* levels)
{
	if (root->DownWard.size() > 0)
		for each (Node* node in root->DownWard)
			AssignLevels(node, levels);
	else
		levels->operator[](root) = 0;

	if (root->UpWard != NULL && levels->operator[](root->UpWard) < levels->operator[](root) + 1)
		levels->operator[](root->UpWard) = levels->operator[](root) + 1;
}

/*
//Preenche estrutura com o level de cada node, necessário executar para cada folha
void AssignLevelsBottomUp(Node* leaf, map<Node*, int>* levels, int value) 
{
	if (levels->operator[](leaf) < value)
		levels->operator[](leaf) = value;

	if (leaf->UpWard != NULL)
		AssignLevelsBottomUp(leaf->UpWard, levels ,++value);
}
*/

//Define para os valores para determinado nivel e compara pra ver se as duas arvores estão equivalentes
bool AssignValuesForLevel(map<int, vector<Node*>>* l1, map<int, vector<Node*>>* l2, map<Node*, vector<int>>* valuesOne, map<Node*, vector<int>>* valuesTwo, int level)
{
	for each (Node* node in l1->operator[](level-1))
		valuesOne->operator[](node->UpWard).push_back(level-1);
		
	for each (Node* node in l2->operator[](level-1))
		valuesTwo->operator[](node->UpWard).push_back(level-1);

	vector<vector<int>> aux1, aux2;

	for each (Node* node in l1->operator[](level))
		aux1.push_back(valuesOne->operator[](node));
	for each (Node* node in l2->operator[](level))
		aux2.push_back(valuesTwo->operator[](node));

	sort(aux1.begin(), aux1.end());
	sort(aux2.begin(), aux2.end());

	if (aux1 != aux2)
		return false;
	else
		return true;
}

//Verifica se as arvores são isomorfas
bool IsIsomorphic(Tree treeOne, Tree treeTwo)
{
	//Se o número de nós for diferente retorna falso logo
	if (treeOne.Nodes.size() != treeTwo.Nodes.size())
		return false;

	//Define o nivel de cada nó da arvore
	map<Node*, int> treeLevelsOne, treeLevelsTwo;
	AssignLevels(&treeOne.Nodes[treeOne.Nodes.size()], &treeLevelsOne);
	AssignLevels(&treeTwo.Nodes[treeOne.Nodes.size()], &treeLevelsTwo);

	/*
	for (map<Node*, int>::iterator it = leavesOne.begin(); it != leavesOne.end(); ++it)
	AssignLevelsBottomUp(it->first, &levelsOne, 0);
	for (map<Node*, int>::iterator it = leavesTwo.begin(); it != leavesTwo.end(); ++it)
	AssignLevelsBottomUp(it->first, &levelsTwo, 0);
	*/

	map<Node*, vector<int>> valuesOne, valuesTwo; //Estrutura lista Nó-Inteiros (0 para todas as folhas)
	map<int, vector<Node*>> levelListOne, levelListTwo; //Recebe os nós arrumados por niveis.
	for (map<Node*, int>::iterator it = treeLevelsOne.begin(); it != treeLevelsOne.end(); ++it)
	{
		levelListOne[it->second].push_back(&*it->first);
		if (it->second == 0)
			valuesOne[&*it->first].push_back(0);
		else
			valuesOne[&*it->first].clear();
	}
	for (map<Node*, int>::iterator it = treeLevelsTwo.begin(); it != treeLevelsTwo.end(); ++it)
	{
		levelListTwo[it->second].push_back(&*it->first);
		if (it->second == 0)
			valuesTwo[&*it->first].push_back(0);
		else
			valuesTwo[&*it->first].clear();
	}

	//Se for diferente podemos retornar daqui mesmo
	if (levelListOne.size() != levelListTwo.size())
		return false;

	for (int i = 1; i < levelListOne.size(); i++)
		if (!AssignValuesForLevel(&levelListOne, &levelListTwo, &valuesOne, &valuesTwo, i))
			return false;

	if (valuesOne[&treeOne.Nodes[treeOne.Nodes.size()]] == valuesTwo[&treeTwo.Nodes[treeTwo.Nodes.size()]])
		return true;
	else
		return false;
}

int main()
{
	try
	{
	
			Tree x = Tree(50);
			Tree y = x.GenerateIsomorphic();

			if (IsIsomorphic(x, y))
				throw exception("eita");

		return 0;
	}
	catch (exception e)
	{
		cout << e.what();
		return 404;//Page not found xD
	}
}