#include <cstdio>

int main(){
    int qtd, linha = 1;
    double entrada;
    char medida[10];
            
    scanf( "%d", &qtd );
        
    while( qtd-- ){
           scanf( "%lf%s", &entrada, medida );
           
           //gallons -> litro
           if( medida[ 0 ] == 'g' || medida[ 0 ] == 'G' ){
               entrada *= 3.7854;
               printf( "%d %.4lf l\n", linha, entrada );

           
           //killo -> pound
           }else if( medida[ 0 ] == 'k' || medida[ 0 ] == 'K' ){
                 entrada *= 2.2046;
                 printf( "%d %.4lf lb\n", linha, entrada );
          
          
          //pounds -> killo
           }else if( medida[ 1 ] == 'b' || medida[ 1 ] == 'B' ){
                 entrada *= 0.4536;
                 printf( "%d %.4lf kg\n", linha, entrada );
                 
           //litro -> gallon
           }else{
                 entrada *= 0.2642;
                 printf( "%d %.4lf g\n", linha, entrada );
           }
           
           ++linha;       
    }
    
}
