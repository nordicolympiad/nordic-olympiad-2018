#include <bits/stdc++.h>
using namespace std;

char s[2020][2020];

int isempty(int y1, int y2, int x1, int x2){
	for (int i=y1;i<=y2;i++){
		for (int ii=x1;ii<=x2;ii++){
			if (s[i][ii]=='#') return 0;
			else assert(s[i][ii]=='.');
		}
	}
	return 1;
}

int main(){
	int n,m,q;
	cin>>n>>m;
	for (int i=0;i<n;i++){
        for (int j = 0; j < m; j++) {
            cin >> s[i][j];
        }
	}
    cin >> q;
	for (int i=0;i<q;i++){
		int y,x;
		cin>>y>>x;
		y--;
		x--;
		int v=0;
		for (int a=0;a<n;a++){
			for (int b=0;b<m;b++){
				for (int c=1;c<=n+m;c++){
					if (a+c>n||b+c>m) break;
					if (a<=y&&a+c>y&&b<=x&&b+c>x){
						if (isempty(a, a+c-1, b, b+c-1)){
							v=max(v, c);
						}
					}
				}
			}
		}
		cout<<v*v<<'\n';
	}
}
