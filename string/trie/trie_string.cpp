struct Trie{
    int next[4000001][27], node;
    
    Trie(){ 
        node = 1; 
        for(int i=0;i<4000001;i++)for(int j=0;j<27;j++)next[i][j]=-1;
    }

    void insert(const string &x){
        int cur = 0;
        for(int i=0;i<(int)x.size();i++){
            assert('a' <= x[i] && x[i] <= 'z');
            if(!~next[cur][x[i]-'a'])next[cur][x[i]-'a'] = node++;
            cur = next[cur][x[i]-'a'];
        }
        next[cur][26] = 1;
    }
};
