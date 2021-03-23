#include "huff.h"
#include <fstream>


void HTree::createList(int* tab) // Создание упорядоченного списка
{
	NodeH* node = NULL;
	Root = NULL;

	for (int i = 0; i < 256; i++)
	{
		if (tab[i])
		{
			node = new NodeH;  // Создаем узел 
			node->weight = tab[i]; //число повторений
			node->vec += i; // создаем ассоциативный вектор, в него записываем элемент
			if (Root == NULL)  //Если это первый элемент, делаем его головой
			{
				Root = node;
			}
			else // Если не первый, ищем место
			{
				NodeH** ptr = &Root;
				while (*ptr && node->weight > (*ptr)->weight) //ищем по возрастанию
				{
					ptr = &((*ptr)->next);
				}
				node->next = *ptr;
				*ptr = node;
			}
		}
	}
	if (Root && !Root->next)
	{
		NodeH* ptr = Root;
		Root = new NodeH;
		Root->next = ptr;
	}
}

void HTree::Periodicity(const char* fileName, int* tab) //Построение таблицы частот
{
	fstream file(fileName, ios::in);
	char sym;
	while (!file.eof()) //
	{
		sym = file.get(); //Считываем символ
		tab[sym]++; //записываем в ассоциативный массив
	}
	tab[sym]--; 
	file.close();
}

bool HTree::buildTree() //построение дерева из списка
{
	if (Root)
	{
		NodeH* node = Root;	// записываем корень				// по алгоритму мы должны взять два узла с самыми маленькими весами и
														// объединить в один узел, потомками которого будут символы которые мы объединили
		while (node->next)
		{
			NodeH* newNode = new NodeH;					
			Root = newNode;			
			NodeH* left = node;			//Первый элемент из списка становится левым поддеревом						
			newNode->left = left;
			NodeH* right = NULL;									
			if (node->next)//если есть второй
				right = node->next;//становится правым
			newNode->next = right->next;
			right->next = NULL;			//убираем из списка
			left->next = NULL;
			newNode->right = right;
			newNode->weight = left->weight + right->weight; //Складываем частоты
			Set tmp_vec = left->vec; //суммируем вектора
			tmp_vec |= right->vec;
			newNode->vec = *(new Set(tmp_vec));
			NodeH* ptr = Root->next;
			while (ptr) // Ищем место для нового узла
			{
				if (newNode->weight > ptr->weight) {
					if (newNode == Root || right == Root || left == Root) // Проверяем, будет ли он корнем
					{
						Root = ptr;
					}
					if ((ptr->next) && ((newNode->weight) > (ptr->next->weight)))
					{
						ptr = ptr->next;
					}
					else
					{
						newNode->next = ptr->next;
						ptr->next = newNode;
						ptr = NULL;
					}
				}
				else
				{
					ptr = NULL;
				}
			}
			node = Root; // указатель в начало списка
		}
		return true;
	}

	return false;
}

bool HTree::createTree(const char* fileName)//построение дерева
{ 
	if (Root)  //если уже построенно
		return false;
	int tab[256] = { 0 };
	Periodicity(fileName, tab); //создаем таблицу частот
	createList(tab); // создаем список
	if (buildTree()) // создаем дерево
		return true;
	return false;
}

HTree::HTree()
{
	Root = nullptr;
}



void HTree::clear(NodeH* nd)// Рекурсивная очистка дерева
{ 
	if (nd) 
	{
		if (nd->left)
			clear(nd->left);
		if (nd->right)
			clear(nd->right);
		nd->left = NULL;
		nd->right = NULL;
		delete nd;
		nd = NULL;
	}
}

bool HTree::code(const const char* sourceFile, const const char* resFile)
{
	bool result = createTree(sourceFile);//создаем дерево
	if (!result)
	{
		return false;
	}
	fstream file(sourceFile, ios_base::in); // исходный файл на чтение
	fstream codedFile(resFile, ios_base::out); // файл для кода на запись
	NodeH* buf = Root;
	if (Root) //если есть дерево кодируем
	{
		unsigned char sym;
		sym = file.get(); //считываем символ
		do
		{
			buf = Root;
			
			while (buf->left)//(если есть левый всегда есть правый)идем по дереву пока не доберемся до узла без потомков
			{
				if (buf->left->vec[sym])
				{
					codedFile << 0;
					
					buf = buf->left;
				}
				else
				{
					codedFile << 1;
					
					buf = buf->right;
				}
			}
			sym = file.get();
		} while (!file.eof());
		file.close();
		codedFile.close();
		return true;
	}
	return false;
}
bool HTree::decode(const char* sourse, const char* result)
{
	if (Root) // проверяем создано ли дерево
	{
		NodeH* findNode = NULL;
		char sym;
		fstream CodedFile(sourse, ios_base::in); // файл с кодом на чтение
		fstream ResultFile(result, ios_base::out); // файл с результатом на запись
		bool flag = true;
		int i = 0;
		while (!CodedFile.eof())
		{
			if (!flag)
				ResultFile << (char)(i - 1); // если найден нужный записываем
			findNode = Root;
			do
			{
				
				sym = CodedFile.get(); // Считываем символ 
				if (sym == 48) // Если 0, то символ находится в левом поддереве
					findNode = findNode->left;
				else        // 1 - в правом
					findNode = findNode->right;
			} while (findNode->left); //(если есть левый всегда есть правый) идем по дереву пока не доберемся до узла без потомков
			
			for (i = 0, flag = true; i < 255 && flag; i++) //получаем код ASCII
			{
				if ((findNode->vec)[i])
					flag = false;
			}
		}
		return true;
	}
	return false;
}
HTree::~HTree()
{
	clear(Root);
}

