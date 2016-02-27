#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int m;
int adj[ 6 ][ 6 ];

int main(){
	memset( adj, false, sizeof( adj ) );
	scanf( "%d", &m );
	for( int i = 0; i < m; ++i ){
		int u, v;
		scanf( "%d%d", &u, &v );
		adj[ u ][ v ] = adj[ v ][ u ] = true;
	}
	
	int ar[] = { 0, 0, 1, 1, 1 };
	
	bool achou = false;
	do{
		int c = 0;
		int p[ 3 ];
		for( int i = 0; i < 5; ++i ){
			if( ar[ i ] == 1 )
				p[ c++ ] = i + 1;
		}
		
		bool sim = true, nao = true;
		for( int i = 0; i < 3; ++i ){
			for( int j = i + 1; j < 3; ++j ){
				sim = sim && adj[ p[i] ][ p[j] ];
				nao = nao && !adj[ p[i] ][ p[j] ];
			}
		}
		achou = sim || nao;		
	}while( !achou && next_permutation( ar, ar + 5 ) );
	
	if( achou )
		printf( "WIN\n" );
	else
		printf( "FAIL\n" );
}

