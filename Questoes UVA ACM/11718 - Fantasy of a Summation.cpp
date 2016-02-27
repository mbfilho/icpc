#include <cstdio>

using namespace std;

int main(){

	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	long long soma;
	int casos, n, k, mod, exp, resposta, val, temp;
	scanf( "%d", &casos );
	
	for( int i = 1; i <= casos; i++ ){
		scanf( "%d%d%d", &n, &k, &mod );
		exp = k - 1;
		soma = 0;
		resposta = 1;
		val = n;
		
		while( exp ){
			if( exp & 1 )
				resposta = ( resposta * val ) % mod;
			
			val = ( val * val ) % mod;
			exp = exp >> 1;
		}
		
		resposta = ( (k % mod ) * resposta ) % mod;
		
		soma = 0;
		while( n-- ){
			scanf( "%d", &temp );
			soma += temp;
		}		
		
		soma = ( ( soma % mod ) * resposta ) % mod;
		
		printf( "Case %d: %d\n", i, soma );		
	}
	
	return 0;
}
