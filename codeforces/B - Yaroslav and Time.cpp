#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 500
typedef pair<int,int> pii;
#define mp make_pair
#define X first
#define Y second
#define oo 2000000000

pii pts[N];
int a[N], n, d;
int mk[N];

int dist(int a, int b){
	return abs(pts[a].X - pts[b].X) + abs(pts[a].Y - pts[b].Y);
}

void dij(int s){
	rep(i, n) mk[i] = oo;
	priority_queue<pii> heap;
	heap.push(mp(0, s));
	mk[s] = 0;
	
	while(!heap.empty()){
		int at = heap.top().second, custo = -heap.top().first; heap.pop();
		
		if(custo > mk[at]) continue;
		
		rep(nt, n) if(mk[nt] > mk[at] + dist(at, nt)){
			mk[nt] = mk[at] + dist(at, nt);
			heap.push(mp(-mk[nt], nt));
		}
	}
}
int pd[N];
int mk2[N];
int faz(){
	rep(i, n) mk2[i] = oo;
	priority_queue<pii> heap;
	heap.push(mp(0, 0));
	mk2[0] = 0;
	
	while(!heap.empty()){
		int at = heap.top().second, custo = -heap.top().first;
		heap.pop();
		
		if(custo > mk2[at]) continue;
		
		
		rep(nt, n){
			int tran = dist(at, nt) * d - a[at];
			if(nt != at && mk2[nt] > mk2[at] + tran){
				mk2[nt] = mk2[at] + tran;
				heap.push(mp(-mk2[nt], nt));
			}
		}
	}
	
	return mk2[n-1];
}

int main(){
	memset(a, 0, sizeof a);
	memset(pd, -1, sizeof pd);
	scanf("%d%d", &n, &d);
	fr(i, 1, n-1) scanf("%d", a + i);
	rep(i, n) scanf("%d%d", &pts[i].X, &pts[i].Y);
	dij(n-1);
	printf("%d\n", faz());
}



