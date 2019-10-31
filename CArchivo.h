//
// Created by Jorge Luis Vasquez on 31/10/2019.
//
#ifndef TRANBAJOFINAL_CARCHIVO_H
#define TRANBAJOFINAL_CARCHIVO_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <sstream>
#include <algorithm>

using namespace std;

typedef string texto;
typedef int number;

class CArchivo{

private:
    texto ruta;
    texto outruta;
    number PositionChar(texto stringvalues,number pos);
public:
    CArchivo();
    CArchivo(texto ruta,texto outruta);
    CArchivo(texto ruta);
    void PrintText();
    void Justificar();
    void Alinear(number opcion);
    void BuscarPalabra(texto palabra);
    void Remplazar(texto remplazo, texto nueva);
    void ContarPalabra(texto palabra);
    void Cifrado(number opcion);
    void setRuta(texto ruta);
    void setOutruta(texto outruta);

};
#endif //TRANBAJOFINAL_CARCHIVO_H
