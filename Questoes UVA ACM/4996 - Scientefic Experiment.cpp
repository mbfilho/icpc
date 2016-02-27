#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 1001
int pd[ N ][ 2 ], x, y, z, n;


/*
Primeiro, não há distinção de altura dos andares. Entao se vc tem de decidir o pior caso
entre o 1 e o 3 ou entre o 7 e o 10, o resultado sera o mesmo. Ele só depende do tamanho
do intervalo. Entao imagine que vc tem de resolver o problema num intervalo de "n" andares.
Vc pode estar em cada um dos "n" andares do intervalo. Para cada andar vc vai perguntar:
	Qual o pior caso? Ou eu quebro o ovo e desco, para resolver num intervalo de "i" andares ( chegando
	sem o ovo )	ou eu não quebro o ovo e subo para resolver o problema em um intervalo de "n-i" andares (chegando
	com o ovo). Eu devo, para cada andar, selecionar o pior caso.
Dentre todos os andares eu devo pegar aquele que tem o menor pior caso.
  
*/
int faz(){
	pd[ 1 ][ 0 ] = 0;
	pd[ 1 ][ 1 ] = - x / 2;
	for( int k = 2; k <= n; ++k ){
		int custo = 0x7fffffff;
		for( int i = 1; i < k; ++i )//para cada andar
			custo = min( custo, max( pd[ i ][ 0 ], pd[ k - i ][ 1 ] ) );//desco ou subo, qual o pior?
		
		pd[ k ][ 0 ] = x + y + custo;
		pd[ k ][ 1 ] = z + custo;
	}
	
	return pd[ n ][ 0 ];
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int caso = 1; caso <= casos; ++caso ){
		scanf( "%d %d %d %d", &n, &x, &y, &z );
		printf( "Case %d: %d\n", caso, faz() );
	}	
}






