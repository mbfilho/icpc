#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
#define P 10
const int mod = 1000000007;
ll n, r, k;

ll A[ P ], S[ P ], fim[ P ], fim2[ P ];
ll inicial[ P ][ P ], pulo[ P ][ P ], extendida[ P ][ P ], kesima[ P ][ P ];

void print( ll a[ P ][ P ], int tam ){
	for( int i = 0; i < tam; ++i ){
		for( int j = 0; j < tam; ++j )
			cout << a[ i ][ j ] << " ";
		cout << endl;
	}
	
	cout << endl;	
}

void mult( ll a[ P ][ P ], ll b[ P ][ P ], ll res[ P ][ P ], int tam ){
	ll aux[ P ][ P ];
	for( int i = 0; i < tam; ++i ){
		for( int j = 0; j < tam; ++j ){
			aux[ i ][ j ] = 0;
			
			for( int k = 0; k < tam; ++k )
				aux[ i ][ j ] = ( aux[ i ][ j ] + a[ i ][ k ] * b[ k ][ j ] ) % mod;
		}
	}
	
	for( int i = 0; i < tam; ++i ){
		for( int j = 0; j < tam; ++j )
			res[ i ][ j ] = aux[ i ][ j ];
	}
}

void expo( ll a[ P ][ P ], ll res[ P ][ P ], ll xp, int tam ){
	ll quad[ P ][ P ], answ[ P ][ P ];
	
	for( int i = 0; i < tam; ++i ){
		for( int j = 0; j < tam; ++j ){
			quad[ i ][ j ] = a[ i ][ j ];
			answ[ i ][ j ] = 0;
		}
		
		answ[ i ][ i ] = 1;
	}
	
	while( xp ){
		if( xp & 1 )
			mult( answ, quad, answ, tam );
		mult( quad, quad, quad, tam );
		xp = xp >> 1;
	}
	
	for( int i = 0; i < tam; ++i ){
		for( int j = 0; j < tam; ++j )
			res[ i ][ j ] = answ[ i ][ j ];
	}
}

void ler(){
	//cin >> n >> r >> k;
	scanf( "%lld %lld %lld", &n, &r, &k );
	
	for( int i = 0; i < r; ++i )
		scanf( "%lld", S + i );
		//cin >> S[ i ];
		
	for( int i = 0; i < r; ++i )
		scanf( "%lld", A + i );
		//cin >> A[ i ];
}

void montar(){
	for( int i = 0; i < r; ++i ){
		for( int j = 0; j < r; ++j )
			inicial[ i ][ j ] = 0;
	}
	
	for( int i = 0; i < r; ++i ){
		inicial[ i ][ 0 ] = A[ i ];
		inicial[ i ][ i + 1 ] = 1;
	}
}

int main(){
	int casos, ind, qtd;
	//cin >> casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		ler();
		montar();
		
		if( k == 1 ) 
			ind = r + 1;
		else
			ind = r + k - ( r % k );
		
		qtd = max( 0LL, n - ( r / k ) );
		
		if( qtd ){
			expo( inicial, pulo, ind - r, r );
						
			for( int i = 0; i < r; ++i )
				fim[ i ] = S[ r - i - 1 ];
			
			for( int i = 0; i < r; ++i ){
				fim2[ i ] = 0;
				for( int k = 0; k < r; ++k )
					fim2[ i ] = ( fim2[ i ] + ( fim[ k ] * pulo[ k ][ i ] ) ) % mod;
			}
			
			expo( inicial, kesima, k, r );
			fim[ 0 ] = fim2[ 0 ];
			for( int i = 1; i <= r; ++i )
				fim[ i ] = fim2[ i - 1 ];
			
			extendida[ 0 ][ 0 ] = 1;
			for( int i = 1; i <= r; ++i ){
				extendida[ i ][ 0 ] = kesima[ i - 1 ][ 0 ];
				extendida[ 0 ][ i ] = 0;
			}
			
			
			for( int i = 1; i <= r; ++i ){
				for( int j = 1; j <= r; ++j )
					extendida[ i ][ j ] = kesima[ i - 1 ][ j - 1 ];
			}
					
			ll soma = 0;
			--qtd;
			
			for( int i = k; i <= r; i += k )
				soma = ( soma + S[ i - 1 ] ) % mod;
						
			expo( extendida, extendida, qtd, r + 1 );
			
			for( int i = 0; i <= r; ++i )
				soma = ( soma + extendida[ i ][ 0 ] * fim[ i ] ) % mod;
			
			printf( "%lld\n", soma );
			
			//cout << soma << endl;
		}else{
			ll soma = 0;
			int cont = n;
			
			for( int i = k; i <= r; i += k ){
				if( cont == 0 )  break;
				soma = ( soma + S[ i - 1 ] ) % mod;
				--cont;
			}
			
			printf( "%lld\n", soma );
		//	cout << soma << endl;
		}
	}
}
