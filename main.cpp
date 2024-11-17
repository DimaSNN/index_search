#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

#include <fmt/core.h>

struct TrieNode
{
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;

    bool isEndOfWord = false;
};

class Trie
{
private:
    std::unique_ptr<TrieNode> root;

    static void searchHelper(std::string prefix, TrieNode *node, std::vector<std::string> &words)
    {
        if (node->isEndOfWord)
        {
            words.push_back(prefix);
            // return; don't return, for the case like "milk" and "milkyway"
        }

        // TrieNode* node = this;
        for (const auto &pair : node->children)
        {
            searchHelper(prefix + pair.first, pair.second.get(), words);
        }
    }

public:
    Trie()
    {
        root = std::make_unique<TrieNode>();
    }

    void insert(std::string word)
    {
        TrieNode *node = root.get();

        for (auto ch : word)
        {
            auto found = node->children.find(ch);
            if (found == node->children.end())
            {
                TrieNode* newNode = new TrieNode;
                node->children[ch] = std::move(std::unique_ptr<TrieNode>(newNode));
                node = newNode;

            } else {
                node = found->second.get();
            }
        }
        node->isEndOfWord = true;
    }

    std::vector<std::string> search(std::string word)
    {
        TrieNode *node = root.get();

        for (auto ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                return {};
            }
            node = node->children[ch].get();
        }

        std::vector<std::string> words;
        searchHelper(word, node, words);
        return words;
    }
};

int main()
{

    Trie root;

    root.insert("apple");
    root.insert("orange");
    root.insert("application");
    root.insert("milk");
    root.insert("milkyway");
    root.insert("meat");
    root.insert("men");
    root.insert("arbuz");

    auto foundItems = root.search("milk");

    fmt::print("found items:\n");
    for (auto w : foundItems)
    {
        fmt::print("  {}\n", w);
    }

    return 0;
}