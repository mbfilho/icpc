#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

char num[ 80 ];
ll qtd[ 20 ];
ll qtdA[ 20 ];

int busca( int ind ){
	for( int i = 1; i < 19; ++i ){
		if( ind > qtdA[ i ] && ind <= qtdA[ i + 1 ] )
			return i + 1;
	}
}

void rec( int ini, int fim, int ind, int tam ){
	--ind;
	if( tam < 3 ){
		num[ ini ] = num[ fim ] = ind + '0';
		return;
	}
	
	int grupo = ind / qtd[ tam - 2 ];
	num[ ini ] = num[ fim ] = grupo + '0';
	ind = 1 + ( ind % qtd[ tam - 2 ] );
	
	rec( ini + 1, fim - 1, ind, tam - 2 );	
}

int main(){
	qtd[ 1 ] = qtd[ 2 ] = 10;
	qtdA[ 1 ] = 9;
	qtdA[ 2 ] = 18;
	
	for( int i = 3; i < 20; ++i ){
		qtd[ i ] = 10 * qtd[ i - 2 ];
		qtdA[ i ] = qtdA[ i - 1 ] + 9 * qtd[ i - 2 ];
	}
	
		
	int ind;
	while( cin >> ind && ind ){
		if( ind <= 18 ){
			if( ind <= 9 )
				cout << ind << endl;
			else{
				ind -= 9;
				cout << ind << ind << endl;
			}
			continue;
		}
		
		int tam = busca( ind );
		ind = ind - qtdA[ tam - 1 ];
		int grupo = 1 + ( ind - 1 ) / qtd[ tam - 2 ];
		
		num[ 0 ] = num[ tam - 1 ] = grupo + '0';
		int a;
		rec( 1, tam - 2, a = ind - ( grupo - 1 ) * qtd[ tam - 2 ], tam - 2 );
		num[ tam ] = '\0';
		cout << num << endl;
	}
	
}
