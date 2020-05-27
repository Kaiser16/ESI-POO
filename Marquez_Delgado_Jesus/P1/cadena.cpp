#include "cadena.hpp"

Cadena::Cadena(int tam,char c): s_(new char[tam+1]), tam_(tam)
{
	for(int i = 0;i < tam; ++i)
		s_[i] = c;
	s_[tam] = '\0';
}

Cadena::Cadena(const Cadena& c): s_(new char[c.tam_+1]), tam_(c.tam_)
{
	strcpy(s_,c.s_);
	s_[tam_] = '\0';
}

Cadena::Cadena(Cadena &&c): s_(c.s_), tam_(c.tam_)
{
	c.s_ = nullptr;
	c.tam_ = 0;
}

Cadena::Cadena(const char* s): s_(new char[strlen(s)+1]), tam_(strlen(s))
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

Cadena& Cadena::operator=(Cadena&& c)
{
	if(this != &c)
	{
		delete[] s_;
		s_ = c.s_;
		tam_ = c.tam_;
		c.s_ = nullptr;
		c.tam_ = 0;
	}
	return *this;
}

const char* Cadena::c_str() const
{
	return s_;
}

int Cadena::length() const
{
	return tam_;
}

Cadena& Cadena::operator += (const Cadena& c)
{
	char a[tam_+1];
	strcpy(a,s_);
	delete[] s_;
	s_ = new char[tam_+c.tam_+1];
	for(int i = 0;i < tam_; i++)
		s_[i] = a[i];
	for(int i = 0; i < c.tam_; i++)
		s_[i+tam_] = c[i];
	tam_ += c.tam_;
	s_[tam_] = '\0';
	return *this;
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
	if(tam_-1 < i)
		throw std::out_of_range("Fuera del tamaño de la cadena");
	return s_[i];
}

char& Cadena::at(int i)
{
	if(tam_-1 < i)
		throw std::out_of_range("Fuera del tamaño de la cadena");
	return s_[i];
}

bool operator <(const Cadena& a,const Cadena& b)
{
	if(strcmp(a.c_str(),b.c_str()) < 0)
		return true;
	else
		return false;
}

bool operator ==(const Cadena& a,const Cadena& b)
{
	if(strcmp(a.c_str(),b.c_str()) == 0)
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
	if(j < 0 || tam < 0 || j > tam_ || j + tam > tam_)
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

std::ostream& operator <<(std::ostream& os,const Cadena &c)
{
	os << c.c_str();
	return os;
}

std::istream& operator >>(std::istream& is, Cadena &c)
{
	char aux[33] = ""; 

    is.width(33);  
    is >> aux;
    c = aux;

    return is;
}

Cadena::iterator Cadena::begin(){return s_;}

Cadena::iterator Cadena::end(){return s_ + tam_;}

Cadena::const_iterator Cadena::begin() const{return s_;}
Cadena::const_iterator Cadena::end() const{return s_ + tam_;}
Cadena::const_iterator Cadena::cbegin() const{return s_;}
Cadena::const_iterator Cadena::cend() const{return s_ + tam_;}

Cadena::reverse_iterator Cadena::rbegin(){return reverse_iterator(end());}
Cadena::reverse_iterator Cadena::rend(){return reverse_iterator(begin());}

Cadena::const_reverse_iterator Cadena::rbegin() const{return const_reverse_iterator(cend());}
Cadena::const_reverse_iterator Cadena::rend() const{return const_reverse_iterator(cbegin());}
Cadena::const_reverse_iterator Cadena::crbegin() const{return const_reverse_iterator(cend());}
Cadena::const_reverse_iterator Cadena::crend() const{return const_reverse_iterator(cbegin());}
