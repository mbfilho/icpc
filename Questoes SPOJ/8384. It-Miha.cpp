#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
#define P 200000
typedef long long ll;

ll primos[ P / 2 ];
int contp;
bool crivo[ P ];

void encher(){
	contp = 0;
	memset( crivo, true, sizeof crivo );
	
	for( int i = 4; i < P; i += 2 )
		crivo[ i ] = false;
	
	for( int i = 3; i * i < P; i += 2 ){
		if( !crivo[ i ] ) continue;
		for( int j = i * i; j < P; j += 2 * i )
			crivo[ j ] = false;
	}
	
	contp = 1;
	primos[ 0 ] = 2;
	
	for( int i = 3; i < P; i += 2 ){
		if( crivo[ i ] ) primos[ contp++ ] = i;
	}
}

ll array[ P ];
bool mask[ P ];

ll back( ll num, ll temp, bool soma, int tam, int ind ){
	if( temp > num ) return 0;
	
	ll ret = num / temp;
	if( !soma ) ret = -ret;
	
	if( tam == ind ) return ret;
	while( ind < tam ){
		mask[ ind ] = true;
		ll aux = back( num, temp * array[ ind ], !soma, tam, ind + 1 );
		mask[ ind ] = false;
		
		if( !aux ) break;
		ret += aux;
		++ind;
	}
	
	return ret;
}


void faz(){
	for( int i = 0; i < contp; ++i ){
		array[ i ] = primos[ i ] * primos[ i ];

	}
}

int bs( ll num ){
	int ini = 0, fim = contp - 1, resul = -1, meio;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( num > array[ meio ] ){
			ini = meio + 1;
			resul = meio;
		}else if( num < array[ meio ] )
			fim = meio - 1;
		else{	
			resul = meio;
			break;
		}
	}
	
	return resul + 1;
}


ll ler(){
	ll num = 0;
	char ch = getchar_unlocked();
	
	
	while( ch < '0' || ch > '9' ){
		ch = getchar_unlocked();
	}
	
	while( ch >= '0' && ch <= '9' ){
		num = num * 10 + ch - '0';
		ch = getchar_unlocked();
	}
	
	return num;
}

int main(){
	encher();
	faz();
	memset( mask, false, sizeof mask );
	
	ll ordem;
	int casos;
	scanf( "%d", &casos );
	while( casos-- ){
//		scanf( "%lld", &ordem );
		ordem = ler(); 
		ll ini = 1, fim = 2 * ordem;
		ll resp = -1;
		
		while( ini <= fim ){
			ll num = ( ini + fim ) / 2;
			ll soma = 0;
			int prt = bs( num );
			for( int i = 0; i < prt; ++i ){
				mask[ i ] = true;
				soma += back( num, array[ i ], true, prt, i + 1 );
				mask[ i ] = false;
			}
			
			soma = num - soma;
			if( soma == ordem ){
				resp = num;
				fim = num - 1;
			}else if( soma > ordem )
				fim = num - 1;
			else
				ini = num + 1;
		}
		printf( "%lld\n", resp );
	}	
}



