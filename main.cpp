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

static number CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg, LPARAM lParam, LPARAM lpData)
{

    if(uMsg == BFFM_INITIALIZED)
    {
        string tmp = (const char *) lpData;
        //cout << "path: " << tmp << std::endl;
        SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
    }

    return 0;
}
number positionchar (texto stringvalues,number pos)
{
    if(pos==1){
        for(int i=0; i<stringvalues.length();i++){
            if(stringvalues[i]!=' '){
                return  i;
            }
        }
    }
    if(pos==2){
        for(int i=stringvalues.length()-1; i>=0;i--){
            if(stringvalues[i]!=' '){
                return  i;
            }
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
void PrintText( texto ruta){
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
void justificar(texto ruta){
    ifstream myfile( ruta );
    unsigned max_size = 0;
    texto line;
    ofstream outfile;
    texto path=BrowseFolder("D:'\'");
    outfile.open(path+"\\justificar.txt", fstream::in | fstream::out | fstream::trunc);
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
            number inichar=positionchar(line,1);
            number finish=positionchar(line,2);
            line=line.substr(inichar,finish-inichar+1);

            if(line.size()==max_size){
                //mismo numero de max_size
                outfile << line << '\n';
                //cout<<line<<"\n";
            }
            else if (line.size()>70){
                //mayores a 70 caracteres pero diferente de el max.
                istringstream iss( line );
                string temp_line;
                string new_text;
                number contador=0;
                number newcontadot=0;
                string temp;
                while (iss>>temp){
                    new_text+=temp+" ";
                    contador++;
                }
                number need_space = max_size - (new_text.size()-1);
                number count_space = (contador-1);
                number per_espace=need_space/count_space;
                number sobrantes=need_space%count_space;

                string temp2;
                istringstream iss2(line);
                while (iss2>>temp2){
                    if(newcontadot!=contador){
                        temp_line +=  temp2+" ";
                    }else {
                        temp_line += temp2;
                    }
                    for (number i=0;i<per_espace;i++){
                        temp_line +=" ";
                        if(sobrantes!=0){
                            temp_line +=" ";
                            sobrantes--;
                        }
                    }
                    newcontadot++;
                }

                outfile << temp_line << '\n';
                cout  << temp_line << '\n';

           }
            else{
                outfile << line << '\n';
                cout<<line<<"\n";
            }
        }
        myfile.close();
        outfile.close();
        cout<<"\n";
    }
    else cout << "Unable to open file";
}
void alinear(texto ruta ,number opcion){
    texto tipoalinear="";
    if(opcion==1){
        tipoalinear="derecha";
    }else if(opcion==2){
        tipoalinear="izquierda";
    }else{
        tipoalinear="centro";
    }
    ifstream myfile( ruta );
    unsigned max_size = 0;
    texto line;
    ofstream outfile;
    texto path=BrowseFolder("D:'\'");
    outfile.open(path+"\\alinear"+tipoalinear+".txt", fstream::in | fstream::out | fstream::trunc);

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
            number inichar=positionchar(line,1);
            number finish=positionchar(line,2);
            line=line.substr(inichar,finish-inichar+1);
            if(line.size()==max_size){
                outfile << line << '\n';
                cout<<line<<"\n";
            }
            else{
                unsigned need_space = max_size - line.size();
               // string temp_line;
                if(opcion==1){
                    while( need_space-- ){
                        line.insert(0," ");
                    }
                    //temp_line+=line;
                }
                if(opcion==2){
                    //temp_line+=line;
                    while( need_space-- ){
                        //temp_line +=" ";
                        line.push_back(' ');
                    }
                }
                if(opcion==3){
                    while( need_space-- ){
                        if(need_space%2==0){
                            line.push_back(' ');
                        }else{
                            line.insert(0," ");
                        }
                    }
                }
                outfile << line << '\n';
                cout  << line << '\n';
            }
        }
        myfile.close();
        outfile.close();
        cout<<"\n";
    }
    else cout << "Unable to open file";
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
    ofn.lpstrTitle   = "Select a File, yo!";
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
void BuscarPalabra(texto ruta,texto palabra){
    ifstream myfile( ruta );
    unsigned max_size = 0;
    string line;
    number linea=0;
    number pal=0;
    if (myfile.is_open()) {
        while ( getline (myfile,line) )
        {
            string word;
            stringstream s(line);
            while (s>>word){
                if(palabra==word){
                    cout<<"Linea: "<<linea+1<<", Palabra:"<<pal++<<endl;
                }
                pal++;
            }
            linea++;
        }
        myfile.close();

    }else{
        cout << "Unable to open file";
    }
}
void replazar(texto ruta, texto remplazo,texto nueva){
    ifstream myfile( ruta );
    unsigned max_size = 0;
    string line;
    ofstream outfile;
    texto path=BrowseFolder("D:'\'");
    outfile.open(path+"\\remplazar.txt", fstream::in | fstream::out | fstream::trunc);
    if (myfile.is_open()) {
        while ( getline (myfile,line) )
        {
            while(line.find(remplazo)!=string::npos){
                 line.replace(line.find(remplazo),remplazo.length(),nueva);
            }
            cout  << line << '\n';
            outfile << line << '\n';
        }
        myfile.close();
        outfile.close();
        cout<<"\n";

    }else{
        cout << "Unable to open file";
    }
}
void contarpalabra(texto ruta,texto palabra){
    ifstream myfile( ruta );
    unsigned max_size = 0;
    texto line;
    number contador=0;
    if (myfile.is_open()) {
        while ( getline (myfile,line) )
        {
            string word;
            stringstream s(line);
            while (s>>word){
                if(palabra==word){
                   contador++;
                }
            }

        }
        cout<<"# de veces palabra "<<palabra<< ": "<<contador<<endl;
        myfile.close();

    }else{
        cout << "Unable to open file";
    }
}
void cifrado(texto ruta,number opcion){
    texto type=(opcion==1?"encriptado":"desencriptado");
    texto ABC ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    texto abc="abcdefghijklmnopqrstuvwxyz";
    number n=5;
    ifstream myfile( ruta );
    texto line;
    ofstream outfile;
    texto path=BrowseFolder("D:'\'");
    outfile.open(path+"\\"+type+".txt", fstream::in | fstream::out | fstream::trunc);
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {

            switch (opcion) {
                case 1:
                    for (number i = 0; line[i]; i++) {
                        if (abc.find(line[i]) <= 26) {
                            //cout<<abc.find(texto[i])<<endl;
                            line[i] = abc[(abc.find(line[i]) + n) % 26];
                        }
                        if (ABC.find(line[i]) <= 26) {
                            //cout<<ABC.find(texto[i])<<endl;
                            line[i] = ABC[(ABC.find(line[i]) + n) % 26];
                        }
                    }
                    break;
                case 2:
                    for (number i = 0; line[i]; i++) {
                        if (abc.find(line[i]) <= 26) {
                            //cout<<abc.find(texto[i])<<endl;
                            line[i] = abc[(abc.find(line[i]) - n + 26) % 26];
                        }
                        if (ABC.find(line[i]) <= 26) {
                            //cout<<ABC.find(texto[i])<<endl;
                            line[i] = ABC[(ABC.find(line[i]) - n + 26) % 26];
                        }
                    }
                    break;
            }
            cout  << line << '\n';
            outfile << line << '\n';
        }
        myfile.close();
        outfile.close();
        cout<<"\n";
        }
    else{
        cout << "Unable to open file";
    }

}

int main() {
    number opcion = -1;
    boleano encriptado=false;
    texto ruta="";

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
        texto remplazo,nueva;
        switch (opcion){
            case 9:
                ruta=GetFileGraphWindows();
                cifrado(ruta,1);
                break;
            case 10:
                ruta=GetFileGraphWindows();
                cifrado(ruta,2);
                break;
            case 1 :
                ruta=GetFileGraphWindows();
                PrintText(ruta);
                break;
            case 7:
                ruta=GetFileGraphWindows();
                cout<<"Ingrese palabra a replazar: ";
                cin>>remplazo;
                cout<<"Ingrese palabra palabra nueva: ";
                cin>>nueva;
                replazar(ruta,remplazo,nueva);
                break;
            case 8:
                ruta=GetFileGraphWindows();
                cout<<"Ingrese palabra a contar: ";
                cin>>nueva;
                contarpalabra(ruta,nueva);
                break;
            case 2:
                ruta=GetFileGraphWindows();
                justificar(ruta);
                break;
            case 3:
                ruta=GetFileGraphWindows();
                alinear(ruta,1);
                break;
            case 4:
                ruta=GetFileGraphWindows();
                alinear(ruta,2);
                break;
            case 5:
                ruta=GetFileGraphWindows();
                alinear(ruta,3);
                break;
            case 6:
                ruta=GetFileGraphWindows();
                texto palabra;
                cout<<"Ingrese palabra para buscar: ";
                cin>>palabra;
                BuscarPalabra(ruta,palabra);
                break;
        }
    }

    return 0;
}