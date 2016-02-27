#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct Ponto{
	int x, y;
	int id;
	
	Ponto(){}
	Ponto( int xx, int yy ){
		x = xx;
		y = yy;
	}
	
	Ponto operator-( const Ponto& p ) const{
		return Ponto( x - p.x, y - p.y );
	}
	
	int operator*( const Ponto& p ) const{
		return x * p.y - y * p.x;
	}
	
	int operator!() const{
		return x * x + y * y;
	}

	
}pts[ 8 ];

Ponto pv;

bool comp( const Ponto& a, const Ponto& b ){
	Ponto aa = a - pv, bb = b - pv;
	int prod = aa * bb;
	
	if( !prod ) return !aa < !bb;
	
	return prod > 0; 
}

int bits( int n ){
	int cont = 0;
	while( n ){
		++cont;
		n -= n & (-n);
	}
	
	return cont;
}

int main(){
	for( int i = 0; i < 8; ++i ){
		scanf( "%d %d", &pts[ i ].x, &pts[ i ].y );
		pts[ i ].id = i;
	}
	
	bool achou = false;
	vector<Ponto> quad, ret;
	for( int mk = 1; !achou && mk < ( 1 << 8 ); ++mk ){
//		if( bits( mk ) != 4 ) continue;
		quad.clear();
		ret.clear();
		
		
		for( int i = 0; i < 8; ++i ){
			if( mk & ( 1 << i ) )
				quad.push_back( pts[ i ] );
			else
				ret.push_back( pts[ i ] );
		}
		
		if( quad.size() != ret.size() ) continue;
		
		pv = quad[ 0 ];
		for( int i = 1; i < 4; ++i ){
			if( quad[ i ].x < pv.x || ( quad[ i ].x == pv.x && quad[ i ].y < pv.y ) )
				pv = quad[ i ];
		}
		
//		for( int i = 0; i < 4; ++i )
//			printf( ">> %d\n", quad[ i ].id + 1 );
		sort( quad.begin(), quad.end(), comp );
//		for( int i = 0; i < 4; ++i )
//			printf( ">> %d\n", quad[ i ].id + 1 );
//		printf( "---\n" );
		int d = -1;
		bool dm = false;
		for( int i = 0; i < 4; ++i ){
			int dist = !( quad[ i ] - quad[ ( i + 3 ) % 4 ] );
			if( d == -1 ) d = dist;
			else if( d != dist ){
				dm = true;
				break;
			}
		}

		Ponto v1 = quad[ 1 ] - quad[ 0 ], v2 = quad[ 3 ] - quad[ 0 ];
		if( v1.x * v2.x + v1.y * v2.y != 0 ) dm = true;		
				
		if( dm ) continue;
		
		
//		printf( "Sim %d\n", d );
		
		pv = ret[ 0 ];
		for( int i = 1; i < 4; ++i ){
			if( ret[ i ].x < pv.x || ( ret[ i ].x == pv.x ) && ret[ i ].y < pv.y )
				pv = ret[ i ];
		}
		sort( ret.begin(), ret.end(), comp );
		
		vector<int> vet;
		for( int i = 0; i < 4; ++i ){
			vet.push_back( !( ret[ i ] - ret[ ( i + 3 ) % 4 ] ) );
		}
		
		sort( vet.begin(), vet.end() );
		if( vet[ 1 ] != vet[ 0 ] || vet[ 2 ] != vet[ 3 ] ) dm = true;
		
		v1 = ret[ 1 ] -ret[ 0 ];
		v2 = ret[ 3 ] - ret[ 0 ];
		if( v1.x * v2.x + v1.y * v2.y != 0 ) dm = true;
		
		achou = !dm;
	}
	
	if( achou ){
		printf( "YES\n" );
		printf( "%d", quad[ 0 ].id + 1 );
		for( int i = 1; i < 4; ++i ) printf( " %d", quad[ i ].id + 1 );
		printf( "\n%d", ret[ 0 ].id + 1 );
		for( int i = 1; i < 4; ++i ) printf( " %d", ret[ i ].id + 1 );
		printf( "\n" );
	}else
		printf( "NO\n" );
}




