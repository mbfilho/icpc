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
#define N 110
#define M 110
#define POS 1100
#define oo 0x3f3f3f3f

int n, m, l;
int pd[POS];
int power[M], cost[M];
int pos[N];
int dist[N];

void fillPd(){
	memset(pd, 0x3f, sizeof pd);
	pd[0] = 0;

	rep(i, m){
		for(int p = POS - 1; p - power[i] >= 0; --p){
			pd[p] = min(pd[p], pd[p-power[i]] + cost[i]);
		}
	}
}

int bfs(int s, int t){
	memset(dist, -1, sizeof dist);
	queue<int> fila;
	fila.push(s);
	dist[s] = 0;

	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		if(at == t) return dist[t];

		rep(i, n){
			int d = abs(pos[i] - pos[at]);
			if(pd[d] <= l && dist[i] == -1){
				dist[i] = 1 + dist[at];
				fila.push(i);
			}
		}
	}

	return -1;
}

int main(){
	int casos;
	scanf("%d", &casos);

	while(casos--){
		scanf("%d%d%d", &n, &m, &l);
		rep(i, n) scanf("%d", pos + i);
		rep(i, m) scanf("%d%d", cost + i, power + i);

		int s = 0, t = 0;
		rep(i, n){
			if(pos[i] < pos[s]) s = i;
			if(pos[i] > pos[t]) t = i;
		}

		fillPd();
		printf("%d\n", bfs(s, t));
	}
}






