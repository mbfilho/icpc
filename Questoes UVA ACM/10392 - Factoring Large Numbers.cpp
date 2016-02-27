#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;
typedef long long ll;
#define maxi 1000000

int primos[ maxi ], contp;
bool crivo[ maxi + 1 ];

void gerar(){
	contp = 0;
	fill( crivo, crivo + maxi + 1, true );
	
	for( int i = 4; i <= maxi; i += 2 )
		crivo[ i ] = false;
		
	for( int i = 3; i * i <= maxi; i += 2 ){
		if( !crivo[ i ] ) continue;
		
		for( int j = i * i; j <= maxi; j += 2 * i )
			crivo[ j ] = false;
	}
	
	contp = 1;
	primos[ 0 ] = 2;
	for( int i = 3; i <= maxi; i += 2 ){
		if( crivo[ i ] )
			primos[ contp++ ] = i;
	}
		
}

int main(){
	gerar();
	ll num;
	
	while( scanf( "%lld", &num ) && num != -1 ){
		ll temp = num;
		for( int i = 0; i < contp; ++i ){
			if( primos[ i ] * primos[ i ] > num ) break;
			
			while( temp % primos[ i ] == 0 ){
				printf( "    %d\n", primos[ i ] );
				temp /= primos[ i ];
			}
		}
		
		if( temp != 1 )
			printf( "    %lld\n", temp );
			
		printf( "\n" );
	}
}


