#include<bits/stdc++.h>
using namespace std;

const int N = 1e4;

int tc;
int n,q;
map<string,int> ans;

void proc(string s){
    vector<string> cur;
    stringstream ss;
    ss << s;
    while(ss >> s){
        cur.push_back(s);
    }
    set<string> lol;
    for(int i=0;i<cur.size();i++){
        string pft = "";
        for(int j=i;j<cur.size();j++){
            if(pft != "") pft.push_back(' ');
            pft+=cur[j];
            lol.insert(pft);
        }
    }
    for(auto x : lol){
        ans[x]++;
    }
    return;
}

string s;

int main(){
    cin >> tc;
    for(int tc_i=1;tc_i<=tc;tc_i++){
        ans.clear();
        cin >> n >> q;
        getchar();
        for(int i=1;i<=n;i++){
            getline(cin,s);
            proc(s);
        }
        cout << "Case " << tc_i << ":\n";
        for(int i=1;i<=q;i++){
            getline(cin,s);
            cout << ans[s] << endl;
        }
    }
    return 0;
}
