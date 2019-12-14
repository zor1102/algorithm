#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define long long long
const int BASE = 1000000007;
vector<long> pow;

void hash_build(string word, int sizeOfWord, vector<long> &hash_code) {
    hash_code.resize(sizeOfWord + 1);
    for (int i = 0; i < sizeOfWord; i++)
        hash_code[i + 1] = (hash_code[i] * pow[1] + word[i]) % BASE;
}

long hash_range(vector<long> hash_code, int left, int right) {
    return (hash_code[right] - hash_code[left - 1] * pow[right - left + 1] + 1LL * BASE * BASE) % BASE;
}

int main() {
    int n, maxLength = 0;
    string pattern;
    vector<string> listWords;
    vector<long> hash_code_of_pattern;
    cin >> pattern >> n;

    int sizeOfPattern = pattern.size();

    for(int i = 0; i < n; i++) {
        string term;
        cin >> term;
        listWords.push_back(term);
        if(term.size() > maxLength)
            maxLength = term.size();
    }

    pow.resize(maxLength + 1);
    pow[0] = 1; pow[1] = 2309;
    for (int i = 2; i < maxLength; i++)
        pow[i] = pow[i - 1] * pow[1] % BASE;

    hash_build(pattern, sizeOfPattern, hash_code_of_pattern);

    for(int i = 0; i < n; i++) {
        int sizeOfWord = listWords[i].size();
        if(sizeOfWord < sizeOfPattern) {
            cout << -1 << endl;
            continue;
        }
        vector<long> hash_code_of_word;
        hash_build(listWords[i], sizeOfWord, hash_code_of_word);
        bool isExits = 0;
        for (int i = 1; i <= sizeOfWord - sizeOfPattern + 1; i++) 
            if (hash_range(hash_code_of_word, i, i + sizeOfPattern - 1) == hash_code_of_pattern[sizeOfPattern]) {
                isExits = 1;
                cout << i << endl;
                break;
            }
        if(!isExits)
            cout << -1 << endl;
        
    }
    return 0;
}