#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define S 42

int n, s, k;
int valores[ S ];

struct Tripla{
	int maior, menor, val;
}snd[ 1 << ( S / 2 ) ];
int prt2;

int fst[ 1 << ( S / 2 ) ], prt;

void faz_fst( int soma, int ind ){
	if( soma < 0 || soma > n ) return;
	
	if( ind == k / 2 ){
		fst[ prt++ ] = soma;
	}else{
		faz_fst( soma + valores[ ind ], ind + 1 );
		faz_fst( soma - valores[ ind ], ind + 1 );
	}
}

void faz_snd( int soma, int maior, int menor, int ind ){
	if( soma > n ) return;
	maior = max( maior, soma );
	menor = min( menor, soma );
	
	if( ind == k ){
		snd[ prt2 ].maior = maior;
		snd[ prt2 ].menor = menor;
		snd[ prt2 ].val = soma;
		++prt2;
	}else{
		faz_snd( soma + valores[ ind ], maior, menor, ind + 1 );
		faz_snd( soma - valores[ ind ], maior, menor, ind + 1 );
	}
}

int faz_maior(){
	int ret = -1;
	
	for( int i = 0; i < prt2; ++i ){
		int ini = 0, fim = prt - 1, meio;
		while( ini <= fim ){
			meio = ( ini + fim ) / 2;
			int peq = fst[ meio ] + snd[ i ].menor, grd = fst[ meio ] + snd[ i ].maior;
			if( peq < 0 )
				ini = meio + 1;
			else if( grd > n )
				fim = meio - 1;
			else{
				ret = max( ret, fst[ meio ] + snd[ i ].val );
				ini = meio + 1;
			}
		}
	}
	return ret;
}

int faz_menor(){
	int ret = 0x7fffffff;
	
	for( int i = 0; i < prt2; ++i ){
		int ini = 0, fim = prt - 1, meio;
		while( ini <= fim ){
			meio = ( ini + fim ) / 2;
			int peq = fst[ meio ] + snd[ i ].menor, grd = fst[ meio ] + snd[ i ].maior;
			if( peq < 0 )
				ini = meio + 1;
			else if( grd > n )
				fim = meio - 1;
			else{
				ret = min( ret, fst[ meio ] + snd[ i ].val );
				fim = meio - 1;
			}
		}
	}
	return ret;
}

int main(){
	scanf( "%d %d %d", &n, &s, &k );
	prt = prt2 = 0;
	for( int i = 0; i < k; ++i )
		scanf( "%d", valores + i );
		
	if( k == 1 ){
		int maior = s + valores[ 0 ], menor = s - valores[ 0 ];
		if( maior > n ) maior = s - valores[ 0 ];
		if( menor < 0 ) menor = s + valores[ 0 ];
		printf( "%d %d\n", menor, maior );
	}else{
		faz_fst( s, 0 );
		faz_snd( 0, 0x80000000, 0x7fffffff, k / 2 );
		sort( fst, fst + prt );	
		printf( "%d %d\n", faz_menor(), faz_maior() );
	}
}

