#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 200
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define T 5*90000
typedef pair<int,int> pii;
typedef set<pii>::iterator SI;


int maior[T], cov[T];

int query(int no, int x, int y, int ini, int fim){
	if(ini > y || fim < x) return 0;
	
	if(ini <= x && fim >= y){
		return cov[no];
	}else{
		int mid = (x+y)/2;
		return max(query(2*no, x, mid, ini, fim), query(2*no+1, mid+1, y, ini,fim)) + cov[no];
	}
}

void insert(int no, int x, int y, int ini, int fim){
	if(ini > y || fim < x) return;
	
	if(ini <= x && fim >= y){
		++cov[no];
	}else{
		int mid = (x+y)/2;
		query(2*no, x, mid, ini, fim);
		query(2*no+1, mid+1, y, ini, fim);
	}
}

int who[N];
struct Evt{
	int pt, i;
	bool ini;
	Evt(){}
	Evt(int x, int quem, bool eh){
		pt = x;
		ini = eh;
		i = quem;
	}
	
	bool operator<(const Evt& ot) const{
		if(pt != ot.pt) return pt < ot.pt;
		return ini && !ot.ini;
	}
};
vector<Evt> E;
pii pts[N];
int c[N], n, k;
char watch[N];
int _max[N];

bool ehSat(){
	E.clear();
	rep(i, n){
		if(watch[i] == '1') E.pb(Evt(pts[i].X, i, true)), E.pb(Evt(pts[i].Y, i, false));
	}
	sort(E.begin(), E.end());
	set<pii> caras;
	rep(i, k) caras.insert(mp(0, i)), _max[i] = 0;
	
	int at = 0, tam = E.size();
	while(at < tam){
		int fim = at;
		while(fim < tam && E[fim].ini && E[fim].pt == E[at].pt){
			SI livre = caras.upper_bound(mp(c[E[fim].i], 10000000));

			if(livre != caras.begin()){
				--livre;
				who[E[fim].i] = livre -> Y;
				_max[livre->Y] = max(_max[livre->Y], c[E[fim].i]);
				caras.erase(livre);
			}else{
				return false;
			}
			++fim;
		}
		
		while(fim < tam && !E[fim].ini && E[fim].pt == E[at].pt){
			caras.insert(mp(_max[who[E[fim].i]], who[E[fim].i]));
			++fim;
		}
		at = fim;
	}
	return true;
}

int main(){
	scanf("%d%d", &n, &k);
	rep(i, n) watch[i] = '0';
	
	rep(i, n){
		int a, b;
		scanf("%d%d%d", &a, &b, c+i);
		pts[i] = mp(a, b-1);
		
		if(query(1, 0, 90000, a, b-1) + 1 <= k){
			watch[i] = '1';
			if(ehSat())
				insert(1, 0, 90000, a, b-1);
			else watch[i] = '0';
		}
	}
	watch[n] = 0;
	printf("%s\n", watch);
}

