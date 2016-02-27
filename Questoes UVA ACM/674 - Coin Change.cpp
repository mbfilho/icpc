#include <cstdio>

int moedas[] = { 1, 5, 10, 25, 50 };
int pd[ 7490 ];

int resolver(){

	for( int i = 0; i <= 7489; ++i )
		pd[ i ] = 1;
	
	for( int i = 1; i < 5; ++i ){
		for( int j = 1; j <= 7489; ++j ){
			if( j - moedas[ i ] >= 0 )
				pd[ j ] += pd[ j - moedas[ i ] ];
		}
	}
}

int main(){
	int qtd;
	resolver();
	
	while( scanf( "%d", &qtd ) != EOF )
		printf( "%d\n", pd[ qtd ] );
	
}