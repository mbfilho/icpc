#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 100000

int m[N];
ll coef[N];
int n, k;

ll faz(ll power){
//	memcpy(m, s, sizeof m);
	ll soma = 0, passo = 0, atp = 0, tiros = 0;
	int prt = n - 1;
	
	for(int i = n - 1; i >= 0; --i){
		while(prt > i){
			ll dist = prt - i;
			if(dist * dist > power){
				soma += coef[prt] * (dist) * (dist) - coef[prt] * power;
				passo -= (2 * dist + 1) * coef[prt];
				atp -= 2*coef[prt];
				--prt;
			}else break;
		}
		
//		printf( "> %lld\n", soma);
		if(soma <= m[i]){
			ll tmp = m[i];
			tmp -= soma;
			
			ll qtd = (tmp + power - 1) / power;
			if(tmp % power == 0) ++qtd;

			coef[i] = qtd;
			tiros += qtd;
//			if(tiros > k) return k + 1;
			
			soma -= passo;
			soma += qtd * power - qtd;
			passo += atp + 3*qtd;
			atp += 2*qtd;
//			printf("*%lld\n", qtd);
		}else{
			soma -= passo;
			passo += atp;
			coef[i] = 0;
		}
	}
	
	return tiros;
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d%d", &n, &k);
		for(int i = 0; i < n; ++i){
			scanf("%d", m + i);
		}
		
		ll ini = 1, fim = 7000000010LL;
		ll best = 7000000110LL;
//		printf( ">>> %lld\n", faz(130));
//				printf( ">>> %lld\n", faz(130));
		while(ini <= fim){
			ll meio = (ini+fim)/2;
			ll tiros = faz(meio);
//			printf( "%lld %lld\n", meio, tiros);
			if(tiros <= k){
				best = meio;
				fim = meio - 1;
			}else
				ini = meio + 1;
		}
		
		printf("%lld\n", best);
	}
}

