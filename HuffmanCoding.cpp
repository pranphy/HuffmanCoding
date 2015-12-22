#include<bits/stdc++.h>

using namespace std;

#define PROBSUM 1000

typedef unsigned ProbType;

class ProbCode {
public:
    string Code;
    ProbType Prob;
};

ostream& operator<<(ostream& os,ProbCode p) {
    cout<<" Prob="<<p.Prob<<" Code=|"<<p.Code<<"|";
    return os;
}

vector<ProbCode> Initialize(vector<ProbType>);
vector<ProbCode> IterateCode(vector<ProbCode>);
vector<ProbCode> TrimCodes(vector<ProbCode>);


template<typename T>
void DisplayVector(vector<T> Vector);




int main() {
    vector<ProbType> Prob1 = {40,20,10,20,10};
    vector<ProbType> Prob2 = {41,23,13,12,11};
    vector<ProbType> Prob3 = {2500,2500,1250,1250,625,625};
    sort(Prob1.begin(),Prob1.end());
    sort(Prob2.begin(),Prob2.end());
    sort(Prob3.begin(),Prob3.end());
    DisplayVector(IterateCode(Initialize(Prob1))); cout<<"\n";
    DisplayVector(IterateCode(Initialize(Prob2))); cout<<"\n";
    DisplayVector(IterateCode(Initialize(Prob3)));
    
}



vector<ProbCode> IterateCode(vector<ProbCode> Codes) {
    int Rem = Codes.size();
    vector<ProbCode> RetVec = Codes;
    ProbType LastTwoSum = Codes.at(0).Prob + Codes.at(1).Prob;
    RetVec.at(0).Code = '1';
    RetVec.at(1).Code = '0';

    if(Rem == 2) {
        if(LastTwoSum != PROBSUM)
            cout<<" Error: Do not add to 1 as should probability "<<endl;
        return RetVec;
    } else {
        vector<ProbCode> RedCodes = IterateCode(TrimCodes(Codes));
        int RedSize = RedCodes.size();
        vector<bool> FoundRed(RedSize,false);
        vector<bool> FoundOrg(Rem,false);
        bool FoundSum = false;

        for(int j = RedSize - 1; j >= 0; j--) {
            if(LastTwoSum == RedCodes.at(j).Prob and !FoundSum and !FoundRed.at(j)) {
                RetVec.at(0).Code = RedCodes.at(j).Code + RetVec.at(0).Code;
                RetVec.at(1).Code = RedCodes.at(j).Code + RetVec.at(1).Code;
                FoundRed.at(j) = true;
                FoundSum = true;
                break;
            }
        }

        for(int i = 2; i<Rem; i++) {
            for(int j = 0; j< RedSize; j++) {
                if(RetVec.at(i).Prob == RedCodes.at(j).Prob and !FoundRed.at(j) and !FoundOrg.at(i)) {
                    RetVec.at(i).Code = RedCodes.at(j).Code;
                    FoundRed.at(j) = true;
                    FoundOrg.at(i) = true;
                    break;
                }
            }
        }
        return RetVec;
    }
}

vector<ProbCode> TrimCodes(vector<ProbCode> Codes) {
    ProbType LastTwoSum = Codes.at(0).Prob + Codes.at(1).Prob;
    auto It = Codes.begin();
    for(;It->Prob < LastTwoSum and It < Codes.end(); It++);
    ProbCode P = {"",LastTwoSum};
    Codes.insert(It,P);
    Codes.erase(Codes.begin(),Codes.begin()+2);
    return Codes;
}


vector<ProbCode> Initialize(vector<ProbType> Prob) {
    vector<ProbCode> Generated;
    for(auto pr : Prob){ ProbCode P;P.Prob = pr;
        Generated.push_back(P);
    }
    return Generated;
}

template <typename T>
void DisplayVector(vector<T> Vector) {
    for(auto i : Vector)
        cout<<i<<" ";
}
