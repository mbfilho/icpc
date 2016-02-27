#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

typedef long long ll;

ll total;
int cont;

struct Aresta{
	int no;
	ll peso;
	
	Aresta( int a, ll b ){
		no = a;
		peso = b;
	}
};

struct No{
	vector<Aresta> adj;
	ll dist;
}nos[ 100100 ];

void dfs( int no ){
	for( int i = nos[ no ].adj.size() - 1; i >= 0; --i ){
		Aresta temp = nos[ no ].adj[ i ];
		if( nos[ temp.no ].dist == -1 ){
			nos[ temp.no ].dist = nos[ no ].dist + temp.peso;
			dfs( temp.no );
		}
	}
}

void path(){
	ll maxi = -1;
	int ind;
	
	for( int i = 1; i <= cont; ++i ){
	//	printf( "No %d dist %I64d\n", i, nos[ i ].dist );
		if( nos[ i ].dist > maxi ){
			maxi = nos[ i ].dist;
			ind = i;
		}
	}
	
	//printf( "Ind %d\n", ind );
	
	
	total = 2 * ( total - nos[ ind ].dist ) + nos[ ind ].dist;
}

int main(){
	scanf( "%d", &cont );
	int a, b, p;
	total = 0;
	
	for( int i = 1; i <= cont; ++i ){
		nos[ i ].dist = -1;
		nos[ i ].adj.clear();
	}
	
	for( int i = 1; i < cont; ++i ){
		scanf( "%d %d %d", &a, &b, &p );
		nos[ a ].adj.push_back( Aresta( b, p ) );
		nos[ b ].adj.push_back( Aresta( a, p ) );
		total += p;
	}
	
	nos[ 1 ].dist = 0;
	dfs( 1 );
	path();
	
	printf( "%I64d\n", total );
}

