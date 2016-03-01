#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
typedef long long ll;
#define N 300300
#define MOD 1000000000

int pog = 1000000;

struct No{
	int esq, dir;
	ll se, sd;
	ll x, y;
	
	void reset( ll a ){
		esq = dir = -1;
		se = sd = 0;
		x = a;
		y = pog--;
	}
}nos[ N ];
int prt;
int op;
/*
void dfs( int root ){
	if( root == -1 ) return;
	
	printf( "(%I64d,%I64d - %I64d, %I64d)\n", nos[root].x, nos[root].y, nos[root].se, nos[root].sd );
	dfs( nos[root].esq );
	dfs( nos[root].dir );
}
*/
void split( int t, int x, int& l, int& r ){
	if( t == -1 ){
		l = r = -1;
	}else{
		if( x < nos[ t ].x ){
			split( nos[t].esq, x, l, nos[t].esq );
			r = t;
		}else{
			split( nos[t].dir, x, nos[t].dir, r );
			l = t;
		}
	}
}

int add( int t ){
	if( t == -1 || nos[prt].y > nos[t].y ){
		//printf( "aqui %d %d\n", t, nos[prt].x );
		split( t, nos[prt].x, nos[prt].esq, nos[prt].dir );
		++prt;
		return prt - 1;
	}else{
		int aux = prt;
		if( nos[prt].x < nos[t].x ){
			nos[t].esq = add( nos[t].esq );
			if( aux != prt )
				nos[t].se += nos[aux].x;
				
		}else if( nos[prt].x > nos[t].x ){
			//if( nos[prt].x == 7 ) printf( "Here\n" );
			nos[t].dir = add( nos[t].dir );
			if( aux != prt )
				nos[t].sd += nos[aux].x;
			//if( nos[aux].x == 7 ) printf( "D %d %I64d (%d)\n", aux == prt, nos[t].sd, t );
			
		}
			
		return t; 
	}
}

ll busca( int t, int val ){
	if( t == -1 ) return 0;
	
	if( nos[t].x == val ) return nos[t].sd;
	
	if( val > nos[t].x ) return busca( nos[t].dir, val );
	
	if( val < nos[t].x ){
		return nos[t].x + busca( nos[t].esq, val ) + nos[t].sd;
	}
	
	return 0;
}
char buf[ 10 ];

int main(){
	freopen( "sum.in", "r", stdin );
	freopen( "sum.out", "w", stdout );
	srand( time(0) );
	prt = 0;
	scanf( "%d", &op );
	ll prev = 0;
	int root = -1;
	
	while( op-- ){
		scanf( "%s", buf );
		if( buf[ 0 ] == '+' ){
			ll tmp;
			scanf( "%I64d", &tmp );
			//printf( "|%I64d\n", tmp );
			
			nos[prt].reset( ( tmp + prev ) % MOD );
			root = add( root );
			//printf( ">>> %d\n", tmp );
			//dfs( root );
			//printf( ">>>> %d\n", nos[0].sd );
			prev = 0;
		}else{
			int l, r;
			scanf( "%d %d", &l, &r );
			prev = busca( root, l - 1 ) - busca( root, r );
			//printf( ">>>>> %I64d %I64d\n", busca( root, l - 1 ), busca( root, r ) );
			
			printf( "%I64d\n", prev );
		}
	}
	
}



