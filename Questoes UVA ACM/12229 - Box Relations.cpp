#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 2000

struct Regra{
	int tipo, i, j;
	
	Regra( int a, int b, int c ){
		tipo = a;
		i = b;
		j = c;
	}
};
vector<Regra> regras;

int n, r;
int conj[ N ];
int valx[ N ], valy[ N ], valz[ N ];
bool marc[ N ];
vector<int> adjx[ N ], adjy[ N ], adjz[ N ];

int find( int a ){
	if( conj[ a ] != a )
		conj[ a ] = find( conj[ a ] );
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

int ordem[ N ], prt;

bool dfs( int no, vector<int> adj[ N ] ){
	marc[ no ] = true;
	
	for( int i = 0; i < adj[ no ].size(); ++i ){
		int nt = adj[ no ][ i ];
		if( marc[ nt ] ) return true;
		
		if( dfs( nt, adj ) ) return true; 
	}
	
	ordem[ prt++ ] = no;
	return false;
}

int main(){
	int caso = 0;
	while( scanf( "%d %d", &n, &r ) == 2 && ( n | r ) ){
		regras.clear();
		
		for( int i = 0; i <= n; ++i ){
			adjx[ i ].clear();
			adjy[ i ].clear();
			adjz[ i ].clear();
		}
		
		for( int i = 0; i <= n; ++i ) conj[ i ] = i;
		
		for( int i = 0; i < r; ++i ){
			char temp[10];
			int a, b;
			scanf( "%s %d %d", temp, &a, &b );
			
			if( temp[ 0 ] == 'I' )
				unir( a, b );
			else
				regras.push_back( Regra( temp[ 0 ], a, b ) );
		}
		
		for( int i = 0; i < regras.size(); ++i ){
			if( regras[ i ].tipo == 'X' )
				adjx[ find( regras[i].i ) ].push_back( find( regras[i].j ) );
			else if( regras[ i ].tipo == 'Y' )
				adjy[ find( regras[i].i ) ].push_back( find( regras[i].j ) );
			else
				adjz[ find( regras[i].i ) ].push_back( find( regras[i].j ) ); 
		}
		
		bool ciclo = false;
		int cont = 1;
		//Faz x
		memset( marc, false, sizeof marc );
		prt = 0;
		for( int i = 1; i <= n; ++i ){
			if( find( i ) == i && !marc[ i ] )
				ciclo |= dfs( i, adjx );
		}
		
		if( !ciclo ){
			for( int i = prt - 1; i >= 0; --i ){
				valx[ find( ordem[i] ) ] = cont;
				cont += 2;
			}
		}
		
		//Faz y
		if( !ciclo )
			memset( marc, false, sizeof marc );
		prt = 0;
		for( int i = 1; !ciclo && i <= n; ++i ){
			if( find( i ) == i && !marc[ i ] )
				ciclo |= dfs( i, adjy );
		}
		
		if( !ciclo ){
			for( int i = prt - 1; i >= 0; --i ){
				valy[ find( ordem[i] ) ] = cont;
				cont += 2;
			}
		}
		
		//Faz z
		if( !ciclo )
			memset( marc, false, sizeof marc );
		prt = 0;
		for( int i = 1; !ciclo && i <= n; ++i ){
			if( find( i ) == i && !marc[ i ] )
				ciclo |= dfs( i, adjz );
		}
		
		if( !ciclo ){
			for( int i = prt - 1; i >= 0; --i ){
				valz[ find( ordem[i] ) ] = cont;
				cont += 2;
			}
		}
		
		printf( "Case %d: ", ++caso );
		if( ciclo )
			printf( "IMPOSSIBLE\n" );
		else{
			printf( "POSSIBLE\n" );
			for( int i = 1; i <= n; ++i ){
				int x = valx[ find(i) ], y = valy[ find(i) ], z = valz[ find(i) ];
				printf( "%d %d %d %d %d %d\n", x, y, z, x + 1, y + 1, z + 1 );
			}
		}
		
		printf( "\n" );
		
		
		
	}
}






