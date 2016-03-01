#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define P 2000000
#define N 2000000
int pd[N];
int primos[P/2], A[P], pc;
int D[P], Q[P];

int l, r;
void pre(){
	memset( A, 0, sizeof A );
	pc = 0;
	
	for( int i = 2; i < P; ++i ){
		if( !A[i] ){
			primos[++pc] = i;
			A[i] = pc;
			D[i] = 2;
			Q[i] = 1;
		}
		
		for( int j = 1; j <= A[i] && ll( i * primos[j] ) < P; ++j ){
			A[i*primos[j]] = j;
			if( A[i] == A[primos[j]] ){
				Q[i*primos[j]] = 1 + Q[i];
				D[i*primos[j]] = (Q[i] + 2) * ( D[i] / (Q[i]+1) );
			}else{
				Q[i*primos[j]] = 1;
				D[i*primos[j]] = D[i] * 2;
			}
		}
	}
}

int faz(){
	pd[r] = 1;
	int maior = 1;
	
	for( int i = r - 1; i >= l; --i ){
		ll soma = 2 + i;
		pd[i] = 1;
		for( int j = i + 1; j <= r; ++j ){
			int qtd = D[soma];
			
			if( qtd == 2 ){
				pd[i] += pd[j];
				break;
			}
			soma = qtd + j;
		}
		maior = max( maior, pd[i] );
	}
	
	return maior;
}

int main(){
	#ifndef X
	freopen( "primes.in", "r", stdin );
	freopen( "primes.out", "w", stdout );
	#endif
	
	pre();

	int caso = 0;
	while( scanf( "%d %d", &l, &r ) == 2 && ( l | r ) ){
		printf( "Window %d: There can be up to %d primes.\n", ++caso, faz() );
	}
}





