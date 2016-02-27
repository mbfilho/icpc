#include <iostream>
#include <map>
#include <bitset>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
map<vector<int>,long long> memo;
map<vector<int>,long long>::iterator it;
int primos[ 1 << 16 ];
int contp;
int vetor[ 9 ];

bool comp( int a, int b ){
	return a > b;
}

void imprimir( vector<int> n ){
	for( int i = 0; i < n.size(); ++i )
		printf( "%d ", n[ i ] );
	printf( "\n" );
}

void preprocesso(){
	for( int i = 0; i < 9; ++i )
		vetor[ i ] = 0;

	bitset< (1<<16) > aux;
	contp = 0;
	for( int i = 2; i < ( 1 << 16 ); ++i ){
		if( aux[ i ] == 1 )
			continue;
		for( int j = 2 * i; j < ( 1 << 16 ); j += i )
			aux[ j ] = 1;
	}
	
	for( int i = 2; i < ( 1 << 16 ); ++i ){
		if( aux[ i ] == 0 )
			primos[ contp++ ] = i;
	}
	
}

vector<int> fatorar( unsigned int n ){
	vector<int> retorno( vetor, vetor + 9 );
		
	int c = 0;
	int raiz = (int) sqrt( n );
	++raiz;
	for( int i = 0; primos[ i ] <= raiz; ++i ){
		if( n % primos[ i ] == 0 ){
			do{
				++retorno[ c ];
				n = n / primos[ i ];
			}while( n % primos[ i ] == 0 );
			++c;
		}
	}
	
	if( n != 1 )
		retorno[ c ] = 1;
	
	return retorno;
}



void soma( vector<int> &n, vector<int>& original, int tam ){
	int carry = 0;
	++n[ 0 ];
	if( n[ 0 ] == original[ 0 ] + 1 ){
		carry = 1;
		n[ 0 ] = 0;
	}
	
	for( int i = 1; i < tam && carry; ++i ){
		n[ i ] += carry;
		if( n[ i ] == original[ i ] + 1 )
			n[ i ] = 0;
		else
			carry = 0;
	}
}

long long calcular( vector<int>& n ){
	long long retorno = 0;
	int formas = 1, tam = 0;

	while( n[ tam ] )
		++tam;
	
	for( int i = 0; i < tam; ++i )
		formas *= ( n[ i ] + 1 );
	
	vector<int> atual( vetor, vetor + 9 );
	vector<int> auxiliar;
	
	--formas;
	for( int i = 0; i < formas; ++i ){
		auxiliar = atual;
		sort( auxiliar.begin(), auxiliar.begin() + tam, comp );
		if( (it = memo.find( auxiliar ) ) != memo.end() ){
			retorno += it -> second;
		}else{
			long long t = calcular( auxiliar );
			retorno += t;
			memo[ auxiliar ] = t;
		}
		
		soma( atual, n, tam );
	}
	
	return retorno;
	
} 

int main(){	
	vector<int> base( vetor, vetor + 9 );
	memo[ base ] = 1;
	base[ 0 ] = 1;
	memo[ base ] = 1;

	preprocesso();
		
	int casos;
	unsigned int num;


	scanf( "%d", &casos );
	for( int c = 1; c <= casos; ++c ){
		scanf( "%u", &num );
		base = fatorar( num + 1 );
		cout << "Case " << c << ": " << calcular( base ) << endl;
	}
	
}
