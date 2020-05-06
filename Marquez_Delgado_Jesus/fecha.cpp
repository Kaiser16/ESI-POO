#include "fecha.hpp"

Fecha::Fecha(int d,int m,int a): dia_(d), mes_(m), anno_(a)
{
	if(dia_ == 0 || mes_ == 0 || anno_ == 0)
	{
		std::time_t t_calendario = std::time(NULL);
		std::tm t_descompesto = *std::localtime(&t_calendario);
		std::mktime(&t_descompesto);
		if(dia_ == 0)
			dia_ = t_descompesto.tm_mday;
		if(mes_ == 0)
			mes_ = t_descompesto.tm_mon + 1;
		if(anno_ == 0)
			anno_ = t_descompesto.tm_year + 1900;
	}
	valida();
}

Fecha::Fecha(const char* cadena_fecha)
{
	//Comprobar si se introducen mas o menos de 3
	sscanf(cadena_fecha,"%d/%d/%d",&dia_,&mes_,&anno_);
	valida();
}

int Fecha::dia() const {return dia_;}

int Fecha::mes() const {return mes_;}

int Fecha::anno() const {return anno_;}

Fecha::Invalida::Invalida(const char* r): r_(r) {}

const char* Fecha::Invalida::por_que() const
{
	return r_;
}

bool Fecha::bisiesto() const
{
	return (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0));
}

Fecha& Fecha::operator += (int dias)
{
	dia_ += dias;
	corregir();
	valida();
	return *this;
}

Fecha& Fecha::operator -=(int dias)
{
	*this += -dias;
	return *this;
}
//PONER EXTERNA
Fecha operator +(const Fecha& f,int dias)
{
	Fecha t(f);
	return t += dias;
}
//PONER EXTERNA
Fecha operator -(const Fecha& f,int dias)
{
	Fecha t(f);
	return t += -dias;
}

Fecha Fecha::operator ++(int)//Post-incremento
{
	Fecha t(*this);
	*this+=1;
	return t;
}

Fecha& Fecha::operator ++()//Pre-incremento
{
	*this+=1;
	return *this;
}

Fecha Fecha::operator --(int)//Post-incremento
{
	Fecha t(*this);
	*this+=-1;
	return t;
}

Fecha& Fecha::operator --()//Pre-incremento
{
	*this+=-1;
	return *this;
}

int Fecha::ult_dia() const
{
	if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
		return 31;
	else if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
		return 30;
	else if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0))
		return 29;
	else
		return 28;
}

void Fecha::valida() const
{
	if(anno_ > AnnoMaximo || anno_ < AnnoMinimo)
		throw Invalida("Anno Incorrecto");
	if(mes_ > 12 || mes_ < 0)
		throw Invalida("Mes Incorrecto");
	if(dia_ > ult_dia() || dia_ < 0)
		throw Invalida("Dia Incorrecto");
}

void Fecha::corregir()
{
	while(dia_ > ult_dia())
	{
		dia_ -= ult_dia();
		mes_++;
		if(mes_ > 12)
		{
			mes_ = 1;
			anno_++;
		}
	}
	while(dia_ < 1)
	{
		mes_--;
		if(mes_ < 1)
		{
			mes_ = 12;
			anno_--;
		}
		dia_ += ult_dia();
	}
}

const char* Fecha::cadena() const 
{
	setlocale(LC_TIME,"es_ES.UTF-8");
  	setlocale(LC_TIME,"es_utf8");
  	setlocale(LC_TIME,"Spanish_Spain");
  	std::time_t t = std::time(NULL);
  	std::tm* tm = std::localtime(&t);
  	tm->tm_mday = dia_;
  	tm->tm_mon = mes_ - 1;
  	tm->tm_year = anno_ - 1900;
  	std::mktime(tm);

  	static char f[100];
  	std::strftime(f,100,"%A %d de %B de %Y",tm);
  	return f;
}

bool operator ==(const Fecha& a,const Fecha& b)
{
	if(a.dia() == b.dia() && a.mes() == b.mes() && a.anno() == b.anno())
		return true;
	else 
		return false;
}

bool operator <(const Fecha& a,const Fecha& b)
{
	if(a.anno() < b.anno())
		return true;
	else if(a.anno() == b.anno() && a.mes() < b.mes())
		return true;
	else if(a.anno() == b.anno() && a.mes() == b.mes() && a.dia() < b.dia())
		return true;
	return false;
}

bool operator !=(const Fecha& a,const Fecha& b)
{
	return !(a==b);
}

bool operator >(const Fecha& a,const Fecha& b)
{
	return b<a;
}

bool operator <=(const Fecha& a,const Fecha& b)
{
	return !(b<a);
}

bool operator >=(const Fecha& a,const Fecha& b)
{
	return !(a<b);
}

std::ostream& operator <<(std::ostream &out, const Fecha &f)
{
	out << f.cadena();
	return out;
}

std::istream& operator >>(std::istream &in,Fecha &f)
{	
	char cadena[11];
	in.getline(cadena,11);
	try{
		f = Fecha(cadena);
	}catch(Fecha::Invalida &e)
	{
		in.setstate(std::ios::failbit);
		throw;
	}
	return in;
}

//12/03/2020