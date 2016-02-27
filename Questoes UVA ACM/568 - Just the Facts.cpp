#include <cstdio>

typedef long long ll;


int main(){
	int n;
	ll resp, mod = 100000000000000LL;
	
	while( scanf( "%d", &n ) != EOF ){
		resp = 1;
		for( int i = n; i > 1; --i ){
			resp = ( resp * i ) % mod;
			while( resp % 10 == 0 )
				resp /= 10;
		}
	
		printf( "%5d -> %d\n", n, int( resp % 10 ) );
	}
}

