#include <iostream>
using namespace std;

int aux[16], conj[15];
int qtd, k;
typedef long long ll;

int euclides( int a, int b ){
    int temp;
    while( b ){
           temp = a % b;
           a = b;
           b = temp;
    }
    
    return a;
}

ll MMC( ll a, ll b ){
 //   cout << "Euclides: " << euclides( a, b ) << endl;
   // cout << "PArte1: " << b << endl;
  //  cout << "Parte2: " << ( a/euclides(a,b) ) << endl;
    return b * (a / euclides( a, b ));
}

ll exc( int r ){
    for( int i = 1; i <= k; ++i )
         aux[i] = i;
  //  cout << "AQUI: " << aux[1] << endl;
    int c = k - r;
    ll excluido = 0;
    ll mmc;


    while( true ){
        int i = r;
        mmc = 1;
        for( int j = 1; j <= r; ++j ){
           //  cout << "MMC ant: " << mmc; 
          //   cout << "J: " << j << " " << aux[1] << endl;
             mmc = MMC( mmc, conj[ aux[j] - 1 ] );
         //    cout << " Retorno :" << mmc << endl;
        }

        excluido += qtd / mmc;


        while( i != 0 && aux[i] == c + i )
           --i;

        if( i == 0 )
           break;

       ++aux[i];
       for( i = i + 1; i <= r; ++i )
            aux[i] = aux[i - 1] + 1;
    }   
    
    return excluido;
}

int main(){
    ll resp;
    
    while( cin >> qtd >> k ){
           for( int i = 0; i < k; ++i )
                cin >> conj[i];
           resp = 0;
           for( int i = 0; i <= k; ++i ){
             //   cout << "D: " << i << endl;
                if( i % 2 == 0 )
                    resp += exc( i );
                else
                    resp -= exc( i );
           }
           cout << resp << endl;
    }
}
