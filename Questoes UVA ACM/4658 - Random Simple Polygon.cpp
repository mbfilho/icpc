#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k;

struct P{
	int id;
	ll x, y;
	
	P( ll a, ll b ){
		x = a;
		y = b;
	}
	
	P(){}
	
	P operator-( const P& a ) const{
		return P( x - a.x, y - a.y );
	}
	
	ll operator%( const P& p ) const{
		return x * p.y - y * p.x;
	}
	
	bool operator==( const P& p ) const{
		return x == p.x && y == p.y;
	}
}pts[ 20000 ], p;


bool comp( const P& a, const P& b ){		
	return ( a - pts[ 0 ] ) % ( b - pts[ 0 ] ) > 0;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &k );
		for( int i = 0; i < n; ++i ){
			scanf( "%lld %lld", &pts[ i ].x, &pts[ i ].y );
			pts[ i ].id = i + 1;
		}
		
		p = pts[ 0 ];
		int ind = 0;
		for( int i = 1; i < n; ++i ){
			if( pts[ i ].y < p.y ){
				p = pts[ i ];
				ind = i;
			}else if( pts[ i ].y == p.y && pts[ i ].x < p.x ){
				ind = i;
				p = pts[ i ];
			}
		}
		
		pts[ ind ] = pts[ 0 ];
		pts[ 0 ] = p;

		sort( pts + 1, pts + n, comp );
		for( int i = 0; i < k; ++i ){
			printf( "%d\n", pts[ i ].id );
		}
	}
}


