#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario* u,Pedido* p)
{
    if(Usuario_Pedido.insert(std::pair<Usuario*,std::set<Pedido*>>(u,std::set<Pedido*>(p))->second))
        Usuario_Pedido.find(u)->second.insert(p);
    Pedido_Usuario.insert(std::pair<Pedido*,Usuario*>(u,p));
}
void asocia(Pedido* p,Usuario* u)
{
    if(Usuario_Pedido.insert(std::pair<Usuario*,std::set<Pedido*>>(u,std::set<Pedido*>(p))->second))
        Usuario_Pedido.find(u)->second.insert(p);
    Pedido_Usuario.insert(std::pair<Pedido*,Usuario*>(u,p));
}

const Pedidos& pedidos(const Usuario* u) const
{
    return Usuario_Pedido.find(u)->second;
}

const Usuarios& cliente(const Pedido* p) const
{
    return Pedido_Usuario.find(p)->second;
}