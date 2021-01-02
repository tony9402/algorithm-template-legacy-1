#define MAXB 20
struct Trie{
    int next[2 << MAXB][2], node;
    
    Trie(){ 
        for(int i=0;i<(2<<MAXB);i++)next[i][0]=next[i][1]=-1;
        node = 1;
    }

    void insert(int bit, int p=MAXB){
        int cur = 0;
        for(int i=p;~i;i--){
            int b = bit >> i & 1;
            if(!~next[cur][b])next[cur][b] = node++;
            cur = next[cur][b];
        }
    }
};
