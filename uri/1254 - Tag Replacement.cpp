#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)


char buf[1000], text[1000];
char tag[100];
char num[100];

char lower(char ch){
	if(ch >= 'A' && ch <= 'Z'){
		ch = ch - 'A' + 'a';
	}
	
	return ch;
}

int main(){
	while(gets(tag)){
		gets(num);
		gets(buf);
		
		int prt = 0;
		int tam = strlen(buf), pat = strlen(tag);
		
		int cnt = 0;
		int i = 0;
		int tn = strlen(num);
		while(i < tam){
			if(buf[i] == '<'){
				++cnt;
				text[prt++] = '<';
				++i;
			}
			else if(buf[i] == '>'){
				--cnt;
				text[prt++] = '>';
				++i;
			}
			else if(cnt){
				bool dm = false;
				int j, k;
				for(j = 0, k = i; j < pat && k < tam; ++j, ++k){
					if(lower(buf[k]) != lower(tag[j])){
						dm = true;
						break;
					}
				}
				
				if(!dm && j == pat){
					rep(x, tn) text[prt++] = num[x];
					i += pat;
				}else{
					text[prt++] = buf[i];
					++i;
				}
			}else{
				text[prt++] = buf[i++];
			}
		}
		
		text[prt] = 0;
		printf("%s\n", text);
	}
}




