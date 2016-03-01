#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
#define N 500000
#define M 500000

int resp[ M ], c;

struct No{
	int x, y;
	int val;
	int cont;
	int esq, dir;
	
	No(){
		x = 8; y = 0; val = -1; cont = -1; esq = 0; dir = 0;
	}
	
	void set( int ind ){
		val = 0;
		cont = 0;
		x = ind;
		y = rand();
		esq = dir = -1;
	}
}nos[M];
int n, m;

void ajeitar( int t ){
	if( t == -1 ) return;
	
	nos[t].x = 1;
	if( nos[t].val == 0 ) nos[t].cont = 1;
	else nos[t].cont = 0;
	
	if( nos[t].esq != -1 ){
		nos[t].x += nos[ nos[t].esq ].x;
		nos[t].cont += nos[ nos[t].esq ].cont;
	}
	
	if( nos[t].dir != -1 ){
		nos[t].x += nos[ nos[t].dir ].x;
		nos[t].cont += nos[ nos[t].dir ].cont;
	}
	
}


void split( int t, int x, int& l, int& r ){
	if( t == -1 ){
		l = r = -1;
		return;
	}
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd += nos[ nos[t].esq ].x;
	
	if( x == qtd ){
		l = t;
		r = nos[t].dir;
		
		nos[t].dir = -1;
	}else if( x < qtd ){
		split( nos[t].esq, x, l, nos[t].esq );
		r = t;
	}else{
		split( nos[t].dir, x - qtd, nos[t].dir, r );
		l = t;
	}
	
	ajeitar(t);
}

int merge( int& l, int& r ){
	if( l == -1 ) return r;
	if( r == -1 ) return l;
	
	if( nos[l].y > nos[r].y ){
		nos[r].esq = merge( l, nos[r].esq );
		ajeitar(r);
		return r;
	}else{
		nos[l].dir = merge( nos[l].dir, r );
		ajeitar(l);
		return l;
	}
}

int add( int t, int nw ){
	if( t == -1 || nos[t].y > nos[nw].y ){
		split( t, nos[nw].x, nos[nw].esq, nos[nw].dir );
		ajeitar(nw);
		return nw;
	}
	
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd += nos[ nos[t].esq ].x;
	
	if( nos[nw].x < qtd ){
		nos[t].esq = add( nos[t].esq, nw );
	}else{
		nos[nw].x -= qtd;
		nos[t].dir = add( nos[t].dir, nw );
	}
	
	ajeitar(t);
	return t;
}

bool insert( int t, int x, int val ){
	if( t == -1 ) return false;
	
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd = 1 + nos[ nos[t].esq ].x;
	
	if( x == qtd ){
		if( !nos[t].val ){
			--nos[t].cont;
			nos[t].val = val;
			return true;
		}else return false;
	}else if( x < qtd ){
		if( insert( nos[t].esq, x, val ) ){
			ajeitar(t);
			return true;
		}else return false;
	}else{
		if( insert( nos[t].dir, x - qtd, val ) ){
			ajeitar(t);
			return true;
		}else return false;
	}
}

int remove( int t ){
	if( t == -1 ) return t;
	int esq = 0, dir = 0;
	if( nos[t].esq != -1 ) esq = nos[ nos[t].esq ].cont;
	if( nos[t].dir != -1 ) dir = nos[ nos[t].dir ].cont;
	
	if( esq ){
		nos[t].esq = remove( nos[t].esq );
	}else if( !nos[t].val ){
		int tmp = merge( nos[t].esq, nos[t].dir );
		ajeitar( tmp );
		return tmp;
	}else if( dir ){
		nos[t].dir = remove( nos[t].dir );
	}
	
	ajeitar(t);
	return t;
}

void print( int t, bool b = false ){
	if( t == -1 ) return;
	
	print( nos[t].esq, b );
	resp[c++] = t;
	print( nos[t].dir, b );
}

int main(){
	srand( time(0) );
	#ifndef X
	freopen( "key.in", "r", stdin );
	freopen( "key.out", "w", stdout );
	#endif
		
	scanf( "%d %d", &n, &m );
	int root = -1;
	int prt = 0;
	c = 0;
	
	for( int i = 1; i <= m + n + 7; ++i ){
		nos[prt].set(i);
		root = add( root, prt );
		prt++;
	}
	
	for( int i = 1; i <= n; ++i ){
		int tmp;
		scanf( "%d", &tmp );
		
		if( !insert( root, tmp, i ) ){
			int p1 = -1, p2 = -1, p3 = -1;
			split( root, tmp, p1, p2 );
			
			
			split( p1, tmp - 1, p1, p3 );
			p2 = remove( p2 );
			
			nos[prt].set(1);
			nos[prt].val = i;

			root = merge( p1, prt );
			p3 = merge( p3, p2 );
			root = merge( root, p3 );
			++prt;
		}
	}
	
	print( root );
	--c;
	while( c >= 0 && nos[ resp[c] ].val == 0 ){
		--c;
	}

	printf( "%d\n", c + 1 );
	for( int i = 0; i <= c; ++i ){
		printf( "%d ", nos[ resp[i] ].val );
	}
	printf( "\n" );
}


