#include "../src/ladder.h"

#define my_assert(e) {std::cout << #e << ((e) ? " passed": " failed") << std::endl;}

void error(std::string word1, std::string word2, std::string msg) {
    std::cout << word1 << " " << word2 << " " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string &str2, int d) {
    // Be able to compare distances of strings that aren't the same length
    int i = 0;
    int j = 0;
    int distance = 0;
    while (i < str1.size() && j < str2.size()) {
        if (str1[i] != str2[j]) {
            distance++;
            if (distance > d) {
                return false;
            }
            if (str1.size() > str2.size()) {
                i++;
            } else if (str1.size() < str2.size()) {
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
    return distance <= d;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    
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