// WORD HUNT because words are hard
const int n = 4;
string board[n];
ifstream fin("/Users/bobby/all_words");
set<string> v;
set<string> pre;
string cur = "";
bitset<n> vis[n];
vector<pair<string, vector<string>>> ans;
set<string> anses;
vector<string> curMoves;
void dfs(int r, int c, int d)
{
    if(r < 0 || r >= n || c < 0 || c >= n || vis[r][c]) return;
    if(pre.find(cur) == pre.end()) return;
    cur += board[r][c];
    curMoves[r][c] = d+'0';
    if(v.find(cur) != v.end())
    {
        if(anses.find(cur) == anses.end())
            ans.push_back({cur, curMoves});
        anses.insert(cur);
    }
    vis[r][c] = 1;
    dfs(r+1, c, d+1);
    dfs(r-1, c, d+1);
    dfs(r+1, c+1, d+1);
    dfs(r+1, c-1, d+1);
    dfs(r, c+1, d+1);
    dfs(r, c-1, d+1);
    dfs(r-1, c+1, d+1);
    dfs(r-1, c-1, d+1);
    vis[r][c] = 0;
    cur = cur.substr(0, cur.length()-1);
    curMoves[r][c] = board[r][c];
}
bool comp(pair<string, vector<string>> s1, pair<string, vector<string>> s2)
{
    return s1.f.length() > s2.f.length();
}
int main()
{
    //USE CAPITAL LETTERS
    input();
    string st;
    while(!fin.eof())
    {
        fin >> st;
        v.insert(st);
        for(int i = 0; i < st.length(); i ++)
            pre.insert(st.substr(0, i+1));
    }
    for(int i = 0; i < n; i ++)
        cin >> board[i];
    for(int i = 0; i < n; i ++)
        curMoves.push_back(board[i]);
    pre.insert("");
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            dfs(i, j, 1);
    sort(ans.begin(), ans.end(), comp);
    for(auto it : ans)
    {
        if(it.f.length() < 3) continue;
        cout << it.f << '\n';
        for(int i = 0; i < n; i ++)
        {
            for(int j = 0; j < n; j ++)
            {
                if(it.s[i][j] >= '1' && it.s[i][j] <= '9')
                    cout << it.s[i][j];
                else
                    cout << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
}
