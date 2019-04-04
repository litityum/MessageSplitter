#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const long long int d = 31;
const long long int asal = 1000000007;
int k;
vector<long long int>func;
vector<vector<long long int>> text_hash;
vector<long long int>dict_hash;
vector<string> dict;
int text_length;
string text;
long long int my_hash(string s){
    long long int length = s.length();
    long long int hash = 0;
    for (int i = 0; i < length; ++i) {
        hash = (d * hash + (long long int)(s[i]-96)) % asal;
    }
    return hash;
}
long long int here_we_go(int start){
    if(start == text_length)
        return 1;
    if(start > text_length)
        return 0;
    long long int count = 0;
    if(func[start] != -1){
        return func[start];
    }
    else{
        for (int i = 0; i < k; ++i) {
            int len = dict[i].length();
            if(text_hash[start][len] == -1){
                if(len > 0 && text_hash[start][len - 1] != -1)
                    text_hash[start][len] =(d * text_hash[start][len - 1] + (long long int) (text.substr(start, len)[len - 1] - 96)) % asal;
                else
                    text_hash[start][len] = my_hash(text.substr(start, len));
            }
            if(text_hash[start][len] == dict_hash[i]){
                if(text.substr(start, len) == dict[i]) {
                    count += here_we_go((start + len));
                }
            }
        }
        count %= asal;
        func[start] = count;
        return count;
    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    ifstream infile(argv[1]);
    infile >> text;
    infile >> k;

    dict = vector<string>(k);
    text_length = text.length();
    text_hash = vector<vector<long long int>>(text_length + 1, vector<long long int>(text_length + 1, -1));
    dict_hash = vector<long long int>(k);
    func = vector<long long int>(text_length, -1);

    for (int i = 0; i < k; ++i) {
        string word;
        infile >> word;
        dict[i] = word;
    }
    for (int i = 0; i < k; ++i) {
        dict_hash[i] = my_hash(dict[i]);
    }
    ofstream outfile(argv[2]);
    outfile << here_we_go(0) << endl;
    return 0;
}
