#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 100100

map<int,int> rows[N];
int n, m, p;

bool can(int r, int j1, int j2){
	int v1 = j1 + (rows[r].count(j1) ? rows[r][j1] : 0);
	int v2 = j2 + (rows[r].count(j2) ? rows[r][j2] : 0);

	return v2 >= v1;
}

int cost(int j1, int j2){
	return max(0, j2 - j1);
}

int main(){
	ios::sync_with_stdio(false);

	cin >> n >> m >> p;

	_(p){
		int row, col;
		cin >> row >> col;
		rows[row][col]++;
	}

	fr(r, 1, n+1){
		if(rows[r].size() == 0) cout << m-1 << "\n";
		else{
			ll tot = 0;
			bool dm = false;
			vector<pii> row (rows[r].begin(), rows[r].end());
			if(row[0].ft != 1) row.insert(row.begin(), mp(1, 0));
			if(row.back().ft != m) row.pb(mp(m, 0));

			_(SIZE(row) - 1){
				pii a = row[i], b = row[i+1];
				if(!can(r, a.ft, a.ft+1)) dm = true;

				if(!can(r, b.ft-1, b.ft)) dm = true;
				if(dm) break;

				if(a.ft == b.ft - 1) tot += (b.ft + b.sd) - (a.ft + a.sd);
				else{
					tot += cost(a.ft+1, b.ft-1);
					tot += (a.ft + 1) - (a.ft + a.sd) + (b.ft + b.sd) - (b.ft - 1);
				}

			}

			if(dm) cout << "-1\n";
			else cout << tot << "\n";
		}
	}
}