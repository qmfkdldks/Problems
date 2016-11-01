#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

ifstream in_file("encriptado.in");
ofstream out_file("encriptado.out");

string encriptado (int clave, int N, string texto);

int main()
{
    int N, clave;
    string str;
    in_file >> N >> clave;
    getline(in_file, str);
    cout << N << " " << clave;
    std::getline(in_file, str);
    cout << str << endl;
    encriptado(clave, N, str);
    in_file.close();
    return 0;
}

string encriptado(int clave, int N, string texto)
{
    auto it = std::remove(texto.begin(), texto.end(), ' ');
    texto.resize(distance(texto.begin(), it));

    string sclave = to_string(clave);
    // agregar 0 adelante
    int difference = max(N, (int)sclave.size()) - min(N, (int)sclave.size());

    sclave.insert(sclave.begin(), difference, '0');

    for(int i = 0; i < texto.size();)
        for(int j = 0; j < N; j++)
        {
            if(i > texto.size())
                break;
            // convertir a int
            int distancia = sclave[j] - '0';
            // si sobra z, devuelve 'A' + sobra sino devuelve d
            texto[i] = ( texto[i] + distancia > 90 ) ? char(64) + ((texto[i] + distancia) - 90) : texto[i] + distancia;
            ++i;
        }

    cout << texto << endl;
    return texto;
}
