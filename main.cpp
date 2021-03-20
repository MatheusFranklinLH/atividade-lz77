#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int menu()
{
    int m;
    cout << "\n>>>>> Menu <<<<<" << endl;
    cout << "1 - Comprimir string" << endl;
    cout << "0 -  Sair" << endl;
    cin >> m;
    cin.ignore(256, '\n');

    if(m > 1 || m < 0)
        m = 0;

    return m;
}

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

    int tamDic = 6;
    int tamBuf = 4;

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
    int i1, i2, tamR;

    while(cursor < tamCodigo)
    {

        tamR = resultado.size();
        aux1 = codigo[cursor+1];
        aux2 = codigo[cursor+3];
        i1 = stoi(aux1);
        i2 = stoi(aux2);

        if(i2 ==0)
        {
            resultado = resultado + codigo[cursor+5];
        }else if(i2 > i1)
        {
            aux1 = resultado.substr(tamR - i1, i1);
            aux2 = resultado.substr(tamR - i1, i2 - i1);
            resultado = resultado + aux1 + aux2 + codigo[cursor + 5];
        }else
        {
            resultado =  resultado + resultado.substr(tamR - i1, i2) + codigo[cursor+5];
        }
        cout << codigo.substr(cursor, 7) << " : " << resultado <<endl;

        cursor = cursor + 7;
    }

    return resultado;
}

int main()
{

    while(menu()!=0)
    {
        string codigo;
        cout << "Digite a string que deseja comprimir: " <<endl;
        getline (cin, codigo);

        codigo = comprimir(codigo);
        cout << codigo << endl;

        cout << "Descomprimir para teste ? 1-s|2-n" << endl;
        int op;
        cin >> op;
        cin.ignore(256, '\n');

        if(op==1)
            cout << descomprimir(codigo) << endl;
    }
    return 0;
}
