#include "../src/ladder.h"

#define my_assert(e) {std::cout << #e << ((e) ? " passed": " failed") << std::endl;}

void error(std::string word1, std::string word2, std::string msg) {
    std::cout << word1 << " " << word2 << " " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string &str2, int d) {
    int count = 0;
    for (size_t i = 0; i < str1.size(); i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }
    return count <= d; 
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    std::queue<std::vector<std::string>> q;
    std::vector<std::string> ladder = {begin_word};
    q.push(ladder);
    while (!q.empty()) {
        std::vector<std::string> current_ladder = q.front();
        q.pop();
        std::string current_word = current_ladder.back();
        if (current_word == end_word) {
            return current_ladder;
        }
        for (const auto& word : word_list) {
            if (is_adjacent(current_word, word) && std::find(current_ladder.begin(), current_ladder.end(), word) == current_ladder.end()) {
                std::vector<std::string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                q.push(new_ladder);
            }
        }
    }
    return {};
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