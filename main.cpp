#include <bits/stdc++.h>
using namespace std;

const string DB_FILE = "db.txt";

// Insert a (index, value) pair if not already present
void insert_entry(const string &idx, int val) {
    // Check existence by scanning file
    ifstream fin(DB_FILE);
    string curIdx; int curVal;
    while (fin >> curIdx >> curVal) {
        if (curIdx == idx && curVal == val) return; // already exists
    }
    fin.close();
    // Append new entry
    ofstream fout(DB_FILE, ios::app);
    fout << idx << ' ' << val << '\n';
}

// Delete a specific (index, value) pair if it exists
void delete_entry(const string &idx, int val) {
    ifstream fin(DB_FILE);
    if (!fin) return; // file may not exist
    string tmpPath = "db_tmp.txt";
    ofstream fout(tmpPath);
    string curIdx; int curVal;
    while (fin >> curIdx >> curVal) {
        if (!(curIdx == idx && curVal == val)) {
            fout << curIdx << ' ' << curVal << '\n';
        }
    }
    fin.close();
    fout.close();
    rename(tmpPath.c_str(), DB_FILE.c_str());
}

// Find all values for a given index and output them sorted
void find_entry(const string &idx) {
    ifstream fin(DB_FILE);
    if (!fin) {
        cout << "null\n";
        return;
    }
    vector<int> vals;
    string curIdx; int curVal;
    while (fin >> curIdx >> curVal) {
        if (curIdx == idx) vals.push_back(curVal);
    }
    fin.close();
    if (vals.empty()) {
        cout << "null\n";
        return;
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (size_t i = 0; i < vals.size(); ++i) {
        if (i) cout << ' ';
        cout << vals[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    string cmd, idx;
    int val;
    for (int i = 0; i < n; ++i) {
        cin >> cmd >> idx;
        if (cmd == "insert") {
            cin >> val;
            insert_entry(idx, val);
        } else if (cmd == "delete") {
            cin >> val;
            delete_entry(idx, val);
        } else if (cmd == "find") {
            find_entry(idx);
        }
    }
    return 0;
}
