#include <cstdio>
#include <cstring>
typedef unsigned long long ull;

ull BASE = 17;
char nome[ 6000000 ];
int cont[ 6000000 ];

int faz(){
	ull h1 = 0, h2 = 0, ac = 1;

	cont[ 0 ] = 1;
	h1 = h2 = nome[ 0 ];
	ac *= BASE;
	int res = 1;
	
	for( int i = 1; nome[ i ]; ++i ){
		h1 = h1 * BASE + nome[ i ];
		h2 = h2 + nome[ i ] * ac;
		ac *= BASE;
		
		//0123456789
		int temp = 0;		
		if( h1 == h2 ){
			int ind = ( i - 1 ) / 2; //so para impares
			temp = 1 + cont[ ind ];
			cont[ i ] = temp;
			res += temp;
		}else
			cont[ i ] = 0;
	}
	
	return res;
}

int main(){
	scanf( "%s", nome );
	printf( "%d\n", faz() );
}





