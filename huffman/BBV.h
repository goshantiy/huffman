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
	BBV();						//конструктор по умолчанию
	BBV(int len);				//конструктор с параметром (длина вектора)
	explicit BBV(const char* vector);			//конструктор с параметром (по строке)
	BBV(char* vector, int nl);	//конструктор с параметром (часть строки)
	BBV(BBV& obj);				//конструктор копирования
	bool Set0(int ix);			//установка в 0 ix-й компоненты
	bool SetBits0(int ix, int lenghth);	//установка в 0 len компонент, начиная с ix
	bool Set1(int ix);			//установка в 1 ix-й компоненты
	bool SetBits1(int ix, int length);//установка в 0 len компонент, начиная с ix
	bool Inversion(int ix);		//инверсия ix-й компоненты		
	bool InversionBits(int ix, int length);//инверсия len компонент, начиная с ix
	int weight();				//вес вектора
	BBV& operator = (const BBV& obj);//оператор присвоения
	BBV operator &(BBV& obj);	//перегрузка &
	BBV operator |(BBV& obj);	//перегрузка |
	BBV operator ^(BBV& obj);	//перегрузка ^
	BBV& operator ^=(BBV& obj);	//перегрузка ^=
	BBV& operator &=(BBV& obj);	//перегрузка &=
	BBV& operator |=(BBV& obj);	//перегрузка |=
	BBV& operator <<=(int k);	//перегрузка <<=
	BBV& operator >>=(int k);	//перегрузка >>=
	BBV operator <<(int k);		//перегрузка <<
	BBV operator >>(int k);		//перегрузка <<
	BBV operator~();			//перегрузка ~
	operator char* ();			//перегрузка преобразования в char*
	bool operator==(BBV& obj);	//перегрузка ==
	bool operator!=(BBV& obj);  //перегрузка !+
	bit operator [] (int N);
	friend std::ostream& operator << (std::ostream& out, const BBV&); //перегрузка cout
	friend std::istream& operator >> (std::istream& in, BBV&);		//перегрузка cin

	~BBV();						//деструктор
};

