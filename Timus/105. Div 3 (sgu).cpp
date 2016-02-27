#include <cstdio>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;
typedef long long ll;

int main(){
    ll n;

    while( scanf( "%lld", &n ) != EOF ){
        ll qtd = ( n / 3 ) * 2;
        if( n % 3 == 2 )
            ++qtd;
        printf( "%lld\n", qtd );
    }
}
