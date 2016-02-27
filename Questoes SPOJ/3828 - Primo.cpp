#include <cstdio>
#include <cmath>

int main(){
	int num;
	scanf( "%d", &num );
	
	if( num < 0 )
		num = -num;
			
	if( num == 0 || num == 1 )
		printf( "nao\n" );
	else{

		int raiz = (int) ceil( sqrt( num ) );
		int i;
		for( i = 2; i <= raiz; ++i ){
			if( num % i == 0 ){
				printf( "nao\n" );
				i = -1;
				break;
			}
		}
		
		if( i != -1 )
			printf( "sim\n" );
	}
}
