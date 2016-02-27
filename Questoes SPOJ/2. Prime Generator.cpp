#include <cstdio>
#include <cmath>
#include <cstring>

const int RAIZ = 31625;//Raiz de 10^9
bool crivo[RAIZ], aux[100005];
int maior, menor;
//set<int> excluidos;

void preencher(){
	memset( crivo, true, sizeof( crivo ) );
		
	crivo[1] = crivo[0] = false;
	for( int i = 4; i < RAIZ; i += 2 )
		crivo[i] = false;
		
	for( int i = 3; i * i < RAIZ; i += 2 ){
		if( crivo[i] == false ) 
			continue;
		for( int j = i * i; j < RAIZ; j += 2 * i )
			crivo[j] = false;
	}

}

void responder(){
	int j, raiz = int( sqrt( maior ) ) + 1;
	memset( aux, true, (maior - menor + 1) * sizeof(bool) );
	
	for( int i = 2; i <= raiz; ++i ){
		if( crivo[i] == false )
			continue;
		if( i >= menor )
			j = 2 * i;
		else
			j = menor + ( (i - menor % i) % i );
			
		for(; j <= maior; j += i )
			aux[j - menor] = false;
	}
	
	for( int i = menor; i <= maior; ++i ){
		if( aux[i - menor] )
			printf( "%d\n", i );
	}
	
	printf( "\n" );
}

int main(){
	preencher();
	//printf( "ola: %d\n", crivo[2] );
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &menor, &maior );
		if( menor < 2 )
			menor = 2;
		if( menor >= 1 && maior <= RAIZ ){
			for( int i = menor; i <= maior; ++i ){
				if( crivo[i] )
					printf( "%d\n", i );
			}
			printf( "\n" );
		}else
			responder();
	}
}