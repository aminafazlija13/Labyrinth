#ifndef LABIRINT_H
#define LABIRINT_H

#include <fstream>
#include <iostream>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<queue>
#include <stdexcept>

using namespace std;


int red[] = { -1, 0, 0, 1 };
int kolona[] = { 0, -1, 1, 0 };


class Labirint{

public:
    struct Cvor
    {
        int x, y, udaljenost;
    };

private:
    int brojRedova, brojKolona;
    vector< vector<int>> L;

public:
    Labirint();
    Labirint( int m, int n);
    void Prolazi(int &brojac, vector<int> praznine);
    int BFS( int i, int j, int x, int y);
    int Udaljenost(char slovo, int j, char slovo1, int y);
    bool jeLiValidan( vector< vector<bool>> posjecen, int red, int kolona);
    int charUInt(char slovo);

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Labirint::Labirint( int m, int n)
{
    brojRedova = m;
    brojKolona = n;
    L.resize(m);

    for( int i = 0; i < m; i++ )
        L[i].resize(n);

    for( int i = 0; i < m; i++)
        for( int j = 0; j < n; j++)
        {
            if(i==0 or i==-1)
                L[i][j]=j+1;
            else
                L[i][j]=0;
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Labirint::Prolazi(int &brojac, vector<int> praznine)
{


    if(praznine.size()==1 )
    {
        for( int j=0; j<brojKolona; j++)
         if( j+1 != praznine[0]){
                L[brojac][j]=j+1;
                L[brojac+1][j]=j+1;
         }
    }
    else{
            int v =0;
    while(v < praznine.size()){
         for( int j=0; j<brojKolona; j++)
         if( j+1 != praznine[v]){
                L[brojac][j]=j+1;
                L[brojac+1][j]=j+1;
         }
         else v++;
}}

brojac++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Labirint::BFS( int i, int j, int x, int y)
{
	vector< vector<bool>> posjecen;
	posjecen.resize(brojRedova);

    for (int k = 0; k < brojRedova; k++)
    {
        posjecen[k].resize(brojKolona);
        for (int l= 0 ; l < brojKolona; l++)
            posjecen[k][l]=0;
    }

	queue<Cvor> q;

	posjecen[i][j] = true;
	q.push({i, j, 0});

	int minimalnaUdaljenost = INT_MAX;

	while (!q.empty())
	{
		Cvor cvor = q.front();
		q.pop();

		int i = cvor.x, j = cvor.y, udaljenost = cvor.udaljenost;
		if (i == x && j == y)
		{
			minimalnaUdaljenost = udaljenost;
			break;
		}

		for (int k = 0; k < 4; k++)
		{
			if (jeLiValidan( posjecen, i + red[k], j + kolona[k]))
			{
				posjecen[i + red[k]][j + kolona[k]] = true;
				q.push({ i + red[k], j + kolona[k], udaljenost + 1 });
			}
		}
	}

	if (minimalnaUdaljenost != INT_MAX)
		return minimalnaUdaljenost;
	else
		return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Labirint::Udaljenost(char slovo, int j, char slovo1, int y)
{

    int i = charUInt(slovo);
    int x = charUInt(slovo1);

    if((i==0 or i%2==0)and (x==brojRedova-1))
      return BFS(i,j-1,x-1,y-1);

    if(i==0 and x%2==1)
        return BFS(i,j-1,x+1,y-1);

    if(i==0 and x%2==0)
        return BFS(i,j-1,x+1,y-1)+1;

    if(i%2==0 and x%2==1)
        return BFS(i+1,j-1,x-1,y-1)+1;

    if(i%2==1 and x%2==1)
        return BFS(i-1,j-1,x-1,y-1)+1;

    if(i%2==0 and x%2==0)
        return BFS(i+1,j-1,x+1,y-1)+1;

    return BFS(i-1,j-1,x+1,y-1)+1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Labirint::jeLiValidan( vector< vector<bool>> posjecen, int red, int kolona)
{
	return (red >= 0) && (red < brojRedova) && (kolona >= 0) && (kolona < brojKolona)
		&& !L[red][kolona] && !posjecen[red][kolona];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Labirint::charUInt(char slovo){
    int a[26];
    a[0] = 0;
    for(int i = 1;i < 26; i++){
        if(i%2 == 1) a[i] = a[i-1] + 3;
        else a[i] = a[i-1] + 1;
    }
    return a[int(slovo)-65];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
