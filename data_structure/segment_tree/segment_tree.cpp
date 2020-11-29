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
