#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxi 100100
typedef long long ll;

ll acc[ maxi ], k;
int num[ maxi ], ord[ maxi ], n;

ll contar( ll rodada ){
	if( rodada == 0 ) return 0;
	
	int ini = 0, fim = n - 1, meio;
	ll best = rodada * n;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		
		if( ord[ meio ] > rodada )
			fim = meio - 1;
		else{
			best = acc[ meio ] + rodada * ( n - 1 - meio );
			ini = meio + 1; 
		} 
	}
	
	return best;
}

pair<ll,ll> bs(){
	ll ini = 0, fim = 1000000000000LL, meio;
	ll rodada = 0;
	ll qtd, best = 0;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		qtd = contar( meio );
					
		if( qtd > k )
			fim = meio - 1;
		else{
			rodada = meio;
			best = qtd;
			ini = meio + 1;
		}
	}
	
	return make_pair( rodada, best );
}

int main(){
	cin >> n >> k;
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d", num + i );
		ord[ i ] = num[ i ];
	}
	
	sort( ord, ord + n );
	acc[ 0 ] = ord[ 0 ];
	for( int i = 1; i < n; ++i )
		acc[ i ] = acc[ i - 1 ] + ord[ i ];
	
	if( acc[ n - 1 ] < k )
		printf( "-1\n" );
	else if( acc[ n - 1 ] == k )
		printf( "\n" );
	else{
		pair<ll,ll> temp = bs();
		ll rodada = temp.first;
		k -= temp.second;
	//	printf( "Rodada %d\n", rodada );
		for( int i = 0; i < n; ++i )
			num[ i ] = max( 0LL, num[ i ] - rodada );
			
		int prt;
		for( prt = 0; k; ++prt ){
			if( num[ prt ] ){
				--k;
				--num[ prt ];
			}
		}
		
		int pog = 0;
		for( int p = prt; p < n; ++p ){
			if( num[ p ] )
				ord[ pog++ ] = ( p + 1 );
		}
		
		for( int p = 0; p < prt; ++p ){
			if( num[ p ] )
				ord[ pog++ ] = ( p + 1 );
		}
		
		printf( "%d", ord[ 0 ] );
		for( int i = 1; i < pog; ++i ){
			printf( " %d", ord[ i ] );
		}
		printf( "\n" );
		
	}
}

