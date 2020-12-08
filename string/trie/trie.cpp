namespace Trie{
    struct Node{
        char data;
        int value;
        map<char, Node*> _next;
        Node() { }
        ~Node() { for(auto &i: _next) delete i.second; }
        Node* insert(char x){ if(_next.count(x) == 0)_next[x] = new Node(); return _next[x]; }
        Node* next(char x){ return _next.count(x) ? _next[x] : NULL; }

        bool find(char x){ return _next.count(x) != 0; }
        bool end(){ return _next.count(0); }
    }*root = new Node();
    int words = 0;

    void insert(const string &word){
        Node *cursor = root;
        for(int i=0;i<(int)word.size();i++)cursor = cursor->insert(word[i]);            
        if(!cursor->find(0))words++;
        cursor->insert(0); // Dummy Node
    }
    
    bool find(string str){
        Node *cursor = root;
        for(int i=0;i<(int)str.size();i++){
            Node *nxt = cursor->insert(str[i]);
            if(nxt == NULL)return false;
        }
        return cursor->end();
    }
}
