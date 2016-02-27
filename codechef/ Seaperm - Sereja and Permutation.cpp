#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 3000
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back
#define ft first
#define sd second

int input[N];
int main(){
	int t;
	scanf("%d", &t);

	while(t--){
		int n, k, s;
		scanf("%d%d%d", &n, &k, &s);
		rep(i, n) scanf("%*d");
		rep(i, n) input[i] = i+1;
		random_shuffle(input, input + n);

		printf("%d", input[0]);
		fr(i, 1, n) printf(" %d", input[i]);
		printf("\n");
	}

}