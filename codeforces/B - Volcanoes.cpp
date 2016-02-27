#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
typedef pair<int,int> pii;
#define M 100100
#define oo 0x7fffffff
vector<int> volcs[M];
vector<pii> input;
int mapa[M];
int n, m, v;

int main(){
	scanf("%d%d", &n, &m);
	rep(i, m){
		pii tmp;
		scanf("%d%d", &tmp.ft, &tmp.sd);
		input.pb(tmp);
	}
	sort(input.begin(), input.end());
	v = 0;
	{
		int i = 0;
		while(i < input.size()){
			int row = input[i].ft;
			while(i < input.size() && input[i].ft == row) volcs[v].pb(input[i].sd), ++i;
			volcs[v].pb(n+1);
			mapa[v] = row;
			++v;
		}
	}
	
	vector<pii> sweep;
	bool dm = false;
	if(input[0].ft == 1) sweep.pb(mp(1,1));
	else sweep.pb(mp(1, n));
	
	rep(row, v){
// 		printf("Linha comp %d [%d]\n", row, mapa[row]);
// 		rep(i, sweep.size()) printf("(%d %d)", sweep[i].ft, sweep[i].sd);
// 		printf("\n");
		if(sweep.empty()){
			dm = true;
			break;
		}
		if(row > 0 && mapa[row-1] + 1 != mapa[row]){
			pii tmp = sweep[0];
			sweep.clear();
			sweep.pb(mp(tmp.first, n));
		}
		
		vector<pii> events = sweep, next;
		rep(i, volcs[row].size()) events.pb(mp(volcs[row][i], oo));
		sort(events.begin(), events.end());
		int far = -1, at = -1;
		
		rep(i, events.size()){
			if(events[i].sd == oo){
				if(at == -1) continue;
				pii tmp = mp(at, events[i].ft - 1);
				if(tmp.ft <= tmp.sd)
					next.pb(tmp);
				if(far > events[i].ft) at = events[i].ft + 1;
				else at = -1;
			}else{
				if(at == -1) at = events[i].ft;
				far = max(far, events[i].sd);
			}
		}
		sweep = next;
// 		printf("Final Linha comp %d [%d]\n", row, mapa[row]);
// 		rep(i, sweep.size()) printf("(%d %d)", sweep[i].ft, sweep[i].sd);
// 		printf("\n");


	}
	
// 	printf("%d %d (%d %d)\n", dm, sweep.size(), sweep.back().ft, sweep.back().sd);
	if(!dm){
		if(input.back().ft != n) dm = sweep.empty();
		else{
			dm = true;
			rep(i, sweep.size()) if(n >= sweep[i].ft && n <= sweep[i].sd) dm = false;
		}
	}
	
	if(!dm) printf("%d\n", 2*n-2);
	else printf("-1\n");
}