#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    unordered_map<string, vector<int>> mp;
    string cmd, idx;
    int val;
    for(int i=0;i<n;++i){
        cin>>cmd>>idx;
        if(cmd=="insert"){
            cin>>val;
            auto &vec = mp[idx];
            // check duplicate value
            if(!binary_search(vec.begin(), vec.end(), val)){
                // insert keeping sorted order
                vec.insert(lower_bound(vec.begin(), vec.end(), val), val);
            }
        } else if(cmd=="delete"){
            cin>>val;
            auto it = mp.find(idx);
            if(it!=mp.end()){
                auto &vec = it->second;
                auto pos = lower_bound(vec.begin(), vec.end(), val);
                if(pos!=vec.end() && *pos==val){
                    vec.erase(pos);
                }
                if(vec.empty()) mp.erase(it);
            }
        } else if(cmd=="find"){
            auto it = mp.find(idx);
            if(it==mp.end() || it->second.empty()){
                cout<<"null\n";
            } else {
                const auto &vec = it->second;
                for(size_t j=0;j<vec.size();++j){
                    if(j) cout<<' ';
                    cout<<vec[j];
                }
                cout<<"\n";
            }
        }
    }
    return 0;
}
