#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define TREE 1000000

ll soma[ TREE ], ops[ TREE ];

void makeTree( int no, int ini, int fim ){
	ops[ no ] = 0;
	soma[ no ] = 0;
	if( ini != fim ){
		int meio = ( ini + fim ) / 2;
		makeTree( 2 * no, ini, meio );
		makeTree( 2 * no + 1, meio + 1, fim );
	}
}

void ajeitar( int no, int tam ){
	soma[ no ] += tam * ops[ no ];
	ops[ 2 * no ] += ops[ no ];
	ops[ 2 * no + 1 ] += ops[ no ];
	ops[ no ] = 0;
}

ll query( int no, int ini, int fim, int a, int b ){
	ajeitar( no, fim - ini + 1 );
	int meio = ( ini + fim ) / 2; 
	if( a <= ini && b >= fim )
		return soma[ no ];
	else if( b <= meio )
		return query( 2 * no, ini, meio, a, b );
	else if( a >= meio + 1 )
		return query( 2 * no + 1, meio + 1, fim, a, b );
	else{
		ll soma = query( 2 * no, ini, meio, a, meio );
		soma += query( 2 * no + 1, meio + 1, fim, meio + 1, b );
		return soma;
	}
}

void incrementar( int no, int ini, int fim, int a, int b, ll val ){
	ajeitar( no, fim - ini + 1 );
	if( b < ini || a > fim ) return;
	
	if( a <= ini && b >= fim ){
		ops[ no ] += val;
		ajeitar( no, fim - ini + 1 );
	}else{
		int meio = ( ini + fim ) / 2;
		incrementar( 2 * no, ini, meio, a, b, val );
		incrementar( 2 * no + 1, meio + 1, fim, a, b, val );
		soma[ no ] = soma[ 2 * no ] + soma[ 2 * no + 1 ];
	}
}

int n, m;
int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &m );
		makeTree( 1, 0, n - 1 );
		while( m-- ){
			int a, b, op;
			scanf( "%d %d %d", &op, &a, &b );
			--a;
			--b;
			if( op ){
				printf( "%lld\n", query( 1, 0, n - 1, a, b ) );
			}else{
				ll val;
				scanf( "%lld", &val );
				incrementar( 1, 0, n - 1, a, b, val );
			}
		}
	}
}



