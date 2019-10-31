//
// Created by Jorge Luis Vasquez on 31/10/2019.
//
#include "CArchivo.h"

CArchivo::CArchivo(){

}

CArchivo::CArchivo(texto ruta){
    this->ruta=ruta;
}

CArchivo::CArchivo(texto ruta,texto outruta){
    this->ruta=ruta;
    this->outruta=outruta;
}

number CArchivo::PositionChar (texto stringvalues,number pos)
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

void CArchivo::PrintText( ){
    string line;
    ifstream myfile (CArchivo::ruta);
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

void CArchivo::Justificar(){
    ifstream myfile( CArchivo::ruta );
    number max_size = 0;
    texto line;
    ofstream outfile;
    //texto path=BrowseFolder("D:'\'");
    outfile.open(CArchivo::outruta+"\\justificar.txt", fstream::in | fstream::out | fstream::trunc);
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
            number inichar=CArchivo::PositionChar(line,1);
            number finish=CArchivo::PositionChar(line,2);
            line=line.substr(inichar,(finish-inichar)+1);

            if(line.size()==max_size){
                outfile << line << '\n';
                cout<<line<<'\n';
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

void CArchivo::Alinear(number opcion){
    texto tipoalinear="";

    if(opcion==1){
        tipoalinear="derecha";
    }else if(opcion==2){
        tipoalinear="izquierda";
    }else{
        tipoalinear="centro";
    }
    ifstream myfile( CArchivo::ruta );
    unsigned max_size = 0;
    texto line;
    ofstream outfile;
    //texto path=BrowseFolder("D:'\'");
    outfile.open( CArchivo::outruta+"\\alinear"+tipoalinear+".txt", fstream::in | fstream::out | fstream::trunc);

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
            number inichar=CArchivo::PositionChar(line,1);
            number finish=CArchivo::PositionChar(line,2);
            line=line.substr(inichar,(finish-inichar)+1);
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

void CArchivo::BuscarPalabra(texto palabra){
    ifstream myfile( CArchivo::ruta );
    unsigned max_size = 0;
    texto line;
    number linea=0;
    number pal=0;
    if (myfile.is_open()) {
        while ( getline (myfile,line) )
        {
            texto word;
            stringstream s(line);
            while (s>>word){
                if(palabra==word){
                    cout<<"Linea: "<<linea+1<<", Palabra:"<<pal+1<<endl;
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

void CArchivo::Remplazar(texto remplazo,texto nueva){
    ifstream myfile( CArchivo::ruta );
    unsigned max_size = 0;
    texto line;
    ofstream outfile;
    //texto path=BrowseFolder("D:'\'");
    outfile.open(CArchivo::outruta+"\\remplazar.txt", fstream::in | fstream::out | fstream::trunc);
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

void CArchivo::ContarPalabra(texto palabra){
    ifstream myfile( CArchivo::ruta );
    unsigned max_size = 0;
    texto line;
    number contador=0;
    if (myfile.is_open()) {
        while ( getline (myfile,line) )
        {
            texto word;
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

void CArchivo::Cifrado(number opcion){
    texto type=(opcion==1?"encriptado":"desencriptado");
    texto ABC ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    texto abc="abcdefghijklmnopqrstuvwxyz";
    number n=5;
    ifstream myfile( CArchivo::ruta );
    texto line;
    ofstream outfile;
    //texto path=BrowseFolder("D:'\'");
    outfile.open(CArchivo::outruta+"\\"+type+".txt", fstream::in | fstream::out | fstream::trunc);
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {

            switch (opcion) {
                case 1:
                    for (number i = 0; line[i]; i++) {
                        if (abc.find(line[i]) <= 26) {
                            line[i] = abc[(abc.find(line[i]) + n) % 26];
                        }
                        if (ABC.find(line[i]) <= 26) {
                            line[i] = ABC[(ABC.find(line[i]) + n) % 26];
                        }
                    }
                    break;
                case 2:
                    for (number i = 0; line[i]; i++) {
                        if (abc.find(line[i]) <= 26) {
                            line[i] = abc[(abc.find(line[i]) - n + 26) % 26];
                        }
                        if (ABC.find(line[i]) <= 26) {
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

void CArchivo::setRuta(texto ruta) {
    CArchivo::ruta = ruta;
}

void CArchivo::setOutruta( texto outruta) {
    CArchivo::outruta = outruta;
}
