#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 1000
int n, k, p;
pii chef[N], guy[N];

int main(){
	int t;
	scanf("%d", &t);

	while(t--){
		scanf("%d%d%d", &n, &k, &p);
		rep(i, k){
			scanf("%d%d", &chef[i].X, &chef[i].Y);
			if(chef[i].Y < chef[i].X) chef[i].Y += n;
		}

		rep(i, p){
			scanf("%d%d", &guy[i].X, &guy[i].Y);
			if(guy[i].Y < guy[i].X) guy[i].Y += n;
		}

		bool dm = false;
		rep(i, k){
			bool ok = false;
			rep(j, p){
				if(chef[i].X >= guy[j].X && chef[i].Y <= guy[j].Y){
					ok = true;
					break;
				}
				if(chef[i].X + n >= guy[j].X && chef[i].Y + n <= guy[j].Y){
					ok = true;
					break;
				}
			}

			bool inter = false;
			rep(j, p){
				if(chef[i].X >= guy[j].X && chef[i].X <= guy[j].Y) inter = true;
				if(chef[i].Y >= guy[j].X && chef[i].Y <= guy[j].Y) inter = true;
				if(chef[i].X + n >= guy[j].X && chef[i].X + n <= guy[j].Y) inter = true;
				if(chef[i].Y + n >= guy[j].X && chef[i].Y + n <= guy[j].Y) inter = true;
				
			}

			if(!ok && inter){
				dm = true;
				break;
			}
		}

		if(dm) printf("No\n");
		else printf("Yes\n");


	}
}

