// LETTER BOXED because words are hard
ifstream fin("/Users/bobby/all_words");
struct node
{
    node* nx[26];
    node* par;
    int cnt = 0;
};
struct trie
{
    node* root = nullptr, *cur;
    trie()
    {
        root = new node();
    }
    void add(string st)
    {
        cur = root;
        for(auto it : st)
        {
            if(cur->nx[it-'a'] == nullptr)
                cur->nx[it-'a'] = new node();
            cur->nx[it-'a']->par = cur;
            cur = cur->nx[it-'a'];
        }
        cur->cnt ++;
    }
    bool go(char c)
    {
        if(cur->nx[c-'a'] == nullptr) return false;
        cur = cur->nx[c-'a'];
        return true;
    }
    void back()
    {
        cur = cur->par;
    }
    bool isWord()
    {
        if(cur == nullptr) return false;
        return cur->cnt > 0;
    }
    bool has(string st)
    {
        cur = root;
        for(auto it : st)
        {
            if(cur->nx[it-'a'] == nullptr)
                return false;
            cur = cur->nx[it-'a'];
        }
        return cur->cnt > 0;
    }
};
trie v;
string all;
string cur;
vector<vector<string>> pos;
int ogIdx;
void rec(int idx)
{
    bool b = v.go(all[idx]);
    if(!b)
    {
        return;
    }
    cur.push_back(all[idx]);
    for(int i = 0; i < 12; i ++)
        if(i/3 != idx/3)
            rec(i);
    if(v.isWord())
        pos[ogIdx].push_back(cur);
    v.back();
    cur.pop_back();
}

vector<string> curAns;
vector<vector<string>> ans;
int cnt[26], id[26];
const int mx = 4;
void search(int idx, int wrd)
{
    bool done = true;
    for(auto it : all)
        if(cnt[it-'a'] == 0)
        {
            done = false;
            break;
        }
    if(done)
    {
        ans.push_back(curAns);
        return;
    }
    if(wrd == 0) return;
    for(auto it : pos[idx])
    {
        for(auto it2 : it)
            cnt[it2-'a'] ++;
        curAns.push_back(it);
        search(id[it.back()-'a'], wrd-1);
        for(auto it2 : it)
            cnt[it2-'a'] --;
        curAns.pop_back();
    }
}
int main()
{
    input();
    string st;
    v = trie();
    while(!fin.eof())
    {
        fin >> st;
        for(int i = 0; i < st.length(); i ++)
            st[i] += ('a'-'A');
        v.add(st);
    }
    cin >> all;
    assert(all.length() == 12);
    pos.resize(12);
    for(int i = 0; i < 12; i ++)
    {
        id[all[i]-'a'] = i;
        ogIdx = i;
        v.cur = v.root;
        rec(i);
    }
    for(int i = 0; i < 12; i ++)
    {
        search(i, 3); // dont wanna get more than 4 words
    }
    int mn = mx;
    for(auto it : ans)
        mn = min(mn, (int)it.size());
    for(auto it : ans)
    {
        if((int)it.size() == mn)
        {
            for(auto it2 : it)
                cout << it2 << ' ';
            cout << '\n';
        }
    }
}
