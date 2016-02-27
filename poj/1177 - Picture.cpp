#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 10000
#define TREE 10*N

int segs[ TREE ];
bool left[ TREE ], right[ TREE ];
int marc[ TREE ], tam[ TREE ];

int n;
int Y[ 4 * N ], prt;

void build(){
	memset( segs, 0, sizeof segs );
	memset( left, false, sizeof left );
	memset( right, false, sizeof right );
	memset( marc, 0, sizeof marc );
	memset( tam, 0, sizeof tam );
}


int inserir( int no, int x, int y, int a, int b ){
	if( a > y || b < x  ) return 0;
	
	if( a <= x && b >= y ){
		++marc[ no ];
		left[ no ] = right[ no ] = true;
		segs[ no ] = 1;
		
		if( marc[ no ] == 1 ){
			tam[ no ] = Y[ y + 1 ] - Y[ x ]; //Segmento passa a ser coberto
			
			return tam[ no ] - ( tam[ 2 * no ] + tam[ 2 * no + 1 ] );
		}else
			return 0; //segmentos o cobrem
	}else{
		int ret = 0, meio = ( x + y ) / 2;
		
		ret += inserir( 2 * no, x, meio, a, b );
		ret += inserir( 2 * no + 1, meio + 1, y, a, b );
		
		if( marc[ no ] ){
			segs[ no ] = 1;
			left[ no ] = right[ no ] = true;
			tam[ no ]  = Y[ y + 1 ] - Y[ x ]; //totalmente coberto
			return 0;
		}else{
			segs[ no ] = segs[ 2 * no ] + segs[ 2 * no + 1 ];
			
			if( right[ 2 * no ] && left[ 2 * no + 1 ] )
				--segs[ no ];
			
			left[ no ] = left[ 2 * no ];
			right[ no ] = right[ 2 * no + 1 ];
			
			tam[ no ] = tam[ 2 * no ] + tam[ 2 * no + 1 ];
			return ret;
		}
	}
}

void remover( int no, int x, int y, int a, int b ){
	if( a > y || b < x ) return;
	
	if( a <= x && b >= y ){
		--marc[ no ];
	}else{
		int meio = ( x + y ) / 2;
		remover( 2 * no, x, meio, a, b );
		remover( 2 * no + 1, meio + 1, y, a, b );	
	}
	
	if( !marc[ no ] ){
		segs[ no ] = segs[ 2 * no ] + segs[ 2 * no + 1 ];

		if( right[ 2 * no ] && left[ 2 * no + 1 ] )
			--segs[ no ];
		
		left[ no ] = left[ 2 * no ];
		right[ no ] = right[ 2 * no + 1 ];
		tam[ no ] = tam[ 2 * no ] + tam[ 2 * no + 1 ];
	}else{ /*continua do jeito que ta*/ }
}

struct No{
	pair<int,int> low, high;
}nos[ N ];

int bs( int val ){
	int ini = 0, fim = prt - 1, meio;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		
		if( Y[ meio ] == val ) return meio;
		else if( Y[ meio ] > val ) fim = meio - 1;
		else ini = meio + 1;
	}
	return -1;
}

pair<int,bool> sweep[ 2 * N ];

int getX( const pair<int,bool>& a ){
	if( a.second ) return nos[ a.first ].low.first;
	else return nos[ a.first ].high.first;
}

bool comp( const pair<int,bool>& a, const pair<int,bool>& b ){
	int xa = getX( a ), xb = getX( b );
	
	return xa < xb;
}

int main(){
	while( scanf( "%d", &n ) == 1 ){
		build();
		prt = 0;
		
		for( int i = 0; i < n; ++i ){
			scanf( "%d %d %d %d", &nos[i].low.first, &nos[i].low.second, &nos[i].high.first, &nos[i].high.second );
			Y[ prt++ ] = nos[i].low.second;
			Y[ prt++ ] = nos[i].high.second;
		}
		
		sort( Y, Y + prt );
		prt = unique( Y, Y + prt ) - Y;
		
		for( int i = 0; i < n; ++i ){
			nos[ i ].low.second = bs( nos[ i ].low.second );
			nos[ i ].high.second = bs( nos[ i ].high.second );
			
			sweep[ 2 * i ].first = i;
			sweep[ 2 * i ].second = true;
			
			sweep[ 2 * i + 1 ].first = i;
			sweep[ 2 * i + 1 ].second = false;;
		}
		sort( sweep, sweep + 2 * n, comp );
		
		int perimetro = 0, last;
		
		for( int i = 0; i < 2 * n; ++i ){
			int id = sweep[ i ].first;
			
			if( i )
				perimetro += 2 * segs[ 1 ] * ( getX( sweep[ i ] ) - last );
			
			if( !sweep[ i ].second )
				remover( 1, 0, prt - 1, nos[ id ].low.second, nos[ id ].high.second - 1 ); 
			else{
				int visivel = inserir( 1, 0, prt - 1, nos[ id ].low.second, nos[ id ].high.second - 1 );
				perimetro += 2 * visivel;
			}
			last = getX( sweep[ i ] );
		}
		
		printf( "%d\n", perimetro );
	}
}


