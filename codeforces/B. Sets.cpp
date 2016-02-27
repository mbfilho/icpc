#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct No{
	ll sets[ 400 ];
	
	void setar( int pos ){
		int ind = pos / 64, offset = pos % 64;
		sets[ ind ] |= ( 1 << offset );
	}
	
	void limpar(){
		for( int i = 0; i < 400; ++i )
			sets[ i ] = 0;
	}
	
	bool operator==( const No& a ) const{
		for( int i = 0; i < 400; ++i ){
			if( sets[ i ] != a.sets[ i ] )
				return false;
		}
		
		return true;			
	}
		
}pertinencia[ 201 ];



int main(){
	int conj[ 201 ], n;
	fill( conj, conj + 201, -2 );
	for( int i = 0; i < 201; ++i )
		pertinencia[ i ].limpar();
		
	scanf( "%d", &n );
	int temp, k;
	for( int i = 0; i < n * ( n - 1 ) / 2; ++i ){
		scanf( "%d", &k );
		while( k-- ){
			scanf( "%d", &temp );
			conj[ temp ] = -1;
			pertinencia[ temp ].setar( i );
		}
	}
	
	if( n == 2 ){
		for( int i = 1; i <= 200; ++i ){
			if( conj[ i ] == -1 ){
				printf( "1 %d\n", i );
				conj[ i ] = 0;
				break;
			}
		}
		int cont = 0;
		for( int i = 1; i <= 200; ++i ){
			if( conj[ i ] == -1 ) ++cont;
		}
		
		printf( "%d", cont );
		for( int i = 1; i <= 200; ++i ){
			if( conj[ i ] == -1 ) 
				printf( " %d", i );
		}
		printf( "\n" );
	}else{
		int cont = 0;
		vector<int> resp[ n ];
		for( int i = 1; i <= 200; ++i ){
			if( conj[ i ] == -2 || conj[ i ] != -1 ) continue;
			conj[ i ] = cont;
			resp[ cont ].push_back( i );
			for( int j = i + 1; j <= 200; ++j ){
				if( pertinencia[ i ] == pertinencia[ j ] ){
					conj[ j ] = cont;
					resp[ cont ].push_back( j );
				}
			}
			++cont;
		}
	
		int tam;
		for( int i = 0; i < n; ++i ){
			tam = resp[ i ].size();
			printf( "%d", tam );
			for( int j = 0; j < tam; ++j )
				printf( " %d", resp[ i ][ j ] );
			printf( "\n" );
		}
	}
}


