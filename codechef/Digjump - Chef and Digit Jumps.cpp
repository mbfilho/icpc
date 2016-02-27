#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define reps(i, str) for(int i = 0; str[i]; ++i)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 100100

char input[N];
int n;
vector<int> pos[10];
int dist[N];

int main(){
	ios::sync_with_stdio(false);

	cin >> input;
	n = strlen(input);
	if(n == 1) cout << "0\n";
	else{
		memset(dist, -1, sizeof dist);
		_(n) pos[input[i]-'0'].pb(i);
		queue<int> fila;
		fila.push(0);
		dist[0] = 0;

		while(!fila.empty()){
			int at = fila.front();
			fila.pop();
			if(at == n-1) break;

			if(at && dist[at-1] == -1) fila.push(at-1), dist[at-1] = dist[at]+1;
			if(dist[at+1] == -1)  fila.push(at+1), dist[at+1] = dist[at] + 1;
			while(pos[input[at]-'0'].size()){
				int nt = pos[input[at]-'0'].back();
				pos[input[at]-'0'].pop_back();
				if(dist[nt] == -1) fila.push(nt), dist[nt] = 1 + dist[at];
			}
		}

		cout << dist[n-1] << endl;
	}

}
