#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> Ponto;
#define N 2000
#define P first
#define Q second
#define mp make_pair
#define pb push_back

map<string,int> mapa;
int cont;

set<ll> qualidade;
ll din;

vector<Ponto> nos[N];
int n;
char tmp[10000];

bool can(ll menor){
	ll b = din;
	
	for(int i = 0; i < cont; ++i){
		bool tem = false;
		for(int j = 0; j < nos[i].size(); ++j){
			if(nos[i][j].Q >= menor){
				tem = true;
				b -= nos[i][j].P;
				break;
			}
		}
		
		if(!tem) return false; 
	}
	
	return b >= 0;
}

int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		mapa.clear();
		qualidade.clear();
		for(int i = 0; i < N; ++i) nos[i].clear();
		
		scanf("%d %lld", &n, &din);
		cont = 0;
		
		Ponto p;
		for(int i = 0; i < n; ++i){
			scanf( "%s %*s %lld %lld", tmp, &p.P, &p.Q);
			
			if(mapa.find(tmp) == mapa.end())
				mapa[tmp] = cont++;

			int ind = mapa[tmp];
			nos[ind].pb(p);
			qualidade.insert(p.Q);
		}
		
		for(int i = 0; i < cont; ++i)
			sort(nos[i].begin(), nos[i].end());
		
		
		ll best;
		for(set<ll>::iterator it = qualidade.begin(); it != qualidade.end(); ++it){
			if(can(*it)) best = *it;
		}
		
		printf( "%lld\n", best);
		
		

	}
}

