#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <sstream>
#include <algorithm>


using namespace std;
typedef int number;
typedef bool boleano;
typedef  string texto;

static int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lParam, LPARAM lpData)
{

    if(uMsg == BFFM_INITIALIZED)
    {
        string tmp = (const char *) lpData;
        cout << "path: " << tmp << std::endl;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}
string BrowseFolder(string saved_path)
{
    TCHAR path[MAX_PATH];

    wstring wsaved_path(saved_path.begin(),saved_path.end());
    const wchar_t * path_param = wsaved_path.c_str();

    BROWSEINFO bi = { 0 };
    bi.lpszTitle  = ("Browse for folder...");
    bi.ulFlags    = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn       = BrowseCallbackProc;
    bi.lParam     = (LPARAM) path_param;

    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );

    if ( pidl != 0 )
    {
        //get the name of the folder and put it in path
        SHGetPathFromIDList ( pidl, path );

        //free memory used
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

void PrintText( string ruta){
    string line;
    ifstream myfile (ruta);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
        cout<<"\n";
    }
    else cout << "Unable to open file";
}

void justificar(string ruta){

    ifstream myfile( ruta );
    unsigned max_size = 0;
    string line;

    if (myfile.is_open())
    {
        unsigned max_size = 0;
        while ( getline (myfile,line) ){
            if ( max_size < line.size() ) max_size = line.size();
        }
        //limpiar
        myfile.clear();
        myfile.seekg( 0 , ios_base::beg );  // rewind


        while ( getline (myfile,line) )
        {
            if(line.size()==max_size){
                //mismo numero de max_size
                cout<<line<<"\n";
            }
            else if (line.size()>70){
                //mayores a 70 caracteres pero diferente de el max.
                unsigned need_space = max_size - line.size();
                unsigned count_space = count( line.begin(), line.end(), ' ' );

                istringstream iss( line );

                string temp_line;
                while( need_space-- && count_space-- ){
                    string temp;
                    iss >> temp;
                    temp_line +=  temp + "  ";
                }
                iss.get();  // get rid of a single space in the iss stream
                // extracts the rest of the iss stream:
                temp_line.append(  istreambuf_iterator<char>( iss ), istreambuf_iterator<char>() );
                cout  << temp_line << '\n';
           }
            else{
                //menores de 70 caracteres
                cout<<line<<"\n";
            }
        }
        myfile.close();
        cout<<"\n";
    }
    else cout << "Unable to open file";
}


string GetFileGraphWindows(){
    char filename[ MAX_PATH ];
    OPENFILENAME ofn;
    ZeroMemory( &filename, sizeof( filename ) );
    ZeroMemory( &ofn,      sizeof( ofn ) );
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter  = "Text Files\0*.txt\0Any File\0*.*\0";
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = "Select a File, yo!";
    ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA( &ofn ))
    {
        //std::cout << "You chose the file \"" << filename << "\"\n";
        return filename;
    }
    else
    {
        // All this stuff below is to tell you exactly how you messed up above.
        // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
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


int main() {
    //string ruta="../example.txt";
    //PrintText(ruta);
    number opcion = -1;
    boleano encriptado=false;
    //Primero debo seleecionar el archivo.
    texto ruta="";
    //texto path = BrowseFolder("D:'\'");
    //cout<<path;

    while(opcion!=0) {
        cout << "Menu de Acciones: " << "\n";
        //cout<<"Texto Seleccionado: "<<ruta<<"\n";
        cout << "1. Leer Archivo" << "\n";
        cout << "2. Justificar" << "\n";
        cout << "3. Alinear texto a la izquierda" << "\n";
        cout << "4. Alinear texto a la derecha" << "\n";
        cout << "5. Centrar Text" << "\n";
        cout << "6. Buscar una palabra" << "\n";
        cout << "7. Reemplazar una palabra" << "\n";
        cout << "8. Contar la cantidad de veces que aparece una palabra" << "\n";
        if(encriptado){
            cout << "9. Encriptar" << "\n";
        }else{
            cout << "9. Desencriptar" << "\n";
        }
        cout << "0. Salir" << "\n";
        cout<<"Seleccione opcion: "<<"\n";
        cin>>opcion;
        switch (opcion){
            case 1 :
                ruta=GetFileGraphWindows();
                PrintText(ruta);
                break;
            case 2:
                ruta=GetFileGraphWindows();
                justificar(ruta);
                break;
        }
    }

    return 0;
}