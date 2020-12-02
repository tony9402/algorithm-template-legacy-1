template<typename T>
struct Segment2D{
    vector<vector<T>> tree;
    int sizY, sizX;

    Segment2D() { }
    Segment2D(int y, int x){ setSize(y, x); }

    void setSize(int y, int x){
        sizY = sizX = 1;
        while(sizY <= y)sizY <<= 1;
        while(sizX <= x)sizX <<= 1;
        tree.resize(2 * sizY);
        for(int i=0; i < sizY * 2; i++)tree[i].resize(2 * sizX);
    }
    void putItem(int y, int x, T data){ tree[sizY + y][sizX + x]  = data; }
    void addItem(int y, int x, T data){ tree[sizY + y][sizX + x] += data; }
    void build(){
        for(int i=sizY;i<sizY*2;i++)
            for(int j=sizX-1;j;j--)
                tree[i][j] = mergeNode(tree[i][j<<1], tree[i][j<<1|1]);

        for(int i=sizY-1;i;i--)
            for(int j=0;j<2*sizX;j++)
                tree[i][j]=mergeNode(tree[i<<1][j], tree[i<<1|1][j]);
    }
    void update(int y, int x, T data, bool add=false){
        if(add) addItem(y, x, data);
        else    putItem(y, x, data);
        x += sizX; y += sizY;
        for(int i = x >> 1; i; i >>= 1) tree[y][i] = mergeNode(tree[y][i << 1], tree[y][i << 1 | 1]);

        for(int i = y >> 1; i; i >>= 1)
            for(int j = x; j; j >>= 1)
                tree[i][j] = mergeNode(tree[i<<1][j], tree[i<<1|1][j]);
    }
    T query1D(int y, int l, int r){
        T ret = 0;
        for(l += sizX, r += sizX + 1; l < r; l >>= 1, r >>= 1){
            if(l & 1) ret += tree[y][l++];
            if(r & 1) ret += tree[y][--r];
        }
        return ret;
    }
    T query(int y1, int x1, int y2, int x2){
        T ret = 0;
        for(y1 += sizY, y2 += sizY + 1; y1 < y2; y1 >>= 1, y2 >>= 1){
            if(y1&1) ret += query1D(y1++, x1, x2);
            if(y2&1) ret += query1D(--y2, x1, x2);
        }
        return ret;
    }
    T mergeNode(T a, T b){ return a + b; }
};
