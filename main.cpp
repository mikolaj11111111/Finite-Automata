#include <iostream>
#include <string>
#include <vector>

using namespace std;

void FiniteAutomata(string pattern, vector<int>& a, vector<int>& b, vector<int>& c, string txt) {
    int stateCount = pattern.length() + 1;

    for (int state = 0; state < stateCount; state++) {
        for (char ch : {'a', 'b', 'c'}) {
            string prefix = pattern.substr(0, state) + ch;
            int nextState = 0;

            
            for (int len = min(state + 1, (int)pattern.length()); len > 0; len--) {
                cout << "state == " << state << " char: " << ch << " len: " << len << 
                    " prefix.substr(prefix.length() - len): " << prefix.substr(prefix.length() - len) << endl;
                if (prefix.substr(prefix.length() - len) == pattern.substr(0, len)) { //prefix.substr(prefix.length() - len) => wskazany jest poczatkowa wartosc i wyciagany jest ciag znakoe az do konca
                    nextState = len;
                    break;
                }
            }
            if (nextState == pattern.length()) {
                cout << "Pattern found in index i: " << txt.length() - nextState - 1<<  " For T[i]: " << txt[txt.length() - nextState - (txt.length() - nextState - 2)] << " stan(T[i]): "
                    << a[txt.length() - nextState - (txt.length() - nextState - 2)] << endl;
            }

            if (ch == 'a') a[state] = nextState;
            if (ch == 'b') b[state] = nextState;
            if (ch == 'c') c[state] = nextState;
        }
    }
}

void InsertTable(string txt, int arr[12], vector<int>& a, vector<int>& b, vector<int>& c) {
    int next_val = 0;
    for (int i = 0; i <= txt.length(); i++) {
        if (txt[i] == 'a') {
            arr[i] = a[next_val];
            next_val = a[next_val];
        }
        else if (txt[i] == 'b') {
            arr[i] = b[next_val];
            next_val = b[next_val];
        }
        else if (txt[i] == 'c') {
            arr[i] = c[next_val];
            next_val = c[next_val];
        }
    }
    for (int j = 0; j < txt.length(); j++) {
        if (j > 8) {
            cout << arr[j] << "  ";
        }
        else {
            cout << arr[j] << " ";
        }
    }
}

int main() {
    string txt = "abababacaba";
    string pattern = "ababaca";
    int stateCount = pattern.length() + 1;

    vector<int> a(stateCount, 0);
    vector<int> b(stateCount, 0);
    vector<int> c(stateCount, 0);

    FiniteAutomata(pattern, a, b, c, txt);

    cout << "stan " << " a    " << "b    " << "c" << endl;
    for (int state = 0; state < stateCount; state++) {
        cout << state << "     " << a[state] << "    " << b[state] << "    " << c[state] << endl;
    }

    cout << "- ";
    for (int i = 1; i <= txt.length(); i++) {
        cout << i << " ";
    }
    cout << endl;

    cout << "- ";
    for (int i = 0; i < txt.length(); i++) {
        if (i > 8) {
            cout << txt[i] << "  ";
        }
        else {
            cout << txt[i] << " ";
        }
        
    }
    cout << endl;

    int arr[12] = { 0 };
    cout << "0 ";
    InsertTable(txt, arr, a, b, c);
    cout << endl;

    return 0;
}


