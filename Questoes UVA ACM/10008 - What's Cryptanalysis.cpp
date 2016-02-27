 #include <iostream>
 using std::cout;
 using std::cin;

#include <cstdlib>
#include <cstdio>

#define ascii 1
#define qtd 0
int main(){
	int letras[ 2 ][ 58 ];
	char buffer;
	int linhas;

	memset( letras[ qtd ], 0, 58 * sizeof( int ) );
	for( int i = 0; i < 58; ++i )
		letras[ ascii ][ i ] = i;
		
	cin >> linhas;

	while( cin.eof() == false ){
		cin.get( buffer );
		if( buffer >= 65 && buffer <= 122 ){
			if( buffer - 97 < 0 )
				++letras[ qtd ][ buffer - 65 ];
			else
				++letras[ qtd ][ buffer - 97 ];
		}
	}		

	
	//bubble sort!
	int temp[ 2 ];
	for( int i = 0; i < 58; ++i ){
		for( int j = i; j < 57; ++j ){
			if( letras[ qtd ][ j ] == 0 )
				continue;
				
			if( letras[ qtd ][ j ] < letras[ qtd ][ j + 1 ] || letras[ qtd ][ j + 1 ] == 0 ){
				temp[ qtd ] = letras[ qtd ][ j ];
				temp[ ascii ] = letras[ ascii ][ j ];
					
				letras[ qtd ][ j ] = letras[ qtd ][ j + 1 ];
				letras[ ascii ][ j ] = letras[ ascii ][ j + 1 ];
					
				letras[ qtd ][ j + 1 ] = temp[ qtd ];
				letras[ ascii ][ j + 1 ] = temp[ ascii ];
					
			}else if( letras[ qtd ][ j ] == letras[ qtd ][ j + 1 ] ){
				if( letras[ ascii ][ j ] > letras[ ascii ][ j + 1 ] ){
					temp[ qtd ] = letras[ qtd ][ j ];
					temp[ ascii ] = letras[ ascii ][ j ];
						
					letras[ qtd ][ j ] = letras[ qtd ][ j + 1 ];
					letras[ ascii ][ j ] = letras[ ascii ][ j + 1 ];
						
					letras[ qtd ][ j + 1 ] = temp[ qtd ];
					letras[ ascii ][ j + 1 ] = temp[ ascii ];
				}
			}	
		}
	}
	
	for( int i = 0; i < 58; ++i ){
		if( letras[ qtd ][ i ] != 0 )
			cout << static_cast<char>( letras[ ascii ][ i ] + 65 ) << " " 
			<< letras[ qtd ][ i ] << std::endl;
			
	}
}

 