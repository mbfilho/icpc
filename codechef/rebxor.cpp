#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 500500
#define TRIE (32*N)

int n;

struct No{
	int adj[2];
	int val;

	void clear(){
		adj[0] = adj[1] = -1;
	}
}trie[TRIE];

int cont;

void insert(int val){
	int i = 1<<30;
	int at = 0;

	while(i){
		int nt = (val & i) ? 1 : 0; 
		if(trie[at].adj[nt] == -1){
			trie[cont].clear();
			trie[at].adj[nt] = cont++;
		}
		at = trie[at].adj[nt];
		i >>= 1;
	}

	trie[at].val = val;
}

void clearTrie(){
	cont = 1;
	trie[0].clear();
	insert(0);
}


int getMax(int val){
	int i = 1<<30, at = 0, ans = 0;

	while(i) {
		int nt = (val & i) ? 1 : 0;
		if(~trie[at].adj[1-nt]){
			ans |= i;
			at = trie[at].adj[1-nt];
		}else at = trie[at].adj[nt];
		i >>= 1;
	}

	return ans;
}

void faz(int input[N], int out[N]){
	clearTrie();
	int acc = 0;

	rep(i, n){
		acc ^= input[i];
		out[i] = getMax(acc);
		if(i) out[i] = max(out[i], out[i-1]);
		insert(acc);
	}
}

int input[N], tmp[N], tmpRev[N];

int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%d", input+i);

	faz(input, tmp);
	reverse(input, input + n);
	faz(input, tmpRev);

	int best = 0;

	rep(i, n-1) {
		best = max(best, tmp[i] + tmpRev[n-1-(i+1)]);
	}

	printf("%d\n", best);
}


