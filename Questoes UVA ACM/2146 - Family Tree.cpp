#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <iostream>
#include <cstdio>
using namespace std;
#define N 2000

int pai[ N ];

struct Tripla{
	int id;
	int ident;
	int pai;
	
	Tripla( int a, int b, int c ){
		id = a;
		ident = b;
		pai = c;
	}
	
	Tripla(){}
	
	void set( int a, int b, int c ){
		id = a;
		ident = b;
		pai = c;
	}
	
}pilha[ N ];

map<string,int> mapa;
int id, sp, n, m;
char nome[ N ], n2[ N ], op[ N ];

bool ancestral( int pa, int filho ){
	int temp = filho;
	
	while( temp != -1 ){
		if( temp == pa )
			return true;
		temp = pai[ temp ];
	}
	
	return false;
}

void buildTree(){
	int cont;
	
	for( int i = 1; i < n; ++i ){
		gets( nome );
		
		for( int j = strlen( nome ) - 1; j >= 0; --j ){
			if( (nome[ j ] >= 'a' && nome[ j ] <= 'z' ) || ( nome[ j ] >= 'A' && nome[ j ] <= 'Z' ) )
				break;
			nome[ j ] = '\0';
		}
		
		//printf( "Linha completa: |%s|\n", nome );
		cont = 0;
		
		while( nome[ cont ] == ' ' )
			++cont;
		
		mapa[ ( nome + cont ) ] = id;
		
		if( cont == pilha[ sp ].ident ){
			pai[ id ] = pilha[ sp ].pai;	
		}else if( cont > pilha[ sp ].ident ){
			pai[ id ] = pilha[ sp ].id;
		}else{
			do{
				--sp;
			}while( cont < pilha[ sp ].ident );
			pai[ id ] = pilha[ sp ].pai;
		}
		
	//	printf( "Nome: %s id %d ident %d pai %d\n", ( nome + cont ), id, cont, pai[ id ] );
		
		++sp;
		pilha[ sp ].set( id, cont, pai[ id ] );
		
		++id;
	}
}

int main(){
	
	while( scanf( "%d %d", &n, &m ) && ( n | m ) ){
		mapa.clear();
		scanf( "%s", nome );
		
		gets( n2 );//\n
		
		mapa[ nome ] = 0;
		pai[ 0 ] = -1;
		pilha[ 0 ].set( 0, 0, -1 );
		
		id = 1;
		sp = 0;
		buildTree();
		
		for( int i = 0; i < m; ++i ){
			scanf( "%s %*s %*s %s %*s %s", nome, op, n2 );
			for( int j = 0;; ++j ){
				if( n2[ j ] == '.' ){
					n2[ j ] = '\0';
					break;
				}
			}
			
				
			int c1 = mapa[ nome ], c2 = mapa[ n2 ];
			bool resp;
			switch( op[ 0 ] ){
				case 'c':// n1 eh filho de n2
					resp = ( pai[ c1 ] == c2 );
					break;
				case 'p'://n1 eh pai de n2
					resp = ( c1 == pai[ c2 ] );
					break;
				case 's'://irmaos
					resp = ( pai[ c1 ] == pai[ c2 ] );
					break;
				case 'd': //n1 eh descendente de n2
					resp = ancestral( c2, c1 );
					break;
				case 'a':
					resp = ancestral( c1, c2 );
					break;
				default:
					while( true );
					break;
			}
			
			if( resp )
				printf( "True\n" );
			else
				printf( "False\n" );
		}
		printf( "\n" );
	}
}


