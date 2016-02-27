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
#define N 60000

char maze[N];
int mk[N], cont;
int n, m;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int get(int a, int b){
	return a * m + b;
}

int get(pii a){
	return get(a.ft, a.sd);
}

pii pilha[N];

void search(int x, int y){
	int sp = 1;
	pilha[0] = mp(x, y);
	mk[get(x,y)] = cont;

	while(sp--){
		pii at = pilha[sp];
		rep(d, 4){
			pii nt = mp(at.ft + dx[d], at.sd + dy[d]);
			if(nt.ft >= 0 && nt.ft < n && nt.sd >= 0 && nt.sd < m && maze[get(nt)] == 'o' && mk[get(nt)] == -1) {
				mk[get(nt)] = cont;
				pilha[sp++] = nt;
			}
		}
	}
	++cont;
}

int conta(){
	cont = 0;
	rep(i, n*m) mk[i] = -1;

	rep(i, n) rep(j, m){
		pii at = mp(i,j);
		if(mk[get(i, j)] == -1 && maze[get(i,j)] == 'o') search(i, j);
	}

	return cont;
}

int main(){
	int t;
	scanf("%d", &t);

	while(t--){
		scanf("%d%d", &n, &m);
		rep(i, n) scanf("%s", maze+i*m);
		conta();
		int tot = 0, ok = 0;
		rep(i, n) rep(j, m) if(mk[get(i,j)] != -1){
			++tot;
			if(mk[get(i,j)] == 0) ++ok;
		}

		double expected = 0, p = 1.0;
		rep(i, tot-ok+1){
			
		}

		printf("%lf\n", expected);

	}
}






