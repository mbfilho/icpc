#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#define menor( a, b ) (a) < (b) ? (a) : (b)
using namespace std;
typedef long long ll;

int adj[ 301 ][ 301 ];


int main(){
	int cid, k;
	
	cin >> cid;
	
	for( int i = 1; i <= cid; ++i ){
		adj[ i ][ i ] = 0;
		for( int j = 1; j <= cid; ++j ){
			cin >> adj[ i ][ j ];
			adj[ j ][ i ] = adj[ i ][ j ];
		}
	}
	
	cin >> k;
	
	int origem, fim, custo;
	for( int i = 1; i <= k; ++i ){
		cin >> origem >> fim >> custo;
		
		if( adj[ origem ][ fim ] > custo ){
			adj[ origem ][ fim ] = custo;
			adj[ fim ][ origem ] = custo;
			
			for( int u = 1; u <= cid; ++u ){
				for( int v = 1; v <= cid; ++v ){
					adj[ u ][ v ] = menor( adj[ u ][ v ], adj[ u ][ fim ] + adj[ fim ][ v ] );
					adj[ u ][ v ] = menor( adj[ u ][ v ], adj[ u ][ origem ] + adj[ origem ][ v ] );
					adj[ v ][ u ] = adj[ u ][ v ];
				}
			}
		}
		
		ll soma = 0;
		for( int u = 1; u <= cid; ++u ){
			for( int v = u; v <= cid; ++v )
				soma += adj[ u ][ v ];
		}
		
		cout << soma;
		if( i != k )
			cout << " ";
		else
			cout << endl;
	}
	
}
