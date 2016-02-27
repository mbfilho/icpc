#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<double, pair<double,double> > Eq;
#define ft first
#define sd second
#define A ft
#define B sd.ft
#define C sd.sd
#define mp make_pair
#define pb push_back
#define N 100
#define EPS 1e-7
#define conj kjshdfkhd

double T;
int e, n;
int esta[N*N], caso = 1;
int conj[N];

struct Evt{
	int e[2];
	double t;
	
	bool operator<(const Evt& ot) const{
		return t < ot.t;
	}
};
vector<Evt> eventos;

struct P{
	double pt[3], v[3];
	P(){}
	P(double a, double b, double c){
		pt[0] = a;
		pt[1] = b;
		pt[2] = c;
	}
}pontos[N];

double eval(Eq q1, double t){
	return q1.A * t * t + q1.B * t + q1.C;
}

double sq(double x){ return x * x; }
int cmp(double a, double b){
	if(abs(a-b) < 1e-7) return 1;
	return 0;
}


struct E{
	int p[2];
	
	Eq get() const{
		P pts[] = {pontos[p[0]], pontos[p[1]]};
		double a = 0, b = 0, c = 0;	
		rep(i, 3) a += sq(pts[0].v[i] - pts[1].v[i]);
		rep(i, 3) b += 2 * (pts[0].pt[i] - pts[1].pt[i]) * (pts[0].v[i] - pts[1].v[i]);
		rep(i, 3) c += sq(pts[0].pt[i] - pts[1].pt[i]);
		
		return mp(a, mp(b,c));
	}	
	
	bool operator<(const E& ot) const{
		Eq q1 = get(), q2 = ot.get();
		double t1 = eval(q1, T), t2 = eval(q2, T);
		return t1 < t2;
	}
}edges[N*N];


vector<double> solve(double a, double b, double c){
	vector<double> resp;
	if(cmp(a,0)){
		if(!cmp(b,0)){
			double t =  -c/b;
			if(t >= 0)
				resp.pb(t);
		}
	}else{
		double delta = (b*b - 4*a*c);
		if(delta >= 0){
			delta = sqrt(delta);
			double t1 = (-b + delta)/(2*a), t2 = (-b - delta)/(2*a);
			if(t1 >= 0) resp.pb(t1);
			if(t2 >= 0) resp.pb(t2);
		}
	}
	return resp;
}

vector<double> solve(int e1, int e2){
	Eq eq1 = edges[e1].get(), eq2 = edges[e2].get();
	Eq res = mp(eq1.A - eq2.A, mp(eq1.B - eq2.B, eq1.C - eq2.C));
	return solve(res.A, res.B, res.C);
}

int find(int a){
	if(conj[a] != a) conj[a] = find(conj[a]);
	return conj[a];
}

void unir(int u, int v){
	conj[find(u)] = find(v);
}

int ord[N*N];
bool compEdges(int a, int b){
	return edges[a] < edges[b];
}

int tree[N];
bool mst(double t){
	bool mudou = false;
	T = t + EPS;
	rep(i, n) conj[i] = i;
	sort(ord, ord + n+1, compEdges);
	
	int c= 0;
	rep(i, e){
		int u = edges[ord[i]].p[0], v = edges[ord[i]].p[1];
		if(find(u) != find(v)){
			unir(u, v);
			if(esta[ord[i]] != caso) mudou = true;
			esta[ord[i]] = caso+1;
			tree[c++] = ord[i];
		}
		if(c==n-1) break;
	}
	++caso;
	if(c != n-1) throw 1;
	return mudou;
}

int sweep(){
	T = 0;
	eventos.clear();
	int cont = 0;
	rep(i, e){
		fr(j, i+1, e){
			vector<double> tmp = solve(i, j);
			rep(k, tmp.size()){
				tmp[k] += 1e-7;
				if(tmp[k] < 0) continue;
				Evt x;
				x.e[0] = i; x.e[1] = j;
				x.t = tmp[k];
				eventos.pb(x);
			}
		}
	}
	sort(eventos.begin(), eventos.end());

	rep(i, e) ord[i] = i;
	sort(ord, ord + e, compEdges);
	mst(0);
	rep(i, eventos.size()){
		int u = eventos[i].e[0], v = eventos[i].e[1];
		if((esta[u] == caso) xor (esta[v] == caso)){
			rep(j, n-1) ord[j] = tree[j];
			ord[n] = (esta[u] == caso) ? v : u;

			bool mudou = mst(eventos[i].t);
			if(mudou){++cont;}
		}
	}	
	
	return cont;
}

int main(){
	int cas = 0;
	memset(esta, 0, sizeof esta);
	
	while(scanf("%d", &n) == 1){
		rep(i, n){
			rep(j, 3) scanf("%lf", &pontos[i].pt[j]);
			rep(j, 3) scanf("%lf", &pontos[i].v[j]);
		}
		e = 0;
		rep(i, n){
			fr(j, i+1, n){
				edges[e].p[0] = i, edges[e].p[1] = j;
				e++;
			}
		}
		printf("Case %d: %d\n", ++cas, sweep()+1);
	}
}




