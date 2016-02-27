#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
int pd[21];

int faz(int n){
	if(~pd[n]) return pd[n];
	if(!n) return pd[n] = 1;
	
	pd[n] = 0;
	int esq = 0, dir = n-2;
	while(dir >= 0){
		pd[n] += faz(esq) * faz(dir);
		esq += 2;
		dir -= 2;
	}
	
	return pd[n];
}

int main(){
	memset(pd, -1, sizeof pd);
	int n;
	bool ft = true;
	while(scanf("%d", &n) == 1){
		if(ft) ft = false;
		else printf("\n");
		printf("%d\n", faz(2*n));
	}
}


