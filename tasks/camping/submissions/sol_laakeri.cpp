#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

const int N=1<<12;

char s[N+10][N+10];

int sq[N+10][N+10];

int st[2*N+10][2*N+10];

void setv2(int i, int ii, int x1, int x2, int v, int stl, int str){
	if (x2<stl||str<x1) return;
	if (x1<=stl&&str<=x2){
		st[i][ii]=max(st[i][ii], v);
	}
	else{
		int m=(stl+str)/2;
		setv2(i, ii*2, x1, x2, v, stl, m);
		setv2(i, ii*2+1, x1, x2, v, m+1, str);
	}
}

void setv1(int i, int y1, int y2, int x1, int x2, int v, int stl, int str){
	if (y2<stl||str<y1) return;
	if (y1<=stl&&str<=y2){
		setv2(i, 1, x1, x2, v, 0, N-1);
	}
	else{
		int m=(stl+str)/2;
		setv1(i*2, y1, y2, x1, x2, v, stl, m);
		setv1(i*2+1, y1, y2, x1, x2, v, m+1, str);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,q;
	cin>>n>>m;
	assert(n<=N&&m<=N);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> s[i][j];
        }
    }
	for (int i=n-1;i>=0;i--){
		for (int ii=m-1;ii>=0;ii--){
			if (s[i][ii]=='#'){
				sq[i][ii]=0;
			}
			else{
				assert(s[i][ii]=='.');
				sq[i][ii]=min(min(sq[i+1][ii], sq[i][ii+1]), sq[i+1][ii+1])+1;
			}
		}
	}
	for (int i=0;i<n;i++){
		for (int ii=0;ii<m;ii++){
			setv1(1, i, i+sq[i][ii]-1, ii, ii+sq[i][ii]-1, sq[i][ii], 0, N-1);
		}
	}
	for (int i=0;i<N*2;i++){
		for (int ii=0;ii<N*2;ii++){
			if (i<N){
				st[i*2][ii]=max(st[i*2][ii], st[i][ii]);
				st[i*2+1][ii]=max(st[i*2+1][ii], st[i][ii]);
			}
			if (ii<N){
				st[i][ii*2]=max(st[i][ii*2], st[i][ii]);
				st[i][ii*2+1]=max(st[i][ii*2+1], st[i][ii]);
			}
		}
	}
	cin>>q;
	for (int i=0;i<q;i++){
		int y,x;
		cin>>y>>x;
		y--;
		x--;
		cout<<st[N+y][N+x]*st[N+y][N+x]<<'\n';
	}
}
