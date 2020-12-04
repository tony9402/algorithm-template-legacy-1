#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct PST{
    struct Node{
        T data;
        Node *left, *right;
        Node():left(0), right(0),data(0){}
    };
    int siz;

    vector<Node*> tree;
    PST() { tree.resize(1); }
    PST(int n) { build(n); }
    void build(Node *cur, int l, int r){ 
        if(l == r)return;
        int m = (l + r) / 2;
        cur->left = cur->right = new Node();
        build(cur->left, l, m);
        build(cur->right, m+1,r);
    }
    void build(int n){ 
        siz = 1;
        while(siz <= n)siz <<= 1;
        tree[0] = new Node();
        build(tree[0], 0, siz-1); 
    }
    void update(Node *prv, Node *cur, int l, int r, int idx, T data){
        if(l == r)return cur->data = data, (void)0;
        int m = (l + r) / 2;
        if(idx <= m){
            cur->left = new Node(); cur->right = prv->right;
            update(prv->left, cur->left, l, m, idx, data);
        }
        else{
            cur->right = new Node(); cur->left = prv->left;
            update(prv->right, cur->right, m + 1, r, idx, data);
        }
        cur->data = cur->left->data + cur->right->data;
    }
    void update(int idx, T data){
        Node *newRoot = new Node();
        update(tree.back(), newRoot, 0, siz-1, idx, data);
        tree.emplace_back(newRoot);
    }

    T query(Node *cur, int l, int r, int s, int e){
        if(e < l || r < s)return T();
        if(s <= l && r <= e)return cur->data;
        int m = (s + e) / 2;
        return mergeNode(query(cur->left, l, m, s, e), query(cur->right, m+1,r, s, e));
    }
    T query(int s, int e, int v){ return query(tree[v], 0, siz - 1, s, e); }

    T kth(Node *l, Node *r, int s, int e, int k){
        if(s == e) return s;
        int m = (s + e) / 2;
        T data = r->left->data - l->left->data;
        if(data >= k) return kth(l->left, r->left, s, m, k);
        return kth(l->right, r->right, m+1, e, k - data);
    }
    T kth(int s, int e, int k){ return kth(tree[s], tree[e], 0, siz-1, k); }

    T mergeNode(T a, T b){ return a + b; }
};

vector<long long> v, tmpv;
PST<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q; cin >> n >> q;
    for(int i=0;i<n;i++){
        long long x;cin >> x;
        v.push_back(x);
        tmpv.push_back(x);
    }
    sort(tmpv.begin(), tmpv.end());
    tmpv.erase(unique(tmpv.begin(), tmpv.end()), tmpv.end());
    for(auto &i: v) i = lower_bound(tmpv.begin(),tmpv.end(), i) - tmpv.begin();
    tree.build(n);
    for(int i=0;i<(int)v.size();i++) tree.update(v[i], 1);
    
    for(int i=0;i<q;i++){
        int l, r, k; cin >> l >> r >> k;
        cout << tmpv[tree.kth(l-1, r, k)] << '\n';    
    } 
}
