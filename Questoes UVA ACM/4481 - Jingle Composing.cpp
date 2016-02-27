#include <iostream>

using namespace std;

int main(){
    freopen( "in.txt", "r", stdin );
    freopen( "out.txt", "w", stdout );
    
    char str[ 201 ];
    char c;
    int total, i, soma;
    
    cin >> str;
    while( str[ 0 ] != '*' ){
           c = str[ 0 ];
           i = 1;
           total = 0;
           soma = 0;
           while( c != '\0' ){
               if( c == 'W' )
                   soma += 64;
               else if( c == 'H' )
                    soma += 32;
               else if( c == 'Q' )
                    soma += 16;
               else if( c == 'E' )
                    soma += 8;
               else if( c == 'S' )
                    soma += 4;
               else if( c == 'T' )
                    soma += 2;
               else if( c == 'X' )
                    soma += 1;
               else if( c == '/' ){
                    if( soma == 64 )
                        total++;
                    soma = 0;
               }
               
               c = str[ i ];
               i++;
           }
           
           cout << total << endl;
           cin >> str;
    }    
}
