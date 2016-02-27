#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 200

int manha[ N ], tarde[ N ];
int n, r, d;


int main(){
	while( scanf( "%d %d %d", &n, &d, &r ) != EOF && ( n | r | d ) ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", manha + i );
		for( int i = 0; i < n; ++i )
			scanf( "%d", tarde + i );
		
		sort( manha, manha + n );
		sort( tarde, tarde + n );
		
		int cont = 0;
		for( int i = 0; i < n; ++i )
			cont += max( 0, manha[ i ] + tarde[ n - 1 - i ] - d );
		printf( "%d\n", cont * r );
	}
}






