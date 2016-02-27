#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

string nomes[17][3];
string impr[ 17 ];
int ordem[ 17 ];
string ant;

int main(){
	int qtd;
	freopen( "in.txt", "r", stdin );
	
	cin >> qtd;
	
	for( int i = 1; i <= qtd; ++i ){
		cin >> nomes[ i ][ 0 ] >> nomes[ i ][ 1 ] >> nomes[ i ][ 2 ];
		sort( nomes[ i ], nomes[ i ] + 3 );
	}
	
	for( int i = 1; i <= qtd; ++i )
		cin >> ordem[ i ];
	
	ant = "";
	bool sair = false;
	
	for( int i = 1; i <= qtd && !sair; ++i ){
		for( int j = 0; j < 3; ++j ){
			if( nomes[ ordem[ i ] ][ j ] > ant ){
				impr[ i ] = nomes[ ordem[ i ] ][ j ];
				ant = impr[ i ];
				break;
			}else if( j == 2 ){
				cout << "IMPOSSIBLE" << endl;
				sair = true;
				break;
			}
		}
	}
	
	if( sair == false ){
		for( int i = 1; i <= qtd; ++i )
			cout << impr[ i ] << endl;
	}
	
}

