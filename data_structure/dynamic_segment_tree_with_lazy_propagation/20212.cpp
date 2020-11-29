#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXL = (int)1e9;

template<typename T>
struct DynamicSegmentLazy{
    struct Node{
        int l, r; // range
        T data, lazy;
        Node *left, *right;
        Node():l(1),r(MAXL),data(0),lazy(0),left(0),right(0) { }
        void extend(T lzy=0){
            if(l == r)return;
            if(left == 0){ //if leaf node
                left  = new Node();
                right =  new Node();
                int m = (l + r) / 2;
                left->l  = l;
                left->r  = m;
                right->l = m + 1;
                right->r = r;
            }
            left->lazy += lzy;
            right->lazy += lzy;
            return;
        }
    };
    Node *tree;

    DynamicSegmentLazy() { tree = new Node(); }
    void pushdown(Node *cur){
        if(cur->lazy){
            cur->data += (cur->r - cur->l + 1) * cur->lazy;
            cur->extend(cur->lazy);
            cur->lazy = 0;
        }
    }

    void update(Node *cur, int l, int r, T data){
        pushdown(cur);
        if(cur->l > cur->r || cur->l > r || l > cur->r)return;
        if(l <= cur->l && cur->r <= r){
            cur->data += (cur->r - cur->l + 1) * data;
            if(cur->l != cur->r)cur->extend(data);
            return;
        }
        cur->extend();
        update(cur->left, l, r, data);
        update(cur->right, l, r, data);
        cur->data = mergeNode(cur->left->data, cur->right->data);
    }
    void update(int l, int r, T data){ update(tree, l, r, data); }

    T query(Node *cur, int l, int r){
        if(cur->l > cur->r || cur->l > r || l > cur->r)return T(0);
        pushdown(cur);
        if(l <= cur->l && cur->r <= r)return cur->data;
        cur->extend();
        return mergeNode(query(cur->left, l, r), query(cur->right, l, r));
    }
    T query(int l, int r){ return query(tree, l, r); }

    T mergeNode(T a, T b){ return a + b; }
};

struct Query{
    ll i, j, k, idx;
    Query(ll i=0,ll j=0,ll k=0,ll idx=0):i(i),j(j),k(k),idx(idx){ }
    bool operator<(const Query& o) const { return k > o.k; }
};
vector<Query> f, s;
vector<ll> answer;

DynamicSegmentLazy<ll> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    for(int i=0;i<n;i++){
        int t;
        ll a, b, c;
        cin >> t >> a >> b >> c;
        (t == 1 ? f : s).push_back(Query(a,b,c,s.size()));
    }
    answer.resize(s.size());
    sort(s.begin(),s.end());
    for(int i=1;i<=(int)f.size();i++){
        while(s.size() && s.back().k < i){
            answer[s.back().idx] = tree.query(s.back().i, s.back().j);
            s.pop_back();
        }
        tree.update(f[i-1].i, f[i-1].j, f[i-1].k);
    }
    while(s.size()){
        answer[s.back().idx] = tree.query(s.back().i, s.back().j);
        s.pop_back();
    }
    for(auto &i: answer)cout << i << '\n';
    
    return 0;    
}
