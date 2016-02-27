#include <cstdlib>
#include <cstdio>

int main(){
    int qtd, linha = 1, soma, arg;
        
    scanf( "%d", &qtd );
    
    while( qtd-- ){
           scanf( "%d", &arg );
           soma = 0;
           int k;
           int temp;
           
           for( k = 1; k <= arg; ++k ){
                temp = ( k + 2 ) * ( k + 1 ) / 2;
                soma += k * temp;
           } 
           
           printf( "%d %d %d\n", linha, arg, soma );
           ++linha;
    }
    
}
