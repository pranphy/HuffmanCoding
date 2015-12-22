#include<bits/stdc++.h>

using namespace std;

typedef unsigned ProbType;

class ProbCode {
public:
    string Code;
    ProbType Prob;
};

ostream& operator<<(ostream& os,ProbCode p) {
	cout<<"Prob="<<p.Prob<<" Code=|"<<p.Code<<"| ";
    return os;
}

vector<ProbCode> Initialize(vector<ProbType>);

template<typename T>
bool Greater(T,T);

template<typename T>
void DisplayVector(vector<T> Vector);

vector<ProbCode> IterateCode(vector<ProbCode>);

vector<ProbCode> TrmCodes(vector<ProbCode>);



int main() {
    //vector<ProbType> Prob = {40,20,10,20,10};
    vector<ProbType> Prob = {2500,2500,1250,1250,625,625};
    sort(Prob.begin(),Prob.end());
    vector<ProbCode> Here = Initialize(Prob);
    DisplayVector(Prob);
    cout<<endl<<" now here \n"<<endl;
    DisplayVector(Here);
    cout<<"\n Trimmed now "<<endl;
    vector<ProbCode> Trimd = IterateCode(Here);
    DisplayVector(Trimd);
}



vector<ProbCode> IterateCode(vector<ProbCode> Codes) {
    int Rem = Codes.size();
    vector<ProbCode> RetVec = Codes;
    ProbType LastTwoSum = Codes.at(0).Prob + Codes.at(1).Prob;
    RetVec.at(0).Code = '1';
    RetVec.at(1).Code = '0';
    if(Rem == 2) {
		if(LastTwoSum != 100)
			cout<<" Error: Do not add to 1 as should probability "<<endl;
        return RetVec;
    } else {
        //cout<<" Rem has "<<Rem<<endl;
        vector<ProbCode> TrdCodes = TrmCodes(Codes);
        bool FoundSum = false;
        //cout<<TrdCodes.size()<<" must be one less than "<<Rem<<endl;
        //cout<<" Trimmed now "<<endl;
        vector<ProbCode> RedCodes = IterateCode(TrdCodes);
        //cout<<" New produced codes apnd prob pari \n";
        DisplayVector(RedCodes);
        cout<<" \n========================\n";
        int RedSize = RedCodes.size();
		vector<bool> FoundRed(RedSize,false);
		vector<bool> FoundOrg(Rem,false);


		for(int j = RedSize - 1; j >=0; j--) {
            //cout<<j<<". "<<RedCodes.at(j).Prob<<" pr with code "<<RedCodes.at(j).Code<<endl;
            //cout<<LastTwoSum<<" == "<<RedCodes.at(j).Prob;
            cout.precision(15);
            //if(LastTwoSum == RedCodes.at(j).Prob) cout<<" Passes "<<endl; else cout<< " Fails "<<endl;
            if(LastTwoSum == RedCodes.at(j).Prob and !FoundSum and !FoundRed.at(j)) {
                cout<< LastTwoSum<<" found at  "<<j<<"  with code "<<RedCodes.at(j).Code<<" "<<endl;
                RetVec.at(0).Code = RedCodes.at(j).Code + RetVec.at(0).Code;
                RetVec.at(1).Code = RedCodes.at(j).Code + RetVec.at(1).Code;
                FoundRed.at(j) = true;
                FoundSum = true;
                break;
            }

        }

        for(int i = 2; i<Rem; i++) {
            //cout<<" Trying to find next one "<<endl;
			for(int j = 0; j< RedSize;j++){
				//cout<<RetVec.at(i).Prob<<" == "<<RedCodes.at(j).Prob;
				//if(RetVec.at(i).Prob == RedCodes.at(j).Prob) cout<<" Passes "<<endl; else cout<< " Fails "<<endl;
				if(RetVec.at(i).Prob == RedCodes.at(j).Prob and !FoundRed.at(j) and !FoundOrg.at(i)){
                    cout<<"At "<<i<<" Assigning for "<<RetVec.at(i).Prob<<" as code "<<RedCodes.at(j).Code<<endl;
					RetVec.at(i).Code = RedCodes.at(j).Code;
					FoundRed.at(j) = true;
					FoundOrg.at(i) = true;
					break;
				}
			}
        }
        cout<<" ===============Returnig now=============== \n";
        DisplayVector(RetVec);
        cout<<" \n*********************************************** \n";
        return RetVec;
    }
}

vector<ProbCode> TrmCodes(vector<ProbCode> Codes) {
	//cout<< "\n ========I am colled here ==== \n ";

    int Size = Codes.size();
    //cout<<" The size of array is"<< Size<<endl;
    vector<ProbCode> RetCode;
    ProbType LastTwoSum = Codes.at(0).Prob + Codes.at(1).Prob;
    //cout<<" Last two sum is "<<LastTwoSum<<endl;
    //cout<<" Safe here test "<<endl;
    bool EqualFlag = false;
    int k = 0, j = 2;
    while(j < Size and Codes.at(j).Prob <= LastTwoSum) {
        //cout<<j<<" is j here \n";
        RetCode.push_back(Codes.at(j++));
        //cout<<" Testing for "<<Codes.at(j).Prob<<" Against "<<LastTwoSum<<" Now in the next iteration"<<endl;
    }
    //cout<<" Checket all small and equal "<<endl;
    ProbCode P;
    P.Prob = LastTwoSum;
    RetCode.push_back(P);
    if(j == Size) return RetCode;

    else{
        for(int t = j; t<Size; t++)
            RetCode.push_back( Codes.at(t));
    }
    return RetCode;
}

vector<ProbCode> Initialize(vector<ProbType> Prob) {
    int Symbols = Prob.size(), i = 0;
    vector<ProbCode> Generated(Symbols);
    for(auto pr : Prob) {
        Generated.at(i++).Prob = pr;
    }

    return Generated;
}



template <typename T>
void DisplayVector(vector<T> Vector) {
    for(auto i : Vector)
        cout<<i<<" ";
}


template<typename T>
bool Greater(T a, T b) {
    return a>b;
}
