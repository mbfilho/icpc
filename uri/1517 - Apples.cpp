#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>    
#include <queue>
using namespace std;
#define mp make_pair
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 1110
#define ft first
#define sd second
 
typedef pair<int,int> pii;
int x[N], y[N], t[N], n, m, k;
int pd[N];
 
int d[21][21][21][21];
int dist(int a, int b){
    return d[x[a]][y[a]][x[b]][y[b]];
}
  
void bfs(pii ini){
    queue<pii> fila;
    fila.push(ini);
    d[ini.ft][ini.sd][ini.ft][ini.sd] = 0;
     
    while(!fila.empty()){
        pii at = fila.front();
        fila.pop();
         
        fr(i, -1, 2){
            fr(j, -1, 2){
                pii nt = at;
                nt.ft += i, nt.sd += j;
                if(nt.ft >= 1 && nt.ft <= n && nt.sd >= 1 && nt.sd <= m &&  d[ini.ft][ini.sd][nt.ft][nt.sd] == -1){
                    d[ini.ft][ini.sd][nt.ft][nt.sd] = 1 + d[ini.ft][ini.sd][at.ft][at.sd];
                    fila.push(nt);
                }
            }
        }
    }
}
 
 
int main(){     
     
    while(cin >> n >> m >> k && (n|m|k)){
        rep(i, k) cin >> x[i] >> y[i] >> t[i];
        int a, b;
        cin >> a >> b;
                 
        int ans = 0;
         
        memset(d, -1, sizeof d);
        fr(i, 1, n+1) fr(j, 1, m+1) bfs(mp(i, j));
         
        for(int i = k - 1; i >= 0; --i){
            int best = 0;
            for(int j = i + 1; j < k; ++j){
                if(dist(i, j) + t[i] <= t[j]){
                    best = max(best, pd[j]);
                }
            }
            pd[i] = 1 + best;
            //cout << i << " " << pd[i] << endl;
        }
         
        rep(i, k){
            if(d[a][b][x[i]][y[i]] <= t[i])
                ans = max(ans, pd[i]);
        }
         
        cout << ans << endl;
         
    }
     
}