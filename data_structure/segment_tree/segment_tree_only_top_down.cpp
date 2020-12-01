#define MAX 1 << 21 //19 ~ 22
template<typename T>
struct Segment{
    T node[MAX];
    int siz=0;

    Segment() { }
    Segment(int n){ setSize(n); }
    void setSize(int n){
        siz=1;
        while(siz <= n) siz <<= 1;
    }
    void putItem(int idx, T data) { node[siz + idx]  = data; }
    void addItem(int idx, T data) { node[siz + idx] += data; }
    void build(){ for(int i=siz-1;i;i--) node[i] = mergeNode(node[i << 1], node[i << 1 | 1]); }

    void update(int idx, int l, int r, int pos, T data, bool add=false){
        if(idx < l ||  r < idx)return;
        if(l == r) return node[pos] = mergeNode((add ? node[pos] : T()), data), (void)0;
        int m = (l + r) / 2;
        update(idx, l, m, pos << 1, data, add);
        update(idx, m+1,r, pos << 1 | 1, data, add);
        node[pos] = mergeNode(node[pos << 1], node[pos << 1 | 1]);
    }
    void update(int idx, T data, bool add=false){ 
        update(idx, 0, siz-1, 1, data, add);
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
