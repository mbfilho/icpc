#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;

double dist[ 30 ][ 30 ];
int n, m;
map<string, int> mapa;

int main(){

	string nome, nome2;
	double custo;
	int caso = 1;
	
	while( scanf( "%d", &n ) != EOF && n != 0 ){
		mapa.clear();
		for( int i = 0; i < n; ++i ){
			cin >> nome;
			mapa[ nome ] = i;
		}
		
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j )
				dist[ i ][ j ] = 999999;
			dist[ i ][ i ] = 0.0;
		}
		
		scanf( "%d", &m );
		for( int i = 0; i < m; ++i ){
			cin >> nome >> custo >> nome2;
			dist[ mapa[ nome ] ][ mapa[ nome2 ] ] = -log( custo );
		}
		
		for( int k = 0; k < n; ++k ){
			for( int i = 0; i < n; ++i ){
				for( int j = 0; j < n; ++j )
					dist[ i ][ j ] = min( dist[ i ][ j ], dist[ i ][ k ] + dist[ k ][ j ] );
			}
		}
				
		bool arbitrage = false;
		for( int i = 0; i < n; ++i ){
			if( dist[ i ][ i ] < 0.0 ){
				arbitrage = true;
				break;
			}
		}
		
		if( arbitrage )
			printf( "Case %d: Yes\n", caso );
		else
			printf( "Case %d: No\n", caso );
		++caso;
	}
}
