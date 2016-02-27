#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 1000100

int primos[100000], prt;
int crivo[N];
int resp[N];

void pre(){
	prt = 0;
	memset(crivo, -1, sizeof crivo);
	
	for(int i = 2; i < N; ++i){
		if(crivo[i] == -1){
			crivo[i] = prt;
			primos[prt++] = i;
		}
		
		for(int j = 0; j < prt && i * primos[j] < N; ++j)
			crivo[i*primos[j]] = j;
	}
}

int main(){
	pre();
	resp[1] = 0;
	
	for(int k = 2; k <= 1000000; ++k){
		resp[k] = resp[k-1];
		int tmp = k;
		
		while(tmp != 1){
			++resp[k];
			tmp /= primos[crivo[tmp]];
		}
	}
	
	int n;
	while(scanf("%d", &n) == 1){
		printf("%d\n", resp[n]);
	}
	
}


