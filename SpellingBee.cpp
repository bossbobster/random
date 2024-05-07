// SPELLING BEE because words are hard
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
vector<pis> ans;
int cnt[26];
void rec(int idx)
{
    bool b = v.go(all[idx]);
    if(!b) return;
    cur.push_back(all[idx]);
    cnt[all[idx]-'a'] ++;
    for(int i = 0; i < 7; i ++)
        rec(i);
    if(v.isWord() && cnt[all[0]-'a'] > 0)
        ans.push_back({cur.length(), cur});
    v.back();
    cnt[all[idx]-'a'] --;
    cur.pop_back();
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
    assert(all.length() == 7);
    for(int i = 0; i < 7; i ++)
    {
        v.cur = v.root;
        rec(i);
    }
    sort(ans.begin(), ans.end(), greater<pis>());
    for(int i = 0; i < 100; i ++)
        cout << ans[i].s << '\n';
}
