#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100

int perm[N];
int n;

int main(){
	while(scanf("%d", &n) && n){
		int ind = 1, par = 2, impar = 1;
		while(par <= n){
			perm[ind] = par;
			++ind;
			par += 2;
		}
		while(impar <= n){
			perm[ind] = impar;
			++ind;
			impar += 2;
		}
		if( (n%6) != 2 && (n%6) != 3){
			printf("%d", perm[1]);
			fr(i, 2, n+1) printf(" %d",perm[i]);
			printf("\n");
		}else if(n%6 == 2){
			int ind = 1;
			fr(i, 1, n+1){
				if(perm[i] == 1) printf(" 3");
				else if(perm[i] == 3) printf(" 1");
				else if(perm[i] == 5) continue;
				else{
					if(i == 1) printf("%d", perm[i]);
					else printf(" %d", perm[i]);
				}
			}
			printf(" 5\n");
		}else if(n%6 == 3){
			int ind = 1;
			fr(i, 1, n+1){
				if(perm[i] == 2) continue;
				if(perm[i] == 1) printf(" 2");
				else if(perm[i] == 1 || perm[i] == 3)continue;
				else{
					if(i == 2) printf("%d", perm[i]);
					else printf(" %d", perm[i]);
				}
			}
			printf(" 1 3\n");
		}
	}
}




