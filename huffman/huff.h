#pragma once
#include "Set.h"
#include <fstream>
using namespace std;
class HTree
{
class NodeH
{
public:
	Set vec; // ��� �������
	int weight; // ������� ������������� �������
	NodeH* left, * right; // ��������� �� ����� � ������ ����� ������
	NodeH* next; // ��������� �� ��������� ������� ������
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


	NodeH* Root; // ��������� �� ������ ������
	void createList(int* tab); // ���������� ���������������� ������ �������� �� ������������� �������
	bool buildTree(); // ���������� ������ �� ���������������� ������ ��������
	void Periodicity(const char* fileName, int* tab); // ������� �������� � �������� �����, ������� ������: �������� ��������� �����, ������������� �������.
	void clear(NodeH* Root); // ������� ������, ������� ������ - ��������� �� ������
	bool createTree(const char* fileName); // ���������� ������ �� ��������� �����
public:
	HTree();
	~HTree();
	bool code(const char* sourseFile, const char* resFile); // �����������, ������� ���������: �������� ������ � ��������� � ��������������� �������
	bool decode(const char* sourseFile, const char* resFile); // �������������, ������� ���������: �������� ������ ��������������� � ���������������� �������

};

