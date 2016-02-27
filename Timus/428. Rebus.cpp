#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    char permut[] = "ABCDEFGHI";

    //Parcela1:
    char p1[] = "IHGFDCBAFA"; //+permut
    
    //Parcela2:
    char p2[] = "BBBBBBBAFA", as[] = "AAAAAAAAA";
    
    //Resposta:
    char r1[] = "JIHGEDCBAA"; //+permut
    
    for( int i = 0; i < 1000; ++i ){
        printf( "%s%s+%s%s=%s%s\n", p1, permut, p2, as, r1, permut );
        next_permutation( permut, permut + 9 );
    }
}