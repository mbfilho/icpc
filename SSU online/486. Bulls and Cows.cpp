#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);

	int t, q;
	bool m[10];
	bool n[10];
	string a, b;
	cin >> a >> b;
	
	for( int i=0; i<10; i++ ){
		n[ i ] = m[ i ] = false;		
	}
	
	t=0;
	for( int i=0; i<4; i++ ){
		if( a[i] == b[i] )
			t++;
		n[a[i]-'0'] = true;
		m[b[i]-'0'] = true;
	}
	cout << t << " ";
	
	q=0;	
	for( int i=0; i<10; i++ ){
		if( n[i] == true && m[i] == true )
			q++;
	}
	
	cout << (q-t) << endl;
	
	return 0;
}

