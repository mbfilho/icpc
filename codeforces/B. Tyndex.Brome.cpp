#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

#define maxi 400200
#define inf 1000000000
struct Caracter{
	char c;
	int id;
	
	bool operator<( const Caracter& car ) const{
		if( c != car.c )
			return c < car.c;
		return id < car.id;
	}
}word[ maxi ];

char s[ maxi ];
int ini[ 300 ], fim[ 300 ], size;

void config(){
	fill( ini, ini + 300, inf );
	fill( fim, fim + 300, -1 );
	
	sort( word, word + size );
	
	for( int i = 0; i < size; ++i ){
		ini[ word[ i ].c ] = min( ini[ word[ i ].c ], i );
		fim[ word[ i ].c ] = max( fim[ word[ i ].c ], i );
	}
	
}

int bs( int id ){
	int start = ini[ s[ id ] ], end = fim[ s[ id ] ], mean, ret = inf;
	if( start == inf )
		return inf;
		
	while( start <= end ){
		mean = ( start + end ) / 2;
		
		if( ret == inf || abs( word[ mean ].id - id ) < abs( word[ ret ].id - id ) )
			ret = mean;
			
		if( id == word[ mean ].id ){
		//	printf( "entrei alguma vez %d\n", id );
			return id;
		}else if( word[ mean ].id > id ){
			end = mean - 1;
		}else
			start = mean + 1; 
	}
	
	return word[ ret ].id;
}

void ig(){
	while( cin.peek() == '\n' ) cin.ignore();
}

int main(){
	int qtd;
	
	scanf( "%d %d", &qtd, &size );
	ig();
	
	for( int i = 0; i < size; ++i ){
		scanf( "%c", &word[ i ].c );
		word[ i ].id = i;
	}
	
	config();
	
	while( qtd-- ){
		scanf( "%s", s );
//		printf( "Lida %s\n", s );
		int tam = strlen( s ), id;
		ll custo = 0;
		
		for( int i = 0; i < tam; ++i ){
			id = bs( i );
			
		//	printf( "Retorno %c %d\n", s[ i ], id );
			if( id == inf ) 
				custo += tam;
			else
				custo += abs( id - i );			
		}
		
		printf( "%I64d\n", custo );
	}
	
}


