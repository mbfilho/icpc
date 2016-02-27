#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define N 120000
#define BASE 97
#define MOD ((1LL<<31) - 1)

ll hpre[ N ], hsuf[ N ], inv;
char input[ N ], compr[ N ];
int tam;

ll pre[ N ];
void inverso(){
	int xp = MOD - 2;
	ll resp = 1;
	ll a = BASE;
	
	while( xp ){
		if( xp & 1 ) resp = ( resp * a ) % MOD;
		a = ( a * a ) % MOD;
		xp >>= 1;
	}
	
	inv = resp;
}

void comprimir(){
	int t = strlen( input );
	int pr = 0;
	compr[ 0 ] = input[ 0 ];
	
	int i = 0;
	while( i < t ){
		while( i < t && input[ i ] == compr[ pr ] ) ++i;
		if( i < t ) compr[ ++pr ] = input[ i ];
	}
	
	compr[ ++pr ] = 0;
	tam = pr;
}

ll expo( ll a, int xp ){
	ll resp = 1;
	
	while( xp ){
		if( xp & 1 ) resp = ( resp * a ) % MOD;
		a = ( a * a ) % MOD;
		xp >>= 1;
	}
	
	return resp;
}

void calc(){
	hpre[ 0 ] = compr[ 0 ] - 'A' + 1;
	ll pot = BASE;
	for( int i = 1; i < tam; ++i ){
		hpre[ i ] = ( hpre[ i - 1 ] + ( compr[ i ] - 'A' + 1 ) * pot ) % MOD; 
		pot = ( pot * BASE ) % MOD;
	}
	
	hsuf[ tam - 1 ] = compr[ tam - 1 ] - 'A' + 1;
	pot = BASE;
	for( int i = tam - 2; i >= 0; --i ){
		hsuf[ i ] = ( hsuf[ i + 1 ] + ( compr[ i ] - 'A' + 1 ) * pot ) % MOD;
		pot = ( pot * BASE ) % MOD;
	}
}

int bs( int ind ){
	int ini = 1, fim = tam, meio, best = -1;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		
		if( ind + meio >= tam || ind - meio < 0 ){
			fim = meio - 1;
		}else{
			ll esq = ( MOD + hsuf[ ind - meio ] - hsuf[ ind ] ) % MOD, dir = ( MOD + hpre[ ind + meio ] - hpre[ ind ] ) % MOD;
			esq = ( esq * pre[ tam - ind ] ) % MOD;
			dir = (dir * pre[ ind + 1 ] ) % MOD;
			
			if( esq == dir ){
				best = meio;
				ini = meio + 1;
			}else
				fim = meio - 1;
		}
	}
	
	return best + 1;
}


int main(){
	inverso();
	pre[ 0 ] = 1;
	for( int i = 1; i < N; ++i )
		pre[ i ] = ( pre[ i - 1 ] * inv ) % MOD;
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%s", input );
		comprimir();
		calc();
		int resp = 1;
		
		for( int i = 0; i < tam; ++i ){
			resp = max( resp, bs( i ) );
		}
		
		printf( "%d\n", resp );
	}
}




