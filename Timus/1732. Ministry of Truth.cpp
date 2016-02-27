#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
typedef unsigned long long ull;
#define mp make_pair
#define BASE 997
char in[ 200000 ], out[ 200000 ];
bool marc[ 200000 ];
vector< pair<int,int> > matchs;

int main(){
	
	gets( in );
	gets( out );
	
	int prt = strlen( out ) - 1;
	int cont = strlen( in ) - 1;
	bool dm = false;
	
	while( prt >= 0 && cont >= 0 ){
		ull ha = 0, hb = 0, pot = 1;
		bool achou = false;
		
		int tam = 0;
		if( out[ prt ] == ' ' ){
//			printf( "Aqui %d |%c|\n", cont, in[ cont ] );
			if( in[ cont ] != ' ' ) in[ cont ] = '_';
			--prt;
			--cont;
			continue;
		}else{
			while( prt >= 0 && out[ prt ] != ' ' ){
				ha = ha * BASE + out[ prt ];
				--prt;
				++tam;
			}
		}
		
		if( cont >= tam - 1 ){
			for( int i = 0; i < tam && cont >= 0; ++i, --cont ){
				hb = hb * BASE + in[ cont ];

				if( i ) pot = pot * BASE;
			}
		
//			printf( "Debug: In %c Out %c (%d,%d)\n", in[ cont ], out[ prt ], cont, prt );
			
			while( !achou ){
				if( ha == hb ){
					achou = true;
//					printf( "Achei\n" );
				}else{
					if( cont < 0 ) break;
					
					hb -= in[ cont + tam ] * pot;
					hb = hb * BASE + in[ cont ];
					--cont;
				}
			}
//			printf( "\tAchou? %d\n", achou );
		}

		if( achou )
			matchs.push_back( mp( cont + 1, tam ) );
		else{
			dm = true;
			break;		
		}
	}
	
	if( dm )
		printf( "I HAVE FAILED!!!\n" );
	else{
		int last = strlen( in );
		for( int i = 0; i < last; ++i )
			marc[ i ] = false;
		
		for( int i = 0; i < matchs.size(); ++i ){
			int ind = matchs[ i ].first, tam = matchs[ i ].second;
			
			while( tam-- )
				marc[ ind++ ] = true;
		}
//		printf( ">>>>>>>>%d\n", marc[14] );
		for( int i = 0; i < last; ++i ){
			if( !marc[ i ] && in[ i ] != ' ' )
				in[ i ] = '_';
		}
		
		printf( "%s\n", in );
	}
	
	
}


