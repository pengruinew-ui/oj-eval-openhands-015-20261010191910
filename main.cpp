#include <bits/stdc++.h>
using namespace std;

const string DB_FILE = "db.txt";

// Load database into memory map
void load_db(unordered_map<string, set<int>>& mp) {
    ifstream fin(DB_FILE);
    if (!fin) return; // file may not exist yet
    string idx; int val;
    while (fin >> idx >> val) {
        mp[idx].insert(val);
    }
    fin.close();
}

// Save database from map to file
void save_db(const unordered_map<string, set<int>>& mp) {
    ofstream fout(DB_FILE, ios::trunc);
    for (const auto& p : mp) {
        const string& idx = p.first;
        const set<int>& s = p.second;
        for (int v : s) {
            fout << idx << ' ' << v << '\n';
        }
    }
    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    unordered_map<string, set<int>> mp;
    load_db(mp);
    string cmd, idx;
    int val;
    for (int i = 0; i < n; ++i) {
        cin >> cmd >> idx;
        if (cmd == "insert") {
            cin >> val;
            mp[idx].insert(val);
        } else if (cmd == "delete") {
            cin >> val;
            auto it = mp.find(idx);
            if (it != mp.end()) {
                it->second.erase(val);
                if (it->second.empty()) mp.erase(it);
            }
        } else if (cmd == "find") {
            auto it = mp.find(idx);
            if (it == mp.end() || it->second.empty()) {
                cout << "null\n";
            } else {
                bool first = true;
                for (int v : it->second) {
                    if (!first) cout << ' ';
                    cout << v;
                    first = false;
                }
                cout << "\n";
            }
        }
    }
    save_db(mp);
    return 0;
}
