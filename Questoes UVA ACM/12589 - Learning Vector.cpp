#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for( __typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef pair<int,int> pii;
typedef long long ll;
#define oo 100000000
#define X first
#define Y second
#define mp make_pair
#define N 60

pii pts[N];

int n, k;

bool cmp(const pii& a, const pii& b){
	int prod = a.X * b.Y - a.Y * b.X;
	
	if(prod)
		return prod < 0;
	return a.X * a.X + a.Y * a.Y < b.X * b.X + b.Y * b.Y;
}

int pd[N*N][N][N];
int mk[N*N][N][N], caso;

int memo(int y, int ind, int left){
	if(!left) return 0;
	if(ind == n) return -oo;
	
	int& rec = pd[y][ind][left];
	if(mk[y][ind][left] == caso) return rec;
	mk[y][ind][left] = caso;
	
	rec = 2 * (pts[ind].Y + y) * pts[ind].X - pts[ind].Y * pts[ind].X + memo(y + pts[ind].Y, ind+1, left-1);
	rec = max(rec, memo(y, ind+1, left));
	
	return rec;
}


int main(){
	int t;
	scanf("%d", &t);
	caso = 0;
	
	while(t--){
		++caso;
		scanf("%d%d", &n, &k);
		rep(i, n) scanf("%d%d", &pts[i].X, &pts[i].Y);
		sort(pts, pts + n, cmp);
		printf("Case %d: %d\n", caso, memo(0, 0, k));
	}	
}

