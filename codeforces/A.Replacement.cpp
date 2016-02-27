#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100100

int num[ N ], resp[ N ];
int n;


int main(){
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i )
		scanf( "%d", num + i );
	
	sort( num, num + n );
	bool td1 = ( num[ n - 1 ] == 1 );
	
	if( n == 1 && td1 )
		printf( "2\n" );
	else{
		resp[ 0 ] = 1;
		for( int i = 1; i < n; ++i ){
			if( i != n - 1 || !td1 )
				resp[ i ] = num[ i - 1 ];
			else
				resp[ i ] = 2; 
		}
		
		printf( "%d", resp[ 0 ] );
		for( int i = 1; i < n; ++i )
			printf( " %d", resp[ i ] );
		printf( "\n" );
	}
	
}

