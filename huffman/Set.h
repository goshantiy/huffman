#pragma once
#include "BBV.h"
#include <iostream>
class Set : public BBV
{
	int weightBits;
public:
	Set();
	explicit Set(const char*);
	Set(Set&);
	Set& operator = (const Set&);
	bool operator == (Set&);
	bool operator != (Set&);
	void PerfectSet();
	Set operator | (Set&);
	Set& operator |= (Set&);
	Set operator & (Set&);
	Set& operator &= (Set&);
	Set operator /(Set&);
	Set& operator /=(Set&);
	Set operator + (const char);
	Set& operator +=(const char);
	Set operator - (const char);
	Set& operator -=(const char);
	friend std::ostream & operator << (std::ostream & out, const Set&);
	friend std::istream & operator >> (std::istream & in, Set&);
};

