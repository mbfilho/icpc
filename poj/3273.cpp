#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

#define N 130000
ll num[ N ];
int n, m;

bool pode( ll limite ){
	int at = 0;
	int conj = 0;
	
	while( at < n ){
		ll soma = 0;
		bool mudei = false;
		while( at < n && soma + num[ at ] <= limite ){
			soma += num[ at ];
			++at;
			mudei = true;
		}
		
		if( mudei )
			++conj;
		else
			return false;
	}
	
	return conj <= m;	
}

int main(){
	while( scanf( "%d %d", &n, &m ) != EOF ){
		for( int i = 0; i < n; ++i )
			scanf( "%lld", num + i );
		
		ll ini = 0, fim = 2000000000;
		ll total = -1;
		
		while( ini <= fim ){
			ll meio = ( ini + fim ) / 2;

			if( pode( meio ) ){
				total = meio;
				fim = meio - 1;
			}else{
				ini = meio + 1;
			}
		}
		
		if( total != -1 )
			printf( "%lld\n", total );
	}
}







