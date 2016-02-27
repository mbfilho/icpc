#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
char male[ 200 ][ 30 ];
int fem[ 200 ][ 200 ];
int cm[ 200 ];
int casado[ 200 ]; //Homem 
int par[ 200 ]; //Mulher
int caras[ 200 ];
char buf[ 200 ];

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d", &n );
		for( int i = 0; i < 2 * n; ++i ){
			scanf( "%s", buf );
			caras[ i ] = buf[ 0 ];
		}
		
		for( int i = 0; i < n; ++i ){
			scanf( "%s", buf );
			strcpy( male[ buf[0] ], buf + 2 );
//			printf( "|%c|%s|\n", buf[0], male[buf[0]] );
		}
		
		for( int i = 0; i < n; ++i ){
			char ch;
			scanf( "%s", buf );
			
			for( int j = 2; buf[ j ]; ++j ){
//				printf( "Mul %c -> %c\n", buf[0], buf[j] );
				fem[ buf[0] ][ buf[j] ] = j;
			}
		}
		
		memset( par, -1, sizeof( par ) );
		memset( casado, -1, sizeof( casado ) );
		memset( cm, 0, sizeof( cm ) );
		
		while( true ){
			int ca = -1;
			for( int i = 0; i < n; ++i ){
				if( casado[ caras[ i ] ] == -1 ){
					ca = caras[ i ];
					break;
				}
			}
			
			if( ca == -1 ) break;
			int mulher = male[ ca ][ cm[ca]++ ];
			if( par[ mulher ] == -1 ){
				par[ mulher ] = ca;
				casado[ ca ] = mulher;
			}else{
				if( fem[ mulher ][ ca ] < fem[ mulher ][ par[mulher] ] ){
					casado[ par[mulher] ] = -1;
					par[ mulher ] = ca;
					casado[ ca ] = mulher;
				}
			}
		}
		
		for( int i = 0; i < n; ++i ){
			printf( "%c %c\n", caras[ i ], char( casado[ caras[i] ] ) );
		}
		if( c != casos )
			printf( "\n" );
	}
}





