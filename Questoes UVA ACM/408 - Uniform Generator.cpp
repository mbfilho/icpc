#include <cstdio>

int gcd( int a, int b ){
	int mod;
	
	while( b ){
		mod = a % b;
		a = b;
		b = mod;
	}
	
	return a;
}

int main(){
	int step, mod;
	
	while( scanf( "%d %d", &step, &mod ) != EOF ){
		if( gcd( step, mod ) == 1 ){
			printf( "%10d%10d    Good Choice\n", step, mod );
		}else
			printf( "%10d%10d    Bad Choice\n", step, mod );
		printf( "\n" );
	}
}
