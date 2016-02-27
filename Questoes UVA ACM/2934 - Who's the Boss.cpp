#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;
#define mp make_pair
#define N 40000
#define TREE 1000000

struct Cara{
	int sal, id, alt, empr;
	int chefe;
	vector<int> adj;
	
	bool operator<( const Cara& outro ) const{
		return sal < outro.sal;
	}
}nos[ N ];
int n, q;

void dfs( int no ){
	nos[ no ].empr = 0;
	
	for( int i = nos[ no ].adj.size() - 1; i >= 0; --i ){
		int nt = nos[ no ].adj[ i ];
		if( nos[ nt ].empr == -1 ){
			dfs( nt );
			nos[ no ].empr += ( 1 + nos[ nt ].empr );
		}
	} 
}

int tree[ TREE ];

void buildTree( int no, int ini, int fim ){
	tree[ no ] = -1;
	if( ini == fim )
		return;
	
	int meio = ( ini + fim ) / 2;
	buildTree( 2 * no, ini, meio );
	buildTree( 2 * no + 1, meio + 1, fim );
}

void insert( int no, int ini, int fim, int x ){
	if( x > fim || x < ini ) return;
	
	if( ini == fim && fim == x ){
		tree[ no ] = x;
	}else{
		int meio = ( ini + fim ) / 2;
		insert( 2 * no, ini, meio, x );
		insert( 2 * no + 1, meio + 1, fim, x );
		
		int esq = tree[ 2 * no ], dir = tree[ 2 * no + 1 ];
		if( dir == -1 ) tree[ no ] = esq;
		else if( esq == -1 ) tree[ no ] = dir;
		else{
			if( nos[ dir ].alt > nos[ esq ].alt )
				tree[ no ] = dir;
			else
				tree[ no ] = esq;
		} 
	}
}

int query( int no, int ini, int fim, int arg ){
	if( ini == fim )
		return tree[ no ];
	
	int meio = ( ini + fim ) / 2;
	int esq = tree[ 2 * no ], dir = tree[ 2 * no + 1 ];
	if( esq != -1 && nos[ esq ].alt >= arg )
		return query( 2 * no, ini, meio, arg );
	else if( dir != -1 && nos[ dir ].alt >= arg )
		return query( 2 * no + 1, meio + 1, fim, arg );
	else
		return -1;
}

map<int,int> mapa;
int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &q );
		
		for( int i = 0; i < n; ++i ){
			nos[ i ].adj.clear();
			nos[ i ].empr = -1;
			nos[ i ].chefe = 0;
			scanf( "%d %d %d", &nos[ i ].id, &nos[ i ].sal, &nos[ i ].alt );
		}
		
		sort( nos, nos + n );
		buildTree( 1, 0, n - 1 ); 
		mapa.clear();
		
		for( int i = n - 1; i >= 0; --i ){
			int ind = query( 1, 0, n - 1, nos[ i ].alt );
//			printf( ">>> %d \n", ind );
			if( ind != -1 ){
//				printf( "\t %d\n", nos[ ind ].alt );
				nos[ ind ].adj.push_back( i );
				nos[ i ].chefe = nos[ ind ].id;
			}
			
			insert( 1, 0, n - 1, i );
		}
		int pog = 0;
		for( int i = 0; i < n; ++i ){
			mapa[ nos[i].id ] = i;
			if( !nos[ i ].chefe ){
				dfs( i );
				++pog;
			}
		}
		if( pog != 1 ) throw 2;
		while( q-- ){
			int id;
			scanf( "%d", &id );
			if( mapa.find( id ) == mapa.end() ) throw 2;
			id = mapa[ id ];
			printf( "%d %d\n", nos[ id ].chefe, nos[ id ].empr );
		}
	}
}

