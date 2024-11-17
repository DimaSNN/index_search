#include <iostream>
#include <unordered_map>
#include <vector>

class TrieNode
{
public:
    std::unordered_map<char, TrieNode *> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    Trie(const  Trie&) = delete;
    Trie& operator=(const  Trie&) = delete;
    // ~Trie() {  }   //this example has a leak

    void insert(const std::string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    void searchHelper(TrieNode *node, std::string prefix, std::vector<std::string> &results)
    {
        if (node->isEndOfWord)
        {
            results.push_back(prefix);
        }
        for (auto &pair : node->children)
        {
            searchHelper(pair.second, prefix + pair.first, results);
        }
    }

    std::vector<std::string> search(const std::string &prefix)
    {
        TrieNode *node = root;
        for (char ch : prefix)
        {
            if (node->children.find(ch) == node->children.end())
            {
                return {};
            }
            node = node->children[ch];
        }
        std::vector<std::string> results;
        searchHelper(node, prefix, results);
        return results;
    }
};

int main()
{
    Trie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("apricot");
    trie.insert("avocado");

    std::string prefix = "ap";
    std::vector<std::string> results = trie.search(prefix);

    std::cout << "Products starting with \"" << prefix << "\":" << std::endl;
    for (const std::string &product : results)
    {
        std::cout << product << std::endl;
    }

    return 0;
}