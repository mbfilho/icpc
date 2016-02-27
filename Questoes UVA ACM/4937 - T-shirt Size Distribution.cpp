#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define N 2000
typedef long long ll;

ll val[7], P, p[7];
ll soma;

int main(){
	while(scanf( "%lld", val) != EOF){
		for(int i = 1; i < 7; ++i) scanf( "%lld", val + i);
		scanf( "%lld", &P );
		soma = 0;
		for(int i = 0; i < 7; ++i) soma += val[i];
		
		ll tmp = 0;
		for(int i = 0; i < 7; ++i) tmp += (p[i] = (P*val[i]) / soma);
		ll S = P - tmp;
		
		for(int i = 0; S && i < 7; ++i){
			if(!p[i]){
				--S;
				++p[i];
			}
		}
		
		if(S){
			p[4] += S;
		}
		
		printf( "%lld", p[0] );
		for(int i = 1; i < 7; ++i) printf( " %lld", p[i]);
		printf( "\n" );
	}
}




