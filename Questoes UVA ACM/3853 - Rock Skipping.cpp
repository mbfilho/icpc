#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 300
char lago[ N ], n;

int getCount( int ini, int d, int* ult ){
	int cont = 0;
	*ult = ini;
	
	for( int i = ini; i < n; i += d ){
		*ult = i;
		if( lago[ i ] != '.' )
			break;
		
		++cont;
	}
	
	return cont;
}

int main(){
	
	while( gets( lago ) && lago[ 0 ] != 'E' ){
		n = strlen( lago );
		int maior = -1, inicio, dist, ultimo;
	
		for( int ini = 0; ini < n; ++ini ){
			for( int d = 1; d <= n; ++d ){
				int ult;
				int cont = getCount( ini, d, &ult );
			
				if( cont > maior ){
					maior = cont;
					inicio = ini;
					dist = d;
					ultimo = ult;
				}else if( cont == maior ){
					if( ult > ultimo ){
						inicio = ini;
						dist = d;
						ultimo = ult;
					}else if( ult == ultimo ){
						if( ini > inicio ){
							inicio = ini;
							dist = d;
						}else if( ini == inicio ){
							if( d < dist )
								d = dist;
						}
					}
				}
			}
		}
		printf( "%d %d\n", inicio, dist );
	}
	
	
}

