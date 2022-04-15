string illegal[] = {"the reader", "situation", "illustrate", "through", "interesting", "simple", "simply", " show", "display", "vividly", "directly", " big ", " huge", " large", "lifestyle", "mindset", "pure", "goes to new heights", "amazing", "impact", "effective", "off of", "plot", "to deal with", " me ", " my ", " you", " i ", " we ", " our ", " one ", " us ", " goes into", "confusing", "helps to understand", "later in the novel", "explain", " be ", " is ", " was ", " are ", " were ", " becom", "able to", " very significant ", "attitude", "the book", "to not", "constantly", "go through", "up to", "continuously", "go against", "goes against", "went against", "to put up with", "heavily", "extremely", "in order", "based on", "revolve around", "revolves around", "revolved around", "whilst", " on ", " where "};
int main()
{
    string word, essay =
    //PASTE ESSAY HERE (in between the quotes)
    "<essay>"
    , edited;
    bool quote = false;
    edited.reserve(essay.length());
    for(char ch : essay)
    {
        if(ch >= 'A' && ch <= 'Z') ch += 32;
        if(ch == '\"' || ch == '\xe2' || ch == '\x99' || ch == '\xa6')
            quote = !quote;
        if(!quote)
        {
            if(((ch >= 'a' && ch <= 'z') || ch == ' '))
                edited += ch;
            else edited += " ";
        }
            
    }
    cout << edited;
    for(auto it : illegal)
        if(edited.find(it) != string::npos)
            cout << it << '\n';
}
