template<typename T>
struct Fenwick{
    T *tree, *input; 
    int siz;
    
    Fenwick(){ }
    Fenwick(int n){ setSize(n); }

    void setSize(int n){
        siz  = n;
        tree = new T[siz + 5];
        input= new T[siz + 5];
    }
    void putItem(int idx, T data){ input[idx] = data; __update(idx, data); }
    void __update(int idx, T data){
        for(; idx <= siz; idx += (idx & -idx)) tree[idx] += data;
    }
    void update(int idx, T data, bool add=false){
        if(add) __update(idx, data), input[idx] += data;
        else __update(idx, data - input[idx]), input[idx] = data;
    }
    T query(int idx) { 
        T ret = 0;
        for(; idx ; idx -= (idx & -idx)) ret += tree[idx];
        return ret;
    }
    T query(int l, int r){ return query(r) - query(l - 1); }
};
