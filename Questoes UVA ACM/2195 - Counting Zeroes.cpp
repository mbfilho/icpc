#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAXI 3200000
typedef long long ll;

bool crivo[ MAXI ];
ll primos[ 400000 ];
int contp;

ll num;
int fat[ 400 ], fats;
int divi[ 400 ];

void pre(){
	fill( crivo, crivo + MAXI + 1, true );
	
	for( int i = 4; i <= MAXI; i += 2 )
		crivo[ i ] = false;
	
	
	for( int i = 3; i * i <= MAXI; i += 2 ){
		if( crivo[ i ] == false ) continue;
		
		for( int j = i * i; j <= MAXI; j += 2 * i )
			crivo[ j ] = false;
	}
	
	contp = 1;
	primos[ 0 ] = 2;
	
	for( int i = 3; i <= MAXI; i += 2 ){
		if( crivo[ i ] )
			primos[ contp++ ] = i;
	}
}

void fatorar(){
	ll temp = num;
	fats = 0;
	
	for( int i = 0; i < contp && temp > 1 && primos[i] * primos[i] <= num; ++i ){
		if( temp % primos[ i ] == 0 ){
			fat[ fats ] = 0;
			
			do{
				++fat[ fats ];
				temp /= primos[ i ];
			}while( temp % primos[ i ] == 0 );
			
			++fats;
		}
	}
	
	if( temp != 1 )
		fat[ fats++ ] = 1;		
}

bool incr(){
	int carry;

	divi[ 0 ] = ( divi[ 0 ] + 1 ) % ( fat[ 0 ] + 1 );
	
	carry = ( divi[ 0 ] == 0 );
	
	for( int i = 1; i < fats && carry; ++i ){
		divi[ i ] = ( divi[ i ] + carry ) % ( fat[ i ] + 1 );
		carry = ( divi[ i ] == 0 );
	}
	
	return carry == 0;
}

int calc(){
	int menor = 0x7fffffff;
	
	for( int i = 0; i < fats; ++i ){
		if( divi[ i ] )
			menor = min( menor, ( fat[ i ] - ( fat[ i ] % divi[ i ] ) ) / divi[ i ] );
	}
	
	return menor;
}

int main(){
	pre();
	
	while( scanf( "%lld", &num ) && num ){
		fatorar();
	
		if( num == 1 )
			printf( "1 0\n" );
		else{
			fill( divi, divi + fats, 0 );
			int ret, cont = 0;
			
			while( incr() )
				cont += calc();

			printf( "%lld %d\n", num, cont );
		}

	}
}

