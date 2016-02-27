#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define V(i) 2*(i)
#define F(i) (2*(i)+1)
#define N 3100
#define mp make_pair
#define pb push_back
typedef pair<int,int> pii;

pii wed[N];
int dur[N], n;
vector<int> adj[N];

int tempo[N], pilha[N], cmp[N], cnt, sp, comps;
vector<int> caras[N];
vector<int> dag[N];
int in[N];
int val[N];

int dfs(int no){
	int low = tempo[no] = cnt++;
	pilha[sp++] = no;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(~cmp[nt]) continue;
		
		if(~tempo[nt]) low = min(low, tempo[nt]);
		else low = min(low, dfs(nt));
	}
	
	if(low == tempo[no]){
		int tmp;
		do{
			tmp = pilha[--sp];
			cmp[tmp] = comps;
			caras[comps].pb(tmp);
		}while(tmp != no);
		++comps;
	}
	
	return low;
}

void buildDag(){
	rep(i, comps){
		rep(j, caras[i].size()){
			int at = caras[i][j];
			rep(k, adj[at].size()){
				int nt = adj[at][k];
				if(cmp[nt] == i) continue;
				
				dag[cmp[nt]].pb(i);
				++in[i];
			}
		}
	}
}

void valorar(int no){
	rep(i, caras[no].size()){
		int at = caras[no][i];
		if(val[at] == -1){
			val[at] = 1;
			val[at^1] = 0;
		}
	}
}

void clear(){
	int t = 2*n;
	rep(i, t) in[i] = 0, val[i] = tempo[i] = cmp[i] = -1, dag[i].clear(), caras[i].clear(), adj[i].clear();
	sp = cnt = comps = 0;
}

char buf[100];

int minutos(){
	int h = 0, m = 0;
	h = (buf[0] - '0') * 10 + buf[1] - '0';
	m = (buf[3] - '0') * 10 + buf[4] - '0';
	
	return h * 60 + m;
}


bool inter(pii a, pii b){
	pii inter = mp(max(a.first, b.first), min(a.second, b.second));
	return inter.first <= inter.second;
}

void add(int a, int b){
	adj[a^1].pb(b);
	adj[b^1].pb(a);
}
void print(int a){
	printf("%02d:%02d", a/60, a % 60);
}

void printPii(pii a){
	print(a.first);
	printf(" ");
	print(a.second);
	printf("\n");
}

void printBegin(int i){
	printPii(mp(wed[i].first, wed[i].first + dur[i]));
}

void printEnd(int i){
	printPii(mp(wed[i].second-dur[i], wed[i].second));
}

int main(){
	while(scanf("%d", &n) == 1){
		clear();
		bool dm = false;
				
		rep(i, n){
			scanf("%s", buf);
			wed[i].first = minutos();
			scanf("%s", buf);
			wed[i].second = minutos();
			scanf("%d", dur + i);
		}

		rep(i, n){
			rep(j, i){
				int vi[] = {V(i), F(i)};
				int vj[] = {V(j), F(j)};
				pii ii[] = {mp(wed[i].first, wed[i].first + dur[i]-1), mp(wed[i].second - dur[i], wed[i].second-1)};
				pii jj[] = {mp(wed[j].first, wed[j].first + dur[j]-1), mp(wed[j].second - dur[j], wed[j].second-1)};
				
				rep(ki, 2){
					rep(kj, 2){
						if(inter(ii[ki], jj[kj]))
							add(vi[ki]^1, vj[kj]^1);
					}
				}
			}
		}

		rep(i, n){
			if(cmp[V(i)] == -1) dfs(V(i));
			if(cmp[F(i)] == -1) dfs(F(i));
			if(cmp[V(i)] == cmp[F(i)]){
				dm = true;
				break;
			}
		}

		if(!dm){
			buildDag();
			
			sp = 0;
			rep(i, comps){
				if(!in[i]) pilha[sp++] = i;
			}
			
			while(sp--){
				int at = pilha[sp];
				valorar(at);
				
				rep(i, dag[at].size()){
					int nt = dag[at][i];
					--in[nt];
					if(!in[nt]) pilha[sp++] = nt;
				}
			}
			
			printf("YES\n");
			rep(i, n){
				if(val[V(i)]) printBegin(i);
				else printEnd(i);
			}
		}else printf("NO\n");
	}	
}




