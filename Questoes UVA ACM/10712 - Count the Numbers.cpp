#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back
#define N 200
#define oo 700000000
typedef long long ll;
//obs, nao eh subsequencia. Eh substring =/

int pd[12][4][2];
int fail[5];
void build(char* pat){
	int tam = strlen(pat);
	fail[0] = -1;
	int k = -1;
	fr(i, 1, tam){
		while(k != -1 && pat[k+1] != pat[i]) k = fail[k];
		if(pat[k+1] == pat[i]) ++k;
		fail[i] = k;
	}
}

int memo(char* num, char* pat, int n, int p, bool tdZero, bool tight){
	if(!num[n]){
		if(tdZero || pat[p]) return 0;
		return 1;
	}
	if(!tight && pd[n][p][tdZero] != -1) return pd[n][p][tdZero];
	
	int lim = 10;
	if(tight) lim = num[n] - '0' + 1;

	ll total = 0;
	rep(dig, lim){
		int np = p;
		if(pat[p] &&(pat[p] != '0' || !tdZero)){
			np = p-1;
			while(np != -1 && pat[np+1] != dig + '0') np = fail[np];
			if(pat[np+1] == dig + '0') ++np;
			
			++np;
		}
		total += memo(num, pat, n+1, np, tdZero && !dig, tight && dig == lim - 1);
	}
	
	if(!tight) pd[n][p][tdZero] = total;
	return total;
}

char n[10], a[20], b[20];
int A;
int main(){
	while(scanf("%d%s%s",&A, b, n) == 3 && (n[0] != '-')){
		build(n);
		
		memset(pd, -1, sizeof pd);
		ll total = memo(b, n, 0, 0, true, true);
		memset(pd, -1, sizeof pd);
		sprintf(a, "%d", max(0,A-1));
		total -= memo(a, n, 0, 0, true, true);
		
		if(A==0){
			if(strcmp(n, "0") == 0) ++total;
		}
		
		printf("%lld\n", total);
	} 
}


