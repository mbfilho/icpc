#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;

set<ll> temp, inter;
int ar[ 5 ];

//Mt ineficiente
char g1[ 10 ][ 10 ], g2[ 10 ][ 10 ], nome[ 100 ];

bool add(){
	bool retorno = false;
	for( int i = 0; i < 5; ++i ){
		if( ar[ i ] !=  5 )
			retorno = true;
	}
	
	++ar[ 4 ];
	if( ar[ 4 ] > 5 ){
		ar[ 4 ] = 0;
		int carry = 1;
		
		for( int i = 3; i >= 0; --i ){
			ar[ i ] += carry;
			
			if( ar[ i ] > 5 ){
				ar[ i ] = 0;
				carry = 1;
			}else
				carry = 0;
		}
	}
	
	return retorno;
}

int main(){
	int casos, k;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &k );
		temp.clear();
		inter.clear();
		
		for( int i = 0; i < 6; ++i )
			scanf( "%s", g1[ i ] );
		for( int i = 0; i < 6; ++i )
			scanf( "%s", g2[ i ] );
		
		fill( ar, ar + 5, 0 );
		ll hash;
		
		do{
			hash = 0;
			for( int i = 0; i < 5; ++i )
				hash = hash * 26 + g1[ ar[i] ][ i ] - 'A';
			temp.insert( hash );
		}while( add() );

		
		fill( ar, ar + 5, 0 );		
		do{
			hash = 0;
			for( int i = 0; i < 5; ++i )
				hash = hash * 26 + g2[ ar[i] ][ i ] - 'A'; 
			if( temp.find( hash ) != temp.end() )
				inter.insert( hash );
		}while( add() );
		
		//printf( "Aqui\n" );
		
		if( k > inter.size() )
			printf( "NO\n" );
		else{
			int cont = 1;
			for( set<ll>::iterator it = inter.begin(); it != inter.end(); ++it ){
				if( cont == k ){
					hash = *it;
					for( int i = 4; i >= 0; --i ){
						nome[ i ] = ( hash % 26 + 'A' );
						hash /= 26;
					}
					nome[ 5 ] = '\0';
					
					printf( "%s\n", nome );
					break;
				}
				++cont;
			}
		}
	}
}

