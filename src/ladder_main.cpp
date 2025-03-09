#include "../src/ladder.h"


std::set<std::string> adjacent_coded(const std::string& word) {
    char fill = '~';
    std::set<std::string> vals;
    std::vector<std::string> codes;
    for (int i = 1; i < word.size(); i++) {
        std::string code = word;
        code[i] = fill;
        codes.push_back(code);
    }
    for (int i = 0; i < word.size(); i++) {
        std::string code = word;
        code.insert(i, 1, fill);
        codes.push_back(code);
    }
    codes.push_back(word + fill);
    std::string first = word;
    first[0] = fill;
    codes.push_back(first);
    for (std::string code : codes) {
        vals.insert(code);
    }
    return vals;
}

void test_word_fill() {
    std::string word = "awake";
    std::set<std::string> codes = adjacent_coded(word);
    for (std::string code : codes) {
        std::cout << code << std::endl;
    }
}

void test_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    vector<string> ladder = generate_word_ladder("awake", "sleep", word_list);
    std::cout << ladder.size() << std::endl;
    // verify_word_ladder();
    print_word_ladder(ladder);
}

void test_edit_distance() {
    std::cout << edit_distance_within("hit", "hot", 1) << std::endl;
    std::cout << edit_distance_within("hit", "hot", 2) << std::endl;
    std::cout << edit_distance_within("hit", "hot", 3) << std::endl;
}

void test_adjacency() {
    // std::cout << is_adjacent("hit", "hot") << std::endl;
    // std::cout << is_adjacent("hit", "hat") << std::endl;
    // std::cout << is_adjacent("hit", "cat") << std::endl;
    std::cout << is_adjacent("apple", "app") << std::endl;
}

int main()
{
    // test_adjacency();
    test_word_ladder();
    // test_word_fill();
    return 0;
}