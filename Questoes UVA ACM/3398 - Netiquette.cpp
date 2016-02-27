#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define maiuscula(x) (x >= 'A' && x <= 'Z')
#define digito(x) (x >= '0' && x <= '9')
#define minuscula(x) (x >= 'a' && x <= 'z')
#define letra(x) (maiuscula(x) || minuscula(x))
#define pontuacao(x) (x != ' ' && x != '\"' && !letra(x) && !digito(x) )
int tam;
char linha[ 10000 ];

bool isolated( int pos, int tam ){
	bool retorno = false;
	int cont = 0;
	
	if( pos == tam - 1 )
		++cont;
	else if( linha[ pos + 1 ] == ' ' )
		++cont;
		
	if( pos == 0 )
		++cont;
	else if( linha[ pos - 1 ] == ' ' )
		++cont;
	
	return cont == 2;		
}

int faz(){
	for( int i = 0; i < tam; ++i ){
		if( isolated( i, tam ) && linha[ i ] != 'a' && linha[ i ] != 'A' && linha[ i ] != 'I' )
			return 1;
			 
		if( maiuscula( linha[ i ] ) ){
			if( i && ( maiuscula( linha[ i - 1 ] ) || digito( linha[ i - 1 ] ) ) )
				return 2;
		}else if( minuscula( linha[ i ] ) ){
			if( i && digito( linha[ i - 1 ] ) )
				return 3;
		}else if( digito( linha[ i ] ) ){
			if( i && letra( linha[ i - 1 ] ) )
				{ return 4; }
		}else if( pontuacao( linha[ i ] ) ){
			if( i && pontuacao( linha[ i - 1 ] ) )
				{ return 5; }
		}
	}
	
	return false;
}

int main(){
	while( gets( linha ) && strcmp( linha, "#" ) ){
		if( (tam = strlen( linha ) ) == 0 ) 
			continue;
		if( !faz() )
			printf( "OK\n" );
		else
			printf( "suspicious\n" );
	}

}



