#include "pedido.hpp"

Pedido::Pedido(Usuario_Pedido& usuPed,Pedido_Articulo& pedArt,Usuario& usuario,
Tarjeta& tarjeta,Fecha& fecha): tarjeta_(&tarjeta), fecha_(fecha)
{
    if(usuario.compra().empty())
        throw Vacio(usuario);
    else if(usuario.id() != tarjeta_->titular()->id())
        throw Impostor(usuario);
    else if(tarjeta_->caducidad() < fecha_)
        throw Tarjeta::Caducada(tarjeta_->caducidad());
    else if(!tarjeta_->activa())
        throw Tarjeta::Desactivada();
    else
    {
        Usuario::Articulos compra = usuario.compra();
        for(Usuario::Articulos::iterator it = compra.begin(); it != compra.end(); ++it)
        {
            if(it->first->stock() < it->second)
                throw Pedido::SinStock(*it->first);
            else
            {
                it->first->stock() -= it->second;
                pedArt.pedir(*this,*it->first,it->first->precio(),it->second);
                total_ += it->first->precio() * it->second;
                usuario.compra(*it->first,0);
            }
        }        
        usuPed.asocia(*this,usuario);
    }
}

const unsigned Pedido::numero() const
{
    return numero_;
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

const unsigned Pedido::n_total_pedidos() const
{
    return n_total_pedidos_;
}

std::ostream& operator << (std::ostream& os, const Pedido& p)
{
    os<<"\n";
    os<<"Num. pedido:\t"<<p.numero()<<std::endl;
    os<<"Fecha:\t"<<p.fecha()<<std::endl;
    os<<"Pagado con:\t";
    
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
		os<<"Otros";

    os<<" n.º: "<<p.tarjeta()->numero()<<std::endl;
    os<<"Importe:\t"<<p.total()<<" €"<<std::endl;

    return os;
}