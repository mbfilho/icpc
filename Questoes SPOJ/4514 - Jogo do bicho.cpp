#include <cstdio>
#include <cstdlib>


int main(){
    double dinheiro;
    int aposta, sorteio;
        
    while( true ){
            scanf( "%lf %d %d", &dinheiro, &aposta, &sorteio );
            
            if( dinheiro == 0.0 && aposta == 0 && sorteio == 0 )      
                    break;
                    
            if( aposta < sorteio ){
                int temp = aposta;
                aposta = sorteio;
                sorteio = temp;
            }
                       
            if( ( aposta - sorteio ) % 10000 == 0 ){
                printf( "%.2lf\n", 3000 * dinheiro );
            }else if( ( aposta - sorteio ) % 1000 == 0 ){
                printf( "%.2lf\n", 500 * dinheiro );
            }else if( ( aposta - sorteio ) % 100 == 0 ){
                printf( "%.2lf\n", 50 * dinheiro );
            }else{
          
                  aposta = aposta % 100;
                  sorteio = sorteio % 100;
                  if( aposta == 0 ) aposta = 100;
                  if( sorteio == 0 ) sorteio = 100;
                  
                  if( aposta - sorteio > -4 && aposta - sorteio < 4 )
                      printf( "%.2lf\n", 16 * dinheiro );
                  else
                      printf( "0.00\n" ); 

            }
    
    }
}
