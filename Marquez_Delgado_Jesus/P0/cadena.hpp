/*Jesús Márquez Delgado*/
#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
public:
	Cadena(int tam = 0,char c = ' ');
	Cadena(const char* s);
	Cadena(const Cadena &c);
	operator const char*() const;
	int length() const;
	Cadena& operator += (const Cadena& c);
	Cadena& operator=(const Cadena& c);
	char operator[](int i) const;
	char& operator[](int i);
	char at(int i) const;
	char& at(int i);
	Cadena substr(int i,int j) const;
	~Cadena();

private:
	char *s_;
	int tam_;
};

Cadena operator +(const Cadena& a,const Cadena& b);

bool operator <(const Cadena& a,const Cadena& b);

bool operator ==(const Cadena& a,const Cadena& b);

bool operator !=(const Cadena& a,const Cadena& b);

bool operator >(const Cadena& a,const Cadena& b);

bool operator <=(const Cadena& a,const Cadena& b);

bool operator >=(const Cadena& a,const Cadena& b);

#endif //CADENA_HPP_