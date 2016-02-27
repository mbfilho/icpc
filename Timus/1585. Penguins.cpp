#include <iostream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

int cont[ 2000 ];
map<string,int> mapa;

void ig(){
    while( cin.peek() == '\n' ) cin.ignore();
}

int main(){
    int n;

    while( scanf( "%d",&n) != EOF ){
        string temp;
        mapa.clear();
        for( int i = 0; i < n; ++i )
            cont[ i ] = 0;
        int ind = 0;

        for( int i = 0; i < n; ++i ){
            ig();
            getline( cin, temp );

            if( mapa.find( temp ) == mapa.end() )
                mapa[ temp ] = 0;
            else
                ++mapa[ temp ];
        }

        int maior = -1;
        string arg;
        for( map<string,int>::iterator it = mapa.begin(); it != mapa.end(); ++it ){
            if( it -> second > maior ){
                maior = it -> second;
                arg = it -> first;
            }
        }

        cout << arg << endl;
    }
}
