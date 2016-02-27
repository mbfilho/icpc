#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;

const int raiz = 1000, tam = 1000000;
bool crivo[ tam ];

void gerar(){
	fill( crivo, crivo + tam, true );
	for( int i = 4; i < tam; i += 2 )
		crivo[ i ] = false;

	crivo[ 0 ] = crivo[ 1 ] = false;
	
	for( int i = 3; i <= raiz; i += 2 ){
		if( crivo[ i ] == false ) continue;
		
		for( int j = i * i ; j < tam; j += i )
			crivo[ j ] = false;
	}
}

int main(){
	gerar();
	int num, indice, a, b;

	while( scanf( "%d", &num ) != EOF && num ){
		
		for( indice = 3; ; indice += 2 ){
			if( crivo[ indice ] && crivo[ num - indice ] ){
				a = indice;
				b = num - indice;
				break;
			}
		}
		
		printf( "%d = %d + %d\n", num, a, b );
		
	}
	
}


