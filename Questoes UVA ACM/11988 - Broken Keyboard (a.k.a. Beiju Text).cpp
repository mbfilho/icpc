#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100

deque<char> str;
char buf[N];

int main(){
	while(scanf("%s", buf) == 1){
		while(!str.empty()) str.pop_back();
		int prt = 0, tam = strlen(buf);
		
		while(prt < tam){
			while(prt < tam && buf[prt] != '[' && buf[prt] != ']')
				str.push_back(buf[prt++]);
			
			if(prt < tam && buf[prt] == '['){//home
				int fim = prt + 1;
				while(fim < tam && buf[fim] != '[' && buf[fim] != ']') ++fim;
				for(int i = fim - 1; i > prt; --i)
					str.push_front(buf[i]);
				prt = fim;
			}else if(prt < tam && buf[prt] == ']')//end
				++prt;
		}
		
		while(!str.empty()){
			printf("%c", str.front());
			str.pop_front();
		}
		printf("\n");
	}
}







