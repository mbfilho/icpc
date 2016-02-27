#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

class Aero{
public:
	int cong;
	int id;
	
	bool operator<( const Aero& o ) const{
		if( cong == o.cong )
			return id < o.id;
			
		return cong > o.cong;
	}
}aeros[ 101 ];

int main(){
	int a, v, x, y;
	int teste = 1;
	
	freopen( "in.txt", "r", stdin );
	cin >> a >> v;
	
	while( a | v ){
		for( int i = 1; i <= a; ++i ){
			aeros[ i ].id = i;
			aeros[ i ].cong = 0;
		}
		
		for( int i = 0; i < v; ++i ){
			cin >> x >> y;
			++aeros[ x ].cong;
			++aeros[ y ].cong;
		}
		
		sort( aeros + 1, aeros + a + 1 );
		
		printf( "Teste %d\n", teste++ );
		printf( "%d", aeros[ 1 ].id );
		
		int i = 2;
		while( i <= a && aeros[ i ].cong == aeros[ 1 ].cong ){
			printf( " %d", aeros[ i++ ].id );
		}
		
		printf( "\n\n" ); 
		
		cin >> a >> v;		
	}
}
