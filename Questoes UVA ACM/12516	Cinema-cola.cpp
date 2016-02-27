//nem de longe a melhor solução
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 10000

vector<int> adj[N];

int scc[N], pilha[N], tempo[N];
int sp, tmp, cont;

int dfs(int no){
    pilha[sp++] = no;
    int low = tempo[no] = tmp++;
    
    rep(i, adj[no].size()){
        int nt = adj[no][i];
        if(~scc[nt]) continue;
        if(~tempo[nt])
            low = min(low, tempo[nt]);
        else
            low = min(low, dfs(nt));
    }
    
    if(low == tempo[no]){
        int aux;
        
        do{
            aux = pilha[--sp];
            scc[aux] = cont;
        }while(aux != no);
        ++cont;
    }
    
    return low;
}

void antes(){
    cont = 0;
    sp = 0;
    tmp = 0;

    memset(scc, -1, sizeof scc);
    memset(tempo, -1, sizeof tempo);
}

void add(int a, int b){
    adj[a].push_back(b);
    adj[b^1].push_back(a^1);
}

void setar(int a, bool val){
    if(val)
        add(2*a+1, 2*a);
    else
        add(2*a, 2*a+1);
}

int n, m, p;
bool jah[200][200];

int main(){
	
    while(cin >> n >> m && (n|m)){
    	memset(jah, false, sizeof jah);
    	
        rep(i, n){
            rep(j, m){
                adj[2*(i*m+j)].clear();
                adj[2*(i*m+j)+1].clear();
            }
        }
        
        int p;
        cin >> p;
        
        char buf[10];
        while(p--){
            cin >> buf;
            int r, c;
            r = buf[0] - 'A';
            sscanf(buf + 1, "%d", &c);
            cin >> buf;
            bool ehTrue = buf[0] == '-';
            --c;
            jah[r][c] = true;
            
            setar(r * m + c, ehTrue);
            //printf("(%d,%d %d\n", r, c, ehTrue);
        }
        
          
        cin >> p;
        
        while(p--){
            int i, j;
            cin >> buf; 
            i = buf[0] - 'A';
            sscanf(buf + 1, "%d", &j);
            --j;
            
            //printf("(%d) -> %d\n", 2*(i * m + j), 2*(i*m + j-1));
//            printf("%d -> %d\n", 2*(i*m + j) + 1);
            if(j && jah[i][j-1])
                add(2*(i * m + j), 2*(i*m + j-1));
            if(j != m-1 && jah[i][j+1])
                add(2*(i*m + j) + 1, 2*(i*m + j + 1) + 1);
               jah[i][j] = true;
        }
        
        antes();
        bool sat = true;
        rep(i, n){
            if(!sat) break;
            
            rep(j, m){
                if(scc[2*(i*m + j)] == -1){
                    sp = 0;
                    dfs(2*(i*m + j));
                }
                if(scc[2*(i*m + j) + 1] == -1){
                    sp = 0;
                    dfs(2*(i*m + j) + 1);
                }
                if(scc[2*(i*m + j)] == scc[2*(i*m + j) + 1]){
                    sat = false;
                    break;
                }
            }
        }
        
        if(sat) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}

