#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

/*
Simulação do jogo. Cada jogador deve procurar fazer o máximo de pontos.
Note que, para cada situação de nós marcados ( exauridos, sei lá ) a resposta
é a mesma, e é isso que permite a utilização da pd.
*/
int profit[ 16 ];
vector<int> adj[ 16 ];
bool pd[ 1 << 17 ];
pair<int,int> memo[ 1 << 17 ]; 
int n;

void rec( int jog, int* pts, int marc ){
	if( pd[ marc ] ){
		pts[ 0 ] = memo[ marc ].first;
		pts[ 1 ] = memo[ marc ].second;
		return;
	}
//	cout << "Passei" << endl;
	pts[ 0 ] = pts[ 1 ] = 0;
	
	int maior[ 2 ], p[ 2 ];
	maior[ jog ] = 0x80000000;
	maior[ jog xor 1 ] = 0;
	
	for( int i = 0; i < n; ++i ){
		if( marc & ( 1 << i ) ) continue;
		
		bool dm = true;
		for( int j = adj[ i ].size() - 1; j >= 0; --j ){
			if( marc & ( 1 << adj[ i ][ j ] ) ){
				dm = false;
				break;
			}
		}
		if( dm ) continue;
		
		rec( jog xor 1, p, marc | ( 1 << i ) );
				
		if( p[ jog ] + profit[ i ] > maior[ jog ] ){
			maior[ jog ] = p[ jog ] + profit[ i ];
			maior[ jog xor 1 ] = p[ jog xor 1 ];
		}
	}
	
	if( maior[ jog ] != 0x80000000 ){
		for( int i = 0; i < 2; ++i )
			pts[ i ] += maior[ i ];
	}	

	pd[ marc ] = true; 
	memo[ marc ].first = pts[ 0 ];
	memo[ marc ].second = pts[ 1 ];
}

int main(){
	int m;
	while( scanf( "%d", &n ) && n ){
		memset( pd, false, sizeof( pd ) );
		for( int i = 0; i < n; ++i ){
			adj[ i ].clear();
			scanf( "%d", profit + i );
		}
		
		scanf( "%d", &m );
		int a, b;
		for( int i = 0; i < m; ++i ){
			scanf( "%d %d", &a, &b );
			adj[ a - 1 ].push_back( b - 1 );
			adj[ b - 1 ].push_back( a - 1 );
		}
	
		int maior[ 2 ] = { 0x80000000, 0 }, temp[ 2 ];
		for( int i = 0; i < n; ++i ){

//			cout << profit[i] << "{" << endl;
			rec( 1, temp, 1 << i );
//			cout << "}" << endl;
			if( temp[ 0 ] + profit[ i ] > maior[ 0 ] ){
				maior[ 0 ] = temp[ 0 ] + profit[ i ];
				maior[ 1 ] = temp[ 1 ];
			}
		}
	
		if( maior[ 0 ] > maior[ 1 ] ){
			printf( "First player wins! %d to %d.\n", maior[ 0 ], maior[ 1 ] );
		}else if( maior[ 0 ] < maior[ 1 ] ){
			printf( "Second player wins! %d to %d.\n", maior[ 1 ], maior[ 0 ] );
		}else{
			printf( "Tie game! %d all.\n", maior[ 0 ] ); 
		}
	}
}

