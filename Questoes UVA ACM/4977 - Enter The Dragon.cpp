#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

#define maxi 1000100
#define mp( x, y ) make_pair( x, y )

int resp[ maxi ], seco, lg, ultimo[ maxi ], num[ maxi ];

int main(){
	int casos;
	set< pair<int,int> > conj;
	scanf( "%d", &casos );
	
	while( casos-- ){
		int temp, aux;

		scanf( "%d %d", &lg, &temp );
		conj.clear();
		fill( ultimo, ultimo + lg + 1, -1 );
	//	fill( resp, resp + lg + 1, -1 );
		
		bool dm = false;
		set< pair<int,int> >::iterator it; 
		pair<int,int> par;
		//printf( "Temp %d size %d\n", temp, conj.size() );
		seco = 0;
		for( int i = 0; i < temp; ++i )
			scanf( "%d", num + i );
		
		for( int i = 0; i < temp; ++i ){
			aux = num[ i ];
			
			if( aux == 0 ){
				conj.insert( mp( i, seco ) );
				++seco;
			}else{
				par.first = ultimo[ aux ];
				it = conj.upper_bound( par );
				if( it != conj.end() ){
					resp[ (*it).second ] = aux;
					conj.erase( it );
				}else{
					dm = true;
					break;
				}
				
				ultimo[ aux ] = i;
			}
		}
		
		if( dm ){
			printf( "NO\n" );
		}else{			
			for( it = conj.begin(); it != conj.end(); ++it )
				resp[ (*it).second ] = 0;
				
			printf( "YES\n%d", resp[ 0 ] );
			for( int i = 1; i < seco; ++i )
				printf( " %d", resp[ i ] );
			printf( "\n" );
		}
	}
}
