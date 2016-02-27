#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 30000

int soma[N], caras[N], input[N];

ll faz(int i){
	return (caras[i] * i - soma[i]) + (soma[N-1] - soma[i]) - (caras[N-1] - caras[i])*i;
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int n;
		scanf("%d", &n);
		memset(input, 0, sizeof input);
		memset(soma, 0, sizeof soma);
		memset(caras, 0, sizeof caras);
		
		for(int i = 0; i < n; ++i){
			int tmp;
			scanf("%d", &tmp);
			++input[tmp];
		}
		
		int pre = 0;
		for(int i = 0; i < N; ++i){
			caras[i] = pre + input[i];
			pre = caras[i];
		}
		
		pre = 0;
		for(int i = 0; i < N; ++i){
			soma[i] = pre + input[i] * i;
			pre = soma[i];
		}
		
		ll best = (-1ULL) >> 1;
		int ini = 0, fim = N - 1;
		while(ini + 1 < fim){
			int tam = (fim - ini + 1) /3;
			int e = ini + tam, d = e + 1;
			if(faz(e) < faz(d)){
				best = min(best, faz(d));
				fim = d - 1;
			}else{
				best = min(best, faz(e));
				ini = e + 1;
			}
		}
		best = min(best, min(faz(ini), faz(fim)));
		
		printf("%lld\n", best);
	}
}

