#include <cstdio>
#include <vector>
#include <map>
using namespace std;

//int pot[ 21 ];
map< int,vector<int> > mapa;

map< int,vector<int> >::iterator it2;
vector<int> win( int est ){
	if( (it2 = mapa.find( est ) ) != mapa.end() )
		return it2 -> second;
		
	vector<int> resp;
	
	if( est == 0 )
		return mapa[ est ] = resp;
	
	for( int i = 2; i <= 20; ++i ){
		if( est & ( 1 << i ) ){
			int rec = est;
			
			for( int j = i; j <= 20; j += i ){
				rec = rec & ( ~( 1 << j ) );
				
				for( int k = 20 - j; k >= 2; --k ){
					if( ( est & ( 1 << k ) ) == 0 )
						rec = rec & ( ~(1 << (k + j) ) );
				}
			}
			
			if( win( rec ).size() == 0 )
				resp.push_back( i );
		}
	}
	
	return mapa[ est ] = resp;
}

int main(){
	//for( int i = 0; i <= 20; ++i )
	//	pot[ i ] = ( 1 << i );
		
	int casos, rest, temp;
	vector<int> num;
	
	scanf( "%d", &casos );
	
	for( int k = 1; k <= casos; ++k ){
		printf( "Scenario #%d:\n", k );
		
		scanf( "%d", &rest );
		int base = 0;
		
		for( int i = 0; i < rest; ++i ){
			scanf( "%d", &temp );
			base = base | ( 1 << temp );
		}
		
		if( ( num = win( base ) ).size() == 0 )
			printf( "There is no winning move.\n\n" );
		else{
			printf( "The winning moves are:" );
			int tam = num.size();
			for( int i = 0; i < tam; ++i )
				printf( " %d", num[ i ] );
			printf( ".\n\n" );
		}
	}
	
}
