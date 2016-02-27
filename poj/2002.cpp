#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define VAL 40100
#define BAS 20000
//poj

pair<int,int> pts[ 10100 ];
int n;

pair<int,int> operator-( const pair<int,int>& a ){
	return make_pair( -a.first, -a.second );
}

pair<int,int> operator-( const pair<int,int>& a, const pair<int,int>& b ){
	return make_pair( a.first - b.first, a.second - b.second );
}

pair<int,int> operator+( const pair<int,int>& a, const pair<int,int>& b ){
	return make_pair( a.first + b.first, a.second + b.second );
}

int operator*( const pair<int,int>& a, const pair<int,int>& b ){
	return a.first * b.second - a.second* b.first;
}



int main(){
	
	while( scanf( "%d", &n ) != EOF && n ){
		for( int i = 0; i < n; ++i ){
			int x, y;
			scanf( "%d %d", &x, &y );
			pts[ i ].first = x;
			pts[ i ].second = y;
		}
		int cont = 0;
		sort( pts, pts + n );
				
		for( int i = 0; i < n; ++i ){
			for( int j = i + 1; j < n; ++j ){
				pair<int,int> vet = pts[ j ] - pts[ i ], ort = make_pair( -vet.second, vet.first ); 
				
				if( ort * vet < 0 ) ort = -ort; 
				pair<int,int> pt1 = pts[ i ] + ort, pt2 = pts[ j ] + ort;
//				printf( "(%d,%d) (%d,%d) (%d,%d) (%d,%d)\n", pts[i].first, pts[i].second, pts[j].first, pts[j].second, pt1.first, pt1.second, pt2.first, pt2.second );

				if( binary_search( pts, pts + n, pt1 ) && binary_search( pts, pts + n, pt2 )  )
					++cont;
			}
		}
		printf( "%d\n", cont / 2 );		
		
	}
}

