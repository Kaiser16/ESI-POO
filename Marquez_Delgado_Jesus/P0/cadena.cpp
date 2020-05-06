#include "cadena.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

Cadena::Cadena(int tam,char c): tam_(tam+1), s_(new char[tam+1])
{
	for(int i = 0;i < tam; ++i)
		s_[i] = c;
	s_[tam] = '\0';
}

Cadena::Cadena(const Cadena& c): tam_(c.tam_), s_(new char[c.tam_+1])
{
	strcpy(s_,c.s_);
	s_[tam_] = '\0';
}

Cadena::Cadena(const char* s): tam_(strlen(s)), s_(new char[strlen(s)+1])
{
	strcpy(s_,s);
	s_[tam_] = '\0';
}

Cadena& Cadena::operator=(const Cadena& c)
{
	if(this != &c)
	{
		if(c.tam_ != tam_)
		{
			delete[] s_;
			s_ = new char[c.tam_+1];
			tam_ = c.tam_;
		}
		strcpy(s_,c.s_);
		s_[tam_] = '\0';
	}
	return *this;
}

Cadena::operator const char*() const
{
	return s_;
}

int Cadena::length() const
{
	return tam_;
}

Cadena& Cadena::operator += (const Cadena& c)
{
	char a[c.tam_+tam_+1];
	strcpy(a,s_);
	delete[] s_;
	for(int i = 0;i < c.tam_; ++i)
		a[tam_+i] = c.s_[i];
	strcpy(s_,a);
	tam_ += c.tam_;
	s_[tam_] = '\0';
}

Cadena operator +(const Cadena& a,const Cadena& b)
{
	Cadena c(a);
	c+=b;
	return c;
}

char Cadena::operator[](int i) const
{
	return s_[i];
}

char& Cadena::operator[](int i)
{
	return s_[i];
}

char Cadena::at(int i) const
{
	if(tam_ < i)
		throw std::out_of_range("Fuera del tamaño de la cadena");
	return s_[i];
}

char& Cadena::at(int i)
{
	if(tam_ < i)
		throw std::out_of_range("Fuera del tamaño de la cadena");
	return s_[i];
}

bool operator <(const Cadena& a,const Cadena& b)
{
	if(strcmp(a,b) < 0)
		return true;
	else
		return false;
}

bool operator ==(const Cadena& a,const Cadena& b)
{
	if(strcmp(a,b) == 0)
		return true;
	else
		return false;
}

bool operator !=(const Cadena& a,const Cadena& b)
{
	return !(a==b);
}

bool operator >(const Cadena& a,const Cadena& b)
{
	return b<a;
}

bool operator <=(const Cadena& a,const Cadena& b)
{
	return !(b<a);
}

bool operator >=(const Cadena& a,const Cadena& b)
{
	return !(a<b);
}

Cadena Cadena::substr(int j,int tam) const
{
	if(j + tam > tam_)
		throw std::out_of_range("Memoria excedida al substraer");
	Cadena a(tam+1);
	for(int i = 0; i < tam; ++i)
		a.s_[i] = s_[j+i];
	a.s_[tam] = '\0';
	return a;
}

Cadena::~Cadena()
{
	delete[] s_;
}