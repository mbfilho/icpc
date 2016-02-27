#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char palavra[ 20 ];

int main(){
	int cont;

	scanf( "%d", &cont );

	while( cont-- ){
		scanf( "%s", palavra );
		int tam = strlen( palavra );
		sort( palavra, palavra + tam );
		
		do{
			printf( "%s\n", palavra );
		}while( next_permutation( palavra, palavra + tam ) );
		
		printf( "\n" );
	}
}
