#include <cstdio>


int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		int n, cont = 0, soma = 0;
		scanf("%d", &n);
		
		while(n--){
			int tmp;
			scanf("%d", &tmp);
			if(tmp > 1) ++cont;
			soma ^= tmp;
		}
		
		if( (cont && !soma) || (!cont && soma) )//segundo
			printf("Brother\n");
		else
			printf("John\n");
		
		
	}
	
}
