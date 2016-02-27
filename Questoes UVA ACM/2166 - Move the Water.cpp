#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int c[ 3 ], a[ 3 ], b[ 3 ];
struct No{
	int est[ 3 ], d;
};

bool marc[ 160 ][ 160 ][ 160 ];

int main(){
	while( scanf( "%d%d%d%d%d%d%d%d%d", c, c+1, c+2, a, a+1, a+2, b, b+1, b+2 ) != EOF && c[ 0 ] ){
		bool dm = false;
		for( int i = 0; i < 3; ++i ){
			if( c[ i ] < b[ i ] || c[ i ] < a[ i ] ) dm = true;
		}
		
		int dist = -1;
		if( !dm ){
			memset( marc, false, sizeof( marc ) );
			marc[ a[0] ][ a[1] ][ a[2] ] = true;
			queue<No> fila;
			No inicio;
			inicio.d = 0;
			for( int i = 0; i < 3; ++i )
				inicio.est[ i ] = a[ i ];
			fila.push( inicio );
			while( !fila.empty() ){
				No at = fila.front();
				fila.pop();
				
				bool achei = true;
				for( int i = 0; i < 3; ++i ){
					if( at.est[ i ] != b[ i ] )
						achei = false;
				}
				if( achei ){
					dist = at.d;
					break;
				}
			
				for( int i = 0; i < 3; ++i ){
					if( !at.est[ i ] ) continue;
					
					for( int j = 0; j < 3; ++j ){
						if( j == i ) continue;
						
						No novo;
						for( int k = 0; k < 3; ++k )
							novo.est[ k ] = at.est[ k ];
						novo.est[ j ] = min( c[ j ], at.est[ i ] + at.est[ j ] );
						novo.est[ i ] = max( 0, at.est[ i ] - ( c[ j ] - at.est[ j ] ) );
						novo.d = at.d + 1;
						if( !marc[ novo.est[0] ][ novo.est[1] ][ novo.est[2] ] ){
							marc[ novo.est[0] ][ novo.est[1] ][ novo.est[2] ] = true;
							fila.push( novo );
						}
					}
				}
			
			}
		}
		
		if( dm || dist == -1 )
			printf( "-1\n" );
		else{
			printf( "%d\n", dist );
		}
	}
}


