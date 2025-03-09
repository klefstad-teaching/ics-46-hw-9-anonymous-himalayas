#include "../src/ladder.h"


void test_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    vector<string> ladder = generate_word_ladder("sleep", "awake", word_list);
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
    return 0;
}