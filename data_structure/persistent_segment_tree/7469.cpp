#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct PST{
    struct Node{
        T data;
        Node *left, *right;
        Node():left(0), right(0), data(0) { }
    };
    vector<Node*> roots;
    int siz;
    
    PST(){ 
        siz = (int)2e9+10;
        Node *root = new Node();
        root->left = root->right = root;
        roots.push_back(root);
    }
    void update(Node *prv, Node *cur, int l, int r, int idx, T data, bool add=false){
        if(l == r)return cur->data = (add == true ? prv->data : 0) + data, (void)0;
        int m = l + (r - l) / 2;
        if(idx <= m){
            cur->left = new Node(); cur->right = prv->right;
            update(prv->left, cur->left, l, m, idx, data, add);
        }
        else {
            cur->right = new Node(); cur->left = prv->left;
            update(prv->right, cur->right, m+1, r, idx, data, add);
        }
        cur->data = cur->left->data + cur->right->data;
    }
    void update(int idx, T data, bool add=false){ 
        Node *newNode = new Node(); 
        update(roots.back(), newNode, 0, siz-1, idx, data, add);
        roots.emplace_back(newNode);
    }

    T query(Node *cur, int l, int r, int s, int e){
        if(s <= l && r <= e)return cur->data;
        if(e <  l || r <  s)return T(0);
        int m = l + (r - l) / 2;
        return query(cur->left, l, m, s, e) + query(cur->right, m+1,r, s, e);
    }
    T query(int s, int e, int k){ return query(roots[k], 0, siz-1, s, e); }
    
    T kth(Node *s, Node *e, int l, int r, int k){
        if(l == r)return l;
        int m = l + (r - l) / 2;
        T data = e->left->data - s->left->data;
        if(data >= k)return kth(s->left, e->left, l, m, k);
        return kth(s->right, e->right, m+1,r, k - data);
    }
    T kth(int s, int e, int k){ return kth(roots[s], roots[e], 0, siz-1, k); }
};

PST<int> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q; cin >> n >> q;
    for(int i=0;i<n;i++){
        int x; cin >> x;   
        tree.update(x + 1e9, 1, true);
    }
    for(int i=0;i<q;i++){
        int l, r, k; cin >> l >> r >> k;
        cout << tree.kth(l-1, r, k) - (int)1e9 << '\n';    
    } 
}
