#include "pedido-articulo.hpp"

void Pedido_Articulo::pedir(Pedido& ped,Articulo& art,double precio,unsigned cantidad)
{
    LineaPedido lp(precio,cantidad);
    pedArt[&ped].insert(std::make_pair(&art,lp));
    artPed[&art].insert(std::make_pair(&ped,lp));
}

void Pedido_Articulo::pedir(Articulo& art,Pedido& ped,double precio,unsigned cantidad)
{
    LineaPedido lp(precio,cantidad);
    pedArt[&ped].insert(std::make_pair(&art,lp));
    artPed[&art].insert(std::make_pair(&ped,lp));   
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p) const
{
    return pedArt.find(&p)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const
{
    auto it = artPed.find(&a);
    if(it != artPed.end())
        return it->second;
    else
        return Pedido_Articulo::Pedidos();
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
    double precioTotal = 0;
    for(auto it = pedArt.begin(); it != pedArt.end(); ++it)
    {
        os<<"Pedido num. "<<it->first->numero()<<std::endl;
        os<<"Cliente: "<<it->first->tarjeta()->titular()->id()<<"\t";
        os<<"Fecha: "<<it->first->fecha()<<std::endl;
        os<<it->second;
        precioTotal += it->first->total();
    }
    os<<"TOTAL VENTAS\t"<<std::fixed<<std::setprecision(2)<<precioTotal<<" €"<<std::endl;
    return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
    for(auto it = artPed.begin(); it != artPed.end(); ++it){
		os << "Ventas de [" << it->first->referencia() << "] \""
		<< it->first->titulo() << "\"\n" << it->second << std::endl;
	}
	return os;
}

LineaPedido::LineaPedido(double precioVenta,unsigned cantidadVendida)
:precioVenta_(precioVenta), cantidadVendida_(cantidadVendida)
{}

const double LineaPedido::precio_venta() const
{
    return precioVenta_;
}

const unsigned int LineaPedido::cantidad() const
{
    return cantidadVendida_;
}

bool OrdenaPedidos::operator()(const Pedido* a,const Pedido* b) const
{
    return a->numero() < b->numero();
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido& artsPed)
{
    os << "  PVP\tCantidad\tArticulo " << std::endl
	<< "==================================================================\n";
	double total = 0;
	for(auto it = artsPed.begin(); it != artsPed.end(); ++it){
		os << it->second.precio_venta() << " €\t" << it->second.cantidad() << "\t\t["
		<< it->first->referencia() << "] \"" << it->first->titulo() << "\"" << std::endl;
		total += (it->second.precio_venta() * it->second.cantidad());
	}
	os << "==================================================================\nTotal\t"
	<< total << " €\n";
	return os;
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::Pedidos& pedidos)
{
    double total = 0;
	int cantidad = 0;
	os << "[Pedidos: " << pedidos.size() << "]\n"
	<< "==================================================================\n";
	os << "  PVP\tCantidad\tArticulo " << std::endl
	<< "==================================================================\n";
	for(auto it = pedidos.begin(); it != pedidos.end(); ++it){
		os << it->second.precio_venta() << " €\t" << it->second.cantidad() << "\t\t"
		<< it->first->fecha() << std::endl;
		total += it->second.precio_venta() * it->second.cantidad();
		cantidad += it->second.cantidad();
	}
	os << "==================================================================\n"
	<< std::fixed << std::setprecision(2) << total << " €\t" << cantidad << std::endl;
	return os;
}

std::ostream& operator <<(std::ostream& os,const LineaPedido& lp)
{
    os<<std::fixed<<std::setprecision(2)<<lp.precio_venta()<<" €\t";
    os<<lp.cantidad();
    return os;
}