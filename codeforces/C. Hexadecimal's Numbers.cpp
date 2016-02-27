#include <cstdio>

int getD( int arg, int tam ){
	int ret = 0;
	for( int i = tam - 1; i >= 0; --i ){
		ret *= 10;
		if( arg & ( 1 << i ) ) ++ret;
	}	
	
	return ret;
}

int main(){
	int n, cont = 0;
	scanf( "%d", &n );
//	3446 3315
	
	int c = n;
	while( c ){
		++cont;
		c /= 10;
	}
	
	int resp = 0;
	for( int i = 1; i < ( 1 << cont ); ++i ){
		if( getD( i, cont ) <= n ) ++resp;
	}
	printf( "%d\n", resp );
}

