#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void getHolydays(int sample, int range, int partyCount, int *parametroHartals);

int main()
{
    int sample, range, partyCount;
    int *parametroHartals;
    std::ifstream file("hartals.in");
    if(file.is_open())
    {
        file >> sample >> range >> partyCount;
        parametroHartals = new int[partyCount];
        for(int i = 0; i < partyCount; ++i)
        {
            file >> parametroHartals[i];
            cout << parametroHartals[i] << std::endl;
        }

    }

    getHolydays(sample, range, partyCount, parametroHartals);
}

char days[] = "SDLMMJV";

char getDay(int n)
{
    return days[(n % 7)];
}

struct Day
{
    Day(char day, int num) : mDay(day), mNum(num) {}
    char mDay;
    int mNum;

    bool operator<( const Day& val ) const {
    	return mNum < val.mNum;
    }
};

struct Party
{
    Party(int id) : mId(id) {}
    int mId;
    std::vector<Day> mHuelgas;
};

struct Xgreater
{
    bool operator()( const Day& lx, const Day& rx ) const {


        if(lx.mNum < rx.mNum)
            return true;
    	else
            return false;
    }
};

struct isEqual
{
 bool operator() (const Day& lx, const Day& rx ) const {
        if(lx.mNum == rx.mNum)
            return true;
    	else
            return false;
    }
};

void getHolydays(int sample, int range, int partyCount, int *parametroHartals)
{
                // merge
    std::vector<Day> dst;
    vector<Party> parties;
    for(int i = 0; i < partyCount; ++i)
    {
        Party p(i);
        int v = parametroHartals[i];
        int dayNum = 0;
        int j = 0;
        while(true)
        {
            ++j;
            dayNum = v * j;
            if(dayNum > range)
                break;
            else if(getDay(dayNum) == 'V' || getDay(dayNum) == 'S')
                continue;

                Day d(getDay(dayNum), dayNum);
                p.mHuelgas.push_back(d);
                cout <<  d.mDay << d.mNum << endl;

        }

        parties.push_back(p);

        dst.insert(dst.end(), p.mHuelgas.begin(), p.mHuelgas.end());
//        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
    }

    cout << "Dst size: "<< dst.size() << endl;

    std::sort(dst.begin(), dst.end());
    auto endIt = std::unique(dst.begin(), dst.end(), [](Day l, Day r){ return l.mNum == r.mNum; });
    dst.erase(endIt, dst.end());
    cout << "Dst size: "<< dst.size() << endl;

    for(auto it = dst.begin(); it != endIt; ++it)
        cout <<  it->mDay << ":" << it->mNum << endl;
}
