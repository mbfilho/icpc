#include <bits/stdc++.h>

using namespace std;

#define fr(i,a,b) for(int i=a;i<b;++i)
#define rep(i,a) fr(i,0,a)
#define N 60
#define K 8
#define mp make_pair
#define oo 100000000

int mk[N][10000], mk2[N][10000];
int dist[N][10000];
int caso;

vector<pair<int,int> > adj[N];
int passe[N];
int atr[N];
int curto[K], longo[K];
int pot[20];

struct No{
	int mask;
	int no, dist;
	
	No(){}
	No(int city, int msk, int d){
		no = city;
		dist = d;
		mask = msk;
	}	
	
	
	bool operator<(const No& x) const{
		return !(dist < x.dist);
	}
};


int n, m, k;
//0 -> no visit, no pass
//1 -> no visit, with pass
//2 -> visit, X

int dij(int s){
	priority_queue<No> heap;
	
	heap.push(No(s, 0, 0));
	dist[s][0] = 0;
	mk2[s][0] = caso;
		
	while(!heap.empty()){
		No at = heap.top(); heap.pop();
		
		if(mk[at.no][at.mask] == caso) continue;
		mk[at.no][at.mask] = caso;
		
		int visit = 0, pass = 0, msk = at.mask;		
		int aux = 1;
		while(msk){
			if((msk % 3) == 1)
				pass |= aux;
			else if((msk % 3) == 2){
				visit |= aux;
				pass |= aux;
			}
			aux *= 2;
			msk /= 3;
		}
		
		if( (visit == pot[k] - 1) && at.no == s) return at.dist;
		
		int three = 1;
		msk = at.mask;
		rep(i, k){
			if((passe[at.no] & pot[i]) && (msk %  3) == 0){
				pass |= pot[i];
				at.mask += three;
			}
			three *= 3;
			msk /= 3;
		}
		
		three = 1;
		rep(i, k){
			if((atr[at.no] & pot[i]) && !(visit & pot[i])){
				int custo = at.dist;
				if(pass & pot[i]){
					custo += curto[i];
					msk = at.mask + three;
				}else{
					custo += longo[i];
					msk = at.mask + 2*three;
				}
				
				No nt(at.no, msk, custo);
				if(mk[nt.no][msk] == caso || (mk2[nt.no][msk] == caso && custo >= dist[nt.no][msk])){
					three *= 3;
					continue;
				}
				mk2[nt.no][msk] = caso;
				dist[nt.no][msk] = custo;
				heap.push(nt);
			}
			
			three *= 3;
		}
		
		rep(i, adj[at.no].size()){
			int nt = adj[at.no][i].first, c = adj[at.no][i].second;
			
			if(mk[nt][at.mask] == caso || (mk2[nt][at.mask] == caso && dist[nt][at.mask] <= at.dist + c)) continue;
			mk2[nt][at.mask] = caso;
			//if(nt == 4) printf( ">>>>>> at.no %d\n", at.no);
			dist[nt][at.mask] = at.dist + c;
			heap.push(No(nt, at.mask, at.dist + c));
		}
	}
	
	return -1;
}


int main(){
	int t;
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin >> t;
	rep(i, 20) pot[i] = 1 << i;
	memset(mk, 0, sizeof mk);
	memset(mk2, 0, sizeof mk2);
	caso = 0;
	
	rep(cas, t){
		++caso;
		cin >> n >> m >> k;
		rep(i, n+1){
			adj[i].clear();
			passe[i] = atr[i] = 0;
		}
		
		rep(i, m){
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].push_back(mp(b,c));
			adj[b].push_back(mp(a,c));
		}
		
		rep(i, k){
			int p, tt;
			cin >> p >> longo[i] >> curto[i];
			atr[p] |= pot[i];
			
			int qtd;
			cin >> qtd;
			while(qtd--){
				int x;
				cin >> x;
				passe[x] |= pot[i];
			}
		}
		
		int resp = dij(1);
		cout << "Case #" << (cas+1) << ": " << resp << endl;

		
	}
}
