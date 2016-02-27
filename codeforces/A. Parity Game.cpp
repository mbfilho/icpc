#include <cstdio>

char a[2000], b[2000];

int main(){
	scanf("%s %s", a, b);
	int ta = 0, tb = 0;
	
	for(int i = 0; a[i]; ++i) if(a[i] == '1') ++ta;
	for(int i = 0; b[i]; ++i) if(b[i] == '1') ++tb;
	
	if(ta % 2) ++ta;
	if(ta >= tb) printf("YES\n");
	else printf("NO\n");
	
		
}


