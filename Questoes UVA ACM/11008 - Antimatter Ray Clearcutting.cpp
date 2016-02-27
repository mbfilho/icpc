#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define ft first
#define sd second
#define N 17
#define mp make_pair

pii pts[N];
int n, m;

pii operator-(pii a, pii b){
	return mp(a.ft - b.ft, a.sd - b.sd);
}

int operator%(pii a, pii b){
	return a.ft * b.sd - a.sd * b.ft;
}

int remove(int u, int v, int mask){
	pii vet = pts[v] - pts[u];
	int nmask = 0;
	
	rep(i, n){
		if((1<<i) & mask){
			if((pts[i] - pts[u]) % vet) nmask |= 1 << i;
		}
	}
	
	return nmask;
}

int resp;
pii pares[N*N];
int cnt;
int pd[1<<N][N*N];

int rec(int mask, int ind, int tiros){
	int vivas = __builtin_popcount(mask);
	if(n - vivas >= m){
		resp = min(resp, tiros);
		return tiros;
	}
	if(vivas == 1) return tiros + 1;
	
	if(tiros >= resp) return 10000;
	if(~pd[mask][ind]) return pd[mask][ind];
	
	int old = ind;
	while(ind < cnt && ((mask & (1<<pares[ind].ft)) == 0 || (mask & (1<<pares[ind].sd)) == 0)) ++ind;
	if(ind == cnt) return 1000000;
	
	int nmask = remove(pares[ind].ft, pares[ind].sd, mask);
	return pd[mask][old] = min(rec(nmask, ind+1, 1+tiros), rec(mask, ind+1, tiros));
}

int main(){
	int t;
	scanf("%d", &t);
	
	rep(cas, t){
		if(cas) printf("\n");
		scanf("%d%d", &n, &m);
		memset(pd, -1, sizeof pd);
		
		rep(i, n) scanf("%d%d", &pts[i].ft, &pts[i].sd);
		cnt = 0;
		resp = 100000;
		rep(i, n){
			fr(j, i + 1, n){
				pares[cnt++] = mp(i, j);
			}
		}
		
		printf("Case #%d:\n%d\n", cas+1, rec((1 << n) -1, 0, 0));
	}
}


