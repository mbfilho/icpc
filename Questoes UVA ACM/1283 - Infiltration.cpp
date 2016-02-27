#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef long long ll;
typedef bitset<80> no;

int n;
no adj[80];

int caras[80], cont;

bool generate(int ind, int last, no mk){
	if(ind == cont) return mk.count() == n;
	fr(i, last+1, n){
		caras[ind] = i;
		no tmp = mk;
		tmp.set(i);
		tmp |= adj[i];
		if(generate(ind+1, i, tmp))	return true;
	}
	return false;
}

char buf[80];
int main(){
	int caso = 1;
	while(scanf("%d", &n) == 1){
		rep(i, n) adj[i].reset();
		rep(i, n){
			scanf("%s", buf);
			rep(j, n){
				if(buf[j] == '1') adj[i].set(j);
			}
		}
		cont = 1;
		while(!generate(0,-1, no())) ++cont;
		
		printf("Case %d: %d", caso++, cont);
		rep(i, cont)
			printf(" %d", caras[i]+1);
		printf("\n");
	}
}


