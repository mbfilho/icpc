#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#define N 10000100
#define MOD 1000000007

int a[N];
int primos[N/2], cont;
ll prod[N];

void faz(){
	memset( a, 0, sizeof a );
	cont = 0;
	
	for( int i = 2; i < N; ++i ){
		if( !a[ i ] ){
			++cont;
			primos[ cont ] = i;
			a[ i ] = cont;
		}
		
		for( int j = 1; j <= cont && ll(i*primos[j]) < N; ++j )
			a[i*primos[j]] = j;
	}
}

int main(){
	faz();
	int n;
	prod[ 3 ] = prod[ 2 ] = prod[ 1 ] = 1;
	for( int i = 4; i < N; ++i ){
		int c = 1;
		if( i != primos[a[i]] ) c = i;
		
		prod[ i ] = ( c * prod[ i - 1 ] ) % MOD;
	}
	 
	while( scanf( "%d", &n ) != EOF && n ){
		ll resp = prod[ n ];
		
//		for( int i = 4; i <= n; ++i ){
//			if( i != primos[ a[i] ] ){
//				resp = ( resp * i ) % MOD;
//			}
//		}	
		
		for( int i = 1; i <= cont && primos[i] <= n; ++i ){
			int aux = 0;
			ll tmp = primos[i];
			
			while( n >= tmp ){
				aux += n / tmp;
				tmp *= primos[i];
			}
			if( aux ) --aux;
			
//			printf( "Primo %d QTd %d\n", primos[i], aux );
			if( aux & 1 ) resp = ( resp * primos[i] ) % MOD;
			if( !aux ) break;
		}
		
		printf( "%lld\n", resp );
	}
	
}





