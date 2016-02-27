#include <cstdio>
#include <cstring>
#include <map> 
using namespace std;

map<int,int> mapa;

int menor, maior, prt;

void faz( int no, int ordem ){
	if( no == -1 ) return;
	
	if( ordem < menor )
		menor = ordem;
	if( ordem > maior )
		maior = ordem;
	
	int temp;
	scanf( "%d", &temp );
	faz( temp, ordem - 1 );

	scanf( "%d", &temp );
	faz( temp, ordem + 1 );
	mapa[ ordem ] += no;
}

int main(){
	int temp;
	int caso = 1;
	
	while( scanf( "%d", &temp ) != EOF && ( temp != -1 ) ){
		mapa.clear();
		faz( temp, 0 );
				
		printf( "Case %d:\n", caso++ );
		int tam = mapa.size();
		for( map<int,int>::iterator it = mapa.begin(); it != mapa.end(); ++it ){
			--tam;
			if( tam )
				printf( "%d ", it -> second );
			else
				printf( "%d", it -> second );
		}
		printf( "\n\n" );
		
	}
}

 
