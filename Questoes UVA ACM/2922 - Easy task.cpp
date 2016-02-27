#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
using namespace std;


int tempo[ 65 ][ 30 ];
int sub[ 65 ][ 30 ];
int acc[ 30 ];
map<string, int> mapa;

int cont;

int main(){
	int casos;
	int s;
	
	int t;
	char time[ 5000 ];
	char ques, jud;
	
	scanf( "%d", &casos );
	
	int ind;
	map<string, int>::iterator it;
	while( casos-- ){
		scanf( "%d", &s );
		cont = 0;
		mapa.clear();
		
		for( int i = 0; i < 65; ++i ){
			for( int j = 0; j < 30; ++j ){
				tempo[ i ][ j ] = -1;
				sub[ i ][ j ] = acc[ j ] = 0;
			}
		}
		
		while( s-- ){
			scanf( "%d %s %c %c", &t, time, &ques, &jud );
			
			if( ( it = mapa.find( string( time ) ) ) == mapa.end() ){
				ind = cont;
				mapa[ string( time ) ] = cont++;
			}else
				ind = it -> second;
			
			if( tempo[ ind ][ ques - 'A' ] == -1 ){
				++sub[ ind ][ ques - 'A' ];
				if( jud == 'A' ){
					tempo[ ind ][ ques - 'A' ] = t;
					++acc[ ques - 'A' ];
				}
			}
		}
		
		int soma, c;
		double avgS, avgT;
		for( int i = int( 'A' ); i <= int( 'I' ); ++i ){
			if( acc[ i - 'A' ] != 0 ){
				soma = 0;
				c = 0;
			
				for( int j = 0; j < cont; ++j ){
					if( tempo[ j ][ i - 'A' ] != -1 && sub[ j ][ i - 'A' ] != 0 ){
						soma += sub[ j ][ i - 'A' ];
						++c;
					}
				}
			
				avgS = double( soma ) / c;
				soma = c = 0;
				for( int j = 0; j < cont; ++j ){
					if( tempo[ j ][ i - 'A' ] != -1 ){
						soma += tempo[ j ][ i - 'A' ];
						++c;
					} 
				}
			
				avgT = double( soma ) / c;
		
				printf( "%c %d %.2lf %.2lf\n", char( i ), acc[ i - 'A' ], avgS, avgT );
			}else
				printf( "%c 0\n", char( i ) );
		}
		
		if( casos )
			printf( "\n" );
	}
}


