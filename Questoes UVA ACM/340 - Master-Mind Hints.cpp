#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int codigo[ 2000 ], seq[ 2000 ];
int f1[ 2000 ], f2[ 2000 ], strong, weak, cont;

vector<int> cod[ 10 ], guess[ 10 ];

int main(){
	set<int> ini, fim;
	int game = 1;
	
	while( scanf( "%d", &cont ) && cont ){
		for( int i = 0; i < 10; ++i )
			cod[ i ].clear();
			
		for( int i = 0; i < cont; ++i ){
			scanf( "%d", codigo + i );
			cod[ codigo[i] ].push_back( i + 1 );
		}
		
		int acc;
		printf( "Game %d:\n", game++ );
		
		while( true ){
			acc = 0;
			for( int i = 0; i < 10; ++i )
				guess[ i ].clear();
				
			for( int i = 0; i < cont; ++i ){
				scanf( "%d", seq + i );
				guess[ seq[i] ].push_back( i + 1 );
				acc |= seq[ i ];
			}
			
			if( !acc ) break;
			
			ini.clear();
			fim.clear();
					
			strong = weak = 0;
			for( int i = 0; i < cont; ++i ){
				if( seq[ i ] == codigo[ i ] ){
					ini.insert( i + 1 );
					fim.insert( i + 1 );
					++strong;
				}
			}
			
			for( int i = 0; i < cont; ++i ){
				if( ini.find( i + 1 ) == ini.end() ){
					for( int j = guess[ codigo[i] ].size() - 1; j >= 0; --j ){
						int ind = guess[ codigo[i] ][ j ];
						if( fim.find( ind ) == fim.end() ){
							fim.insert( ind );
							guess[ codigo[i] ].pop_back();
							++weak;
							break;
						}else
							guess[ codigo[i] ].pop_back();
							
					}
				}
			}
			
			//printf( " (%d,%d)\n",strong,weak);
			printf( "    (%d,%d)\n", strong, weak );
		}
			


	}
}
