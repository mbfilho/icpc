#include <cstdio>
#include <algorithm>
using namespace std;

int dias, tempo, soma;
int maxi[ 100 ], mini[ 100 ], real[ 100 ]; 

int main(){
	scanf( "%d %d", &dias, &tempo );
	
	for( int i = 0; i < dias; ++i )
		scanf( "%d %d", mini + i, maxi + i );
	
	fill( real, real + dias, 0 );
	soma = 0;
	for( int i = 0; i < dias; ++i ){
		soma += mini[ i ];
		maxi[ i ] -= mini[ i ];
		real[ i ] = mini[ i ];
	}
	
	if( soma > tempo )
		printf( "NO\n" );
	else{
		for( int i = 0; i < dias; ++i ){
			if( maxi[ i ] + soma >= tempo ){
				real[ i ] += ( tempo - soma );
				soma = tempo;
				break;
			}else{
				real[ i ] += maxi[ i ];
				soma += maxi[ i ];
			}
		}
		
		if( soma < tempo )
			printf( "NO\n" );
		else{
			printf( "YES\n" );
			for( int i = 0; i < dias; ++i )
				printf( "%d%c", real[ i ], (i == dias - 1) ? '\n' : ' ' );
		}
	}	
}
