//Sparse table? Busca binaria sobre o array de frequencias
//Processamento: O( nlogn ) Querys: log(n) cada

#include <cstdio>
#include <cmath>
using namespace std;

#define MAX 1 << 17
#define logMAX 17

int freq[ MAX ], ini[ MAX ], fim[ MAX ];
int n, q;
int matriz[ MAX ][ logMAX ];

int max( int a, int b ){
	if( a > b )
		return a;
	return b;
}

void ler(){
	int num, temp;

	for( int i = 0; i < n; ++i ){
		scanf( "%d", &num );

		if( i == 0 || num != temp ){
			freq[ i ] = 1;
			ini[ i ] = i;
		}else{
			freq[ i ] = freq[ i - 1 ] + 1;
			ini[ i ] = ini[ i - 1 ];
		}

		temp = num;
	}

	fim[ n - 1 ] = n - 1;
	for( int i = n - 2; i >= 0; --i ){
		if( freq[ i ] == freq[ i + 1 ] - 1 )
			fim[ i ] = fim[ i + 1 ];
		else
			fim[ i ] = i;
	}
}

void process(){
	for( int tam = 1; ( 1 << tam ) <= n; ++tam ){
		for( int i = 0; i + ( 1 << ( tam - 1 ) ) <= n; ++i ){
			if( freq[ matriz[ i ][ tam - 1 ] ] > freq[ matriz[ i + (1 << ( tam - 1 )) ][ tam - 1 ] ] ){
				matriz[ i ][ tam ] = matriz[ i ][ tam - 1 ];
			}else{
				matriz[ i ][ tam ] = matriz[ i + (1 << ( tam - 1 ) ) ][ tam - 1 ];
			}
		}
	}
}
void query(){
	int vali, valj, i, j, logs;

	for( int p = 0; p < q; ++p ){
		scanf( "%d %d", &i, &j );
		--i;
		--j;
		vali = valj = 0;

		if( i != ini[ i ] ){
			if( fim[ i ] >= j ){
				printf( "%d\n", ( j - i + 1 ) );
				continue;
			}else{
				vali = fim[ i ] - i + 1;
				i = fim[ i ] + 1;
			}
		}

		if( j != fim[ j ] ){
			valj = j - ini[ j ] + 1;
			j = ini[ j ] - 1;
		}

		if( i <= j ){
			logs = int( ( ( log10( j - i + 1 )/ log10( 2 ) ) ) );

			int desloc = j - ( 1 << logs ) + 1;

			int aux = max( freq[ matriz[ i ][ logs ] ], freq[ matriz[ desloc ][ logs ] ] );
			int aux2 = max( vali, valj );
			printf( "%d\n", max( aux, aux2 ) );
		}else
			printf( "%d\n", max( vali, valj ) ); 
	}

}

int main(){
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	for( int i = 0; i < MAX; ++i )
		matriz[ i ][ 0 ] = i;
		
	scanf( "%d", &n );

	while( n ){
		scanf( "%d", &q );
		ler();
		process();
		query();
		scanf( "%d", &n );
	}
}
