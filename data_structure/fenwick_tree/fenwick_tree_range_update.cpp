template<typename T>
struct FenwickRU{ // Fenwick Range Update
    T *tree, *add, *mul, *input;
    int siz;

    FenwickRU(){ } 
    FenwickRU(int n) { setSize(n); }
    void setSize(int n){
        siz   = n;
        tree  = new T[siz + 5];
        add   = new T[siz + 5];
        mul   = new T[siz + 5];
        input = new T[siz + 5];
    }
    void putItem(int idx, T data){ update(idx, idx, data), input[idx] = data; }
    void __update(int idx, T _mul, T _add){
        for(;idx <= siz;idx += idx & -idx){
           add[idx] += _add;
           mul[idx] += _mul;
        }
    }
    void update(int l, int r, T data){
        __update(l, data, (l-1)*-data);
        __update(r+1, -data, data*r);
    }
    T query(int idx){
        T __add = 0, __mul = 0;
        for(int i=idx; i; i -= i & -i){
            __add += add[i];
            __mul += mul[i];
        }
        return __mul * idx + __add;
    }
    T query(int l, int r){
        return query(r) - query(l - 1);
    }
};
