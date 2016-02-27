#include <cstdio>

class Ponto{
public:
	int x, y;
	
	bool operator==( const Ponto& p ) const{
		return x == p.x && y == p.y;
	}
	
};

class Reta{
public:
	Ponto p1, p2;
	
	long long prod( Reta& r ){
		return ( p1.x - p2.x ) * ( r.p1.x - r.p2.x ) + ( p1.y - p2.y ) * ( r.p1.y - r.p2.y ); 
	}

	
}r[ 5000 ];

int main(){
	int casos;
	freopen("in.txt","r",stdin);

	
	scanf( "%d", &casos );
	
	for( int i = 0; i < casos; ++i )
		scanf( "%d %d %d %d", &r[ i ].p1.x, &r[ i ].p1.y, &r[ i ].p2.x, &r[ i ].p2.y );
	
	long long prod;
	int q  = 0;
	for( int i = 0; i < casos; ++i ){
		for( int j = i + 1; j < casos; ++j ){
			if( ( r[ i ].p1 == r[ j ].p1 ) || ( r[ i ].p1 == r[ j ].p2 ) || ( r[ i ].p2 == r[ j ].p1 ) || ( r[ i ].p2 == r[ j ].p2 ) ){
				if( r[ i ].prod( r[ j ] ) == 0  )
					++q;
			}
		}
	}
	
	printf( "%d\n", q );
}
