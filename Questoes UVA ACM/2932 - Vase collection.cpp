#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 50
#define oo -1
typedef long long ll;

int mapa[ N ], s;

ll vasos[ N ];
int n;
int contar( ll a ){
	int cont = 0;
	
	while( a ){
		++cont;
		a ^= ( a & -a );
	}
	
	return cont;
}


int faz( int ind, ll bits, ll mask, int raiz ){
	int qtd_vasos = contar( bits );
	if( qtd_vasos > raiz ) return 1;
	if( qtd_vasos > contar( mask ) ) return 1;
	if( ind >= s ) return qtd_vasos;
	int best;
	
	best = faz( ind + 1, bits | ( 1LL << ind ), mask & vasos[ ind ], raiz );
	best = max( best, faz( ind + 1, bits, mask, raiz ) );
	
	return best;
}

int raiz( int num ){
	int ini = 0, fim = num, meio, ret;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( meio * meio == num ) return meio;
		if( meio * meio < num ){
			ret = meio;
			ini = meio + 1;
		}else
			fim = meio - 1;
	}
	
	return ret;
}
int perm[ 40 ];

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		for( int i = 0; i < N; ++i ){
			mapa[ i ] = -1;
			vasos[ i ] = 0;
		}
		s = 0;
		scanf( "%d", &n );
		
		for( int i = 0; i < n; ++i ){
			int a, b;
			scanf( "%d %d", &a, &b );
			if( mapa[ a ] == -1 ) mapa[ a ] = s++;
			a = mapa[ a ];
			vasos[ a ] |= ( 1LL << b );
		}
		
		int best = 1, k = raiz( n );
		k = min( k, n );
//		printf( ">>>> %d\n", k );
		best = faz( 0, 0, -1, k );
		
		printf( "%d\n", best );
		
	}
}

