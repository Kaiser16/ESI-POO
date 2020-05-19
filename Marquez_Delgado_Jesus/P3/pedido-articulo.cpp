#include "pedido-articulo.hpp"

void Pedido_Articulo::pedir(Pedido* ped,Articulo* art,double precio,unsigned cantidad = 1)
{
    ItemsPedido ip;
    Pedidos p;
    LineaPedido lp(precio,cantidad);
    ip.insert(std::pair<Articulo*,LineaPedido>(art,lp));
    p.insert(std::pair<Pedido*,LineaPedido>(ped,lp));
    pedArts.insert(std::pair<Pedido*,ItemsPedido>(ped,ip));
    artPeds.insert(std::pair<Articulo*,Pedidos>(art,p));
}

void Pedido_Articulo::pedir(Articulo* art,Pedido* ped,double precio,unsigned cantidad = 1)
{
    ItemsPedido ip;
    Pedidos p;
    LineaPedido lp(precio,cantidad);
    ip.insert(std::pair<Articulo*,LineaPedido>(art,lp));
    p.insert(std::pair<Pedido*,LineaPedido>(ped,lp));
    pedArts.insert(std::pair<Pedido*,ItemsPedido>(ped,ip));
    artPeds.insert(std::pair<Articulo*,Pedidos>(art,p));    
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p) const
{
    return pedArts.find(&p)->second;
}

const Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& a) const
{
    return artPeds.find(&a)->second;
}

std::ostream& operator <<(std::ostream& os,Pedido_Articulo::ItemsPedido artsPed)
{
    double total = 0;
    os<<" PVP\tCantidad\tArticulo"<<std::endl;
    os<<"=================================================================="<<std::endl;
    for(Pedido_Articulo::ItemsPedido::iterator it = artsPed.begin(); it != artsPed.end(); ++it)
    {
        os<<it->second.precio_venta()<<" €\t"<<it->second.cantidad();
        os<<"\t["<<it->first->referencia()<<"] \""<<it->first->titulo()<<"\""<<std::endl;
        total += it->second.precio_venta()*it->second.cantidad();
    }
    os<<"=================================================================="<<std::endl;
    os<<"Total\t"<<total<<std::endl;
}

std::ostream& operator <<(std::ostream& os,Pedido_Articulo::Pedidos pedidos)
{
    double total = 0;
    unsigned nArticulos = 0;
    os<<"[Pedidos: "<<pedidos.begin()->first->n_total_pedidos()<<"]"<<std::endl;
    os<<"=================================================================="<<std::endl;
    os<<" PVP\tCantidad\tFecha de venta"<<std::endl;
    os<<"=================================================================="<<std::endl;
    for(Pedido_Articulo::Pedidos::iterator it = pedidos.begin(); it != pedidos.end(); ++it)
    {
        os<<it->second.precio_venta()<<" €\t"<<it->second.cantidad()<<"\t";
        os<<it->first->fecha()<<std::endl;
        total += it->first->total();
        nArticulos +=it->second.cantidad();
    }
    os<<"=================================================================="<<std::endl;
    os<<total<<" €\t"<<nArticulos<<std::endl;
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
    for(auto it = pedArts.begin(); it != pedArts.end(); ++it)
    {
        os<<"Pedido num. "<<it->first->numero()<<std::endl;
        os<<"Cliente: "<<it->first->tarjeta()->titular()->id()<<"\t";
        os<<"Fecha: "<<it->first->fecha()<<std::endl;
    }
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
    for(auto it = artPeds.begin(); it != artPeds.end(); ++it)
    {
        os<<"Ventas de ["<<it->first->referencia()<<"] \""<<it->first->titulo()<<"\""<<std::endl;
    }
}

const double LineaPedido::precio_venta() const
{
    return precioVenta_;
}

const double LineaPedido::cantidad() const
{
    return catidadVendida_;
}