#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

int last( int a, int b ){
	int resp = 1;
	
	while( b ){
		if( b & 1 )
			resp = ( resp * a ) % 1000;
		a = ( a * a ) % 1000;
		b = b >> 1;
	}
	
	return resp;
}

 
int lead( int a, int b ){
	double num = b * log10( a ), decimal, inteira;
	
	decimal = modf( num, &inteira );
	
	return int( 100 * pow( 10, decimal ) );
}

int main(){
	int casos, a, b;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &a, &b );
		printf( "%03d...%03d\n", lead( a, b ), last( a % 1000, b ) ); 
	}
}
