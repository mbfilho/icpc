#include <set>
#include <cstdio>
using namespace std;
#define MAXI 0x7fffffff
typedef long long ll;

/*
Aplica��o direta do "Legendre Symbol"
a + np = k�
k� = a mod p    ou    a = k� mod p    =P

Queremos saber se 'a' � conguente a um quadrado perfeito modulo p. Isso �
feito atrav�s do simbolo de legendre:
(a|p) = 1 se a � congruente a um quadrado perfeito modulo p e a mod p != 0
= -1 se a n�o � congruente a um quadrado perfeito modulo p
= 0 se a = 0 mod p.

(a|p) = a ^ (p - 1)/2  mod p
*/
int expo( ll a, int b, int mod ){
	ll ret = 1;
	
	while( b ){
		if( b & 1 )
			ret = ( ret * a ) % mod;
		a = ( a * a ) % mod;
		b = b >> 1;
	}
	
	return int( ret );
}

int main(){
	int a, p;
	
	while( scanf( "%d %d", &a, &p ) && ( a != -1 && p != -1 ) ){
		if( p <= 2 )
			printf( "Yes\n" );
		else{
			int t = expo( a, ( p - 1 ) / 2, p );
			//printf( "T: %d\n", t );
			if( t == 0 || t == 1 )
				printf( "Yes\n" );
			else
				printf( "No\n" );
		}
	}
}
