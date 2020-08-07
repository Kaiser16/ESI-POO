#include "pedido.hpp"

unsigned Pedido::Npedidos_ = 0;

Pedido::Pedido(Usuario_Pedido& usuPed,Pedido_Articulo& pedArt,Usuario& usuario,const Tarjeta& tarjeta,const Fecha& fecha)
: num_(Npedidos_+1), tarjeta_(&tarjeta), fecha_(fecha), total_(0.0)
{
    if(usuario.compra().empty())
        throw Pedido::Vacio(&usuario);
    else if(usuario.id() != tarjeta_->titular()->id())
        throw Pedido::Impostor(&usuario);
    else if(tarjeta_->caducidad() < fecha_)
        throw Tarjeta::Caducada(tarjeta_->caducidad());
    else if(!tarjeta_->activa())
        throw Tarjeta::Desactivada();
    else
    {
        Usuario::Articulos compra = usuario.compra();
        for(Usuario::Articulos::iterator it = compra.begin(); it != compra.end(); ++it)
        {
            if(ArticuloAlmacenable* Aa = dynamic_cast<ArticuloAlmacenable*>(it->first))
            {
                if(Aa->stock() < it->second)
                {
                    for(Usuario::Articulos::iterator auxit = it; auxit != compra.end(); ++auxit)
                        usuario.compra(*auxit->first,0);
                    throw Pedido::SinStock(Aa);
                }
            }
            else if(LibroDigital* Ld = dynamic_cast<LibroDigital*>(it->first))
            {
                if(Ld->f_expir() < fecha)
                    usuario.compra(*it->first,0);
            }
        }

        if(usuario.compra().empty())
            throw Pedido::Vacio(&usuario);
        
        compra = usuario.compra();
        for(Usuario::Articulos::iterator it = compra.begin(); it != compra.end(); ++it)
        {
            if(ArticuloAlmacenable* Aa = dynamic_cast<ArticuloAlmacenable*>(it->first))
                Aa->stock() -= it->second;
            pedArt.pedir(*this,*it->first,it->first->precio(),it->second);
            total_ += it->first->precio() * it->second;
            usuario.compra(*it->first,0);
        }
        usuPed.asocia(*this,usuario);
    }
    Npedidos_++;
}

const unsigned Pedido::numero() const
{
    return num_;
}

const Tarjeta* Pedido::tarjeta() const
{
    return tarjeta_;
}

const Fecha Pedido::fecha() const
{
    return fecha_;
}

const double Pedido::total() const
{
    return total_;
}

std::ostream& operator << (std::ostream& os, const Pedido& p)
{
    os<<"Núm. pedido: "<<p.numero()<<std::endl;
    os<<"Fecha:       "<<p.fecha()<<std::endl;
    os<<"Pagado con:  ";
    
    if(p.tarjeta()->tipo() == Tarjeta::AmericanExpress)
		os<<"AmericanExpress";
	else if(p.tarjeta()->tipo() == Tarjeta::JCB)
		os<<"JCB";
	else if(p.tarjeta()->tipo() == Tarjeta::VISA)
		os<<"VISA";
	else if(p.tarjeta()->tipo() == Tarjeta::Mastercard)
		os<<"Mastercard";
	else if(p.tarjeta()->tipo() == Tarjeta::Maestro)
		os<<"Maestro";
	else
		os<<"Tipo indeterminado";
    os<<" n.º: "<<p.tarjeta()->numero()<<std::endl;
    os<<"Importe:     "<<std::fixed<<std::setprecision(2)<<p.total()<<" €"<<std::endl;

    return os;
}