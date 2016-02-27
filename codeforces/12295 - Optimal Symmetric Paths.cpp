#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define oo 0x7fffffffffffffffLL
#define MOD 1000000009
#define N 200
typedef long long ll;

struct No{
	int c, x, y;
	ll s;
	
	No(){}
	No( int a, ll b, int i, int j ){
		c = a;
		s = b;
		x = i;
		y = j;
	}
	bool operator<( const No& b ) const{
		return !( c < b.c );
	}
};

int lim[ N ];
int ma[ N ][ N ];
int custo[ N ][ N ];
ll soma[ N ][ N ];
bool marc[ N ][ N ];
priority_queue<No> heap;
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

int n;

void dij(){
	for( int i = 0; i < n; ++i )
		lim[ i ] = n - 1 - i;
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j < n; ++j ){
			custo[i][j] = 0x7fffffff;
		}
	}
	
	while( heap.empty() == false ) heap.pop();
	memset( marc, false, sizeof( marc ) );
	heap.push( No( ma[0][0] + ma[n-1][n-1], 1, 0, 0 ) );
	custo[ 0 ][ 0 ] = ma[0][0] + ma[n-1][n-1];
	soma[ 0 ][ 0 ] = 1;
	
	while( !heap.empty() ){
		No at = heap.top();
		heap.pop();
		if( marc[ at.x ][ at.y ] ) continue;
		if( at.y > lim[ at.x ] ) continue;
		marc[ at.x ][ at.y ] = true;
		custo[ at.x ][ at.y ] = at.c;
		
		for( int i = 0; i < 4; ++i ){
			if( at.x + dx[ i ] >= n || at.x + dx[ i ] < 0 ) continue;
			if( at.y + dy[ i ] >= n || at.y + dy[ i ] < 0 ) continue;
			if( marc[ at.x + dx[i] ][ at.y + dy[i] ] ) continue;
			if(at.c + ma[ at.x + dx[i] ][ at.y + dy[i] ] + ma[ n-1 - at.y ][ n-1 - at.x ] < custo[ at.x + dx[i] ][ at.y + dy[i] ] ){
				soma[ at.x + dx[i] ][ at.y + dy[i] ] = soma[ at.x ][ at.y ];
				custo[ at.x + dx[i] ][ at.y + dy[i] ] = at.c + ma[ at.x + dx[i] ][ at.y + dy[i] ] + ma[ n-1 - at.y ][ n-1 - at.x ];
				heap.push( No( custo[ at.x + dx[i] ][ at.y + dy[i] ], -1, at.x + dx[i], at.y + dy[i] ) );
			}else if(at.c + ma[ at.x + dx[i] ][ at.y + dy[i] ] + ma[ n-1 - at.y ][ n-1 - at.x ] == custo[ at.x + dx[i] ][ at.y + dy[i] ] ){
				soma[ at.x + dx[i] ][ at.y + dy[i] ] += soma[ at.x ][ at.y ];
				soma[ at.x + dx[i] ][ at.y + dy[i] ] %= MOD;
			}
		}
	}
}

int main(){
	while( scanf( "%d", &n ) != EOF && n ){
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j ){
				scanf( "%d", &ma[ i ][ j ] );
			}
		}
		
		dij();
		ll s;
		int cam = 0x7fffffff;
		for( int i = 0; i < n; ++i ){
			if( custo[ i ][ n - 1 - i ] < cam ){
				cam = custo[ i ][ n - 1 - i ];
				s = soma[ i ][ n - 1 - i ];
			}else if( custo[ i ][ n - 1 - i ] == cam ){
				s += soma[ i ][ n - 1 - i ];
			}
		}
		printf( "%lld\n", s );
	}
}





