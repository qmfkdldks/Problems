#include <iostream>

using namespace std;

int recursion(int seed, int length)
{
    if(seed == 1)
        return length + 1;

    int t = (seed % 2 == 0) ? seed / 2 : seed * 3 + 1;
    return recursion(t, length + 1);
}

int main(int argc, char *argv[])
{
    int r1, r2;
    while(cin >> r1 >> r2)
    {
        int maxL = 0;
        int begin = std::min(r1, r2), end = std::max(r1, r2);
        for(int i = begin; i < end; ++i)
        {
            int length = recursion(i, 0);
            maxL = (length > maxL) ? length : maxL;
        }
        cout << r1 << " " << r2 << " " << maxL << endl;
    }
    return 0;
}
