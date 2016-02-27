#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool marc[ 100 ];
int ar[ 100 ];

int main(){
	int n, b;
	
	while( scanf( "%d%d", &n, &b ) != EOF && ( n | b ) ){
		for( int i = 0; i < b; ++i )
			scanf( "%d", ar + i );
		
		memset( marc, false, sizeof( marc ) );
		for( int i = 0; i < b; ++i ){
			for( int j = i; j < b; ++j ){
				int dif = max( ar[ i ] - ar[ j ], ar[ j ] - ar[ i ] );
				marc[ dif ] = true;
			}
		}
		
		int cont = 0;
		for( int i = 0; i <= n; ++i ){
			if( marc[ i ] ) ++cont;
		}
		if( cont == n + 1 )
			printf( "Y\n" );
		else 
			printf( "N\n" );
	}
}



