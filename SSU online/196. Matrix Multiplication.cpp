#include <cstdio>
#include <iostream>
using namespace std;
//SSU

int main(){
	int n, m, qtd[ 100101 ];
	for( int i = 1; i <= 100000; ++i )
		qtd[ i ] = 0;
		
	
	scanf( "%d %d", &n, &m );
	long long soma = 2 * m;
	
	int a, b;
	while( m-- ){
		scanf( "%d %d", &a, &b );
		++qtd[ a ];
		++qtd[ b ];
	}
	
	for( int i = 1; i <= n; ++i )
		soma += ( qtd[ i ] * ( qtd[ i ] - 1 ) );
	cout << soma << endl;
}
