#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct Fenwick{
    T *tree, *input; 
    int siz;
    
    Fenwick(){ }
    Fenwick(int n){ setSize(n); }

    void setSize(int n){
        siz   = n;
        tree  = new T[siz + 5];
        input = new T[siz + 5];
    }
    void putItem(int idx, T data){ input[idx] = data, __update(idx, data);  }
    void __update(int idx, T data){
        for(; idx <= siz; idx += (idx & -idx)) tree[idx] += data;
    }
    void update(int idx, T data, bool add=false){
        if(add) __update(idx, data), input[idx] += data;
        else __update(idx, data - input[idx]), input[idx] = data; 
    }
    T query(int idx) { 
        T ret = 0;
        for(; idx ; idx -= (idx & -idx)) ret += tree[idx];
        return ret;
    }
    T query(int l, int r){ return query(r) - query(l - 1); }
};

Fenwick<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k; cin >> n >> m >> k;
    tree.setSize(n);
    for(int i=1;i<=n;i++){
        long long x; cin >> x;
        tree.putItem(i, x);
    }
    for(int i=0;i<m+k;i++){
        long long t, l, r; cin >> t >> l >> r;
        if(t == 1)tree.update(l, r);
        else cout << tree.query(l, r) << '\n';
    }
}
