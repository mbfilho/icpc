#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define X first
#define Y second
#define pb push_back
typedef pair<int,int> P;
#define N 10

P pivo, pts[N], pilha[N];
int sp, n, m;
double soma[1<<N], PI = acos(-1);

int operator*(P a, P b){
	return a.X * b.X + a.Y * b.Y;
}

double operator!(P a){
	return sqrt(a*a);
}

P operator-(P a, P b){
	return mp(a.X - b.X, a.Y - b.Y);
}

int operator%(P a, P b){
	return a.X * b.Y - a.Y * b.X;
}

bool cmp(P a, P b){
	P aa = a - pivo, bb = b - pivo;
	int tmp = aa % bb;
	if(tmp) return tmp > 0;
	return (aa*aa) < (bb*bb);
}

void convex(int msk){
	sp = 0;
	if(!msk) return;
	
	vector<P> tmp;
	rep(i, n){
		if(msk & (1<<i)) tmp.pb(pts[i]);
	}
	
	
	pivo = tmp[0];
	rep(i, tmp.size()){
		P at = tmp[i];
		if(at.Y < pivo.Y || (at.Y == pivo.Y && at.X < pivo.X)) pivo = at;
	}
	sort(tmp.begin(), tmp.end(), cmp);
	pilha[sp++] = tmp[0];

	fr(i, 1, tmp.size()){
		P at = tmp[i];
		
		while(sp > 1 && (pilha[sp-1] - pilha[sp-2]) % (at - pilha[sp-2]) < 0) --sp;
		pilha[sp++] = at;
	}
	
}

void peri(int msk){
	soma[msk] = 0;
	if(!sp) return;
	
	rep(i, sp){
		soma[msk] += !(pilha[(i+1)%sp] - pilha[i]);
	}
	soma[msk] += 2 * PI * m;
}

double pd[1<<N];
double memo(int msk){
	if(!msk) return 0;
	
	double &rec = pd[msk];
	if(rec == rec) return rec;
	rec = 1e50;
	
	for(int m = msk; m > 0; m = msk & (m - 1)){
		rec = min(rec, soma[m] + memo((~m) & msk));
	}
	
	return rec;
}

int main(){
	int caso = 0;
	while(scanf("%d%d", &n, &m) == 2 && (n|m)){
		rep(i, n) scanf("%d%d", &pts[i].X, &pts[i].Y);
		rep(i, 1<<n){
			convex(i);
			peri(i);
		}
		
		memset(pd, -1, sizeof pd);
		printf("Case %d: length = %.2lf\n", ++caso, memo((1<<n)-1));
	}
}






