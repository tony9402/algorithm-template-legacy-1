struct UnionFind{
    int *uf;

    UnionFind() { }
    UnionFind(int n){ setSize(n); }
    void setSize(int n){
        uf = new int[n];
        for(int i=0;i<n;i++)uf[i] = -1;
    }
    int find(int a){ 
        if(uf[a] < 0)return a;
        return uf[a] = find(uf[a]);
    }
    bool same(int a, int b) { return find(a) == find(b); }
    bool merge(int a, int b){
        a = find(a), b = find(b);
        if(a == b)return false;
        uf[b] = a;
        return true;
    }
};
