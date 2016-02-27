#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef long long ll;
#define N 200010
#define mp make_pair
#define pb push_back
typedef pair<int,int> pii;
int A[N], primos[N], prt;

void pre(){
	memset(A, -1, sizeof A);
	prt = 0;
	fr(i, 2, N){
		if(A[i] == -1){
			A[i] = prt;
			primos[prt++] = i;
		}
		rep(j, A[i]+1){
			ll tmp = ll(primos[j]) * i;
			if(tmp >= N) break;
			A[tmp] = j;
		}
	}
}

vector<pii> fatora(int num){
	vector<pii> resp;
	
	while(num != 1){
		int p = primos[A[num]];
		pii at = mp(p, 0);
		while((num % p) == 0) ++at.second, num /= p;
		resp.pb(at);
	}
	return resp;
}

int mapa[N], in[N];
vector<pii> pares;
void gera(vector<pii>& fat, int num, int i, int ind){
	if(i == fat.size()) pares.pb(mp(min(ind, mapa[num]), max(ind, mapa[num])));
	else{
		int pot = 1;
		rep(j, fat[i].second+1){
			gera(fat, num * pot, i+1, ind);
			pot *= fat[i].first;
		}
	}
}
struct Query{
	int id, ini, fim, resp;
}que[N];

int pts[N];
int bit[N];

bool cmp(int a, int b){
	return que[a].ini > que[b].ini;
}

	int n, q;
void update(int ind, int val){
	for(int i = ind; i <= n; i += i & -i) bit[i] += val;
}

int query(int ind){
	int s = 0;
	for(int i = ind; i > 0; i -= i & -i) s += bit[i];
	
	return s;
}

int main(){
	pre();
	scanf("%d%d", &n, &q);
	
	rep(i, n){
		int tmp;
		scanf("%d", &tmp);
		mapa[tmp] = i;
		in[i] = tmp;
	}
	int soma = 0;
	rep(i, n){
		vector<pii> fatores = fatora(in[i]);
		gera(fatores, 1, 0, i);
	}
	sort(pares.begin(), pares.end());
	
	rep(x, q){
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		que[x] = (Query){x, u, v, 0};
		pts[x] = x;
	}
	
	sort(pts, pts + q, cmp);
	int idx = pares.size() - 1;
	rep(i, q){
		while(idx >= 0 && pares[idx].first >= que[pts[i]].ini) update(pares[idx].second+1, 1), --idx;
		que[pts[i]].resp = query(que[pts[i]].fim+1);
	}
	
	idx = 0;
	while(idx < q){
		while(que[idx].id != idx) swap(que[ que[idx].id ], que[idx]);
		++idx;
	}
	rep(i, q) printf("%d\n", que[i].resp);
}

