#include <cstdio>

int main(){
	int a, b, c, d, l;
	
	while( scanf( "%d %d %d %d %d", &a, &b, &c, &d, &l ) && (a | b | c | d | l) ){
		int cont = 0;
		for( int i = 0; i <= l; ++i ){
			if( ( a * i * i + b * i + c ) % d == 0 )
				++cont;
		}
		printf( "%d\n", cont );
	}
}

