#include <iostream>
using namespace std;

typedef long long ll;
const ll INF = 0x7FFFFFFFFFFFFFFFLL;

ll bolsa[ 2010 ][ 2010 ];
int c[ 2010 ], t[ 2010 ];

int qtd;

ll menor( ll a, ll b ){
	if( a < b )
		return a;
	return b;
}

ll maior( ll a, ll b ){
	if( a > b )
		return a;
	return b;
}

ll knapsack(){
	for( int i = 0; i <= qtd; ++i ){
		bolsa[0][i] = INF;
	}
	for( int i = 0; i <= qtd; ++i ){
		bolsa[i][0] = 0;
	}
	
	for( int i = 1; i <= qtd; ++i ){
		for( int j = 1; j <= qtd; ++j ){
			int ind = maior( j - 1 - t[i], 0 );
			if( bolsa[i-1][ind] == INF )
				bolsa[i][j] = bolsa[i-1][j];
			else
				bolsa[ i ][ j ] = menor( bolsa[ i - 1 ][ ind ] + c[i], bolsa[i-1][j] );
		}
	}
	
	
	return bolsa[ qtd ][ qtd ];
}

int main(){
	cin >> qtd;
	
	for( int i = 1; i <= qtd; ++i ){
		cin >> t[i] >> c[i];
	}
		
	knapsack();
	cout << bolsa[ qtd ][ qtd ] << endl;
}
