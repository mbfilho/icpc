#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define pb push_back
struct Edge{
    int u, v, custo;
    
    Edge(int a, int b, int c){
         u = a;
        v = b;
        custo = c;
    }
    
    Edge(){}
    
    bool operator<(const Edge& e)const{
        return custo < e.custo;
    }
};

struct Mst{
	vector<int> nos;
    vector<Edge> edges;
    int custo;
    int tmp;
    
    void clear(){
        custo = 0;
        tmp = 0;
        nos.clear();
        edges.clear();
    }
    
    void calc(){
        for(int i = 0; i < edges.size(); ++i){
			custo += edges[i].custo;	
			nos.pb(edges[i].u);
			nos.pb(edges[i].v);
        }
        sort(nos.begin(), nos.end());
        int tam = unique(nos.begin(), nos.end()) - nos.begin();
        nos.resize(tam);
    }
    
    bool operator<(const Mst& a) const{
        if(custo != a.custo) return custo < a.custo;
        if(nos.size() != a.nos.size()) return nos.size() < a.nos.size();
         
        for(int i = 0; i < nos.size(); ++i){
            if(nos[i] != a.nos[i]) return nos[i] < a.nos[i];
        }
        
        return false;
    }
}best;

vector<Edge> edges;
 int conj[30];
int id[30];
int pot[25];
int n, k, m, end;
int sources[30];


void makeSet(){
    for(int i = 0; i <= n; ++i)
        conj[i] = i;
}

int find(int a){
    if(conj[a] != a) conj[a] = find(conj[a]);
     
    return conj[a];
}

void unir(int a, int b){
    conj[find(a)] = find(b);
}


void kruskal(int mask){
    makeSet();
    Mst agpm;
    agpm.clear();
    
    sort(edges.begin(), edges.end());
     
    for(int i = 0; i < edges.size(); ++i){
        int u = edges[i].u, v = edges[i].v, c = edges[i].custo;
        if((mask & pot[u]) == 0 || (mask & pot[v]) == 0) continue;
        if(find(u) == find(v)) continue;
         
        unir(u,v);
        agpm.edges.pb(edges[i]);
        agpm.tmp |= pot[u];
        agpm.tmp |= pot[v];
    }
    
    agpm.calc();
    if(agpm.nos.size() - 1 !=  agpm.edges.size()) return;
    if((agpm.tmp & mask) != mask) return;
    if(agpm < best) best = agpm;
}

vector<int> adj[30];
int pred[30];

void dfs(int no, int pai){
	pred[no] = pai;
	for(int i = 0; i < adj[no].size(); ++i){
		int nt = adj[no][i];
		if(nt == pai) continue;
		dfs(nt, no);
	}
}

void makeAdj(){
	for(int i = 0; i < best.edges.size(); ++i){
		int u = best.edges[i].u, v = best.edges[i].v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
}

void print(int no){
	if(pred[no] == -1) printf( "%d\n", no);
	else{
		printf("%d-", no);
		print(pred[no]);
	}
}

int main(){
	int caso = 0;
    pot[0] = 1;
    for(int i = 1; i < 25; ++i) pot[i] = 2 * pot[i-1];
    
    while(scanf("%d", &n) != EOF && ~n){
    	edges.clear();
        best.clear();
        best.custo = 0x7fffffff;
        for(int i = 0; i <= n; ++i) adj[i].clear();
    	
        scanf( "%d%d", &end, &m);
        for(int i = 0; i < m; ++i){
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            edges.pb(Edge(u,v,c));
        }
        
        scanf("%d", &k);
        int juizes = 0;
        for(int i = 0; i < k; ++i){
            int j;
            scanf("%d", &j);
            sources[i] = j;
			juizes |= pot[j];
        }
        juizes |= pot[end];
        
        int x = 0;
        for(int i = 1; i <= n; ++i){
            if(juizes & pot[i]) continue;
            id[x++] = i;
         }
        
        for(int i = 0; i < pot[x]; ++i){
            int mask = juizes;
            for(int j = 0; j < x; ++j){
            	if(i & pot[j]) mask |= pot[id[j]];
            }
            
            kruskal(mask);
        }
        makeAdj();
        dfs(end, -1);
        printf( "Case %d: distance = %d\n", ++caso, best.custo);
        for(int i = 0; i < k; ++i){
        	printf("   ");
        	print(sources[i]);
        }
        printf( "\n");
    }
}
