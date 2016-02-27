#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;

int adj[20];
int n, pot[20], m;
ll pd[13][13][2][3][1<<13];
char mk[13][13][2][3][1<<13];
char caso;

ll rec(int last, int first, bool metade, int qtd, int mask){
//	printf("%d %d %d %d %d\n", last, first, metade, qtd, mask);
	ll& total = pd[last][first][metade][qtd][mask];
	
	if(mk[last][first][metade][qtd][mask] == caso) return total;
	mk[last][first][metade][qtd][mask] = caso;
	
	total = 0;
	rep(i, n){
		if((mask & pot[i]) && (adj[last] & pot[i])){
			total += rec(i, first, metade, min(qtd+1, 2), mask ^ pot[i]);
		}
	}
	
	if((adj[last] & pot[first]) && qtd == 2){
		if(metade){
			++total;
//			printf(">>> %d %d %d %d %d\n", last, first, metade, qtd, mask);
		}else{
//			printf("XX %d %d %d %d %d\n", last, first, metade, qtd, mask);
			total += rec(first, first, true, 0, mask);
		}
	}
	
	return total;
}

int main(){
	rep(i, 20) pot[i] = 1 << i;
	memset(mk, 0, sizeof mk);
	caso = 0;
	
	int t;
	scanf("%d", &t);
	rep(cas, t){
		++caso;
		scanf("%d%d", &n, &m);
//		printf("GG %d %d\n", n, m);
		memset(adj, 0, sizeof adj);
		
		rep(i, m){
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a] |= pot[b];
			adj[b] |= pot[a];
		}
		
		ll total = 0;
		rep(i, n){
//			printf("# %d %d %d\n", (pot[n]-1) ,pot[i], n);
			ll tmp = rec(i, i, false, 0, (pot[n] -1) ^ pot[i]);
//			printf("Init [%d] = {%lld}\n", i, tmp);
			total += tmp;
		}
		printf("Case %d: %lld\n", cas + 1, total/8);
	}

}








