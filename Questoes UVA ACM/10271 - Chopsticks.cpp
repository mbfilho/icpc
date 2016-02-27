#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define mp make_pair
#define N 5100
#define K 1010
#define quad(x) (x) * (x)
#define oo 0x7fffffff
int n, k;
int tam[ N ], pd[ N ][ K ];

int badness( int a, int b ){
	int x = tam[ a ] - tam[ b ];
	return x * x;
}

//A pd eh muito parecida com o knapsack

/*
Fazer "j" duplas com o intervalo [0..i] da sequencia de chopsticks. pd[i][j] = min( pd[i-2][j-1] + bad(i,i-1), pd[i-1][j] )
Os indices dos dois for's eh que cuidam de garantir a existencia do 3 elemento do conjunto. O primeiro for do
"i" inicia em 2j-1 pq pra fazer 2j duplas sao necessarios 2j elementos, [0..2j-1]. De n-3(k+8-j) ate n - 1 contem
exatamente os elementos necessarios para formar todas as triplas dos k+8-j conjuntos restantes. O elemento anterior,
ou seja, n-3(k+8-j)-1 nao pode ser incluido em nenhuma dupla, pois caso isso ocorra, essa dupla ficara sem terceiro
elemento.
O segundo for comeca em 2j. Se ele comecasse em 2j-1 ele pediria pd[2j-2][j], mas nao da pra fazer j duplas com 2j-1 elementos. Ele termina no mesmo lugar pelo mesmo motivo.
*/
int faz(){
	for( int j = 0; j <= k + 8; ++j )
		pd[ 0 ][ j ] = 0;
	
	for( int j = 1; j <= k + 8; ++j ){
		for( int i = 2 * j - 1; i < n - 3 * ( k + 8 - j ) - 1; ++i ){
			int ante = 0;
			if( i != 1 )
				ante = pd[ i - 2 ][ j - 1 ];
			pd[ i ][ j ] = ante + badness( i, i - 1 );
		}
		for( int i = 2 * j; i < n - 3 * ( k + 8 - j ) - 1; ++i ){
			pd[ i ][ j ] = min( pd[ i ][ j ], pd[ i - 1 ][ j ] );
		}
		
		pd[ n - 3 * ( k + 8 - j ) - 1 ][ j ] = pd[ n - 3 * ( k + 8 - j ) - 2 ][ j ];
	}
	
	return pd[ n - 1 ][ k + 8 ];	
}

int main(){
	int casos;
	scanf( "%d", &casos );
	while( casos-- ){
		scanf( "%d%d", &k, &n );
		for( int i = 0; i < n; ++i )
			scanf( "%d", tam + i );
			
		printf( "%d\n", faz() );
	}
}






