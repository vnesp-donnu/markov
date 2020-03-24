#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Rule {
    string left;
    string right;
    bool final;

    void read(bool debug) {
        cin >> left >> right;
        final = right[right.length() - 1] == '!';
        if (final)
            right.resize(right.length() - 1);
        if (left == "_")
            left = "";
        if (right == "_")
            right = "";
        cout << left << " -> " << right << (final ? "!" : "") << endl;
    }

    bool apply(string& S, bool debug) {
        int pos = S.find(left);
        if (pos == string::npos)
            return false;
        if (debug)
            cout << left << " -> " << right << (final ? "!" : "") << " (position = " << pos << ")" << endl;
        S.replace(pos, left.length(), right);
        return true;
    }
};

const int MAX_ITER = 1000;

struct NAM {
    int NRules;
    vector<Rule> rules;

    string S;

    void read(bool debug) {
        cin >> NRules;
        rules.resize(NRules);
        if (debug)
            cout << "|R| = " << NRules << endl;
        for (int i = 0; i < NRules; i++) {
            if (debug)
                cout << "Rule" << i << ": ";
            rules[i].read(debug);
        }
    }

    bool stepOver(bool debug) {
        for (int i = 0; i < NRules; i++) {
            if (rules[i].apply(S, debug)) {
                return !rules[i].final;
            }
        }
        if (debug) {
            cout << "No applicable rules!" << endl;
        }
        return false;
    }

    void readState() {
        cin >> S;
    }

    void run(bool debug) {
        for (int iter = 1; iter <= MAX_ITER; iter++) {
            if (debug) {
                cout << "Step #" << iter << ":" << endl;
            }
            if (!stepOver(debug)) {
                cout << "Machine is stopped!" << endl;
                return;
            }
            if (debug) {
                cout << "Current state: ";
                printState();
            }
        }
        cout << "Time Limit exceeded" << endl;
    }

    void printState() {
        cout << S << endl;
    }
};

NAM machine;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    machine.read(true);
    int NTest;
    cin >> NTest;
    for (int iTest = 1; iTest <= NTest; iTest++) {
        cout << endl << "Test #" << iTest << ":" << endl;
        machine.readState();
        cout << "Initial state: ";
        machine.printState();
        machine.run(true);
        cout << "Final state: "; 
        machine.printState();
    }
}