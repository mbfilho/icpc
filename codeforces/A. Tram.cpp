#include <cstdio>
#include <algorithm>
using namespace std;
#define N 2000
int a[ N ], b[ N ];
int n;

int main(){
	scanf( "%d", &n );
	
	for( int i = 0; i < n; ++i )
		scanf( "%d %d", a + i, b + i );
	
	int maior = 0, at = 0;
	
	for( int i = 0; i < n; ++i ){
		at -= a[ i ];
		at += b[ i ];
		maior = max( maior, at );
	}
	
	printf( "%d\n", maior );
}



