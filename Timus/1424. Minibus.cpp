#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 100100
#define TREE 1000000

int maior[ TREE ];
int ops[ TREE ];

void ajeitar( int no ){
	maior[ no ] += ops[ no ];
	ops[ 2 * no ] += ops[ no ];
	ops[ 2 * no + 1 ] += ops[ no ];
	ops[ no ] = 0;
}

int query( int no, int ini, int fim, int x, int y ){
	if( x > fim || y < ini ) return -1;
	ajeitar( no );
	
	
	if( ini >= x && fim <= y ){
		return maior[ no ];
	}else{
		int meio = ( ini + fim ) / 2;
		int ret = query( no * 2, ini, meio, x, y );
		ret = max( ret, query( 2 * no + 1, meio + 1, fim, x, y ) );
		
		return ret;
	}
}

void incrementar( int no, int ini, int fim, int x, int y ){
	ajeitar( no );
	if( x > fim || y < ini ) return;
	
	if( ini >= x && fim <= y ){
		++ops[ no ];
		ajeitar( no );
	}else{
		int meio = ( ini + fim ) / 2;
		incrementar( 2 * no, ini, meio, x, y );
		incrementar( 2 * no + 1, meio + 1, fim, x, y );
		
		maior[ no ] = max( maior[ 2 * no ], maior[ 2 * no + 1 ] );
	}
}

struct No{
	int x, y, id;
	
	bool operator<( const No& outro ) const{
		return y < outro.y;
	}
}segs[ N ];

int n, m, k, p;

vector<int> resp;

int main(){
	scanf( "%d %d %d %d", &n, &m, &k, &p );
	
	for( int i = 0; i < k; ++i ){
		scanf( "%d %d", &segs[ i ].x , &segs[ i ].y );
		segs[ i ].id = i + 1;
	}

	memset( maior, 0, sizeof maior );
	memset( ops, 0, sizeof ops );
	sort( segs, segs + k );
	
	resp.clear();
	for( int i = 0; i < k; ++i ){
		if( query( 1, 1, n, segs[i].x, segs[i].y - 1 ) + 1 <= m ){
			resp.push_back( segs[i].id );
			incrementar( 1, 1, n, segs[i].x, segs[i].y - 1 );
		}
	}
	
	long long ganho = resp.size() * (long long ) p;
	
	printf( "%lld\n", ganho );
	if( resp.size() ){
		printf( "%d", resp[ 0 ] );
		for( int i = 1; i < resp.size(); ++i )
			printf( " %d", resp[ i ] );
		printf( "\n" );
	}else
		printf( "\n" );
	
}

