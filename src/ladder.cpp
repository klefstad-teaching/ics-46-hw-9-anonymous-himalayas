#include "../src/ladder.h"

#define my_assert(e) {std::cout << #e << ((e) ? " passed": " failed") << std::endl;}

void error(std::string word1, std::string word2, std::string msg) {
    std::cout << word1 << " " << word2 << " " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string &str2, int d) {
    /*
    Determining legal hops is done in the algorithm above by is_adjacent(), which returns true if two words are neighbors. 
    A neighbor of a given word w is a word that differs by exactly 1 letter from w. 
    Here for our implementation, differing by 1 letter means that one character in one word can not only be replaced, 
    but also inserted or deleted to become the other word. For example, "date" and "data" are neighbors, 
    but so are "chat" and "cheat".
    */
    if (abs((int)str1.length() - (int)str2.length()) > d) {
        return false;
    }
    int i = 0, j = 0;
    int distance = 0;
    while (i < str1.length() && j < str2.length()) {
        if (str1[i] != str2[j]) {
            distance++;
            if (distance > d) {
                return false;
            }
            if (str1.length() > str2.length()) {
                i++;
            } else if (str1.length() < str2.length()) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    return true;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    return edit_distance_within(word1, word2, 1);
}

std::set<std::string> adjacent_codes(const std::string& word) {
    std::set<std::string> codes;
    for (int i = 0; i < word.length(); i++) {
        std::string code = word;
        code[i] = '_';
        codes.insert(code);
    }
    return codes;
}

vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    if (begin_word == end_word)
        return vector<string> {};

    map<string, vector<string>> adj_list;
    for (string word : word_list){
        for (string code : adjacent_codes(word)){
            adj_list[code].push_back(word);
        }
    }

    set<string> visited;
    visited.insert(begin_word);

    queue<vector<string>> q;
    q.push(vector<string>{begin_word});

    while(!q.empty()){
        vector<string> ladder = q.front();
        q.pop();

        for (string code : adjacent_codes(ladder.back())){
            for (string word : adj_list[code]){
                if (word != ladder.back() && visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    q.push(new_ladder);
                }
            }
        }
    }
    return vector<string> {};
}

void load_words(std::set<std::string>& word_list, const std::string& file_name) {
    std::ifstream in(file_name);
    if (!in) {
        error("Unable to open file", file_name, "for reading");
    }
    std::string word;
    while (in >> word) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const std::vector<std::string>& ladder) {
    for (const auto& word : ladder) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}