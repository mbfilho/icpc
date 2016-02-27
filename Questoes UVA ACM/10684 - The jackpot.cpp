#include <cstdio>

int main(){
	int sets;
	long temp, maxima, parcial;
	
	scanf( "%d", &sets );
	
	while( sets ){		
			
		parcial = 0;
		maxima = 0;
		
		while( sets ){
			scanf( "%ld", &temp );
			
			if( parcial + temp > temp )
				parcial += temp;
			else
				parcial = temp;
			
			if( parcial > maxima )
				maxima = parcial;
			--sets;
		}
		
		if( maxima == 0 )
			printf( "Losing streak.\n" );
		else
			printf( "The maximum winning streak is %ld.\n", maxima );	
			
		scanf( "%d", &sets );			
		
	}
	
}
