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
#define N 100100
#define conj askjdfsf
#define DB if(0)

int p[N], n;
int cyc[N];
bool used[N];

int primos[N], A[N], contp;

int conj[N];

vector<pii> graph;

// This is a curious solution =P There is a simplier one using observations about the center(s) of the tree

//join same-size cycles a and b (size s)
void joinSameSize(int a, int b, int s){
	while(s--){
		graph.pb(mp(a+1, b+1));
		a = p[a], b = p[b];
	}
}

//join cycles a and b, with size(a) > size(b)
void joinDistinctSize(int a, int b, int sa) {
	while(sa--) {
		graph.pb(mp(a+1, b+1));
		a = p[a], b = p[b];
	}
}

int find(int a){
	if(a == conj[a]) return a;

	return conj[a] = find(conj[a]);
}

void unir(int a, int b){
	conj[find(a)] = find(b);
}

//find a cycle with size that is a divisor of s and that it's not connected to s yet
int findCycDiv(int s, int cur, int acc = 1){
	if(acc != s && find(s) != find(acc) && ~cyc[acc]) {
		return acc;
	}

	if(cur <= 1) return -1;

	int xp = 0, p = primos[A[cur]];
	while(cur % p == 0) {
		++xp;
		cur /= p;
	}

	rep(i, xp+1){
		int tmp = findCycDiv(s, cur, acc);
		if(~tmp) return tmp;
		acc *= p;
	}

	return -1;
}

void breakIntoCycles(){
	memset(used, false, sizeof used);
	memset(cyc, -1, sizeof cyc);
	graph.clear();

	rep(i, n) if(!used[i]) {
		int cur = i, s = 0;

		do{
			used[cur] = true;
			++s;
			DB printf("%d ", cur+1);
			cur = p[cur];
		}while(cur != i);
		DB printf(" of size %d\n", s);

		if(~cyc[s]) joinSameSize(i, cyc[s], s);
		else cyc[s] = i;
	}	
}

bool faz(){
	breakIntoCycles();

	memset(used, false, sizeof used);
	rep(i, n+1) conj[i] = i;
	for(int s = n; s > 0; --s) if(~cyc[s]) {
		int s2 = findCycDiv(s, s);
		if(s2 == -1) continue;
		DB printf("Found %d\n", s2);
		used[s] = true;
		
		unir(s, s2);
		joinDistinctSize(cyc[s], cyc[s2], s);
	}

	//check if we have exactly 1 component of cycles
	int last = -1;
	rep(i, n+1) if(~cyc[i]) {
		if(last == -1) last = find(i);
		else if(find(i) != last) return false;
	}
	DB printf("yes, 1 comp\n");

	int k = n-1 - graph.size();
	DB printf("K: %d\n", k);
	if(k) {
		//check if the cycle of size 2k exists and is not connected 
		DB printf("Used, cyc %d %d\n", used[2*k], cyc[2*k]);
		if(used[2*k] || cyc[2*k] == -1) return false;

		int cur = cyc[2*k];
		vector<int> tmp;
		rep(i, 2*k) tmp.pb(cur), cur = p[cur];

		//collapse the cycle of size 2k
		rep(i, k) graph.pb(mp(tmp[i]+1, tmp[i+k]+1));
	}

	return true;
}

void pre(){
	contp = 0;
	memset(A, -1, sizeof A);

	fr(i, 2, N) {
		if(A[i] == -1){
			A[i] = contp;
			primos[contp++] = i;
		}

		rep(j, A[i]+1) {
			ll tmp = primos[j];
			if(tmp * i >= N) break;
			A[tmp*i] = j;
		}
	}
}

int main(){
	pre();
	scanf("%d", &n);
	rep(i, n) {
		scanf("%d", p+i);
		--p[i];
	}

	if(!faz()) printf("NO\n");
	else{
		printf("YES\n");
		rep(i, graph.size()) printf("%d %d\n", graph[i].ft, graph[i].sd);
	}
}




