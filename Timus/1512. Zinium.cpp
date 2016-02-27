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
	scanf("%d", &n);

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
		fr(i, 1, n+1)
			printf("%d %d\n", i, perm[i]);
	}else if(n%6 == 2){
		int ind = 1;
		fr(i, 1, n+1){
			if(perm[i] == 1){
				printf("%d 3\n", ind++);
			}else if(perm[i] == 3){
				printf("%d 1\n", ind++);
			}else if(perm[i] == 5) continue;
			else printf("%d %d\n", ind++, perm[i]);
		}
		printf("%d 5\n", n);
	}else if(n%6 == 3){
		int ind = 1;
		fr(i, 1, n+1){
			if(perm[i] == 2) continue;
			if(perm[i] == 1){
				printf("%d %d\n", ind++, 2);
			}else if(perm[i] == 1 || perm[i] == 3)
				continue;
			else{
				printf("%d %d\n", ind++, perm[i]); 
			}
		}
		
		printf("%d 1\n", n-1);
		printf("%d 3\n", n);
	}
	
	
}




