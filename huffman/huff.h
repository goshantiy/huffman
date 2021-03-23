#pragma once
#include "Set.h"
#include <fstream>
using namespace std;
class HTree
{
class NodeH
{
public:
	Set vec; // код символа
	int weight; // частота встречаемости символа
	NodeH* left, * right; // указатель на левую и правую ветвь дерева
	NodeH* next; // указатель на следующий элемент списка
	NodeH() : vec()
	{
		weight = 0;
		left = right = next = nullptr;
	}
	NodeH operator = (NodeH& obj)
	{
		vec = obj.vec;
		weight = obj.weight;
		*left = *(obj.left);
		*right = *(obj.right);
		*next = *(obj.next);
	}
	~NodeH()
	{
		if (left)
		{
			delete left;
			left = NULL;
		}
		if (right)
		{
			delete right;
			right = NULL;
		}
	}

};


	NodeH* Root; // указатель на корень дерева
	void createList(int* tab); // построение отсортированного списка символов по ассоциативной таблице
	bool buildTree(); // построение дерева из отсортированного списка символов
	void Periodicity(const char* fileName, int* tab); // подсчет символов в исходном файле, входные данные: название исходного файла, ассоциативная таблица.
	void clear(NodeH* Root); // очистка дерева, входные данные - указатель на корень
	bool createTree(const char* fileName); // построение дерева из исходного файла
public:
	HTree();
	~HTree();
	bool code(const char* sourseFile, const char* resFile); // кодирование, входные параметры: название файлов с исходными и закодированными данными
	bool decode(const char* sourseFile, const char* resFile); // декодирование, входные параметры: название файлов закодированными и раскодированными данными

};

