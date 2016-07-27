#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

//using namespace std;

void calculate(int LN, std::string *secuencias);

int main()
{

    int LN = 0;
    std::string *secuencias;
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

        secuencias = new std::string[LN];

        for(int i = 0; i < LN; ++i)
        {
            std::getline(file, secuencias[i]);
            std::cout << secuencias[i] << std::endl;
        }
    }

    calculate(LN, secuencias);

    file.clear();
    file.close();

    delete secuencias;
}

// individual code

struct Secuencia
{
    int N = 0, M = 0;
    bool saltarina = 0;
    std::vector<int> mSecuencias;
    std::vector<int> mDiferencias;

    Secuencia(std::string str)
    {
        N = std::stoi(std::string(1, str[0]));
        for(int i = 1; i < str.size(); ++i)
            if(str[i] != ' ')
            {
                mSecuencias.push_back(std::stoi(std::string(1, str[i])));
                std::cout << mSecuencias.back() << std::endl;
            }

    }

    int verify()
    {
        for(auto it1 = mSecuencias.begin(); it1 != mSecuencias.end(); ++it1)
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
                std::cout << "Not found" << std::endl;
                M = i;
                break;
            }
        }

        return M;
    }
};

void calculate(int LN, std::string *secuencias)
{
    for(int i = 0; i < LN; ++i)
    {
        Secuencia s(secuencias[i]);
        std::cout << s.verify() << std::endl;
    }
}
