#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;
/*
Aluno: Matheus Franklin Rodrigues Silva
Matricula: 201665552AC

Tamanho de dicionario usado: 15
Tamanho do buffer: 8
*/


int min(int a, int b)
{
    if(a<b)
        return a;
    else
        return b;
}

int max(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

vector<int> maiorSequencia(string &dicionario, string &buffer)
{
    int p = 0;
    int l = 0;

    vector<int> res;

    int tamDicionario = dicionario.size();
    int tamBuffer = buffer.size();


    for(int i=0; i<tamDicionario; i++)
    {
        int auxL = 0;
        while(auxL < min(tamBuffer, tamDicionario - i) && dicionario[i+auxL] == buffer[auxL])
        {
            auxL++;
        }
        if(auxL == tamDicionario - i) //Pode ser que haja repetição no buffer
        {
            int auxB = 0;
            while(auxL < tamBuffer && buffer[auxB] == buffer[auxL])
            {
                auxB++;
                auxL++;
            }
        }
        if(auxL > l)
        {
            l = auxL;
            p = tamDicionario - i;
        }
    }

    res.push_back(p);
    res.push_back(l);

    return res;
}

string comprimir(string codigo)
{
    int cursor = 0;
    int tamCodigo = codigo.size();

    int tamDic = 15;
    int tamBuf = 8;

    string resultado;

    while(cursor < tamCodigo)
    {
        string dicionario = codigo.substr(max(0, cursor-tamDic), min(cursor, tamDic));
        string buffer = codigo.substr(cursor, tamBuf);

        vector<int> aux = maiorSequencia(dicionario, buffer);

        int p = aux[0];
        int l = aux[1];

        resultado = resultado + "(" + to_string(p) + "," + to_string(l) + "," + codigo[cursor+l] + ")";
        cursor = cursor + l;
        cursor++;
    }

    return resultado;
}

string descomprimir(string codigo)
{

    int cursor = 0;
    int tamCodigo = codigo.size();

    string resultado;
    string aux1, aux2;
    int i1, i2, tamR, cont1, cont2;


    while(cursor < tamCodigo)
    {

        aux1.clear();
        aux2.clear();
        tamR = resultado.size();
        cont1 = 0;
        cont2 = 0;
        while(codigo[cursor+1+cont1] != ',')
        {
            aux1 = aux1 + codigo[cursor+1+cont1];
            cont1++;
        }
        cont1--;


        while(codigo[cursor+3+cont1+cont2] != ',')
        {
            aux2 = aux2 + codigo[cursor+3+cont1+cont2];
            cont2++;
        }
        cont2--;

        i1 = stoi(aux1);
        i2 = stoi(aux2);

        if(i2 ==0)
        {
            resultado = resultado + codigo[cursor+cont1+cont2+5];
        }else if(i2 > i1)
        {
            aux1 = resultado.substr(tamR - i1, i1);
            aux2 = resultado.substr(tamR - i1, i2 - i1);
            resultado = resultado + aux1 + aux2 + codigo[cursor+cont1+cont2+5];
        }else
        {
            resultado =  resultado + resultado.substr(tamR - i1, i2) + codigo[cursor+cont1+cont2+5];
        }
        cout << codigo.substr(cursor, 7+cont1+cont2) << " : " << resultado <<endl;

        cursor = cursor +7+cont1 +cont2;
    }

    return resultado;
}

int main()
{
    string f;
    cout << "Digite o nome do arquivo a ser lido: (arquivo deve estar no diretório do main.cpp)" <<endl;
    getline (cin, f);

    ifstream file;
    string linha, codigo;

    file.open(f);

    if(file.is_open())
    {
       while(getline(file, linha))
       {
           codigo = codigo+linha;
       }
    }else
    {
        cout << "Não foi possível abrir o arquivo" << endl;
        return 0;
    }


    codigo = comprimir(codigo);
    cout << codigo << endl;

    cout << "Descomprimir para teste ? 1-s|2-n" << endl;
    int op;
    cin >> op;

    if(op==1)
        cout << descomprimir(codigo) << endl;

    return 0;
}
