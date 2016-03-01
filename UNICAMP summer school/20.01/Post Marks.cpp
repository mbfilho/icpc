#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define oo 0x7fffffff

int n, k;

struct No{
	int custo, valor;
	
	bool operator<( const No& a ) const{
		return valor < a.valor;
	}
}half[ 1 << 17 ], nos[ 40 ];
int query[ 1 << 17 ];

int getIndex( int a ){
	int cont = 0;
	
	while( a ){
		if( !(a & 1) ) ++cont;
		else break;
		a >>= 1;
	}
	
	return cont;
}

int main(){
	freopen( "stamps.in", "r", stdin );
	freopen( "stamps.out", "w", stdout );
//	
	scanf( "%d %d", &n, &k );
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d", &nos[i].custo );
	}
	
	int custo_total = 0, valor_total = 0;
	for( int i = 0; i < n; ++i ){
		int tmp;
		scanf( "%d", &tmp );
		if( tmp ) custo_total += nos[i].custo;
	}
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d", &nos[i].valor );
		valor_total += nos[i].valor;
	}
	
	if( valor_total < k ) printf( "-1\n" );
	else{
		random_shuffle( nos, nos + n );
	
		for( int i = 0; i < ( 1 << n/2 ); ++i ){
			int tmp = i;
			half[i].custo = 0;
			half[i].valor = 0;
		
			for( int j = 0; j < n/2; ++j ){
				if( i & ( 1 << j ) ){
					half[i].custo += nos[j].custo;
					half[i].valor += nos[j].valor;
				}
			}
		}
	
		sort( half, half + ( 1 << n/2 ) );
		query[ (1 << n/2) - 1 ] = half[ (1<< n/2) - 1 ].custo;
	
		for( int i = (1<<n/2) - 2; i >= 0; --i ){
			query[ i ] = min( query[ i + 1 ], half[ i ].custo );
		}
	
		int resp = oo, qtd = n - n / 2;
	
		for( int i = 0; i < (1 <<qtd); ++i ){
			int custo = 0;
			int valor = 0;
		
			for( int j = 0; j < qtd; ++j ){
				if( i & (1 << j) ){
					custo += nos[ j + n / 2 ].custo;
					valor += nos[ j + n / 2 ].valor;
				}
			}
		
			int ini = 0, fim = (1 << n/2) - 1;
		
			while( ini <= fim ){
				int meio = ( ini + fim ) / 2;
				if( half[ meio ].valor + valor >= k ){
					resp = min( resp, custo + query[ meio ] );
					fim = meio - 1;
				}else
					ini = meio + 1;
			}
		}
	
		printf( "%d\n", max( 0, resp - custo_total ) );
	}
}





