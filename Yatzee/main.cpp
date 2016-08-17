#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <map>
#include <list>
#include <bitset>
#define CATEGORY  13
#define DICE  5

using namespace std;

class Sequence;

typedef vector<int> Vint;
typedef pair<bool, int> boolint;
typedef pair<int, int> intint;
typedef map<int, int> intint_map;
typedef vector<Sequence> VSequence;
typedef std::bitset<13> Log;

vector< function < boolint(Vint &) > > functions;

VSequence gSequence;
bitset<13> availables;
// Helper
int s_accumulate(Vint &s)
{
    return accumulate(s.begin(), s.end(), 0);
}

intint get_MaxTime(Vint &s) {
    int number = 0;
    int maxTime = 0;
    for(unsigned int i = 0; i < s.size(); ++i)
    {
        int c = count(s.begin(), s.end(), s[i]);
        if(c > maxTime)
        {
            maxTime = c;
            number = s[i];
        }
    }

    return intint(maxTime, number);
}

int count_succesive(Vint &s) {
    sort(s.begin(), s.end());
    int c = 0;
    int compare = s[0];
    for(int i = 0; i < 5; ++i)
        if(s[i] != compare + i)
            break;
        else
            ++c;
    return c;
}
// Classifications

struct count_number {
    count_number(int inNumber) : number(inNumber) {}
    boolint operator()(Vint &s) {
        int c = count(s.begin(), s.end(), number);
        return boolint(c > 0, number * c);
    }
    int number;
};

boolint libre(Vint &s) { return boolint(true, s_accumulate(s)); }

boolint trio(Vint &s) {
    return boolint(get_MaxTime(s).first == 3, s_accumulate(s));
}

boolint cuatro_iguales(Vint &s) {
    return boolint(get_MaxTime(s).first == 4, s_accumulate(s));
}

boolint cinco_inguales(Vint &s) {
    return boolint(get_MaxTime(s).first == 5, 50);
}

boolint escalera_corta(Vint &s) {
    return boolint(count_succesive(s) >= 4, 25);
}

boolint escalera_larga(Vint &s) {
    return boolint(count_succesive(s) == 5, 35);
}

boolint full(Vint &s) {
    intint firstPair = get_MaxTime(s);
    Vint des;
    des.resize(s.size());
    auto end_it = remove_copy(s.begin(), s.end(), des.begin(), firstPair.second);
    des.erase(end_it, des.end());

    intint secondPair = get_MaxTime(des);

    return boolint((firstPair.first == 3 && secondPair.first == 2), 40);
}

int max_sum = 0;

struct Sequence {
    Sequence(){}
    Sequence(Vint & intvec) : mSequence(intvec) { }

    void make_table() {
        for(unsigned int i = 0; i < functions.size(); ++i)
        {
            boolint result = functions[i](mSequence);

            if(result.first)
            {
                availables[i] = true;
                mTable.insert(intint(i,result.second));
            }

//            int value = 0;
//            value =  (result.first) ? result.second : 0;
//            intint cell(i, value);
//            mTable.insert(cell);
        }
//        mTable.insert(intint(-1,0));

//        for(auto i : mSequence)
//            cout << i << ",";
//        cout << endl << "Table :" ;
//        for(auto i : mTable)
//            cout << i.first << "," << i.second << ";";
//            cout << endl;
    }

    Vint mSequence;
    intint_map mTable;
    Sequence *next;
//    bool isSelected;
//    int mIndex;
};

void recursiveFunc(Vint &inResult, Log &inLog, int inSequenceIndex, int inSum)
{

    if(inSequenceIndex > CATEGORY - 1)
    {

        if(inSum > max_sum)
        {
            cout << "Sum :" << inSum << "," << max_sum << endl;
            max_sum = inSum;
        }

        return;
    }

    intint_map &mTable = gSequence[inSequenceIndex].mTable;

    for(auto it = mTable.begin(); it != mTable.end(); ++it)
    {
        int vSequenceIndex = inSequenceIndex;
        int vSum = inSum;
        int vCategory = it->first;
        bool logged = inLog[vCategory];
        bool isLast = it == (--mTable.end());

        if(logged && isLast)
        {
            return recursiveFunc(inResult, inLog, vSequenceIndex + 1, vSum);
        }

        if(logged)
            continue;


        Vint vResult = inResult;
        Log vLog = inLog;


        int value = it->second;
        vSum += value;
        vResult.push_back(value);
        vLog[vCategory] = true;

        recursiveFunc(vResult, vLog, vSequenceIndex + 1, vSum);
    }
}

void readFile()
{
    ifstream inFile("10149.inp");
    int caseCount = count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n') / CATEGORY;
//    cout << lineNumber << endl;
    inFile.seekg(0);
    for(int i = 0; i < caseCount; ++i)
    {
        cout << i << "th case..." << endl;

        for(int j = 0; j < CATEGORY; ++j)
        {
            Vint intvec;
            for(int k = 0; k < 5; ++k)
            {
                int number = 0;
                inFile >> number;
                intvec.push_back(number);
            }

            gSequence.push_back(Sequence(intvec));
        }

        for(auto it = gSequence.begin(); it != gSequence.end(); ++it)
        {
//            cout << "it:" << &(*it) << endl;
            it->make_table();
//            if(it != (sequences.end() - 1))
//                it->next = &(*(it + 1));
        }
        Vint vtable;
        Log vLog;
        recursiveFunc(vtable, vLog, 0, 0);

        gSequence.clear();
    }
}

int main()
{

    for(int i = 1; i <= 6; ++i)
        functions.push_back( count_number(i) );

    functions.push_back(libre);
    functions.push_back(trio);
    functions.push_back(cuatro_iguales);
    functions.push_back(cinco_inguales);
    functions.push_back(escalera_corta);
    functions.push_back(escalera_larga);
    functions.push_back(full);

    readFile();

    cout << endl;

    return 0;
}
