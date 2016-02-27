#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
#define N 5010

vector<int> adj[N];
int n, w;
pii pts[N];

pii operator-(pii a, pii b){
	return mp(a.ft - b.ft, a.sd - b.sd);
}

int operator*(pii a, pii b){
	return a.ft * b.ft + a.sd * b.sd;
}

int operator!(pii a){
	return a * a;
}

int pilha[N];
int mk[N], caso;

bool can(double radius){
	++caso;
	rep(i, n) adj[i].clear();
	int sp = 0;
	
	rep(i, n){
		fr(j, i+1, n){
			if(!(pts[i] - pts[j]) <= 4 * radius * radius) adj[i].pb(j), adj[j].pb(i);
		}
	}
	
	double sup = w - radius;
	rep(i, n){
		if(pts[i].sd - radius < sup && pts[i].sd + radius >= sup){
			pilha[sp++] = i;
			mk[i] = caso;
		}
	}
	
	double inf = radius;
	while(sp--){
		int at = pilha[sp];
		if(pts[at].sd - radius <= inf && pts[at].sd + radius > inf) return false;
		rep(i, adj[at].size()){
			int nt = adj[at][i];
			if(mk[nt] != caso){
				mk[nt] = caso;
				pilha[sp++] = nt;
			}
		}
	}
	
	return true;
}

int main(){
	while(scanf("%d%d", &w, &n) == 2 && (w|n)){
		rep(i, n) scanf("%d %d", &pts[i].ft, &pts[i].sd);
		
		double ini = 0, fim = 10.0 + w/2.0;
		rep(it, 40){
			double mid = (ini+fim)/2;
			if(can(mid)){
				ini = mid;
			}
			else{
				fim = mid;
			}
		}
		
		printf("%.3lf\n", (ini+fim));
	}
}



