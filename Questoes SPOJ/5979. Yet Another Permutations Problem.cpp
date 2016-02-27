#include <cstdio>

typedef long long ll;
 
const int MOD = 1000000007;
int n;

int exp(){
	ll retorno = 1;
	ll a = 2, b = n - 1;
	
	while( b ){
		if( b & 1 )
			retorno = ( retorno * a ) % MOD;
		b = b >> 1;
		a = ( a * a ) % MOD;
	}
	
	return (int) retorno;
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		printf( "%d\n", exp() );
	}
}
