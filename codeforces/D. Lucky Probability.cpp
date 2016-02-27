#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll luc[ 1000000 ]; 
int cont = 3;

void gerar(){
	luc[ 0 ] = 0;
	luc[ 1 ] = 4;
	luc[ 2 ] = 7;
	int qtd = 2;
	ll pot = 10;
	int ini = 1;
	
	bool sair = false;
	while( !sair ){
		for( int i = ini; i < ini + qtd; ++i )
			luc[ cont++ ] = pot * 4 + luc[ i ];
		for( int i = ini; i < ini + qtd; ++i )
			luc[ cont++ ] = pot * 7 + luc[ i ];
		if( luc[ cont - 1 ] > 2000000000 ) sair = true;
		ini += qtd;
		qtd *= 2;
		pot *= 10;
	}

}

int max( ll a, int b ){
	if( a > b )
		return a;
	return b;
}

int min( ll a, int b ){
	if( a > b )
		return b;
	return a;
}

int main(){
	int pr, pl, vr, vl;
	ll soma = 0;
	int k;
	gerar();

	scanf( "%d %d %d %d %d", &pl, &pr, &vl, &vr, &k );
	int prt = 1;
	
	while( luc[ prt + k - 1 ] <= pr || luc[ prt + k - 1 ] <= vr ){
		ll il, fl, ir, fr;
		
		//Tirando o menor de P
		il = max( luc[ prt - 1 ] + 1, pl );
		fl = min( luc[ prt ], pr );
		//e portanto o maior de V
		ir = max( luc[ prt + k - 1 ], vl );
		fr = min( luc[ prt + k ] - 1, vr );
		if( il <= fl && ir <= fr )
			soma += ( fl - il + 1 ) * ( fr - ir + 1 );
		
		//Tirando o MAIOR de P
		il = max( luc[ prt - 1 ] + 1, vl );
		fl = min( luc[ prt ], vr );
		//e portanto o menor de V
		ir = max( luc[ prt + k - 1 ], pl );
		fr = min( luc[ prt + k ] - 1, pr );
		
		if( il <= fl && ir <= fr )
			soma += ( fl - il + 1 ) * ( fr - ir + 1 );
	
		if( k == 1 && luc[ prt ] >= vl && luc[ prt ] <= vr && luc[ prt ] >= pl && luc[ prt ] <= pr )
			--soma; 
		++prt;
	}

	ll total = ll( pr - pl + 1 ) * ( vr - vl + 1 );
	double resp = double( soma ) / total;
	printf( "%.9lf\n", resp );
}

