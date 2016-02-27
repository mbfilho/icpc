#include <cstdio>
using namespace std;
/*
int array[ 101 ];

void processo(){
	array[ 100 ] = 91;

	for( int i = 99; i >= 0; --i ){
		if( i + 11 >= 101 )
			array[ i ] = array[ i + 1 ];
		else
			array[ i ] = array[ array[ i + 11 ] ];
	}
}
*/

int main(){
	int num;

	scanf( "%d", &num );
	while( num ){
		if( num >= 101 )
			printf( "f91(%d) = %d\n", num, (num - 10) );
		else
			printf( "f91(%d) = 91\n", num );
		scanf( "%d", &num );
	}
}
