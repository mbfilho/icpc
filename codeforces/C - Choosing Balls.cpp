#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 100100
typedef long long ll;

int c[N], v[N], n;
ll tmp[N];
int mk[N], caso;
pii heap[3];
int hs;

inline bool cmp(const pii& a, const pii& b){
	return a.X > b.X;
}

inline void update(int ind, ll val){
	tmp[ind] = max(tmp[ind], val);
//	mk[ind] = caso;
	
	pii novo = mp(val, ind);
	if(novo.X > heap[0].X) swap(heap[0], heap[1]), heap[0] = novo;
	else if(novo.X > heap[1].X) heap[1] = novo;
}

inline ll maior(int ind){
	if(heap[0].Y == ind)
		return heap[1].X;
	return heap[0].X;
}

ll resp(int a, int b){
	++caso;
	hs = 0;	
	ll best = 0;
	rep(i, n) tmp[i] = -(ll) (1e17);
	heap[0] = heap[1] = mp(0, -1);
	
	rep(i, n){
		//dif
		int cor = c[i];
		ll val = v[i] * ll(b) + maior(cor);
		best = max(best, val);

		ll ig = 0;
		ig = v[i] * ll(a) + tmp[cor];
		best = max(best, ig);
		update(cor, ig);
		update(cor, val);
	}
	
	return best;
}

int main(){
	ios::sync_with_stdio(false);
	int q;
	scanf("%d%d", &n, &q);
	rep(i, n)
		scanf("%d", v + i);
	rep(i, n){
		scanf("%d", c + i);
	}
	
	rep(i, q){
		int a, b;
		scanf("%d%d", &a, &b);
		cout << resp(a,b) << endl;
	}
}

