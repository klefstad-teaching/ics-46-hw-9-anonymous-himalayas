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
    if (abs((int)str1.size() - (int)str2.size()) > d) {
        return false;
    }
    vector<vector<int>> dp(str1.size() + 1, vector<int>(str2.size() + 1, 0));
    for (int i = 0; i <= str1.size(); i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= str2.size(); j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= str1.size(); i++) {
        for (int j = 1; j <= str2.size(); j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[str1.size()][str2.size()] <= d;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    /*
    For the word ladder problem, write a program that prompts the user for two words, a start word and an end word, and finds a minimum-length ladder between the words. 
    Check the input right away to ensure the start and end words are not the same word, because that condition may lead to an infinite loop! If invalid input occurs, 
    your program should print an error message. Use our file words.txt for your dictionary of words, and ignore letter cases.

    Use BFS to guarantee that the first solution you find will be as short as any other. 
    Start by examining ladders that are one step away from the original word, where only one letter is changed. 
    That is the purpose of is_adjacent(last_word, word). Implement the breadth-first algorithm using a queue to store partial ladders that represent possibilities to explore. 
    Each partial ladder is a stack, which means that your overall collection must be a queue of stacks.
    */
    if (word_list.find(end_word) == word_list.end()) {
        return {"No word ladder found."};
    }
    if (begin_word == end_word) {
        return {begin_word};
    }
    std::queue<std::vector<std::string>> q;
    q.push({begin_word});
    std::set<std::string> visited;
    visited.insert(begin_word);
    while (!q.empty()) {
        std::vector<std::string> path = q.front();
        q.pop();
        std::string last_word = path.back();
        if (last_word == end_word) {
            return path;
        }
        for (const auto& word : word_list) {
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                std::vector<std::string> new_path = path;
                new_path.push_back(word);
                q.push(new_path);
                visited.insert(word);
            }
        }
    }
    return {"No word ladder found."};
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