#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define mp make_pair
#define x first
#define y second
typedef pair<int,int> pii;
#define N 120000
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) Fr(i,0,n)


pii input[N];
set<pii> seq[N];
int len, n;

bool menor(pii a, pii b){
	return a.x < b.x && a.y < b.y;
}

int bs(pii par){
	int ini = 1, fim = len, best = 0;
	
	while(ini <= fim){
		int meio = (ini+fim)/2;
		
		set<pii>::iterator it = seq[meio].lower_bound(par);
		if((it != seq[meio].begin() && menor(*(--it), par)) || (it != seq[meio].begin() && menor(*(--it), par))){
			best = meio;
			ini = meio + 1;
		}else
			fim = meio - 1;
	}
	
	return best;
}

bool coberto(pii pivo, pii doSet){
	if(menor(pivo, doSet)) return true;
	if(doSet.x == pivo.x && pivo.y < doSet.y) return true;
	if(doSet.y == pivo.y && pivo.x < doSet.x) return true;
	return false;
}

void insere(int index, pii par){
	set<pii>::iterator it = seq[index].lower_bound(par);
	vector<pii> tmp;

	if(it != seq[index].begin()){
		--it;
		if(coberto(*it, par)) 
			return;
	}
	
	it = seq[index].lower_bound(par);

	while(it != seq[index].end() && coberto(par, *it)){
		tmp.push_back(*it);
		++it;
	}
	
	rep(i, tmp.size())
		seq[index].erase(tmp[i]);

	seq[index].insert(par);
}

void faz(){
	len = 0;
	
	
	rep(i, n){
		int index = bs(input[i]) + 1;
		
		if(index > len)
			++len;
		insere(index, input[i]);
	}
}


int main(){
	while(scanf("%d", &n) == 1 && n >= 2){
		rep(i, n + 1) seq[i].clear();
		
		rep(i, n){
			int u, v;
			scanf("%d%d", &u, &v);
			input[i] = mp(u,v);
		}
		
		faz();
		printf("%d\n", len);
	}
}

