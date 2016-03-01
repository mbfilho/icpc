#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

#define N 100100

struct No{
	int esq, dir;
	int x, y;
	int val;
}nos[ N ];

void dfs( int no, int sp );

void ajeitar( int no ){
	int esq = 0, dir = 0;
	if( nos[no].esq != -1 ) esq = nos[ nos[no].esq ].x;
	if( nos[no].dir != -1 ) dir = nos[ nos[no].dir ].x;
	
	nos[no].x = esq + dir + 1;
}

void split( int t, int x, int& l, int& r ){
	if( t == -1 ) r = l = -1;
	else{
		int qtd = 1;
		if( nos[ t ].esq != -1 ) qtd = nos[ nos[t].esq ].x + 1;
		
		if( x == qtd ){
			l = t;
			r = nos[t].dir;
			
			nos[l].dir = -1;
		}else if( x < qtd ){
			split( nos[t].esq, x,  l, nos[t].esq );
			r = t;
		}else{
			split( nos[t].dir, x - qtd, nos[t].dir, r );
			l = t;
		}
		
		ajeitar( t );
	}
}

int merge( int& l, int& r ){
	if( l == -1 ) return r;
	if( r == -1 ) return l;
	
	if( nos[l].y > nos[r].y ){
		nos[r].esq = merge( l, nos[r].esq );
		ajeitar( r );
		return r;
	}else{
		nos[l].dir = merge( nos[l].dir, r );
		ajeitar( l );
		return l; 
	}
}

int add( int t, int nw ){
	if( t == -1 || nos[t].y > nos[nw].y ){
		split( t, nos[nw].x, nos[nw].esq, nos[nw].dir );
		ajeitar( nw );

		return nw;
	}
	
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd = nos[ nos[t].esq ].x + 1;
	
	if( nos[nw].x < qtd ){
//		nos[nw].x -= 1;
		nos[t].esq = add( nos[t].esq, nw );
	}else{
		nos[nw].x -= qtd;
		nos[t].dir = add( nos[t].dir, nw );
	}
	
	ajeitar( t );
	return t;
}

void dfs( int no, int sp ){
	if( no == -1 ) return;
	
	printf( "%*d, %d: %d\n", sp, nos[no].val, nos[no].y, nos[no].x );
	
	printf( "Esq\n" );
	dfs( nos[no].esq, sp + 1 );
	printf( "Dir\n" );
	dfs( nos[no].dir, sp + 1 );
}

void ordem( int no, vector<int>& r ){
	if( no == -1 ) return;
	
	ordem( nos[no].esq, r );
	r.push_back( nos[no].val );
	ordem( nos[no].dir, r );
}
int main(){
	freopen( "movetofront.in", "r", stdin );
	freopen( "movetofront.out", "w", stdout );
	srand( time(0) );
	int aux = 0;
	
	
	int root = -1;
	int n, m;
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i ){
		nos[i].dir = nos[i].esq = -1;
//		scanf( "%d %d", &nos[i].x, &nos[i].y );
		nos[i].x = i + 1;
		nos[i].y = rand();
		nos[i].val = nos[i].x;
		root = add( root, i );
//		printf( "Inserção %d (%d)\n", i + 1, root );
//		dfs( root, 1 );
	}
	
//	dfs( root, 1 );
	
	int p1, p2, p3;
	scanf( "%d", &m );
	while( m-- ){
		int a, b;
		scanf( "%d %d", &a, &b );
		split( root, a - 1, p1, p2 );
//		printf( "P1\n" );
//		dfs( p1, 1 );
//		printf( "P2\n" );
//		dfs( p2, 1 );
//		
		split( p2, b - a + 1, p2, p3 );
		
		p1 = merge( p2, p1 );
		root = merge( p1, p3 );
	}
	
	vector<int> r;
	ordem( root, r );
	printf( "%d", r[0] );
	for( int i = 1; i < r.size(); ++i ) printf( " %d", r[i] );
	printf( "\n" );
	
}




