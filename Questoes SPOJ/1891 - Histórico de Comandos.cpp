#include <cstdlib>
#include <cstdio>

int array[ 1100 ];

int main(){
    int qtd, soma;
        
    while( true ){
           scanf( "%d", &qtd );
           if( qtd == 0 )
               break;
           soma = 0;
           
           int cont;
           for( cont = 0; cont < qtd; ++cont )
                scanf( "%d", &array[ cont ] );
                  
          for( cont = 0; cont < qtd; ++cont ){
               soma += array[ cont ];
               
               int i;
               for( i = cont + 1; i < qtd; ++i ){
                    if( array[ i ] == array[ cont ] )
                        array[ i ] = 1;
                    else
                        ++array[ i ];
               }
          }
          
          printf( "%d\n", soma ); 
    }
}
