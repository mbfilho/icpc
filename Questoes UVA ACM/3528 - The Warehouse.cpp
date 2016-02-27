#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <list>
#include <iostream>
#include <map>
#include <set>
#include <cmath>
using namespace std;
typedef long long ll;
#define mp make_pair


set< vector< vector<int> > > marc;
queue< vector< vector< int > > > fila;
queue<int> f;
int n;
int incx[] = { -1, 0, 1, 0 };
int incy[] = {  0, 1, 0, -1 };

bool estou( int c ){
	return c & 2;
}

bool saida( int c ){
	return c & ( 1 << 5 );
}

int caixa( int c ){
	for( int i = 2; i <= 4; ++i )
		if( c & ( 1 << i ) ) return i;
	
	return 0;
}

bool ocupado( int c ){
	return c & 1;
}

int bfs( vector< vector<int> > ini ){
	while( fila.empty() == false ) fila.pop();
	while( f.empty() == false ) f.pop();
	marc.clear();
	fila.push( ini );
	f.push( 0 );

	while( !fila.empty() ){
		vector< vector<int> > atual = fila.front();
		int dist = f.front();
		vector< vector<int> > next = atual;
		fila.pop();
		f.pop();
		
		
		int a = -1, b;
		
		for( int i = 0; a == -1 && i < n; ++i ){
			for( int j = 0; j < n; ++j ){
				if( estou( atual[ i ][ j ] ) ){
					a = i;
					b = j;
					break;
				}
			}
		}
		
		if( saida( atual[ a ][ b ] ) ) return dist;
		int tam = caixa( atual[ a ][ b ] );
		if( tam ){
			for( int i = 0; i < 4; ++i ){
				int fi = a + tam * incx[ i ], fj = b + tam * incy[ i ];
				if( fi < 0 || fi >= n || fj < 0 || fj >= n ) continue;
				bool dm = false;
								
				for( int t = 1; t <= tam; ++t ){
					int x = a + incx[ i ] * t;  
					int y = b + incy[ i ] * t;
					
					if( x < 0 || x >= n || y < 0 || y >= n ) dm = true;
					if( ocupado( atual[ x ][ y ] ) ) dm = true;
				}
				
				if( !dm ){
					int cp[ 5 ];
					for( int t = 0; t <= tam; ++t )
						cp[ t ] = next[ a + t * incx[ i ] ][ b + t * incy[ i ] ];
					
					next[ a ][ b ] = 0;
					for( int t = 1; t <= tam; ++t )
						next[ a + incx[ i ] * t ][ b + incy[ i ] * t ] = 1;
					next[ a + incx[ i ] ][ b + incy[ i ] ] |= 2;
					
					if( marc.insert( next ).second ){
						fila.push( next );
						f.push( dist + 1 );
					}
					
					for( int t = 0; t <= tam; ++t )
						next[ a + t * incx[ i ] ][ b + t * incy[ i ] ] = cp[ t ];
				}
			}
		}
		
		for( int i = 0; i < 4; ++i ){
			int x = a + incx[ i ], y = b + incy[ i ];
			if( x < 0 || x >= n || y < 0 || y >= n ) continue;
			
			if( ocupado( next[ x ][ y ] ) ){
				int cp = next[ x ][ y ];
				next[ x ][ y ] |= 2;
				next[ a ][ b ] &= ~2;
				if( marc.insert( next ).second ){
					fila.push( next );
					f.push( dist + 1 );
				}
				next[ x ][ y ] = cp;
				next[ a ][ b ] |= 2;
			}
		}
	}
	
	return -1;	
}

char linha[ 50 ];
int main(){
	int a, b;
	
	while( scanf( "%d %d %d", &n, &a, &b ) != EOF && ( a | b | n ) ){
		vector< vector<int> > ini;
		for( int i = 0; i < n; ++i ){
			scanf( "%s", linha );
			vector<int> aux;
			ini.push_back( aux );
			for( int j = 0; j < n; ++j ){
				if( linha[ j ] == '.' ) ini[ i ].push_back( 0 );
				if( linha[ j ] == '2' ) ini[ i ].push_back( 5 );
				if( linha[ j ] == '3' ) ini[ i ].push_back( 9 );
				if( linha[ j ] == '4' ) ini[ i ].push_back( 17 );
				if( linha[ j ] == 'E' ) ini[ i ].push_back( 33 );  
			}
		}

		ini[ a - 1 ][ b - 1 ] |= 2;
		int dist = bfs( ini );
		if( dist != -1 )
			printf( "%d\n", dist );
		else
			printf( "Impossible.\n" );
		
	}
}

