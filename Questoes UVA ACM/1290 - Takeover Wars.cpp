#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back
typedef long long ll;

int n, m;
vector<ll> seq[2];

int win(vector<ll>* s){
	int player = 1;
	
	while(s[0].size() && s[1].size()){
		if(s[player].back() > s[1-player].back()){
			s[1-player].pop_back();
		}else{
			int tam = s[player].size();
			 if(tam > 1){
			 	s[player][tam-2] += s[player].back();
			 	s[player].pop_back();
			 }
		}
		player = 1 - player;
	}
	
	rep(i, 2) if(s[i].size()){ return i; }
}

int main(){
	int caso = 0;
	
	while(scanf("%d%d", &n, &m) == 2){
		rep(i,2) seq[i].clear();
		rep(i,n){
			ll tmp;
			scanf("%lld", &tmp);
			seq[0].pb(tmp);
		}
		
		rep(i, m){
			ll tmp;
			scanf("%lld", &tmp);
			seq[1].pb(tmp);
		}
		
		rep(i, 2) sort(seq[i].begin(), seq[i].end());
		int winner = -1;
		
		//take
		if(seq[0].back() > seq[1].back()){
			vector<ll> s[] = {seq[0], seq[1]};
			s[1].pop_back();
			winner = win(s);
		}
		if(winner != 0 && seq[0].size() > 1){
			vector<ll> s[] = {seq[0], seq[1]};
			s[0][n-2] += s[0][n-1];
			s[0].pop_back();
			winner = win(s);
		}
		
		printf("Case %d: ", ++caso);
		if(winner == 0) printf("Takeover Incorporated\n");
		else printf("Buyout Limited\n");
	}
}


