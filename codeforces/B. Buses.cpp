#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;
#define mp make_pair
#define oo 0x7fffffff
#define N 200100
#define M 100100
#define MOD 1000000007

map<int,int> mapa;
ll stops[ N ], soma[ N ];
pair<int,int> segs[ M ];
set<int> temp;

int n, m;

bool comp( const pair<int,int>& a, const pair<int,int>& b ){
	return a.second < b.second;
}

int main(){
	scanf( "%d %d", &n, &m );
	int cont = 0, a, b;
	temp.insert( 0 );
		
	for( int i = 0; i < m; ++i ){
		scanf( "%d %d", &a, &b );
		segs[i].first = a;
		segs[i].second = b;
		temp.insert( a );
		temp.insert( b );
	}

	for( set<int>::iterator it = temp.begin(); it != temp.end(); ++it ){
		mapa[ *it ] = cont++;
	}
	
	
	
	if( mapa.find( n ) == mapa.end() )
		printf( "0\n" );
	else{
		memset( stops, 0, sizeof( stops ) );
		stops[ 0 ] = 1;
		soma[ 0 ] = 0;
		sort( segs, segs + m, comp );
		int prt = 0;
	
		for( int i = 0; i < m; ++i ){
			segs[i].first = mapa[ segs[i].first ];
			segs[i].second = mapa[ segs[i].second ];
			for( ; prt <= segs[i].second; ++prt ){
				if( prt )
					soma[ prt ] = ( soma[ prt - 1 ] + stops[ prt - 1 ] ) % MOD;
			}
		
			ll aux = ( soma[ segs[i].second ] - soma[ segs[i].first ]  );
			while( aux < 0 ) aux += MOD;
			
			stops[ segs[i].second ] = ( stops[ segs[i].second ] + aux ) % MOD;
		}
		
		printf( "%lld\n", stops[ mapa[ n ] ] );
	
	}
}
