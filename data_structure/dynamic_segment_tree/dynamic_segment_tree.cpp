const int MAXL = (int)1e9;

template<typename T>
struct DynamicSegment{
    struct Node{
        int l, r; // range
        S data;
        Node *left, *right;
        Node():l(1),r(MAXL),data(0),left(0),right(0) { }
        void extend(){
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
            return;
        }
    };
    Node *tree;

    DynamicSegment() { tree = new Node(); }
    void update(Node *cur, int l, int r, T data){
        if(cur->l > r || cur->r < l || cur->l > cur->r)return;
        if(l <= cur->l && cur->r <= r){
            cur->data += (cur->r - cur->l + 1) * data;
            if(cur->l != cur->r)cur->extend();
            return;
        }
        cur->extend();
        update(cur->left, l, r, data);
        update(cur->right, l, r, data);
        cur->data = mergeNode(cur->left->data, cur->right->data);
    }
    void update(int l, int r, T data){ update(tree, l, r, data); }

    T query(Node *cur, int l, int r){
        if(cur->l > cur->r || cur->r < l || cur->l > r)return T(0);
        if(l <= cur->l && cur->r <= r)return cur->data;
        cur->extend();
        return mergeNode(query(cur->left, l, r), query(cur->right, l, r));
    }
    T query(int l, int r){ return query(tree, l, r); }

    T mergeNode(T a, T b){ return a + b; }
};
