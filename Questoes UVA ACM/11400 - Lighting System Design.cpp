#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define oo 0x7fffffff
#define N 2000
typedef long long ll;

struct No{
	int k, l, c, v;
	
	bool operator<( const No& n ) const{
		return v < n.v;
	}
}nos[ N ];


int pd[ N ][ 11 ];
int n;

int faz(){
	sort( nos, nos + n );
	
	for( int i = 0; i < n; ++i ){
		for( int j = 1; j < 11; ++j )
			pd[ i ][ j ] = oo;
	}
		
	pd[ 0 ][ nos[ n - 1 ].c ] = nos[ n - 1 ].c * nos[ n - 1 ].l + nos[ n - 1 ].k;
	
	for( int i = 1; i < n; ++i ){
		No& atual = nos[ n - 1 - i ];
		
		for( int j = 1; j < 11; ++j ){
			if( pd[ i - 1 ][ j ] == oo ) continue;
			
			if( j <= atual.c )
				pd[ i ][ j ] = min( pd[ i ][ j ], pd[ i - 1 ][ j ] + j * atual.l );
			else{
				pd[ i ][ atual.c ] = min( pd[ i ][ atual.c ], pd[ i - 1 ][ j ] + atual.k + atual.c * atual.l );
				pd[ i ][ j ] = min( pd[ i ][ j ], pd[ i - 1 ][ j ] + atual.l * j );
			}
		}
	}
	
	int menor = oo;
	for( int j = 1; j < 11; ++j )
		menor = min( menor, pd[ n - 1 ][ j ] );
	
	return menor;
}

int main(){
	while( scanf( "%d", &n ) != EOF && n ){
		for( int i = 0; i < n; ++i )
			scanf( "%d %d %d %d", &nos[i].v, &nos[i].k, &nos[i].c, &nos[i].l );
		
		printf( "%d\n", faz() );
	}
}










