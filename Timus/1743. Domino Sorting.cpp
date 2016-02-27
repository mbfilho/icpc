#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define N 100100

pii pts[N];
pii seq[N];
int n;

int main(){
	scanf("%d", &n);
	rep(i, n){
		scanf("%d%d", &pts[i].first, &pts[i].second);
		if(pts[i].first > pts[i].second) swap(pts[i].first, pts[i].second);
		pts[i].second *= -1;
	}

	sort(pts, pts + n);
	int fim = n-1, ini = 0;
	bool dm = false;
	rep(i, n){
		pts[i].second *= -1;
		if(!ini || (pts[i].first >= seq[ini-1].first && pts[i].second <= seq[ini-1].second)){
			seq[ini++] = pts[i];
		}else{
			swap(pts[i].first, pts[i].second);
			if(fim+1 == n || (pts[i].first <= seq[fim+1].first && pts[i].second >= seq[fim+1].second)){
				seq[fim--] = pts[i];
			}else{
				dm = true;
				break;
			}
		}
	}

	rep(i, n){
		if(i && (seq[i].first < seq[i-1].first || seq[i].second > seq[i-1].second)) dm = true;
	}
	
	if(dm) printf("NO\n");
	else{
		printf("YES\n");
		rep(i, n)
			printf("%d %d\n", seq[i].first, seq[i].second);
	}


}


