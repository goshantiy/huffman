#pragma once
#include <iostream>

class BBV
{
protected:
	unsigned char* bits;		
	int len;					
	int sz;						

	class bit
	{
		unsigned char* bitsK;
		unsigned char mask;
	public:
		bit(unsigned char* BAIT, unsigned char MASK);

		bit& operator ~ ();

		bit& operator = (bit& obj);

		bit& operator = (bool x);

		operator bool();

		friend std::istream& operator >> (std::istream& in, bit& obj);
		friend std::ostream& operator << (std::ostream& out, bit& obj);


	};


public:
	BBV();						//����������� �� ���������
	BBV(int len);				//����������� � ���������� (����� �������)
	explicit BBV(const char* vector);			//����������� � ���������� (�� ������)
	BBV(char* vector, int nl);	//����������� � ���������� (����� ������)
	BBV(BBV& obj);				//����������� �����������
	bool Set0(int ix);			//��������� � 0 ix-� ����������
	bool SetBits0(int ix, int lenghth);	//��������� � 0 len ���������, ������� � ix
	bool Set1(int ix);			//��������� � 1 ix-� ����������
	bool SetBits1(int ix, int length);//��������� � 0 len ���������, ������� � ix
	bool Inversion(int ix);		//�������� ix-� ����������		
	bool InversionBits(int ix, int length);//�������� len ���������, ������� � ix
	int weight();				//��� �������
	BBV& operator = (const BBV& obj);//�������� ����������
	BBV operator &(BBV& obj);	//���������� &
	BBV operator |(BBV& obj);	//���������� |
	BBV operator ^(BBV& obj);	//���������� ^
	BBV& operator ^=(BBV& obj);	//���������� ^=
	BBV& operator &=(BBV& obj);	//���������� &=
	BBV& operator |=(BBV& obj);	//���������� |=
	BBV& operator <<=(int k);	//���������� <<=
	BBV& operator >>=(int k);	//���������� >>=
	BBV operator <<(int k);		//���������� <<
	BBV operator >>(int k);		//���������� <<
	BBV operator~();			//���������� ~
	operator char* ();			//���������� �������������� � char*
	bool operator==(BBV& obj);	//���������� ==
	bool operator!=(BBV& obj);  //���������� !+
	bit operator [] (int N);
	friend std::ostream& operator << (std::ostream& out, const BBV&); //���������� cout
	friend std::istream& operator >> (std::istream& in, BBV&);		//���������� cin

	~BBV();						//����������
};

