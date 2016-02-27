#include <cstdio>
#include <map>
#include <cmath>
using namespace std;


typedef long long ll;

map<ll,int> mapa;
int a, b, n, m;

int expo( ll num, int xp, int mod ){
	ll resul = 1;
	
	while( xp ){
		if( xp & 1 )
			resul = ( resul * num ) % mod;
		num = ( num * num ) % mod;
		xp = xp >> 1;
	}
	
	return int( resul );
}

void baby(){
	m = int( sqrt( n ) ) + 1;
	ll num = 1;
	
	for( int i = 0; i < m; ++i ){
		if( mapa.find( num ) == mapa.end() )
			mapa[ num ] = i;
		else
			break;
		num = ( num * a ) % n;
	}
}

int giant(){
	baby();

	ll num = b;
	a = expo( a, n - 1 - m, n );
	
	for( int i = 0; i < m; ++i ){
		if( mapa.find( num ) != mapa.end() )
			return i * m + mapa[ num ];
		num = ( num * a ) % n;
	}
	
	return -1;
}

int main(){
	while( scanf( "%d %d %d", &n, &a, &b ) != EOF ){
		mapa.clear();
		int resp = giant();
		if( resp == -1 )
			printf( "no solution\n" );
		else
			printf( "%d\n", resp );
	}
}


