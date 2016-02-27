#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 5000

bool marc[N];
char buf[N];
int n;

int main(){
	while(scanf("%d", &n) != EOF && n){
		memset(marc, 0, sizeof marc);
		scanf("%s", buf);
		char* prt = buf, *tmp;
		
		while(*prt){
			tmp = prt;
			while(*prt && *prt != ',') ++prt;
			if(*prt != 0){
				*prt = 0;
				++prt;
			}
//			printf( "|%s| %c\n", tmp, *prt);
			
			int a, b, qtd;
			sscanf(tmp, "%d%n", &a, &qtd);
			tmp += qtd;
//			printf( "> %d %d\n", a, qtd);
			if(*tmp == '-'){
				++tmp;
				sscanf(tmp, "%d", &b);
				b = min(b, n);
				
				if(a <= b){
					a = max(1, a);
					for(int i = a; i <= b; ++i) marc[i] = true;
//					printf( "(%d-%d)\n", a, b);
				}
			}else{
				if( a >= 1 && a <= n ) marc[a] = true;
//				printf( "(%d) %c\n", a, *prt );
			}
			if(*prt == 0) break;
		}
		int cnt = 0;
		for(int i = 1; i <= n; ++i){
			if(marc[i]){
//				printf( ">%d\n", i);
				++cnt;
			}
		}
		printf( "%d\n", cnt);
		
	}
}




