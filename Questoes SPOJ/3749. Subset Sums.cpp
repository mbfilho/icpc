#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
ll a, b;
int n;

ll num[ 50 ];
ll s1[ 1 << 19 ], s2[ 1 << 19 ];

int first( ll* ar, int tam, ll val ){
	int ini = 0, fim = tam - 1, meio, best = -1;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ar[ meio ] >= val ){
			fim = meio - 1;
			best = meio;
		}else
			ini = meio + 1;
	}
	
	return best;
}

int last( ll* ar, int tam, ll val ){
	int ini = 0, fim = tam - 1, meio, best = -2;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		
		if( ar[ meio ] <= val ){
			ini = meio + 1;
			best = meio;
		}else
			fim = meio - 1;
	}
	
	return best;
}

int main(){
	
	while( scanf( "%d %lld %lld", &n, &a, &b ) != EOF ){
		for( int i = 0; i < n; ++i )
			scanf( "%lld", num + i );
		
		int t1 = n / 2, t2 = ( n + 1 ) / 2;
		for( int i = 0; i < ( 1 << t1 ); ++i ){
			ll soma = 0;
			
			for( int j = 0; j < t1; ++j ){
				if( i & ( 1 << j ) )
					soma += num[ j ];
			}
			s1[ i ] = soma;
		}
		
		for( int i = 0; i < ( 1 << t2 ); ++i ){
			ll soma = 0;
			
			for( int j = 0; j < t2; ++j ){
				if( i & ( 1 << j ) )
					soma += num[ j + t1 ];
			}
			
			s2[ i ] = soma;
		}
		
		ll resp = 0;
		sort( s2, s2 + ( 1 << t2 ) );

		for( int i = 0; i < ( 1 << t1 ); ++i ){
			int ini = first( s2, ( 1 << t2 ), a - s1[ i ] ), fim = last( s2, ( 1 << t2 ), b - s1[ i ] );
			if( ini == -1 || s1[ i ] + s2[ ini ] > b ) continue;
			if( fim == -1 || s1[ i ] + s2[ fim ] < a ) continue;
			resp += fim - ini + 1;	
		}
		printf( "%lld\n", resp );
				
	}
}

