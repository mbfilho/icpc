#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 301 
#define K 1001
typedef long long ll;
ll pd[ N ][ K ];

void encher(){
	memset( pd, 0, sizeof( pd ) );
	pd[ 0 ][ 0 ] = 1;

	for( int j = 1; j <= 300; ++j ){
		for( int qtd = 1; qtd < K; ++qtd ){
			for( int i = j; i < N; ++i ){
				pd[ i ][ qtd ] += pd[ i - j ][ qtd - 1 ];
			}
		}
	}		
}

ll somar( int n, int a, int b ){
	ll ret = 0;
	for( int i = a; i <= b; ++i )
		ret += pd[ n ][ i ];
	return ret;
}	

int main(){
	encher();
	
	char linha[ 100 ];
	while( gets( linha ) ){
		
		int n, l1, l2;
		int args = sscanf( linha,"%d %d %d", &n, &l1, &l2 );
		
		ll soma = 0;
		if( args == 1 ){
			if( n == 0 )
				soma = 1;
			else
				soma = somar( n, 1, n );
		}else if( args == 2 ){
			if( n == 0 )
				soma = 1;
			else
				soma = somar( n, 1, l1 );
		}else
			soma = somar( n, l1, min( l2, n ) );
		
		printf( "%lld\n", soma );

	}
}



