#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	int grupos, array[ 101 ];
	
	scanf( "%d", &grupos );
	for( int i = 0; i < grupos; ++i )
	     scanf( "%d", &array[ i ] );
	
	sort( array, array + grupos );
	
	int g = 1 + grupos / 2;

	int soma = 0;
	for( int i = 0; i < g; ++i )
		soma += 1 + array[ i ] / 2;
		
	printf( "%d\n", soma );
	
}
