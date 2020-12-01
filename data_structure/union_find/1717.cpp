#include<bits/stdc++.h>

using namespace std;

struct UnionFind{
    int *uf;

    UnionFind() { }
    UnionFind(int n){ setSize(n); }
    void setSize(int n){
        uf = new int[n];
        for(int i=0;i<n;i++)uf[i] = -1;
    }
    int find(int a){ 
        if(uf[a] < 0)return a;
        return uf[a] = find(uf[a]);
    }
    bool same(int a, int b){ return find(a) == find(b); }
    bool merge(int a, int b){
        a = find(a), b = find(b);
        if(a == b)return false;
        uf[b] = a;
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m;  cin >> n >> m;
    UnionFind uf(n + 1);
    for(int i=0;i<m;i++){
        int a, b, c; cin >> a >> b >> c;

        if(a) cout << (uf.same(b, c) ? "YES" : "NO") << '\n';
        else uf.merge(b, c);
    }
}
