#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	char palavra[ 51 ];
	int tam;
	
	while( scanf( "%s", palavra ) && palavra[ 0 ] != '#' ){
		tam = strlen( palavra );
		
		if( next_permutation( palavra, palavra + tam ) )
			printf( "%s\n", palavra );
		else
			printf( "No Successor\n" );
	}
}
