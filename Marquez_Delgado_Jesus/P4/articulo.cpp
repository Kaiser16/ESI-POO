#include "articulo.hpp"

Articulo::Articulo(Autores& autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio)
:autores_(autores),cod_ref_(cod_ref),titulo_(titulo),f_publi_(f_publi),precio_(precio){
	if(autores_.empty())
		throw Autores_vacios();
}

const Cadena Articulo::referencia() const{
	return cod_ref_;
}

const Cadena Articulo::titulo() const{
	return titulo_;
}

const Fecha Articulo::f_publi() const{
	return f_publi_;
}

const double Articulo::precio() const{
	return precio_;
}

double& Articulo::precio(){
	return precio_;
}

std::ostream& operator << (std::ostream& os, const Articulo& a)
{
	os << "[" << a.referencia() << "]"<<" \""<<a.titulo()<<"\", ";
	auto it = a.autores().begin();
	os <<"de "<<(*it)->apellidos();
	++it;
	while(it != a.autores().end()){
		os<<", "<<(*it)->apellidos();
		++it;
	}
	os<<". "<<a.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<a.precio()<<" €\n\t";
	a.impresion_especifica(os);
	return os;
}

ArticuloAlmacenable::ArticuloAlmacenable(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,unsigned stock)
:Articulo(autores,cod_ref,titulo,f_publi,precio),stock_(stock){};

Libro::Libro(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,unsigned n_pag,unsigned stock)
:ArticuloAlmacenable(autores,cod_ref,titulo,f_publi,precio,stock),n_pag_(n_pag){};

const void Libro::impresion_especifica(std::ostream& os) const{
	os <<n_pag_<<" págs., "<<stock_<<" unidades.";
}

Cederron::Cederron(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,unsigned tam,unsigned stock)
:ArticuloAlmacenable(autores,cod_ref,titulo,f_publi,precio,stock),tam_(tam){};

const void Cederron::impresion_especifica(std::ostream& os) const{
	os <<tam_<<" MB, "<<stock_<<" unidades.";
}


LibroDigital::LibroDigital(Autores autores,Cadena cod_ref,Cadena titulo, Fecha f_publi, double precio,Fecha f_expir)
:Articulo(autores,cod_ref,titulo,f_publi,precio),f_expir_(f_expir){};

const void LibroDigital::impresion_especifica(std::ostream& os) const{
	os <<"A la venta hasta el "<<f_expir_<<".";
}


Autor::Autor(Cadena nombre,Cadena apellidos,Cadena direccion)
:nombre_(nombre),apellidos_(apellidos),direccion_(direccion){};