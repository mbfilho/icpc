#include <iostream>
using namespace std;

#include <cmath>

int main(){
    long segundos, ordem, anterior, inicial;
    long i, j;
    
    cin >> segundos;
    while( segundos ){
    
    ordem = static_cast<int>( sqrt( segundos ) );
    if( ordem * ordem < segundos )
        ++ordem;
    anterior = ( ordem - 1 ) * ( ordem - 1 );
    inicial = anterior + 1;
    
    //cima
    if( ordem % 2 == 0 ){
        i = 1;
        j = ordem; 
        //esta em cima ainda
        if( segundos - inicial  + 1 <= ordem )
            i += ( segundos - inicial ); 
        else{
              i = ordem;
              j -= segundos - ( inicial + ordem - 1 );
        }
    //baixo
    }else{
          i = ordem;
          j = 1;
          //em baixo ainda
          if( segundos - inicial + 1 <= ordem ){
              j += ( segundos - inicial );
          }else{
                j = ordem;
                i -= segundos - ( inicial + ordem - 1 ); 
          }
    }
    
    cout << i << " " << j << endl;
    cin >> segundos;
}
        
}
