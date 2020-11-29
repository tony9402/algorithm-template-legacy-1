#define MAX 1 << 21 //19 ~ 22
template<typename T>
struct SegmentLazy{
    T node[MAX], lazy[MAX];
    int siz=0;

    SegmentLazy() { }
    SegmentLazy(int n) { setSize(n); }
    void setSize(int n){
        siz = 1;
        while(siz <= n) siz <<= 1;
    }

    void addItem(int idx, T data, bool add=false){
        if(add) node[siz + idx] += data;
        else node[siz + idx] = data;
    }
    void build() { for(int i=siz-1;i;i--) node[i] = mergeNode(node[i<<1],node[i<<1|1]); }

    void propagate(int l, int r, int pos){
        if(lazy[pos] == 0)return;
        node[pos] = mergeNode(node[pos], lazy[pos] * (r-l+1));
        if(l ^ r){
            lazy[pos << 1] = mergeNode(lazy[pos << 1], lazy[pos]);
            lazy[pos << 1 | 1] = mergeNode(lazy[pos << 1 | 1], lazy[pos]); 
        }
        lazy[pos] = 0;
    }

    void update(int l, int r, int s, int e, int pos, T data){
        if(s <= l && r <= e){
            lazy[pos] = mergeNode(lazy[pos], data);
            propagate(l, r, pos);
            return;
        }
        propagate(l, r, pos);
        if(e < l || r < s)return;
        int m = (l + r) / 2;
        update(l, m, s, e, pos << 1, data);
        update(m+1, r, s, e, pos << 1 | 1, data);
        node[pos] = mergeNode(node[pos << 1], node[pos << 1 | 1]);
        return;
    }

    void update(int s, int e, T data){ update(0, siz-1, s, e, 1, data); }

    T query(int l, int r, int s, int e, int pos){
        propagate(l, r, pos);
        if(e < l || r < s)return 0;
        if(s <= l && r <= e)return node[pos];
        int m = (l + r) / 2;
        return mergeNode(query(l,m,s,e,pos<<1), query(m+1,r,s,e,pos<<1|1)); 
    }
    T query(int s, int e) { return query(0,siz-1,s,e,1); }

    T mergeNode(T a, T b) { return a + b; }
};