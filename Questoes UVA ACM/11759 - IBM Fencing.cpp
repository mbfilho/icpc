#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef pair<double,double> P;
#define N 600
#define pb push_back
#define mp make_pair
#define X first
#define Y second

P operator-(P a, P b){ return mp(a.X - b.X, a.Y - b.Y); }
double operator%(P a, P b){ return a.X * b.Y - a.Y * b.X; }
double operator!(P a){ return sqrt(a.X * a.X + a.Y * a.Y); }
double operator*(P a, P b){return a.X * b.X + a.Y * b.Y;}

struct Cerca{
	vector<P> pts;
	double peri;
	int in;
	bool metal;

	Cerca(){init();}
	
	bool engloba(P q){
		int ini, med, fim;
		if(pts.size() < 3){
			return false;
		}
		ini = 1;
		fim = pts.size()-1;
		while(fim-ini > 1){
			med = (ini + fim)/2;
		
			if((pts[med]-pts[0])%(q - pts[0]) >= 0){
				ini = med;
			}else{
				fim = med;
			}
		}
		if( (pts[ini]-pts[0])%(q - pts[0]) >= 0 &&
			(pts[ini+1]-pts[ini])%(q - pts[ini]) >= 0 &&
				(pts[0]-pts[ini+1])%(q - pts[ini+1]) >= 0){		
			return true;
		}else{
			return false;
		}
		
//		double sinal = 1;
//		int tam = pts.size();
//		rep(i, tam){
//			P p1 = pts[i] - pt, p2 = pts[(i+1) % tam] - pt;
//			double tmp = p1 % p2; 
//			if(i && tmp * sinal <= 1e-7) return false;
//			else{
//				if(tmp <= 1e-7) sinal = -1;
//				else sinal = 1;
//			}
//		}
//		

	}
	
	void init(){
		pts.clear();
		peri = 0;
		in = 0;
		metal = false;
	}
	
}cercas[N];

vector<int> adj[N];
int n;

void buildGraph(){
	rep(i, n){
		adj[i].clear();	
		
		rep(j, n){
			if(i != j && cercas[i].engloba(cercas[j].pts[0])){
				adj[i].pb(j);
				++cercas[j].in;
			}
		}
	}
}

int topological(){
	int grupos = 0;
	queue<int> fila;
	rep(i, n){
		if(!cercas[i].in){
			cercas[i].metal = true, fila.push(i);
			if(cercas[i].pts.size() > 2) 
			++grupos;
		}
	}
	
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		
		rep(i, adj[at].size()){
			int nt = adj[at][i];
			--cercas[nt].in;
			
			if(!cercas[nt].in){
				fila.push(nt);
				cercas[nt].metal = !cercas[at].metal;
			}
		}
	}
	
	return grupos;
}

int main(){
	int caso = 0;
	cout.sync_with_stdio(false);
	
	while(scanf("%d", &n) == 1 && n){
		++caso;
		rep(i, n) cercas[i].init();
		
		rep(i, n){
			int s;
			scanf("%d", &s);
			rep(p, s){
				P tmp;
				scanf("%lf %lf", &tmp.X, &tmp.Y);
				if(p){
					P vet = tmp - cercas[i].pts.back();
					cercas[i].peri += !vet;
				}
				cercas[i].pts.pb(tmp);
			}
			
			P vet = cercas[i].pts.back() - cercas[i].pts[0];
			cercas[i].peri += !vet;
		}
		
		buildGraph();
		int grupos = topological();
		double metal = 0, wood = 0;
		rep(i, n){
			if(cercas[i].metal) metal += cercas[i].peri;
			else wood += cercas[i].peri;
		}
		
		cout << "Case " << caso << ":" << endl;
		cout << "Total Number of Communities " << grupos << endl;
		cout << "Total Cost:" << endl;
	    cout.setf(ios::fixed,ios::floatfield);
	    cout.precision(8);
	    cout << "Steel Fence: " << (metal / 1e4) << " Million Yuan" << endl;
	    cout << "Wooden Fence: " << (50.0 * wood) / 1e6 << " Million Yuan" << endl << endl;
	}
}



