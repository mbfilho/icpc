#include <cstdio>
#include <cmath>
typedef long long ll;


char temp[ 90 ];
int main(){
	int casos;
	scanf( "%d", &casos );
	for( int caso = 1; caso <= casos; ++caso ){
		long long soma = 0;
		
		for( int i = 0; i < 12; ++i ){
			scanf( "%s", temp );
			long long aux = 0;
			for( int i = 0; temp[ i ]; ++i ){
				if( temp[ i ] == '.' ) continue;
				aux = aux * 10 + temp[ i ] - '0';
			}
			soma += aux;
		}
		long long media = ll( round( soma / 12.0 ) );
		int cents = media % 100;
		media /= 100;
		
		printf( "%d $", caso );
		if( media >= 1000000 )
			printf( "%lld,%03lld,%03lld.%02d\n", media / 1000000, ( media / 1000 ) % 1000, media % 1000, cents );
		else if( media >= 1000 )
			printf( "%lld,%03lld.%02d\n", media / 1000, media % 1000, cents );
		else
			printf( "%lld.%02d\n", media, cents ); 
		
	}
}

