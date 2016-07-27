#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <regex>

//using namespace std;

void calculate(int LN, int **secuencias);

int main()
{

    int LN = 0;
    int **secuencias;
    // Read file part
    std::ifstream file;
    file.open("Saltrina.in");
    if(file.is_open())
    {

//        algorithm count function
//        Returns the number of elements in the range [first,last) that compare equal to val.
//        The function uses operator== to compare the individual elements to val.
//        The default-constructed std::istreambuf_iterator is known as the end-of-stream iterator.
//        When a valid std::istreambuf_iterator reaches the end of the underlying stream.

        LN = std::count(std::istreambuf_iterator<char>(file),
                   std::istreambuf_iterator<char>(),
                   '\n'
                   );
        // clear error flag
        file.clear();
        // set pos to 0.
        file.seekg(0);

        secuencias = new int*[LN];

        for(int i = 0; i < LN; ++i)
        {
            // Number of seccesive numbers is 'n'.
            int n = 0;
            file >> n;

            //
            secuencias[i] = new int[n + 1];
            secuencias[i][0] = n;

            std::cout << n << " ";

            for(int j = 1; j <= n; ++j)
            {
                file >> secuencias[i][j];
                std::cout << secuencias[i][j] << " ";
            }

            std::cout << std::endl;

        }
    }

    calculate(LN, secuencias);

    file.clear();
    file.close();

//    delete secuencias;
}

// individual code

struct Secuencia
{
    int N = 0, M = 0;
    bool saltarina = 0;
    std::vector<int> mSecuencias;
    std::vector<int> mDiferencias;

    Secuencia(int* sec)
    {
        N = sec[0];
        for(int i = 1; i <= N; ++i)
            mSecuencias.push_back(sec[i]);
    }

    int verify()
    {
        for(auto it1 = mSecuencias.begin(); it1 != mSecuencias.end() - 1; ++it1)
        {
            auto it2 = it1 + 1;
            // Get difference between max and min
            int d = std::max(*it1, *it2) - std::min(*it1, *it2);
            mDiferencias.push_back(d);
        }

        // initialize i to 1
        for(int i = 1; i < N; ++i)
        {
            bool found = false;
            for(int j = 0; j < mDiferencias.size(); ++j)
            {
                if(i == mDiferencias[j])
                {
                    found = true;
                    break;
                }
            }


            if(!found)
            {
                M = i;
                break;
            }
        }

        return M;
    }
};

void calculate(int LN, int **secuencias)
{
    for(int i = 0; i < LN; ++i)
    {
        Secuencia s(secuencias[i]);

        if(s.verify() == 0)
            std::cout << "Secuencia N:" << i << " is jolly" << std::endl;
        else
            std::cout << "Secuencia N:" << i << " is Not jolly" << std::endl;
    }
}
