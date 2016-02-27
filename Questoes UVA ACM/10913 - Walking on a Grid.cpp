#include <cstdio>
#define N 76
#define K 6
/*
A idéia é ir testando os caminhos. Na pd, guarda-se os indices da célula atual,
a quantidade de números negativos na soma e a origem ( por onde chegou-se a essa
céula.). O que é um pouco diferente nesse problema é que a chamada recursiva começa no
inicio do grid, isto é,(1,1) e encontra, se puder, a célula (n,n) e não o contrário.
Para cada célula, faça uma chamada recursiva para cada um dos caminhos possíveis, atuali
zando o estado da pd. O campo "neg", a quantidade de números negativos será alterado
se a célula atual for negativa, isso indica que um número negativo foi adicionado à soma,.
O campo "origem" é muito importante. Ele indica de qual direção a recursão alcançou a 
célula atual, previnindo de voltar naquela direção e utilizar a mesma célula mais de
uma vez. O valor da celula (i,j,neg,dir) é a soma do valor do grid (i,j) e do maior
valor de um dos caminhos possíveis.
*/
const int nenhuma = 0, esquerda = 1, direita = 2;

int memo[ N ][ N ][ K ][ 3 ];
bool marc[ N ][ N ][ K ][ 3 ];
int grid[ N ][ N ];

int n, k;
const int infinito = 0x7FFFFFFF;

int resolver( int i, int j, int neg, int origem ){	
	if( marc[ i ][ j ][ neg ][ origem ] )
		return memo[ i ][ j ][ neg ][ origem ];
	marc[ i ][ j ][ neg ][ origem ] = true;
	
	int argNeg = neg + ( grid[ i ][ j ] < 0 ? 1 : 0 );

	if( argNeg > k )
		return memo[ i ][ j ][ neg ][ origem ] = infinito;
	
	if( i == n && j == n ){
		return memo[ i ][ j ][ neg ][ origem ] = grid[ i ][ j ];
	}
	
	int best = 0x80000000;
	bool mudou = false;
	int temp;
	if( origem != direita && ( j + 1 <= n ) ){
		//vai para direita
		temp = resolver( i, j + 1, argNeg, esquerda );
		
		if( temp != infinito && best < temp ){
			mudou = true;
			best = temp;
		}
	}
	
	if( origem != esquerda && ( j - 1 >= 1 ) ){
		//vai para esquerda
		temp = resolver( i, j - 1, argNeg, direita );

		if( temp != infinito && best < temp ){
			mudou = true;
			best = temp;
		}
	}
	
	//vai para baixo
	if( i + 1 <= n ){
		temp = resolver( i + 1, j, argNeg, nenhuma );

		if( temp != infinito && best < temp ){
			best = temp;
			mudou = true;
		}
	}
	
	if( mudou == false )
		return memo[ i ][ j ][ neg ][ origem ] = infinito;

	return memo[ i ][ j ][ neg ][ origem ] = best + grid[ i ][ j ];
}

int main(){
	int caso = 1;
	
	while( scanf( "%d %d", &n, &k ) && ( n | k ) ){
		for( int i = 1; i <= n; ++i ){
			for( int s = 1; s <= n; ++s ){
				scanf( "%d", &grid[ i ][ s ] );
				for( int j = 0; j <= k; ++j ){
					marc[ i ][ s ][ j ][ 0 ] = false;
					marc[ i ][ s ][ j ][ 1 ] = false;
					marc[ i ][ s ][ j ][ 2 ] = false;
				}
			}
		}
		
		int ret = resolver( 1, 1, 0, nenhuma );		
		printf( "Case %d: ", caso++ );
		if( ret == infinito )
			printf( "impossible\n" );
		else
			printf( "%d\n", ret );
	}
}
