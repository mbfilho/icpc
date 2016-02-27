#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
#define custo(i,j,k) c[i]*c[k+1]*c[j+1]
using namespace std;

int cont;
int pd[ 11 ][ 11 ], rec[ 11 ][ 11 ];
int c[ 100 ];

string par( int i, int j ){
	if( i == j ){
		char ma[ 10 ];
		sprintf( ma, "A%d", i + 1 );
		return string( ma );
	}else if( j == i + 1 ){
		char ma[ 17 ];
		sprintf( ma, "(A%d x A%d)", i + 1, j + 1 );
		return string( ma );
	}
	string temp;
	temp = "(" + par( i, rec[ i ][ j ] ) + " x " + par( rec[ i ][ j ] + 1, j ) + ")";
	return temp;
}

int main(){
	int caso = 1;
	
	while( scanf( "%d", &cont ) && cont != 0 ){
		int ind = 0;
		for( int i = 0; i < cont; ++i ){
			pd[ i ][ i ] = 0;
			scanf( "%d", c + ind );
			++ind;
			scanf( "%d", c + ind );
		}
				
		for( int i = 0; i < cont - 1; ++i )
			pd[ i ][ i + 1 ] = c[ i ] * c[ i + 1 ] * c[ i + 2 ];
		
		for( int tam = 3; tam <= cont; ++tam ){
			for( int i = 0; i + tam - 1 < cont; ++i ){
				int j = i + tam - 1;
				pd[ i ][ j ] = 0x7fffffff;
				for( int k = i; k < j; ++k ){
					if( pd[i][j] > pd[ i ][ k ] + pd[ k + 1 ][ j ] + custo(i,j,k) ){
						pd[i][j] = pd[ i ][ k ] + pd[ k + 1 ][ j ] + custo(i,j,k);
						rec[ i ][ j ] = k;
					}
				}
					
			}
		}
		
		printf( "Case %d: ", caso++ );
		cout << par( 0, cont - 1 ) << endl;		
	}
}
