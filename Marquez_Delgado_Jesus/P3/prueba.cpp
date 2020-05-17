#include <iostream>
#include "usuario.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "string"

int main()
{
    std::string s("123412   1234412388");
    
    try{
        Numero n("123412   1234412388");
    }catch(Numero::Incorrecto& e)
    {
        std::cout<<e.razon()<<std::endl;
    }
}