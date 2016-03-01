#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;
typedef long long ll;
#define N 300000

int aux = 10000;
 
void dfs( int, int );

struct No{
	ll soma;
	int esq, dir;
	int x, y;
	ll num;
	bool inv;
	
	void set( int ind, ll val ){
		soma = val;
		num = val;
		x = ind;
		
		esq = dir = -1;
		y = rand();
//y = aux++;
		inv = false;
	}
}nos[ N ];

int n, m, prt;

void contador( int t ){
	if( t == -1 ) return;
	int esq = 0, dir = 0;
	
	nos[t].soma = nos[t].num;
	if( nos[t].esq != -1 ) nos[t].soma += nos[ nos[t].esq ].soma;
	if( nos[t].dir != -1 ) nos[t].soma += nos[ nos[t].dir ].soma;
	
	if( nos[t].esq != -1 ) esq = nos[ nos[t].esq ].x;
	if( nos[t].dir != -1 ) dir = nos[ nos[t].dir ].x;
	
	nos[t].x = 1 + esq + dir;
}

void ajeitar( int t ){
	if( t == -1 ) return;
	
	if( nos[t].inv ){
		swap( nos[t].esq, nos[t].dir );
		if( nos[t].dir != -1 ) nos[ nos[t].dir ].inv = !nos[ nos[t].dir ].inv;
		if( nos[t].esq != -1 ) nos[ nos[t].esq ].inv = !nos[ nos[t].esq ].inv;
		nos[t].inv = false;
	}
}

void split( int t, int x, int& l, int& r ){
	ajeitar( t ); 
	
	if( t == -1 ){
		l = r = -1;
		return;
	}
	
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd = nos[ nos[t].esq ].x + 1;
	
	if( x == qtd ){
		r = nos[t].dir;		
		l = t;
		nos[l].dir = -1;
	}else if( x > qtd ){
		split( nos[t].dir, x - qtd, nos[t].dir, r );
		l = t;
	}else{
		split( nos[t].esq, x, l, nos[t].esq );
		r = t;
	}
	contador(t);
}

int merge( int& l, int& r ){
	if( l == -1 ) return r;
	if( r == -1 ) return l;
	
	ajeitar(l); ajeitar(r);
	
	if( nos[l].y > nos[r].y ){
//		ajeitar(r);
		nos[r].esq = merge( l, nos[r].esq );
		contador( r );
		return r;
	}else{
//		ajeitar(l);
		nos[l].dir = merge( nos[l].dir, r );
		contador( l );
		return l;
	}
}

int add( int t, int nw ){
	ajeitar( t );
	
	if( t == -1 || nos[t].y > nos[nw].y ){
		split( t, nos[nw].x, nos[nw].esq, nos[nw].dir );
		contador(nw);
		return nw;
	}
	
	int qtd = 1;
	if( nos[t].esq != -1 ) qtd = nos[ nos[t].esq ].x + 1;
	if( nos[nw].x > qtd ){
		nos[nw].x -= qtd;
		nos[t].dir = add( nos[t].dir, nw );
	}else{
		nos[t].esq = add( nos[t].esq, nw );
	}
	
	contador( t );
	return t;
}

int main(){
	#ifndef X
	freopen( "reverse.in", "r", stdin );
	freopen( "reverse.out", "w", stdout );
	#endif
	
	srand( rand() );
	scanf( "%d %d", &n, &m );
	prt = 0;
	int root = -1;
	for( int i = 0; i < n; ++i ){
		int tmp;
		
		scanf( "%d", &tmp );
		nos[prt].set( i + 1, tmp );
		root = add( root, prt++ );
	}
	
	while( m-- ){
		int op, a, b;
		scanf( "%d %d %d", &op, &a, &b );
		int p1 = -1, p2 = -1, p3 = -1;
		split( root, b, p1, p3 );
		split( p1, a-1, p1, p2 );
		
		assert( p2 != -1 );
		
		if( !op )
			cout << nos[p2].soma << "\n";
		else
			nos[p2].inv = !nos[p2].inv;
		
		p2 = merge( p1, p2 );
		root = merge( p2, p3 );
	}
}




