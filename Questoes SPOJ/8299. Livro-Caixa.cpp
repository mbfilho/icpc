#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

#define mp(x,y) make_pair(x,y)

typedef long long ll;

map< pair<int,int>, pair<ll,ll> > mapa;

int num[ 600 ], n;

pair<ll,ll> rec( int soma, int k ){
	pair<int,int> estado = mp( soma, k );
	map< pair<int,int>, pair<ll,ll> >::iterator it = mapa.find( estado );
	
	if( it != mapa.end() )
		return it -> second;
	
	if( k == n - 1 ){
		//Num[k] deve ser positivo
		if( soma == num[ k ] )
			return mapa[ estado ] = mp( 0, 1LL << k );
		
		//Negativo:
		else if( soma == -num[ k ] )
			return mapa[ estado ] = mp( 1LL << k, 0 );
		
		else
			return mapa[ estado ] = mp( 0, 0 );
	}
	
	ll neg = 0, pos = 0;
	pair<ll,ll> resultado;
	
	//Num[k] negativo
	resultado = rec( soma + num[ k ], k + 1 );
	if( resultado.first | resultado.second ){
		neg = resultado.first;
		pos = resultado.second;
		neg |= ( 1LL << k );
	}
	
	//Num[k] postivo
	resultado = rec( soma - num[ k ], k + 1 );
	if( resultado.first | resultado.second ){
		neg |= resultado.first;
		pos |= resultado.second;
		pos |= ( 1LL << k );
	}
	
	return mapa[ estado ] = mp( neg, pos );	
}

int main(){
	int soma;

	while( scanf( "%d %d", &n, &soma ) && ( n | soma ) ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", num + i );
		mapa.clear();
		
		pair<ll,ll> resp = rec( soma, 0 );
		
		if( resp.first | resp.second ){
			for( int i = 0; i < n; ++i ){
				if( ( resp.first & ( 1LL << i ) ) && ( resp.second & ( 1LL << i ) ) )
					printf( "?" );
				else if( resp.first & ( 1LL << i ) )
					printf( "-" );
				else
					printf( "+" ); 
			}
			
			printf( "\n" );
		}else
			printf( "*\n" );
	}
}



