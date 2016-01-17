#include <map>
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;

#pragma region Node

//Estrutura "N�" que guarda o endere�o de seu pai e seus filhos
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
		//Gera um n�mero aleat�rio maior que o atual e menor ou igual ao n�mero de n�s
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

	//Caso tenha achado mais de uma folha inverte as posi��es delas
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
	//Sen�o troca de lugar com o pai
	else
	{
		//Recebe o pai da folha
		Node* aux = leaves[0]->UpWard;
		
		//Aponta o filho para o av� e adiciona o pai na lista de filhos
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

	//O primeiro n� sempre � folha
	Node* newUpWard = newTree.Nodes[1].UpWard;
	int newNode = 0;
	
	srand(time(NULL));
	while (newUpWard->Number == newTree.Nodes[1].UpWard->Number)
	{
		newNode = 2 + (rand() % (newTree.Nodes.size() - 1));
		newUpWard = &newTree.Nodes[newNode];
	}

	//Posso remover o primeiro filho porque o n� 1 � o primeiro a ser criado e consequentemente ser� sempre o primeiro da lista
	newTree.Nodes[1].UpWard->DownWard.erase(newTree.Nodes[1].UpWard->DownWard.begin());
	newUpWard->DownWard.push_back(&newTree.Nodes[1]);
	newTree.Nodes[1].UpWard = newUpWard;

	return newTree;
}

#pragma endregion

//Define o level de cada n� a partir da raiz da arvore
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

//Preenche estrutura com o level de cada node, necess�rio executar para cada folha
void AssignLevelsBottomUp(Node* leaf, map<Node*, int>* levels, int value) 
{
	if (levels->operator[](leaf) < value)
		levels->operator[](leaf) = value;

	if (leaf->UpWard != NULL)
		AssignLevelsBottomUp(leaf->UpWard, levels ,++value);
}

//IGNORAR ESTA FUN��O, AINDA FAZENDO ALGUNS TESTES
void AssignValues(vector<Node*> l1, vector<Node*> l2, map<Node*, int>* valuesOne, map<Node*, int>* valuesTwo) 
{
	vector<pair<int, vector<int>>> s1, s2;

	for each (Node* node in l1)
		
	for each (Node* node in l2)
		s2[node->Number].push_back(valuesTwo->operator[](node));

	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	

	/*
	map<Node*, vector<int>> subOne, subTwo;

	for (map<Node*, int>::iterator it = leavesOne.begin(); it != leavesOne.end(); ++it)
		subOne[it->first->UpWard].push_back(it->second);

	for (map<Node*, int>::iterator it = leavesTwo.begin(); it != leavesTwo.end(); ++it)
		subTwo[it->first->UpWard].push_back(it->second);
	*/
}

//Verifica se as arvores s�o isomorfas
bool IsIsomorphic(Tree treeOne, Tree treeTwo)
{
	//Se o n�mero de n�s for diferente retorna falso logo
	if (treeOne.Nodes.size() != treeTwo.Nodes.size())
		return false;
	
	//Define o nivel de cada n� da arvore
	map<Node*, int> treeLevelsOne, treeLevelsTwo;
	AssignLevels(&treeOne.Nodes[treeOne.Nodes.size()], &treeLevelsOne);
	AssignLevels(&treeTwo.Nodes[treeOne.Nodes.size()], &treeLevelsTwo);

	/*
	for (map<Node*, int>::iterator it = leavesOne.begin(); it != leavesOne.end(); ++it)
		AssignLevelsBottomUp(it->first, &levelsOne, 0);
	for (map<Node*, int>::iterator it = leavesTwo.begin(); it != leavesTwo.end(); ++it)
		AssignLevelsBottomUp(it->first, &levelsTwo, 0);
	*/

	//Arruma os n�s por niveis.
	map<int, vector<Node*>> levelListOne, levelListTwo;
	for (map<Node*, int>::iterator it = treeLevelsOne.begin(); it != treeLevelsOne.end(); ++it)
		levelListOne[it->second].push_back(it->first);
	for (map<Node*, int>::iterator it = treeLevelsTwo.begin(); it != treeLevelsTwo.end(); ++it)
		levelListTwo[it->second].push_back(it->first);

	//Se for diferente podemos retornar daqui mesmo
	if (levelListOne.size() != levelListTwo.size())
		return false;
	
	//Estrutura lista N�/Inteiro (0 para todas as folhas)
	map<Node*, int> valuesOne, valuesTwo;
	for (int i = 1; i <= treeOne.Nodes.size(); i++)
	{
		if (treeOne.Nodes[i].DownWard.size() == 0)
			valuesOne[&treeOne.Nodes[i]] = 0;
		if(treeTwo.Nodes[i].DownWard.size() == 0)
			valuesTwo[&treeTwo.Nodes[i]] = 0;
	}

	/*
	//Nesse momento s� tem folhas em valuesOne e valuesTwo
	vector<Node*> l1, l2;
	for (map<Node*, int>::iterator it = valuesOne.begin(); it != valuesOne.end(); ++it)
		if (treeLevelsOne[it->first] == 0)
			l1.push_back(it->first);
	for (map<Node*, int>::iterator it = valuesTwo.begin(); it != valuesTwo.end(); ++it)
		if (treeLevelsTwo[it->first] == 0)
			l2.push_back(it->first);
	*/

	for (int i = 1; i <= levelListOne.size(); i++)
		AssignValues(levelListOne[i], levelListTwo[i], &valuesOne, &valuesTwo);

	if (valuesOne[&treeOne.Nodes[treeOne.Nodes.size()]] == valuesTwo[&treeTwo.Nodes[treeTwo.Nodes.size()]])
		return true;
	else
		return false;
	
}

int main()
{
	try
	{
		Tree x(8);
		Tree y = x.GenerateIsomorphic();

		IsIsomorphic(x, y);

		return 0;
	}
	catch (exception e)
	{
		cout << e.what();
		return 404;//Page not found xD
	}
}