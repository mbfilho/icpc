#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b;++i)
#define rep(i, n) fr(i,0,n)
#define X first
#define Y second
#define pb push_back
typedef pair<int, int> P;
#define mp make_pair
#define N 60000

int n;
P pts[N];
vector<P> cont;

int operator!(P a){
	return a.X * a.X + a.Y * a.Y;
}

int read(char num[100]){
	int tam = strlen(num);
	int ind = 0;
	bool neg = (num[0] == '-');
	int ret = 0;
	
	while(ind < tam && num[ind] != '.') ++ind;
	
	if(ind < tam){
		++ind;
		rep(i, 3){
			ret *= 10;
			if(ind < tam) ret += num[ind] - '0';
			++ind;
		}
	}
	if(neg) ret = 1000 - ret;
	
	return ret;
}

int main(){
	scanf("%d", &n);
	rep(i, n){
		char a[100], b[100];
		scanf("%s %s", a, b);
		
		pts[i] = mp(read(a),read(b));
	}
	
	rep(i, n){
		int x[] = {pts[i].X, pts[i].X - 1000};
		int y[] = {pts[i].Y, pts[i].Y - 1000};
		
		rep(a, 2){
			if(a && x[1] == x[0]) break;
			
			rep(b, 2){
				if(b && y[1] == y[0]) break;
				cont.pb(mp(x[a], y[b]));
			}
		}
	}
	
	int qtd = 0;
	int dist;
	sort(cont.begin(), cont.end());
	int ini = 0;
	while(ini < cont.size()){
		int fim = ini;
		while(fim < cont.size() && cont[fim] == cont[ini]) ++fim;
		int nqtd = fim - ini;
		if(nqtd > qtd || (nqtd == qtd && !cont[ini] < dist)){
			qtd = nqtd;
			dist = !cont[ini];
		}
		ini = fim;
	}
	printf("%d %.5lf\n", qtd, sqrt(dist/1e6));
}

