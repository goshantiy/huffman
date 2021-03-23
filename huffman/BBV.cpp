#include "BBV.h"
#include <iostream>

BBV::bit::bit(unsigned char* bits, unsigned char m)
{
	bitsK = bits;
	mask = m;
}

BBV::bit& BBV::bit::operator ~ ()
{
	*bitsK ^= mask;
	return *this;
}

BBV::bit& BBV::bit::operator = (BBV::bit& obj)
{
	if (*(obj.bitsK) & obj.mask)
	{
		*bitsK |= mask;
		return *this;
	}
	*bitsK &= ~mask;
	return *this;
}

BBV::bit& BBV::bit::operator = (bool x)
{
	if (x)
		*bitsK |= mask;
	else
		*bitsK &= ~mask;

	return *this;
}

BBV::bit::operator bool()
{
	return (*bitsK & mask);
}



BBV::BBV()
{
	sz = 1;							
	bits = new unsigned char[sz];
	len = 8;						
	bits[0] = 0;					
}
BBV::BBV(int length)
{
	if (length < 8)
		length = 8;					
	len = length;
	sz = length / 8;
	if (len % 8)
		sz++;						
	bits = new unsigned char[sz];
	if (bits)						//check memory
	{
		for (int i = 0; i < sz; i++)
			bits[i] = 0;			
	}
	else
	{								// нехватка памяти
		len = 8;
		sz = 1;
		bits = new unsigned char[1];
		bits[0] = 0;
	}
}
BBV::BBV(const char* vector)
{
	unsigned char m = 1;
	int i = 0;
	int k = 0;
	while (vector[i])				
		i++;
	if (i < 8)
		i = 8;
	len = i;						
	sz = i / 8;
	if (len % 8)
		sz++;
	bits = new unsigned char[sz];
	if (bits)
	{
		for (i = 0; i < sz; i++)
		{
			bits[i] = 0;			
		}
		i = 0;
		for (i = 0; vector[i]; i++, m = m << 1)			
		{
			if (!m)										
			{
				k++;
				m = 1;
			}
			if (vector[i] != '0')
			{
				bits[k] = bits[k] | m;
			}
		}
	}
	else
	{								
		len = 8;
		sz = 1;
		bits = new unsigned char[1];
		bits[0] = 0;
	}
}
BBV::BBV(char* vector, int nl)
{
	unsigned char m = 1;
	int i = 0;
	int k = 0;
	if (nl < 8)
		nl = 8;
	sz = nl / 8;
	len = nl;
	if (len % 8)
		sz++;
	bits = new unsigned char[sz];
	if (bits)
	{
		for (i = 0; i < sz; i++)
			bits[i] = 0;
		for (i = 0, k = 0; i < nl && vector[i]; i++, m = m << 1)  
		{
			if (!m)
			{
				k++;
				m = 1;
			}
			if (vector[i] != '0')
			{
				bits[k] = bits[k] | m;
			}

		}
	}
	else
	{								
		len = 8;
		sz = 1;
		bits = new unsigned char[1];
		bits[0] = 0;
	}
}
BBV::BBV(BBV& obj)
{
	sz = obj.sz;
	len = obj.len;
	bits = new unsigned char[sz];
	if (bits)
		for (int i = 0; i < sz; i++)
			bits[i] = obj.bits[i];
	else
	{								
		len = 8;
		sz = 1;
		bits = new unsigned char[1];
		bits[0] = 0;
	}
}
bool BBV::Set0(int ix)
{
	if (ix<len && ix>-1)		 
	{
		int k = ix / 8;			
		int p = ix % 8;
		unsigned char m = 1;
		m = m << p;
		bits[k] = bits[k] & (~m);
		return true;
	}
	else
		return false;

}
bool BBV::SetBits0(int ix, int length)
{
	if (ix<len && ix>-1)			
	{
		int j = 0;
		int k = ix / 8;				
		int p = ix % 8;
		unsigned char m = 1;
		m = m << p;
		for (int i = 0; i < length && k < sz; i++, m = m << 1)   
		{
			if (!m)
			{
				m = 1;
				k++;
			}
			if (k < sz)
				bits[k] = bits[k] & (~m);
			else
				return false;
		}
		return true;
	}
	else
		return false;
}
bool BBV::Set1(int ix)					
{
	if (ix<len && ix>-1)
	{
		int k = ix / 8;
		int p = ix % 8;
		unsigned char m = 1;
		m = m << p;
		bits[k] = bits[k] | m;
		return true;
	}
	else
		return false;
}
bool BBV::SetBits1(int ix, int length)			
{
	if (ix<len && ix>-1)
	{
		int j = 0;
		int k = ix / 8;
		int p = ix % 8;
		unsigned char m = 1;
		m = m << p;
		for (int i = 0; i < length && k < sz; i++, m = m << 1)
		{
			if (!m)
			{
				m = 1;
				k++;
			}
			if (k < sz)
				bits[k] = bits[k] | m;
			else
				return false;
		}
		return true;
	}
	else
		return false;
}
bool BBV::Inversion(int ix)					
{
	if (ix<len && ix>-1)
	{
		int k = ix / 8;
		int p = ix % 8;
		unsigned char m = 1;
		m = m << p;
		bits[k] = bits[k] ^ m;
		return true;
	}
	else
		return false;
}
bool BBV::InversionBits(int ix, int length)					
{
	if (ix<len && ix>-1)
	{
		int j = 0;
		int k = ix / 8;
		int p = ix % 8;
		unsigned char m = 1;
		m = m << p;
		for (int i = 0; i < length && k < sz; i++, m = m << 1)
		{
			if (!m)
			{
				m = 1;
				k++;
			}
			bits[k] = bits[k] ^ m;
		}
		return true;
	}
	else
		return false;
}
int BBV::weight()
{
	int w = 0;
	int k = 0;
	unsigned char m = 1;
	for (int i = 0; i < len; i++, m = m << 1)		
	{
		if (!m)								
		{
			k++;
			m = 1;
		}
		if (bits[k] & m)
			w++;
	}
	return w;
}

BBV& BBV::operator=(const BBV& obj)
{
	if (bits == obj.bits)			
		return *this;
	else
	{
		delete[] bits;				
		len = obj.len;
		sz = obj.sz;
		bits = new unsigned char[sz];
		if (bits)
		{
			for (int i = 0; i < sz; i++)
				bits[i] = obj.bits[i];
		}
		else
			throw 1;
		return *this;
	}
}
BBV BBV::operator&(BBV& obj)
{
	if (len == obj.len)					
	{
		BBV res(len);
		for (int i = 0; i < sz; i++)
		{
			res.bits[i] = bits[i] & obj.bits[i];
		}
		return res;
	}
	else
	{
		throw 1;				
		BBV res;				
		return res;
	}
}
BBV BBV::operator|(BBV& obj)			
{
	if (len == obj.len)
	{
		BBV res(len);
		for (int i = 0; i < sz; i++)
		{
			res.bits[i] = bits[i] | obj.bits[i];
		}
		return res;
	}
	else
	{
		throw 1;
		BBV res;
		return res;
	}
}
BBV BBV::operator^(BBV& obj)			
{
	if (len == obj.len)
	{
		BBV res(len);
		for (int i = 0; i < sz; i++)
		{
			res.bits[i] = bits[i] ^ obj.bits[i];
		}
		return res;
	}
	else
	{
		throw 1;
		BBV res;
		return res;
	}
}
BBV& BBV::operator^=(BBV& obj)
{
	if (len == obj.len)
	{
		for (int i = 0; i < sz; i++)
		{
			bits[i] = bits[i] ^ obj.bits[i];
		}
		return *this;
	}
	else
	{
		throw 1;
		delete this;
		BBV res;
		return res;
	}
}
BBV& BBV::operator&=(BBV& obj)
{
	if (len == obj.len)
	{
		for (int i = 0; i < sz; i++)
		{
			bits[i] = bits[i] & obj.bits[i];
		}
		return *this;
	}
	else
	{
		throw 1;
		BBV res;
		return res;
	}
}
BBV& BBV::operator|=(BBV& obj)
{
	if (len == obj.len)
	{
		for (int i = 0; i < sz; i++)
		{
			bits[i] = bits[i] | obj.bits[i];
		}
		return *this;
	}
	else
	{
		throw 1;
		BBV res;
		return res;
	}
}
BBV& BBV::operator>>=(int k)	
{
	unsigned char m = 1;
	unsigned char buffer1 = 0, buffer2 = 0;
	for (int i = 0; i < k; i++, buffer1 = 0, buffer2 = 0, m = 1)
	{
		for (int j = 0; j < sz; j++)		
		{
			buffer1 = bits[j] >> 7;				
			bits[j] = bits[j] << 1;				
			bits[j] |= buffer2;					
			buffer2 = buffer1;					
		}
		if (len % 8)							
		{
			bits[sz - 1] = bits[sz - 1] << (8 - len % 8);
			bits[sz - 1] = bits[sz - 1] >> (8 - len % 8);
		}
	}
	return *this;
}
BBV& BBV::operator<<=(int k)
{
	unsigned char m = 1;
	unsigned char buffer1 = 0, buffer2 = 0;
	for (int i = 0; i < k; i++, buffer1 = 0, buffer2 = 0, m = 1)
	{
		for (int j = sz - 1; j >= 0; j--)			
		{
			buffer1 = bits[j] << 7;					
			bits[j] = bits[j] >> 1;					
			bits[j] |= buffer2;						
			buffer2 = buffer1;
		}											
	}
	return *this;
}
BBV BBV::operator>>(int k) 
{
	unsigned char m = 1;
	unsigned char buffer1 = 0, buffer2 = 0;
	BBV res(*this);
	for (int i = 0; i < k; i++, buffer1 = 0, buffer2 = 0, m = 1)
	{
		for (int j = 0; j < sz; j++)		
		{
			buffer1 = bits[j] >> 7;				
			res.bits[j] = bits[j] << 1;				 
			res.bits[j] |= buffer2;					
			buffer2 = buffer1;					
		}
		if (len % 8)							
		{
			res.bits[sz - 1] = res.bits[sz - 1] << (8 - len % 8);
			res.bits[sz - 1] = res.bits[sz - 1] >> (8 - len % 8);
		}
	}
	return res;
}
BBV BBV::operator<<(int k)			
{
	unsigned char m = 1;
	unsigned char buffer1 = 0, buffer2 = 0;
	BBV res(*this);
	for (int i = 0; i < k; i++, buffer1 = 0, buffer2 = 0, m = 1)
	{
		for (int j = sz - 1; j >= 0; j--)
		{
			buffer1 = res.bits[j] << 7;
			res.bits[j] = res.bits[j] >> 1;
			res.bits[j] |= buffer2;
			buffer2 = buffer1;
		}
	}
	return res;
}
BBV BBV::operator~()
{
	BBV res(len);
	for (int i = 0; i < sz; i++)
		res.bits[i] = ~bits[i];
	return res;
}
BBV::operator char* ()
{
	unsigned char m = 1;
	char* str = nullptr;
	str = new char[len + 1];
	if (str)
	{
		for (int i = 0, j = 0; i < len; i++, m = m << 1)
		{
			if (!m)					
			{
				j++;
				m = 1;
			}
			if (bits[j] & m)
				str[i] = '1';
			else
				str[i] = '0';
		}
		str[len] = '\0';
		return str;
	}
	else
	{
		throw 2;
		return str;
	}
}
bool BBV::operator==(BBV& obj)
{
	if (len != obj.len)
		return false;
	for (int i = 0; i < sz; i++)
	{
		if (bits[i] != obj.bits[i])
			return false;
	}
	return true;
}
bool BBV::operator!=(BBV& obj)
{
	if (len != obj.len)
		return true;
	for (int i = 0; i < sz; i++)
	{
		if (bits[i] != obj.bits[i])
			return true;
	}
	return false;
}
std::ostream& operator <<(std::ostream& out, const BBV& obj)
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
			std::cout << '1';
		else
			std::cout << '0';
	}
	std::cout << std::endl << "len =" << obj.len << "; sz = " << obj.sz << std::endl;
	return out;
}

std::istream& operator >>(std::istream& in, BBV& obj)
{
	std::cout << "enter len";
	std::cin >> obj.len;
	delete[] obj.bits;			//освобождение памяти
	obj.sz = obj.len / 8;
	obj.bits = NULL;
	obj.bits = new unsigned char[obj.sz];
	if (obj.bits)
	{
		for (int i = 0; i < obj.sz; i++)
			obj.bits[i] = 0;
		unsigned char m = 1;
		std::cout << "enter string";
		char sym;
		for (int i = 0, j = 0; i < obj.len; i++, m << 1)
		{
			std::cin >> sym;			
			if (!m)
			{
				m = 1;
				j++;
			}
			if (sym != '0')
				obj.bits[j] |= m;
			else
				obj.bits[j] &= (~m);
		}

		return in;
	}
	throw 2;
	return in;
}

BBV::bit BBV:: operator [] (int N)
{
	int n = N / 8;
	int k = N % 8;

	bit rez(bits + n, 1 << k);

	return rez;
}
BBV::~BBV()
{
	delete[]bits;
}
