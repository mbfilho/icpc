#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100000

struct No{
	int x, y, id;
	int dir, esq, pai;
	
	void set( int a ){
		id = a;
		dir = esq = pai = -1;
	}
	bool operator<( const No& a ) const{
		return x < a.x;
	}
}nos[ N ];
int n;

bool cmp( const No& a, const No& b ){
	return a.id < b.id;
}

int main(){
	freopen( "tree.in", "r", stdin );
	freopen( "tree.out", "w", stdout );
	
	scanf( "%d", &n );
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d %d", &nos[i].x, &nos[i].y );
		nos[i].set( i + 1 );
	}
	
	sort( nos, nos + n );
	
	for( int i = 1; i < n; ++i ){
		int at = i - 1, prev = -1;
		
		while( at != -1 && nos[at].y > nos[i].y ){
			prev = at;
			at = nos[at].pai;
		}
		
		nos[i].pai = at;
		if( at != -1 )
			nos[at].dir = i;

		nos[i].esq = prev;
		if( prev != -1 )
			nos[prev].pai = i;
	}
	
	for( int i = 0; i < n; ++i ){
		int esq, dir, pai;
		
		if( nos[i].pai == -1 ) pai = 0;
		else pai = nos[ nos[i].pai ].id;
		
		if( nos[i].esq == -1 ) esq = 0;
		else esq = nos[ nos[i].esq ].id;
		
		if( nos[i].dir == -1 ) dir = 0;
		else dir = nos[ nos[i].dir ].id;
		
		nos[i].pai = pai;
		nos[i].esq = esq;
		nos[i].dir = dir;
	}
		
	sort( nos, nos + n, cmp );
	
	printf( "YES\n" );
	for( int i = 0; i < n; ++i ){
		printf( "%d %d %d\n", nos[i].pai, nos[i].esq, nos[i].dir );
	}
	
	
	
}



