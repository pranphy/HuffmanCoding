/*******************************//**
 * \file HOffmanRecursiveOptimized.cpp
    Author       :@PrakashGautam
    Date Written :March 20, 2015
    Last Updated :March 20, 2015
    Email     :pranphy@gmail.com
************************************/

#include<bits/stdc++.h>

using namespace std;

#define PROBSUM 10

typedef unsigned ProbType;

struct ProbCode {
    string Code; /*< TODO use vector<bool> here to conserve memory */
    ProbType Prob;
};

ostream& operator<<(ostream& os,ProbCode p) {
    cout<<" Prob="<<p.Prob<<" Code=|"<<p.Code<<"|"<<endl;;
    return os;
}

vector<ProbCode> Initialize(vector<ProbType>);
vector<ProbCode> IterateCode(vector<ProbCode>);
vector<ProbCode> TrimCodes(vector<ProbCode>);

template<typename T>
void DisplayVector(vector<T> Vector);

int main() {
	/** To avoid floating point comparison  each probability is multiplied
	 * here by such a power of ten such that the smallest one of them  is
	 * a whole number. Eg 0.25 is transformed to 25 if it is the least of
	 * the probabilities. The value of PROBSUM #define'd at   top of this
	 * file indicates the least such power of ten used to multiply.'*/
    vector<ProbType> Prob = {625,625,625,625,1250,1250,2500,2500};
    sort(Prob.begin(),Prob.end());
    DisplayVector(IterateCode(Initialize(Prob)));
}



vector<ProbCode> IterateCode(vector<ProbCode> Codes) {
    /**
        This is a recursive implementation of Hoffman Algorithm. We reiterate
        the process up until  an array  with  just  two probabilities is left.
        When we are  left  with just two, we (arbitrarily) assign the symbols
        '0'  and  '1'  to the  last tow of them. When there are more than two
        add  the last two, and push it up(?) the order in rank and remove the
        last two,  and  find code for  that new array. When the code for that
        reduced array is  found, we  find the code  for the added probability
        from highest,  (Hoffman algorithm  gives least  variance with the sum
        pushed  highest up the order),  attach  it to the individual ones and
        for the rest just copy the codes in the order as done before.
    */
    int Rem = Codes.size();
    vector<ProbCode> RetVec = Codes;
    ProbType LastTwoSum = Codes.at(0).Prob + Codes.at(1).Prob;
    /** Assign symbols '0' and '1' to the last two*/
    RetVec.at(0).Code = '1';
    RetVec.at(1).Code = '0';
    /** If only tow are left, check if the sum gives probability 1, and leave */
    if(Rem == 2) {
        if(LastTwoSum != PROBSUM)
            cout<<" Error: Do not add to 1 as should probability "<<endl;
			/** TODO Throw error here instead of cout<<"Error message " */
        return RetVec;
    } else {
        /**
            If  more than two are left, find the code for the reduced array,
            the reduced  array is a new array with the last tow removed and
            their sum placed in the lexicographic (ascending) order
        */
        vector<ProbCode> RedCodes = IterateCode(TrimCodes(Codes));

        int RedSize = RedCodes.size();
        vector<bool> FoundRed(RedSize,false);
        vector<bool> FoundOrg(Rem,false);
        bool FoundSum = false;
        /**
            For the last two elements in the unreduced array, attach the code
            of the sum of them in the reduced array. Search from the sum from
            the top because it will give the least variance codes for symbols
        */
        for(int j = RedSize - 1; j >= 0; j--) {
            if(LastTwoSum == RedCodes.at(j).Prob and
                    !FoundSum and !FoundRed.at(j)) {
                RetVec.at(0).Code = RedCodes.at(j).Code + RetVec.at(0).Code;
                RetVec.at(1).Code = RedCodes.at(j).Code + RetVec.at(1).Code;
                FoundRed.at(j) = true;
                FoundSum = true;
                break;
            }
        }
        /**
            Once code for the sum of them is found, find code for the rest of
            them and copy codes to them. Then return
        */
        for(int i = 2; i<Rem; i++) {
            for(int j = 0; j< RedSize; j++) {
                if(RetVec.at(i).Prob == RedCodes.at(j).Prob and
                        !FoundRed.at(j) and !FoundOrg.at(i)) {
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

/** \brief This function trims the codes for the vector*/
vector<ProbCode> TrimCodes(vector<ProbCode> Codes) {
    /**
        Our job in this function is to add the least (last) two probabilities
        insert the sum in the array in order (lexicographic here)  and remove
        the last two elements whose sum we calculated;
    */
    /** First find the sum of last two as the least two reside on index 0 and 1*/
    ProbType LastTwoSum = Codes.at(0).Prob + Codes.at(1).Prob;
    auto It = Codes.begin();
    /**
        Loop until we find a place where the probability is greater or equal
        to the sum of the last two elements we just found
    */
    // took quite a some time to realize that I needed It < Codes.end() here;
    for(; It->Prob < LastTwoSum and It < Codes.end(); It++);
    /** At that position insert the sum probability with no code*/
    Codes.insert(It,{"",LastTwoSum});//not sure with use of initilizer list here
    /** And obviously remove the last two elements to get a new array*/
    Codes.erase(Codes.begin(),Codes.begin()+2);
    return Codes;
}


vector<ProbCode> Initialize(vector<ProbType> Prob) {
    vector<ProbCode> Generated;
    for(auto pr : Prob)
        Generated.push_back({"",pr});
    return Generated;
}

template <typename T>
void DisplayVector(vector<T> Vector) {
    for(auto i : Vector)
        cout<<" "<<i<<" ";
}
