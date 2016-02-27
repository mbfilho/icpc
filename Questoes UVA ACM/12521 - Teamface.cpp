#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 5100

int friends[N][N];
int caso;

vector<int> adj[N];
vector<int> team[N];
int has[N];
int lead[N];
int m, t;

bool back(int li, int ind){
	if(li == t) return true;
	if(team[li].size() == m){
		rep(i, m){
			int guy = team[li][i];
			int cont = 0;
			rep(j, adj[guy].size()){
				if(has[ adj[guy][j] ] != li) ++cont;
			}
			if(cont >= m/2) return false;
		}
		
		return back(li+1, 0);
	}
	if(adj[lead[li]].size() == ind) return false;

	int guy = adj[lead[li]][ind];
	bool dm = false;
	if(has[guy] == -1){
		rep(i, team[li].size()){
			int mate = team[li][i];
			if(friends[mate][guy] != caso){
				dm = true;
				break;
			}
		}
	
		if(!dm){
			team[li].push_back(guy);
			has[guy] = li;
			
			fr(i, ind+1, adj[lead[li]].size() +1){
				if(back(li, i)) return true;
			}
			team[li].pop_back();
			has[guy] = -1;
		}
	
	}
	
	if(!ind){
		fr(i, 1, adj[lead[li]].size() + 1){
			if(back(li, i)) return true;
		}
	}
	
	return false;
}

int size[N];
int n;
string name[N];

int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	
	memset(friends, 0, sizeof friends);
	caso = 0;
	
	while(cin >> t >> n && (n|t)){
		++caso;
		
		rep(i, n){
			team[i].clear();
			adj[i].clear();
			has[i] = -1;
		}
			
		rep(i, t){
			cin >> name[i] >> lead[i];
			--lead[i];
			has[lead[i]] = i;
			team[i].push_back(lead[i]);
		}
		
		
		rep(i, n){
			int guy, qtd;
			cin >> guy;
			--guy;
			cin >> size[guy] >> qtd;
			while(qtd--){
				int f;
				cin >> f;
				--f;
				adj[guy].push_back(f);
				friends[guy][f] = caso;
			}
		}
		
		cout << "Case " << caso << ":" << endl;
		
		m = n/t;
		while(m >= 2){
			if(back(0, 0)) break;
			--m;
		}
		
		int x[60];
		rep(i, t){
			memset(x, 0, sizeof x);
			cout << name[i] << endl;
			
			rep(j, m){
				int mate = team[i][j];
				++x[size[mate]];
			}
			
			rep(i, 60){
				if(x[i])
					cout << i << " " << x[i] << endl;
			}
			
		}
	}
}


