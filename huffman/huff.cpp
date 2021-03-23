#include "huff.h"
#include <fstream>


void HTree::createList(int* tab) // �������� �������������� ������
{
	NodeH* node = NULL;
	Root = NULL;

	for (int i = 0; i < 256; i++)
	{
		if (tab[i])
		{
			node = new NodeH;  // ������� ���� 
			node->weight = tab[i]; //����� ����������
			node->vec += i; // ������� ������������� ������, � ���� ���������� �������
			if (Root == NULL)  //���� ��� ������ �������, ������ ��� �������
			{
				Root = node;
			}
			else // ���� �� ������, ���� �����
			{
				NodeH** ptr = &Root;
				while (*ptr && node->weight > (*ptr)->weight) //���� �� �����������
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

void HTree::Periodicity(const char* fileName, int* tab) //���������� ������� ������
{
	fstream file(fileName, ios::in);
	char sym;
	while (!file.eof()) //
	{
		sym = file.get(); //��������� ������
		tab[sym]++; //���������� � ������������� ������
	}
	tab[sym]--; 
	file.close();
}

bool HTree::buildTree() //���������� ������ �� ������
{
	if (Root)
	{
		NodeH* node = Root;	// ���������� ������				// �� ��������� �� ������ ����� ��� ���� � ������ ���������� ������ �
														// ���������� � ���� ����, ��������� �������� ����� ������� ������� �� ����������
		while (node->next)
		{
			NodeH* newNode = new NodeH;					
			Root = newNode;			
			NodeH* left = node;			//������ ������� �� ������ ���������� ����� ����������						
			newNode->left = left;
			NodeH* right = NULL;									
			if (node->next)//���� ���� ������
				right = node->next;//���������� ������
			newNode->next = right->next;
			right->next = NULL;			//������� �� ������
			left->next = NULL;
			newNode->right = right;
			newNode->weight = left->weight + right->weight; //���������� �������
			Set tmp_vec = left->vec; //��������� �������
			tmp_vec |= right->vec;
			newNode->vec = *(new Set(tmp_vec));
			NodeH* ptr = Root->next;
			while (ptr) // ���� ����� ��� ������ ����
			{
				if (newNode->weight > ptr->weight) {
					if (newNode == Root || right == Root || left == Root) // ���������, ����� �� �� ������
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
			node = Root; // ��������� � ������ ������
		}
		return true;
	}

	return false;
}

bool HTree::createTree(const char* fileName)//���������� ������
{ 
	if (Root)  //���� ��� ����������
		return false;
	int tab[256] = { 0 };
	Periodicity(fileName, tab); //������� ������� ������
	createList(tab); // ������� ������
	if (buildTree()) // ������� ������
		return true;
	return false;
}

HTree::HTree()
{
	Root = nullptr;
}



void HTree::clear(NodeH* nd)// ����������� ������� ������
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
	bool result = createTree(sourceFile);//������� ������
	if (!result)
	{
		return false;
	}
	fstream file(sourceFile, ios_base::in); // �������� ���� �� ������
	fstream codedFile(resFile, ios_base::out); // ���� ��� ���� �� ������
	NodeH* buf = Root;
	if (Root) //���� ���� ������ ��������
	{
		unsigned char sym;
		sym = file.get(); //��������� ������
		do
		{
			buf = Root;
			
			while (buf->left)//(���� ���� ����� ������ ���� ������)���� �� ������ ���� �� ��������� �� ���� ��� ��������
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
	if (Root) // ��������� ������� �� ������
	{
		NodeH* findNode = NULL;
		char sym;
		fstream CodedFile(sourse, ios_base::in); // ���� � ����� �� ������
		fstream ResultFile(result, ios_base::out); // ���� � ����������� �� ������
		bool flag = true;
		int i = 0;
		while (!CodedFile.eof())
		{
			if (!flag)
				ResultFile << (char)(i - 1); // ���� ������ ������ ����������
			findNode = Root;
			do
			{
				
				sym = CodedFile.get(); // ��������� ������ 
				if (sym == 48) // ���� 0, �� ������ ��������� � ����� ���������
					findNode = findNode->left;
				else        // 1 - � ������
					findNode = findNode->right;
			} while (findNode->left); //(���� ���� ����� ������ ���� ������) ���� �� ������ ���� �� ��������� �� ���� ��� ��������
			
			for (i = 0, flag = true; i < 255 && flag; i++) //�������� ��� ASCII
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

