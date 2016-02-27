#include <cstdio>

int indice, mod;
int fibo[900000], modulos[20];

int preencher(){
	int ant1 = 0, ant2 = 1, tam = 2;
	int atual = ant1 + ant2;
	
	while( ant2 != 1 || atual != 0 ){
		fibo[tam++] = atual;
		
		if( tam > indice )
			return fibo[ indice ];
			
		ant1 = ant2;
		ant2 = atual;
		atual = (ant1 + ant2) & modulos[mod];
	}
	
	return fibo[ indice % tam ];	
}

int main(){
	fibo[0] = 0;
	fibo[1] = 1;
	for( int i = 0; i < 20; ++i )
		modulos[i] = (1 << i) - 1;
	
	while( scanf( "%d %d", &indice, &mod ) != EOF ){
		if( mod == 0 )
			printf( "0\n" );
		else
			printf( "%d\n", preencher() );		
	}
}
