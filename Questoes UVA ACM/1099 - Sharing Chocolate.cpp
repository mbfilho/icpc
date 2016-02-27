#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define inc kjshdfkjsd
#define pb push_back
#define N 16
#define oo 10000000


bool pd[1<<N][101];
int mk[1<<N][101], caso;
int soma[1<<N], cont[1<<N];
int qtd[N], n;

int geta(int mask){
	rep(i, n){
		if(mask & (1<<i)) return i;
	}
}

bool memo(int mask, int x, int y){
	if(cont[mask] == 1){
		return (x*y) == qtd[geta(mask)];
	}
	
	bool& rec = pd[mask][x];
	if(mk[mask][x] == caso) return rec;
	mk[mask][x] = caso;
	
	for(int m = mask & (mask-1); m > 0; m = mask & (m-1)){
		int a = m, b = (~m) & mask, sa = soma[a], sb = soma[b];
		if(!(sa % x) && !(sb % x)){
			if(memo(a, x, sa / x) && memo(b, x, sb / x)) return rec = true;
		}
		if(!(sa % y) && !(sb % y)){
			if(memo(a, sa / y, y) && memo(b, sb / y, y)) return rec = true;
		}
	}
		
	return rec = false;
}

int main(){
	caso = 0;
	while(scanf("%d", &n) == 1 && n){
		++caso;
		int x, y;
		scanf("%d%d", &x, &y);
		
		rep(i, n) scanf("%d", qtd + i);
		
		rep(i, 1 << n){
			soma[i] = cont[i] = 0;
			rep(j, n){
				if((1<<j) & i) ++cont[i], soma[i] += qtd[j];
			}
		}
		
		printf("Case %d: ", caso);
		if(soma[(1<<n)-1] == x * y && memo((1<<n)-1, x, y)) printf("Yes\n");
		else printf("No\n");
	}
}



