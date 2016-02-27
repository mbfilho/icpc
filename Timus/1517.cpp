#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define N 100100
#define BASE 997
typedef unsigned long long ull;
ull rev;

char t[ N ], p[ N ];
int tam;
ull conj[ N ];

int main(){
	scanf( "%d %s %s", &tam, t, p );
//	printf( "tam %d |%s|%s|\n", tam, t, p );
	
	int ini = 1, fim = tam;
	int best = -1, index;
	
	while( ini <= fim ){
		int meio = ( ini + fim ) / 2;
		int prt = 0;
		
		ull pot = 1, ha = 0;
		
		for( int i = 0; i < meio; ++i ){
			if( i ) pot *= BASE;
			ha = ha * BASE + t[ i ];
		}
		
		conj[ prt++ ] = ha;
		for( int i = 1; i + meio <= tam; ++i ){
			ha = ( ha - t[ i - 1 ] * pot ) * BASE + t[ i + meio - 1 ];
			conj[ prt++ ] = ha;
		}
		
		sort( conj, conj + prt );
		
		ha = 0;
		for( int i = 0; i < meio; ++i ){
			ha = ha * BASE + p[ i ];
		}
		
		bool achou = false;

		if( binary_search( conj, conj + prt, ha ) ){
			best = meio;
			ini = meio + 1;
			index = 0;
			achou = true;
		}
		
		for( int i = 1; !achou && i + meio <= tam; ++i ){
			ha = ( ha - p[ i - 1 ] * pot ) * BASE + p[ i + meio - 1 ];
			if( binary_search( conj, conj + prt, ha ) ){
				best = meio;
				ini = meio + 1;
				index = i;
				achou = true;
			}
		}
		
		if( achou ){
			continue;
		}
		
		fim = meio - 1;
	}
	
	p[ index + best ] = 0;
	printf( "%s\n", p + index );
}







