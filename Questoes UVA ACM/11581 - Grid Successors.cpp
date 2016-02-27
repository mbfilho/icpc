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

#define LIM (1<<11)
int prox[LIM];
bool mk[LIM];
int tempo[LIM], state[LIM];
bool reach[LIM];

bool valid(int a, int b){
	return a >= 0 && a < 3 && b >= 0 && b < 3;
}

int get(int num, int x, int y){
	if(num & (1 << (8 - (x*3 + y)))) return 1;
	return 0;
}

void bfs(int num){
	while(!mk[num]){
		mk[num] = true;
		int nt = 0;

		rep(i, 3) rep(j, 3){
			int dx[] = {1, -1, 0, 0};
			int dy[] = {0, 0, 1, -1};
			int sum = 0;

			rep(d, 4) if(valid(i+dx[d], j + dy[d])){
				sum ^= get(num, i+dx[d], j + dy[d]);
			}
			nt *= 2;
			if(sum) nt++;
		}
		prox[num] = nt;
		num = nt;
	}
}

int T;

int dfs(int no){
	int low = tempo[no] = T++;
	state[no] = 1;

	if(prox[no] == no) reach[no] = true;
	else if(state[prox[no]] == 1) low = min(low, tempo[prox[no]]);
	else if(state[prox[no]] == 0) low = min(low, dfs(prox[no]));

	if(low < tempo[no]) reach[no] = true;
	state[no] = 2;
	return low;
}

int main(){
	int t;
	scanf("%d", &t);
	memset(mk, false, sizeof mk);
	rep(i, (1 <<9)) bfs(i);
	memset(state, 0, sizeof state);
	memset(reach, false, sizeof reach);
	T = 0;
	rep(i, (1<<9)){
		if(state[i] == 0) dfs(i);
	}


	while(t--){
		int num = 0;
		char buf[10];
		rep(i, 3){
			scanf("%s", buf);
			rep(j, 3) num *= 2, num += buf[j] - '0';
		}
		int idx = 0, best = -1;

		memset(mk, false, sizeof mk);
		for(int i = num, j = 0; !mk[i]; i = prox[i], ++j){
			mk[i] = true;
			if(!reach[i]) best = j;
		}

		printf("%d\n", best);

	}
}









