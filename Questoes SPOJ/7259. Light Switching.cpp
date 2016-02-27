#include <cstdio>
#include <algorithm>
using namespace std;
#define TREE 2000000

int ligadas[ TREE ];
bool ops[ TREE ];

void makeTree( int no, int ini, int fim ){
	ligadas[ no ] = 0;
	ops[ no ] = false;
	
	if( ini != fim ){
		int meio = ( ini + fim ) / 2;
		makeTree( 2 * no, ini, meio );
		makeTree( 2 * no + 1, meio + 1, fim ); 
	}
}


void ajeitar( int no, int tam ){
	if( ops[ no ] ){
		ligadas[ no ] = tam - ligadas[ no ];
		ops[ 2 * no ] = !ops[ 2 * no ];
		ops[ 2 * no + 1 ] = !ops[ 2 * no + 1 ];
		ops[ no ] = false;
	}		
}

void operacao( int no, int ini, int fim, int a, int b ){
	ajeitar( no, fim - ini + 1 );
	
	if( b < ini || a > fim ) return;
	
	if( a <= ini && b >= fim ){
		ops[ no ] = !ops[ no ];
		ajeitar( no, fim - ini + 1 );
	}else{
		int meio = ( ini + fim ) / 2;
		operacao( 2 * no, ini, meio, a, b );
		operacao( 2 * no + 1, meio + 1, fim, a, b );
		ligadas[ no ] = ligadas[ 2 * no ] + ligadas[ 2 * no + 1 ];
	}		
}

int query( int no, int ini, int fim, int a, int b ){
	ajeitar( no, fim - ini + 1 );
	int meio = ( ini + fim ) / 2;
	
	if( a <= ini && b >= fim )
		return ligadas[ no ];
	else if( b <= meio ){
		return query( 2 * no, ini, meio, a, b );
	}else if( a >= meio + 1 ){
		return query( 2 * no + 1, meio + 1, fim, a, b );
	}else{
		int resp = query( 2 * no, ini, meio, a, meio );
		resp += query( 2 * no + 1, meio + 1, fim, meio + 1, b );
		return resp;
	}
}

int n, m;
int main(){
	while( scanf( "%d %d", &n, &m ) != EOF ){
		makeTree( 1, 0, n - 1 );
	
		int op, a, b;
		while( m-- ){
			scanf( "%d %d %d", &op, &a, &b );
			--a;
			--b;
			if( op )
				printf( "%d\n", query( 1, 0, n - 1, a, b ) );
			else
				operacao( 1, 0, n - 1, a, b );
		}
	}
}




