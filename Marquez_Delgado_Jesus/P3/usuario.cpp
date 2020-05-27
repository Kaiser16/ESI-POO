#include "usuario.hpp"

std::unordered_set<Cadena> Usuario::usuarios_{};

Clave::Clave(const char* clave)
{
	char salt[2];
	const char *const sc{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.//"};
	std::random_device r;
	std::uniform_int_distribution<> dis(0,63);
	salt[0] = sc[dis(r)];
	salt[1] = sc[dis(r)];
	if(strlen(clave) < 5)
		throw Clave::Incorrecta(CORTA);
	else if(char *encriptada = crypt(clave,salt))
		clave_ = encriptada;
	else
		throw Clave::Incorrecta(ERROR_CRYPT);
}

const Cadena Clave::clave() const
{
	return clave_;
}

bool Clave::verifica(const Cadena& clave) const
{
	if(char *encriptada = crypt(clave.c_str(),clave_.c_str()))
		return (clave_ == encriptada);
	else 
		throw Clave::Incorrecta(ERROR_CRYPT);
}

Clave::Incorrecta::Incorrecta(Razon r):r_(r){};

const Clave::Razon Clave::Incorrecta::razon() const
{
	return r_;
}

Usuario::Usuario(Cadena identificador, Cadena nombre, Cadena apellidos, Cadena direccion, Clave clave)
:identificador_(identificador), nombre_(nombre),apellidos_(apellidos),direccion_(direccion),clave_(clave)
{
	if(!(usuarios_.insert(identificador_).second))
		throw Usuario::Id_duplicado(identificador_);
}

const Cadena Usuario::direccion() const
{
	return direccion_;
}

const Usuario::Tarjetas& Usuario::tarjetas() const
{
	return tarjetas_;
}

const Usuario::Articulos& Usuario::compra() const
{
	return articulos_;
}

void Usuario::es_titular_de(Tarjeta& tarjeta)
{
	if(this == tarjeta.titular())
		tarjetas_.insert(std::pair<Numero,Tarjeta*>(tarjeta.numero(),&tarjeta));
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
	tarjeta.anular_titular();
	tarjetas_.erase(tarjeta.numero());
}

void Usuario::compra(Articulo& articulo)
{
	if(!articulos_.insert(std::make_pair(&articulo,1)).second)
	{
		articulos_.erase(&articulo);
		articulos_.insert(std::make_pair(&articulo,1));	
	}
}

void Usuario::compra(Articulo& articulo, unsigned cantidad)
{
	if(cantidad == 0)
		articulos_.erase(&articulo);
	else
	{
		if(!articulos_.insert(std::make_pair(&articulo,cantidad)).second)
		{
			articulos_.erase(&articulo);
			articulos_.insert(std::make_pair(&articulo,cantidad));	
		}
	}
}

unsigned Usuario::n_articulos() const
{
	return articulos_.size();
}

std::ostream& operator << (std::ostream& os, const Usuario& u)
{
	os <<u.identificador_<<" ["<<u.clave_.clave()<<"] "<<u.nombre_<<" "<<u.apellidos_<<"\n";
	os <<u.direccion_<<"\n";
	os <<"\nTarjetas:\n";
	Usuario::Tarjetas::const_iterator it = u.tarjetas_.begin();
	while(it != u.tarjetas_.end())
	{
		os << *(it->second);
		++it;
	}
	return os;
}

Usuario::~Usuario()
{
	Usuario::Tarjetas::const_iterator it = tarjetas_.begin();
	while(it != tarjetas_.end())
	{
		(it->second)->anular_titular();
		++it;
	}
	usuarios_.erase(identificador_);
}

Usuario::Id_duplicado::Id_duplicado(Cadena id): id_(id){};

const Cadena Usuario::Id_duplicado::idd() const
{
	return id_;
}

std::ostream& mostrar_carro (std::ostream& os, const Usuario& u)
{

	os << "Carrito de la compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << std::endl << " Cant.\tArtículo" << std::endl;
    os<<Cadena(50,'=')<<"\n";
    Usuario::Articulos compra = u.compra();
	Usuario::Articulos::const_iterator it = compra.begin();
    while(it != compra.end())
    {
        os << "  " << it->second << "\t" << "[" << it->first->referencia() << "] \"" << it->first->titulo() << "\", ";
        os << it->first->f_publi().anno() << ". " << std::setprecision(2) << std::fixed << it->first->precio() << " €" << std::endl;
        ++it;
    }
	return os;
	/*
	os<<"Carrito de la compra de "<<u.id()<<" [Articulos: "<<u.n_articulos()<<"]\n";
	os<<" Cant. Artículo\n";
	
	Usuario::Articulos compra = u.compra();
	Usuario::Articulos::const_iterator it = compra.begin();
	for(auto& i : u.compra())
    {
        os << "  " << i.second << "\t" << "[" << i.first->referencia() << "] \"" << i.first->titulo() << "\", ";
        os << i.first->f_publi().anno() << ". " << std::setprecision(2) << std::fixed << i.first->precio() << " €" << std::endl;
    }
	return os;*/
}

