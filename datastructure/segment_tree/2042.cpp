#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct Segment{
    T *node;
    int siz=0;

    Segment() { }
    Segment(int n){ setSize(n); }
    void setSize(int n){
        siz=1;
        while(siz <= n) siz <<= 1;
        node = new T[siz << 1];
    }
    void putItem(int idx, T data) { node[siz + idx]  = data; }
    void addItem(int idx, T data) { node[siz + idx] += data; }
    void build(){ for(int i=siz-1;i;i--) node[i] = mergeNode(node[i << 1], node[i << 1 | 1]); }

    void update(int idx, T data, bool add=false){
        if(add)addItem(idx, data);
        else putItem(idx, data);
        idx += siz;
        while(idx >>= 1) node[idx] = mergeNode(node[idx << 1], node[idx << 1 | 1]);
    }

    //[s, e]
    T query(int l, int r, int s, int e, int pos){
        if(s <= l && r <= e)return node[pos];
        if(e <  l || r <  s)return T();
        int m = (l + r) / 2;
        return mergeNode(query(l,m,s,e,pos<<1), query(m+1,r,s,e,pos<<1|1));
    }
    T query(int s, int e) { return query(0, siz-1, s, e, 1); }

    T mergeNode(T a, T b){
        return a + b;
    }
};

Segment<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k; cin >> n >> m >> k;
    tree.setSize(n);
    for(int i=0;i<n;i++){
        long long x; cin >> x;
        tree.putItem(i, x);
    }
    tree.build();
    for(int i=0;i<m+k;i++){
        int t, s, e; cin >> t >> s >> e;
        --s;
        if(t == 1){
            tree.update(s, e);
        }
        else {
            --e;
            cout << tree.query(s, e) << '\n';
        }
    }
}
