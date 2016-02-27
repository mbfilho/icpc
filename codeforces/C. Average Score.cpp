#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include <list>
#include <iostream>
using namespace std;
#define mp(x,y) make_pair(x,y)
typedef long long ll;

struct No{
	int nota, ind;
	
	bool operator<( const No& n ) const{
		if( nota != n.nota )
			return nota < nota;
		else
			return ind < n.ind;
	}
};

bool compa( const No& a, const No& b ){
	if( a.nota != b.nota )
		return a.nota > b.nota;
	else
		return a.ind < b.ind;
}

bool compb( const No& a, const No& b ){
	if( a.nota != b.nota )
		return a.nota > b.nota;
	else
		return a.ind > b.ind;
}

int main(){
	int a, b, n, fim[ 100100 ];
	No num[ 100100 ];
	scanf( "%d %d %d", &n, &a, &b );
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d", &num[ i ].nota );
		num[ i ].ind = i;
	}
	

	if( a < b ){
		sort( num, num + n, compa );
		for( int i = 0; i < a; ++i )
			fim[ num[i].ind ] = 1;
		for( int i = a; i < n; ++i )
			fim[ num[i].ind ] = 2;	
	}else if( a > b ){
		sort( num, num + n, compb );
		for( int i = 0; i < b; ++i )
			fim[ num[i].ind ] = 2;
		for( int i = b; i < n; ++i )
			fim[ num[i].ind ] = 1;	
	}else{
		for( int i = 0; i < a; ++i )
			fim[ i ] = 1;
		for( int i = b; i < n; ++i )
			fim[ i ] = 2;	
	}
	for( int i = 0; i < n; ++i ){
		printf( "%d%c", fim[ i ], ( i == n - 1 ) ? '\n' : ' ' );
	}
	
	
	
	
}

