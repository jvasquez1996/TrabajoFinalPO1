#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <sstream>
#include <algorithm>
#include "CArchivo.h"

using namespace std;
typedef int number;
typedef bool boleano;
typedef  string texto;

static number CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if(uMsg == BFFM_INITIALIZED)
    {
        string tmp = (const char *) lpData;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }
    return 0;
}
texto GetFileGraphWindows(){
    char filename[ MAX_PATH ];
    OPENFILENAME ofn;
    ZeroMemory( &filename, sizeof( filename ) );
    ZeroMemory( &ofn,      sizeof( ofn ) );
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter  = "Text Files\0*.txt\0Any File\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Seleccione un Archivo.";
    ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA( &ofn ))
    {

        return filename;
    }
    else
    {
        switch (CommDlgExtendedError())
        {
            case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
            case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
            case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
            case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
            case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
            case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
            case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
            case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
            case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
            case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
            case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
            case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
            case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
            case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
            case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
            default                    : std::cout << "You cancelled.\n";
        }
    }
}
texto BrowseFolder(texto saved_path)
{
    TCHAR path[MAX_PATH];
    wstring wsaved_path(saved_path.begin(),saved_path.end());
    const wchar_t * path_param = wsaved_path.c_str();
    BROWSEINFO bi = { 0 };
    bi.lpszTitle  = ("Eliga donde guardar el archivo.");
    bi.ulFlags    = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn       = BrowseCallbackProc;
    bi.lParam     = (LPARAM) path_param;
    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
    if ( pidl != 0 )
    {
        SHGetPathFromIDList ( pidl, path );
        IMalloc * imalloc = 0;
        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
        {
            imalloc->Free ( pidl );
            imalloc->Release ( );
        }
        return path;
    }
    return "";
}

int main() {
    number opcion = -1;
    while(opcion!=0) {
        cout << "Menu de Acciones: " << "\n";
        cout << "1. Leer Archivo" << "\n";
        cout << "2. Justificar" << "\n";
        cout << "3. Alinear texto a la derecha" << "\n";
        cout << "4. Alinear texto a la izquierda" << "\n";
        cout << "5. Centrar Text" << "\n";
        cout << "6. Buscar una palabra" << "\n";
        cout << "7. Reemplazar una palabra" << "\n";
        cout << "8. Contar la cantidad de veces que aparece una palabra" << "\n";
        cout << "9. Encriptar" << "\n";
        cout << "10. Desencriptar" << "\n";
        cout << "0. Salir" << "\n";
        cout<<"Seleccione opcion: "<<"\n";
        cin>>opcion;
        texto remplazo,nueva,outruta,ruta;
        CArchivo archivo;

        switch (opcion){
            case 9:
                //Encriptar
                ruta=GetFileGraphWindows();
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Cifrado(1);
                break;
            case 10:
                //Desencriptar
                ruta=GetFileGraphWindows();
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Cifrado(2);
                break;
            case 1 :
                //leer archivo.
                ruta=GetFileGraphWindows();
                archivo.setRuta(ruta);
                archivo.PrintText();
                break;
            case 7:
                // Reemplazar una palabra
                ruta=GetFileGraphWindows();
                cout<<"Ingrese palabra a replazar: ";
                cin>>remplazo;
                cout<<"Ingrese palabra palabra nueva: ";
                cin>>nueva;
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Remplazar(remplazo,nueva);
                break;
            case 8:
                //Contar la cantidad de veces que aparece una palabra
                ruta=GetFileGraphWindows();
                cout<<"Ingrese palabra a contar: ";
                cin>>nueva;
                archivo.setRuta(ruta);
                archivo.ContarPalabra(nueva);
                break;
            case 2:
                //Justificar
                ruta=GetFileGraphWindows();
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Justificar();
                break;
            case 3:
                //Alinear texto a la derecha
                ruta=GetFileGraphWindows();
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Alinear(1);
                break;
            case 4:
                //Alinear texto a la izquierda
                ruta=GetFileGraphWindows();
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Alinear(2);
                break;
            case 5:
                //Centrar Text
                ruta=GetFileGraphWindows();
                outruta=BrowseFolder("D:'\'");
                archivo.setRuta(ruta);
                archivo.setOutruta(outruta);
                archivo.Alinear(3);
                break;
            case 6:
                //Buscar una palabra
                ruta=GetFileGraphWindows();
                texto palabra;
                archivo.setRuta(ruta);
                cout<<"Ingrese palabra para buscar: ";
                cin>>palabra;
                archivo.BuscarPalabra(palabra);
                break;
        }
    }

    return 0;
}