#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int num[ 14 ], n, k;
int pd[ 200000 ], cont;

#define MAX_NUM 200000
bool crivo[ MAX_NUM + 1 ];
 
int somar( int mask ){
	if( !mask ) return -1;
	
	int soma = 0;
	for( int i = 0; i < n; ++i ){
		if( mask & ( 1 << i ) )
			soma += num[ i ];
	}
	
	return soma;
}

void gerar(){
	memset( crivo, true, sizeof( crivo ) );
	crivo[ 0 ] = crivo[ 1 ] = false;
	
	for( int i = 4; i <= MAX_NUM; i += 2 )
		crivo[ i ] = false;
	for( int i = 3; i * i <= MAX_NUM; i += 2 ){
		if( !crivo[ i ] ) continue;
		for( int j = i * i; j <= MAX_NUM; j += 2 * i )
			crivo[ j ] = false;
	}
}

bool comp( const int& a, const int& b ){
	return somar( a ) > somar( b );
}

void prepos(){
	cont = 0;
	
	for( int i = 1; i < ( 1 << n ); ++i ){		
		if( crivo[ somar( i ) ] ){
			pd[ cont++ ] = i;
		}
	}
	
	sort( pd, pd + cont, comp );
}

int rec( int padrao, int conj, int inicio ){
	if( padrao == 0 ){
		if( conj > k ) 
			return 1;
		else
			return 0;		
	}
	
	if( conj > k )
		return 0;
	
	
	for( int i = inicio; i < cont; ++i ){
		if( ( padrao & pd[ i ] ) == pd[ i ] ){
			if( rec( padrao & ( ~pd[i] ), conj + 1, i + 1 ) ){
				return somar( pd[ i ] ); 
			}
		}
	}
	
	return 0;
}


int main(){
	gerar();
	int caso = 0;
	
	while( scanf( "%d", &n ) && n != -1 ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", num + i );
		prepos();
		
		int total = ( 1 << n ) - 1, temp = 0;
		for( int i = 0; i < n; ++i ){
			k = num[ i ];
			if( k > n ) continue;
			temp = max( temp, rec( total & (~ (1 << i) ), 1, 0 ) );
		}
	
				
		printf( "Case %d: ", ++caso );
		if( !temp )
			printf( "not a valid clue\n" );
		else
			printf( "%d\n", temp );
	}
}

