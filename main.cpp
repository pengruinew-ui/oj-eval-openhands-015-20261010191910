#include <bits/stdc++.h>
using namespace std;

const string DB_FILE = "db.txt";

// Load database into memory map
void load_db(unordered_map<string, vector<int>>& mp) {
    ifstream fin(DB_FILE);
    if(!fin) return; // file may not exist yet
    string idx; int val;
    while(fin >> idx >> val) {
        auto &vec = mp[idx];
        vec.push_back(val);
    }
    // sort each vector and remove duplicates (just in case)
    for(auto &p : mp) {
        auto &vec = p.second;
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
    }
    fin.close();
}

// Save database from map to file
void save_db(const unordered_map<string, vector<int>>& mp) {
    ofstream fout(DB_FILE, ios::trunc);
    for(const auto &p : mp) {
        const string &idx = p.first;
        const vector<int> &vec = p.second;
        for(int v : vec) {
            fout << idx << ' ' << v << '\n';
        }
    }
    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin >> n)) return 0;
    unordered_map<string, vector<int>> mp;
    load_db(mp);
    string cmd, idx;
    int val;
    for(int i = 0; i < n; ++i) {
        cin >> cmd >> idx;
        if(cmd == "insert") {
            cin >> val;
            auto &vec = mp[idx];
            // ensure sorted order and uniqueness
            if(!binary_search(vec.begin(), vec.end(), val)) {
                vec.insert(lower_bound(vec.begin(), vec.end(), val), val);
            }
        } else if(cmd == "delete") {
            cin >> val;
            auto it = mp.find(idx);
            if(it != mp.end()) {
                auto &vec = it->second;
                auto pos = lower_bound(vec.begin(), vec.end(), val);
                if(pos != vec.end() && *pos == val) {
                    vec.erase(pos);
                }
                if(vec.empty()) mp.erase(it);
            }
        } else if(cmd == "find") {
            auto it = mp.find(idx);
            if(it == mp.end() || it->second.empty()) {
                cout << "null\n";
            } else {
                const auto &vec = it->second;
                for(size_t j = 0; j < vec.size(); ++j) {
                    if(j) cout << ' ';
                    cout << vec[j];
                }
                cout << "\n";
            }
        }
    }
    // Save changes back to file
    save_db(mp);
    return 0;
}
