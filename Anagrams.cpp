// ANAGRAMS because words are hard
const int n = 6;
ifstream fin("/Users/bobby/all_words");
set<string> v;
bitset<n> vis;
string cur;
set<string> anses;
vector<string> ans;
string in;
void rec(int num)
{
    if(num == 0)
    {
        if(v.find(cur) != v.end())
        {
            if(anses.find(cur) == anses.end())
                ans.push_back(cur);
            anses.insert(cur);
        }
        return;
    }
    if(v.find(cur) != v.end())
    {
        if(anses.find(cur) == anses.end())
            ans.push_back(cur);
        anses.insert(cur);
    }
    for(int i = 0; i < n; i ++)
    {
        if(vis[i]) continue;
        vis[i] = 1; cur += in[i];
        rec(num-1);
        vis[i] = 0; cur = cur.substr(0, cur.length()-1);
    }
}
bool comp(string s1, string s2)
{
    return s1.length() > s2.length();
}
int main()
{
    input();
    string st;
    while(!fin.eof())
    {
        fin >> st;
        v.insert(st);
    }
    cin >> in;
    rec(n);
    sort(ans.begin(), ans.end(), comp);
    for(auto it : ans)
        if(it.length() >= 3)
            cout << it << '\n' << '\n';
}
