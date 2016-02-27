#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

char matriz[20][300]; 
char buffer[300];
int linhas;

int main(){
    freopen( "in.txt", "r", stdin );
    freopen( "out.txt", "w", stdout );
    ostringstream out;
   
	cin >> linhas;
    
	while( cin.peek() == '\n' )
		cin.ignore();
		
    for( int i = linhas - 1; i >= 0; --i ){
         gets( matriz[i] );
    //     printf( "%s\n", matriz[i] );
    }
    
    int i = 0, j = 0;
    int qtd;
    int caminho = 0;
    
     
	do{
	   if( matriz[i][j] == '/' ){
	        qtd = 0;
	  
	        while( i < linhas && j < strlen( matriz[i] ) && matriz[i][j] == '/' ){
			   ++qtd;
			   ++i;
			   ++j;
			   ++caminho;
	        }
			
	        if( i == linhas || matriz[i][j] == ' ' || j >= strlen( matriz[i] ) )
	            --i;
	            
		//printf( "subindO\n" );
	        out << "Up " << qtd << " steps\n";
	    }else if( matriz[i][j] == '_' ){
	          qtd = 0;
	          int tam = strlen( matriz[i] );
	        //  printf( "lado\n" );
	          while( j < tam && matriz[i][j] == '_' ){
	                 ++j;
	                 ++qtd;
	                 ++caminho;
	          }
	          
	          if( i == 0 && j == tam ){
				out << "Walk " << qtd << " steps\n";
				 break;
			  }
			
			if( j == tam || matriz[i][j] == ' ' ){
				if( i > 0 && ( j < strlen( matriz[i-1] ) && matriz[i - 1][j] != ' ') )
					--i;
				else
					++i;
			}

	         // printf( "%d %d %c\n", i, j, matriz[i][j] );
	          
	          out << "Walk " << qtd << " steps\n";
	    }else if( matriz[i][j] == '\\' ){
	          qtd = 0;
	        //  printf( "descendo\n" );
	          while( i >= 0 && j < strlen( matriz[i] ) && matriz[i][j] == '\\' ){
	                 ++qtd;
	                 ++j;
	                 --i;
	                 ++caminho;
	          }

			if( i >= 0 && ( j >= strlen( matriz[i] ) || matriz[i][j] == ' ') ){
				++i;
			}else if( i < 0 )
				++i;
			//	printf( "descido%c|\n", matriz[i][j] );

	          out << "Down " << qtd << " steps\n";
	    }
	}while( i != 0 || j < strlen( matriz[0] ) );
        
        printf( "Total Walk Distance = %d\n", caminho );
        cout << out.str();
       
}
