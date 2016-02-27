#include <cstdio>
#define N 76
#define K 6
/*
A id�ia � ir testando os caminhos. Na pd, guarda-se os indices da c�lula atual,
a quantidade de n�meros negativos na soma e a origem ( por onde chegou-se a essa
c�ula.). O que � um pouco diferente nesse problema � que a chamada recursiva come�a no
inicio do grid, isto �,(1,1) e encontra, se puder, a c�lula (n,n) e n�o o contr�rio.
Para cada c�lula, fa�a uma chamada recursiva para cada um dos caminhos poss�veis, atuali
zando o estado da pd. O campo "neg", a quantidade de n�meros negativos ser� alterado
se a c�lula atual for negativa, isso indica que um n�mero negativo foi adicionado � soma,.
O campo "origem" � muito importante. Ele indica de qual dire��o a recurs�o alcan�ou a 
c�lula atual, previnindo de voltar naquela dire��o e utilizar a mesma c�lula mais de
uma vez. O valor da celula (i,j,neg,dir) � a soma do valor do grid (i,j) e do maior
valor de um dos caminhos poss�veis.
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
