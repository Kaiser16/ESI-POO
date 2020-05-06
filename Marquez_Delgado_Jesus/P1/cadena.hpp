/*Jesús Márquez Delgado*/
#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <ostream>
#include <cstring>
#include <stdexcept>

class Cadena
{
public:
	Cadena(int tam = 0,char c = ' ');
	Cadena(const char* s);
	Cadena(const Cadena &c);
	Cadena(Cadena &&c);
	const char* c_str() const;
	int length() const;
	Cadena& operator += (const Cadena& c);
	Cadena& operator=(const Cadena& c);
	Cadena& operator=(Cadena &&c);
	char operator[](int i) const;
	char& operator[](int i);
	char at(int i) const;
	char& at(int i);
	Cadena substr(int i,int j) const;
	~Cadena();

	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	iterator begin();
	iterator end();
	
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;


private:
	char *s_;
	int tam_;
};

std::ostream& operator <<(std::ostream& os,const Cadena &c);

std::istream& operator >>(std::istream& is, Cadena &c);

Cadena operator +(const Cadena& a,const Cadena& b);

bool operator <(const Cadena& a,const Cadena& b);

bool operator ==(const Cadena& a,const Cadena& b);

bool operator !=(const Cadena& a,const Cadena& b);

bool operator >(const Cadena& a,const Cadena& b);

bool operator <=(const Cadena& a,const Cadena& b);

bool operator >=(const Cadena& a,const Cadena& b);

namespace std { // Estaremos dentro del espacio de nombres std
	template <> // Es una especialización de una plantilla para Cadena
	struct hash<Cadena> { // Es una clase con solo un operador publico
		size_t operator() (const Cadena& cad) const // El operador función
		{
			hash<string> hs; // Creamos un objeto hash de string
			const char* p = cad.c_str(); // Obtenemos la cadena de la Cadena
			string s(p); // Creamos un string desde una cadena
			size_t res = hs(s); // El hash del string. Como hs.operator()(s);
			return res; // Devolvemos el hash del string
		}
	};
}

#endif //CADENA_HPP_