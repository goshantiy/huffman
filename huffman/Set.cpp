#include "Set.h"


Set::Set()
{
	delete[]bits;
	bits = new unsigned char[32];
	for (int i = 0; i < 32; i++)
		bits[i] = 0;
	sz = 32;
	len = 256;
	weightBits = 0;
}
Set::Set(const char* str)
{
	delete[]bits;
	bits = new unsigned char[32];
	for (int i = 0; i < 32; i++)
		bits[i] = 0;
	sz = 32;
	len = 256;
	weightBits = 0;
	unsigned char m = 1;
	while (*str)
	{
		bits[(*str) / 8] |= m << ((*str) % 8);
		m = 1;
		str++;
		weightBits++;
	}
}

Set::Set(Set &obj)
{
	delete[]bits;
	bits = new unsigned char[32];
	sz = obj.sz;
	len = obj.len;
	weightBits = obj.weightBits;
	for (int i = 0; i < sz; i++)
		bits[i] = obj.bits[i];
}

Set & Set::operator=(const Set &obj)
{
	weightBits = obj.weightBits;
	for (int i = 0; i < sz; i++)
		bits[i] = obj.bits[i];
	return *this;
}

bool Set::operator==(Set &obj)
{
	if (sz == obj.sz && len == obj.len&&weightBits == obj.weightBits)
	{
		for (int i = 0; i < sz; i++)
			if (bits[i] != obj.bits[i])
				return false;
		return true;
	}
	return false;
}

bool Set::operator!=(Set &obj)
{
	if (sz == obj.sz && len == obj.len&&weightBits == obj.weightBits)
	{
		for (int i = 0; i < sz; i++)
			if (bits[i] != obj.bits[i])
				return true;
		return false;
	}
	return true;
}

void Set::PerfectSet()
{
	for (int i = 0; i < sz; i++)
	{
		bits[i] = 0;
		bits[i] = ~bits[i];
	}
	weightBits = 256;
}

Set Set::operator|(Set &obj)
{
	Set res;
	for (int i = 0; i < sz; i++)
		res.bits[i] = bits[i] | obj.bits[i];
	res.weightBits = res.weight();
	return res;
}

Set& Set::operator|=(Set &obj)
{
	for (int i = 0; i < sz; i++)
		bits[i] |= obj.bits[i];
	weightBits = this->weight();
	return *this;
}

Set Set::operator&(Set &obj)
{
	Set res;
	for (int i = 0; i < sz; i++)
		res.bits[i] = bits[i] & obj.bits[i];
	res.weightBits = res.weight();
	return res;
}

Set& Set::operator&=(Set &obj)
{
	for (int i = 0; i < sz; i++)
		bits[i] &= obj.bits[i];
	weightBits = this->weight();
	return *this;
}

Set Set::operator/(Set &obj)
{
	Set res;
	for (int i = 0; i < sz; i++)
		res.bits[i] = bits[i] & (~obj.bits[i]);
	res.weightBits = res.weight();
	return res;
}

Set & Set::operator/=(Set &obj)
{

	for (int i = 0; i < sz; i++)
		bits[i] &= ~obj.bits[i];
	weightBits = this->weight();
	return *this;
}

Set Set::operator+(const char sym)
{
	Set res(*this);
	unsigned char m = 1;
	if ((res.bits[sym / 8] & (m << (sym % 8))) == 0)
	{
		res.bits[sym / 8] |= m << (sym % 8);
		weightBits++;
	}
	return res;
}

Set & Set::operator+=(const char sym)
{
	unsigned char m = 1;
	if ((bits[sym / 8] & (m << (sym % 8))) == 0)
	{
		bits[sym / 8] |= m << (sym % 8);
		weightBits++;
	}
	return *this;
}

Set Set::operator-(const char sym)
{
	Set res(*this);
	unsigned char m = 1;
	if ((res.bits[sym / 8] & (m << (sym % 8))) != 0)
	{
		res.bits[sym / 8] &= ~(m << (sym % 8));
		weightBits++;
	}
	return res;
}

Set & Set::operator-=(const char sym)
{
	unsigned char m = 1;
	if ((bits[sym / 8] & (m << (sym % 8))) != 0)
	{
		bits[sym / 8] &= ~(m << (sym % 8));
		weightBits--;
	}
	return *this;
}

std::ostream& operator <<(std::ostream& out, const Set&obj)
{
	unsigned char m = 0;
	m = 1;
	for (int i = 0, j = 0; i < obj.len; i++, m = m << 1)
	{
		if (!m)
		{
			m = 1;
			j++;
		}
		if (obj.bits[j] & m)
			std::cout << (char)(8 * j + i % 8);
	}
	return out;
}

std::istream& operator >>(std::istream &in, Set&obj)
{
	int strlen;
	std::cout << " enter len ";
	std::cin >> strlen;
	for (int i = 0; i < obj.sz; i++)
		obj.bits[i] = 0;
	obj.weightBits = 0;
	unsigned char m = 1;
	std::cout << "enter string ";
	char sym;
	for (int i = 0, j = 0; i < strlen; i++)
	{
		std::cin >> sym;		
		obj.bits[sym / 8] |= m << (sym % 8);
		m = 1;
		obj.weightBits++;
	}
	return in;
}

