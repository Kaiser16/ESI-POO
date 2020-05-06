/*Jesús Márquez Delgado*/
#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha
{
public:
	class Invalida
	{
	public:
		Invalida(const char* r);
		const char* por_que() const;
	private:
		const char* r_;
	};
	static const int AnnoMinimo = 1902, AnnoMaximo = 2037;
	explicit Fecha(int d = 0, int m = 0, int a = 0);
	Fecha(const char*);

	Fecha& operator ++();
	Fecha operator ++(int);
	Fecha& operator +=(int dias);

	Fecha& operator --();
	Fecha operator --(int);
	Fecha& operator -=(int dias);

	operator const char* () const;

	int dia() const;
	int mes() const;
	int anno() const;
	
private:
	int dia_,mes_,anno_;
	bool bisiesto() const;
	void corregir();
	void valida() const;
	int ult_dia() const;
};

Fecha operator +(const Fecha& f,int dias);

Fecha operator -(const Fecha& f,int dias);

bool operator ==(const Fecha& a,const Fecha& b);

bool operator <(const Fecha& a,const Fecha& b);

bool operator !=(const Fecha& a,const Fecha& b);

bool operator >(const Fecha& a,const Fecha& b);

bool operator <=(const Fecha& a,const Fecha& b);

bool operator >=(const Fecha& a,const Fecha& b);

#endif