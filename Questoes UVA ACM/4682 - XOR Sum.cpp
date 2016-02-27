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

#define maxi 100000

struct No{
	int adj[ 2 ];
}trie[ 32 * maxi ];
int nos;

void insert( int num ){
	int ind = ( 1 << 30 ), no = 0;
	
	while( ind ){
		if( ( num & ind ) == 0 ){
			if( trie[ no ].adj[ 0 ] == -1 ){
				trie[ no ].adj[ 0 ] = nos;
				
				trie[ nos ].adj[ 0 ] = trie[ nos ].adj[ 1 ] = -1;
				++nos;
			}
				
			no = trie[ no ].adj[ 0 ];
		}else{
			if( trie[ no ].adj[ 1 ] == -1 ){
				trie[ no ].adj[ 1 ] = nos;
				
				trie[ nos ].adj[ 0 ] = trie[ nos ].adj[ 1 ] = -1;
				++nos;
			}
				
			no = trie[ no ].adj[ 1 ];
		}

		ind = ind >> 1;
	}
}

int findGreedly( int arg ){
	int no = 0, ind = ( 1 << 30 ), ret = 0;
	
	while( ind ){
		if( ( arg & ind ) == 0 ){
			//quero 1
			if( trie[ no ].adj[ 1 ] != -1 ){
				ret |= ind;
				no = trie[ no ].adj[ 1 ];
			}else
				no = trie[ no ].adj[ 0 ];
		}else{
			//quero 0
			if( trie[ no ].adj[ 0 ] == -1 ){
				no = trie[ no ].adj[ 1 ];
				ret |= ind;
			}else
				no = trie[ no ].adj[ 0 ];
			
		}
				
		ind = ind >> 1;
	}
	
	return ret;
}

int main(){
	int casos, cont, maior;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &cont );

		trie[ 0 ].adj[ 0 ] = trie[ 0 ].adj[ 1 ] = -1;
		nos = 1;
		insert( 0 );
			
		int temp;
		int acumulado = 0;
		maior = -1;
		
		for( int i = 1; i <= cont; ++i ){
			scanf( "%d", &temp );
			acumulado = acumulado xor temp;
			maior = max( acumulado, maior );
			
			temp = findGreedly( acumulado );
			
			maior = max( maior, temp xor acumulado );
			insert( acumulado );
		}
		
		printf( "%d\n", maior );
	}
}

