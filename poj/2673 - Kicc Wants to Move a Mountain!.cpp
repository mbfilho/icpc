#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//Poj

int t, x, m;

pair<int,int> bixos[ 11000 ];

int main(){
	scanf( "%d %d", &t, &x );
	scanf( "%d", &m );
	
	for( int i = 0; i < m; ++i )
		scanf( "%d %d", &bixos[ i ].first, &bixos[ i ].second );
	
	if( m == 0 ){
		printf( "%d\n", t * x );
		return 0;
	}
		
	int id = 0, menor = bixos[ 0 ].first / bixos[ 0 ].second;
	
	for( int i = 1; i < m; ++i ){
		if( ( bixos[ i ].first / bixos[ i ].second ) < menor ){
			id = i;
			menor = bixos[ i ].first / bixos[ i ].second;
		}
	}
	
	int soma;
	if( ( bixos[ id ].first % bixos[ id ].second ) == 0 )
		soma = menor - 1;
	else
		soma = menor;
	
	
	soma = min( soma, t );
	if( soma ){
		t -= soma;
		if( t > 0 )
			soma += t / 2;
	}
	
	soma *= x;
	printf( "%d\n", soma );
}

