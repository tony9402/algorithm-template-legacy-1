#define MAX 1 << 21 // 19 ~ 22
template<typename T>
struct Segment{ // SegmentBottomUp
    T node[MAX];
    int siz=0;

    Segment() { }
    Segment(int n){ setSize(n); }
    void setSize(int n){
        siz=1;
        while(siz<=n)siz<<=1;
    }
    void putItem(int idx, T data) { node[siz + idx]  = data; }
    void addItem(int idx, T data) { node[siz + idx] += data; }
    void build() { for(int i=siz-1;i;i--) node[i] = mergeNode(node[i << 1], node[i << 1 | 1]); }

    void update(int idx, T data, bool add=false){
        if(add)addItem(idx, data);
        else putItem(idx, data);
        idx += siz;
        while(idx >>= 1) node[idx] = mergeNode(node[idx << 1], node[idx << 1 | 1]);
    }
    T query(int l, int r){
        T ret = 0;
        for(l += siz, r += siz + 1; l < r; l >>= 1, r >>= 1){
            if(l&1) ret += node[l++];
            if(r&1) ret += node[--r];
        }
        return ret;
    }
};
