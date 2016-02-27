#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct No{
	No* adj[ 4 ];
	int cor;
	int size; 
	int x, y;
	
	No( int c, int s, int a, int b ){
		cor = c;
		size = s;
		x = a;
		y = b;
		
		for( int i = 0; i < 4; ++i )
			adj[ i ] = NULL;	
	}
};
struct Tripla{
	int ini, fim, lin;
	
	Tripla( int a, int b, int c ){
		ini = a;
		fim = b;
		lin = c;
	}
	
	bool operator<( const Tripla& t ) const{
		if( lin != t.lin )
			return lin < t.lin;
		return ini < t.ini;
	}
};

No* raiz;
char linha[ 100000 ];
int prt;

int incx[] = { 0, 1, 0, 1 };
int incy[] = { 0, 0, 1, 1 };

vector<Tripla> resp;

void faz( No* raiz ){
	if( ( raiz -> cor ) == 1 ){
		int size = ( raiz -> size );
		for( int j = raiz -> y; j < raiz -> y + size; ++j )
			resp.push_back( Tripla( raiz -> x, raiz -> x + size - 1, j ) );
	}else if( raiz -> cor == -1 ){
		for( int i = 0; i < 4; ++i )
			faz( raiz -> adj[ i ] );
	}
}

void montar( No* raiz ){
	int x = raiz -> x, y = raiz -> y, size = raiz -> size;
	for( int i = 0; i < 4; ++i ){
		int nx = x + incx[ i ] * size / 2, ny = y + incy[ i ] * size / 2;

		if( linha[ prt ] != '*' ){
			( raiz -> adj )[ i ] = new No( linha[ prt++ ] - '0', size / 2, nx, ny );
		}else{
			( raiz -> adj )[ i ] = new No( -1, size / 2, nx, ny );
			++prt;
			montar( ( raiz -> adj )[ i ] );
		}
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		int size;
		scanf( "%d %s", &size, linha );
		
		int cont = 0, aux = size;
		while( aux ){
			if( aux & 1 ) ++cont;
			aux  = aux >> 1;
		}
		
		if( cont != 1 ){
			printf( "Invalid length\n" );
			continue;
		}
		
		if( linha[ 0 ] != '*' )
			raiz = new No( linha[ 0 ] - '0', size, 1, 1 );
		else{
			prt = 1;
			raiz = new No( -1, size, 1, 1 );
			montar( raiz );
		}
		
		resp.clear();
		faz( raiz );
		sort( resp.begin(), resp.end() );
		int tam = resp.size();
		
		for( int i = 0; i < tam; ){
			int ini = resp[ i ].ini, fim = resp[ i ].fim, linha = resp[ i ].lin;
			++i;
			
			while( i < tam && linha == resp[ i ].lin && fim + 1 == resp[ i ].ini ){
				fim = resp[ i ].fim;
				++i;
			}
			
			if( fim != ini )
				printf( "(%d-%d,%d)%c", ini, fim, linha, ( i == tam ) ? '\n' : ',' );
			else 
				printf( "(%d,%d)%c", ini, linha, ( i == tam ) ? '\n' : ',' );
		}
	}
}

