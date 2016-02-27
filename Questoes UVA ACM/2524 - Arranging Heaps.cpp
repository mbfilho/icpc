#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 1100
#define K N
#define oo 1000000000000000LL

ll w[N];
int y[N];

int mk[N][K], caso;
ll pd[N][K];

int n, k;
ll faz(ll soma, int tmp, int ind, int kk){
	if(ind == n-1){
		if(kk==1){
			return soma;
		}
		return oo;
	}
	
	if(!kk) return oo;
	if(!tmp && mk[ind][kk] == caso)
		return pd[ind][kk];
		
	int delta = y[ind+1] - y[ind];
	ll nfaz = faz(0, 0, ind+1, kk); //não monta um heap aqui =D
	ll f = faz(0, 0, ind+1, kk-1);//monta um heap aqui
	
	if(soma + (tmp + w[ind]) * delta + nfaz >= f + soma){ //aproximação
		ll res = soma + f;
		if(!tmp){
			mk[ind][kk] = caso;
			pd[ind][kk] = res;
		}
		
		return soma + f;
	}else{
		ll res = min(faz(soma + (tmp + w[ind]) * delta, tmp + w[ind], ind + 1, kk), soma + f);;
		if(!tmp){
			mk[ind][kk] = caso;
			pd[ind][kk] = res;
		}
		return res;
	}
}

int main(){
	memset(pd, 0, sizeof pd);
	caso = 0;
	
	while(scanf("%d%d", &n, &k) == 2){
		++caso;
		
		rep(i, n)
			scanf("%d %lld", y + i, w + i);
		printf("%lld\n", faz(0, 0, 0, k));
	}
}



