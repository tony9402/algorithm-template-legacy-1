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
