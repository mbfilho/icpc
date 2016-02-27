#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define ft first
#define sd second
typedef pair<int,int> pii;
#define N 10

pii caras[210*N];
int prt;
int qtd[] = {20, 20, 20, 25, 25, 30, 30};
int age[N];
int pd[210*N];

int rec(int ind){
	if(ind == prt) return 0;
	int& best = pd[ind];
	if(~best) return best;
	best = 100000000;
	int at = ind;
	
	while(at < prt && caras[at].ft <= caras[ind].ft + 1){
		best = min(best, (at-ind+1+caras[ind].sd-1)/caras[ind].sd + rec(at+1));
		++at;
	}
	
	return best;
}


int main(){
	while(1){
		bool sai = true;
		rep(i, 7){
			scanf("%d", age+i);
			if(age[i]) sai = false;
		}
		if(sai) break;
		
		memset(pd, -1, sizeof pd);
		prt = 0;
		rep(i, 7){
			while(age[i]){
				caras[prt++] = mp(i, qtd[i]);
				--age[i];
			}
		}
		printf("%d\n", rec(0));
	}
}


