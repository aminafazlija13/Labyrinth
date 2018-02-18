#include "Labirint.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int stringUInt (string str){
    int i = atoi(str.c_str());
    return i;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> procitajLiniju(string linija, int broj){
    string temp = "";
    vector<int> A;
    int i=0;
    while(linija[i]){
        if(linija[i]!=',')
            {
                temp += linija[i];
            }
        else
            {
                int broj1 = stringUInt(temp);
                if(broj1 > broj )
                     throw invalid_argument("Broj prolaza je veci od broja kolona!");
                A.push_back(broj1);
                temp="";
            }
       i++;
    }
    if(temp!="")
        {int broj1 = stringUInt(temp);
         if(broj1 > broj )
                 throw invalid_argument("Broj prolaza je veci od broja kolona!");
            A.push_back(broj1);}
    return A;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){
    ifstream infile("labirint.txt");
    string linija;
    int m,n;
    int brojLinije=0;

    getline(infile, linija);
    m = 2*stringUInt(linija);
    if(m>52)
        throw invalid_argument("Prva linija ne moze biti veca od 26!");

    getline(infile, linija);
    n = stringUInt(linija);

    Labirint L(m,n);

    while(getline(infile, linija))
    {
            brojLinije+=3;
            vector<int> praznine;
            praznine = procitajLiniju(linija, n);
            L.Prolazi(brojLinije, praznine);
    }

    cout<<endl;
    cout<<"Najkraca udaljenost je: "<<L.Udaljenost('C',1,'F',7)<<endl;
    cout<<endl;
}
