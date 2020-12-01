#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 5;
template<typename T>
struct FenwickRU{ // Fenwick Range Update
    T tree[MAX], add[MAX], mul[MAX], input[MAX];
    int siz;

    FenwickRU(){ } 
    FenwickRU(int n) { setSize(n); }
    void setSize(int n){
        siz   = n;
    }
    void putItem(int idx, T data) { update(idx, idx, data), input[idx] = data; }
    void __update(int idx, T _mul, T _add){
        for(;idx <= siz;idx += idx & -idx){
           add[idx] += _add;
           mul[idx] += _mul;
        }
    }
    void update(int l, int r, T data){
        __update(l, data, (l-1)*-data);
        __update(r+1, -data, data*r);
    }
    T query(int idx){
        T __add = 0, __mul = 0;
        for(int i=idx; i; i -= i & -i){
            __add += add[i];
            __mul += mul[i];
        }
        return __mul * idx + __add;
    }
    T query(int l, int r){
        return query(r) - query(l - 1);
    }
};

FenwickRU<long long> tree;

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
        long long a, b, c, d; cin >> a >> b >> c;
        if(a == 1){
            cin >> d;
            tree.update(b,c,d);
        }
        else cout << tree.query(b, c) << '\n';
    }
}
