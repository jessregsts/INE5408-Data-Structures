#define MOODLE
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// TrieNode representa um nó na estrutura de dados trie
class TrieNode {
public:
    explicit TrieNode(char c) : nodeChar(c), valid(false), position(0), length(0), prefix(0) {}

    char nodeChar;
    bool valid;
    std::vector<TrieNode*> children;
    unsigned long position;
    unsigned long length;
    unsigned long prefix;
};

// Trie representa a estrutura de dados trie
class Trie {
public:
    Trie() {
        root = new TrieNode('\0');
    }

    ~Trie() {
        deleteRoot(root);
    }

    // Inserir uma palavra na trie
    void insert(TrieNode* node, const std::string& word, unsigned long position, unsigned long length) {
        for (char c : word) {
            bool foundInChild = false;
            node->prefix++;

            for (TrieNode* child : node->children) {
                if (child->nodeChar == c) {
                    node = child;
                    foundInChild = true;
                    break;
                }
            }

            if (!foundInChild) {
                TrieNode* newNode = new TrieNode(c);
                node->children.push_back(newNode);
                newNode->prefix++;
                node = newNode;
            }
        }

        node->valid = true;
        node->position = position;
        node->length = length;
    }

    // Encontrar um prefixo na trie
    TrieNode* findPrefix(const std::string& word) {
        TrieNode* node = root;

        for (char c : word) {
            bool foundInChild = false;

            for (TrieNode* child : node->children) {
                if (child->nodeChar == c) {
                    node = child;
                    foundInChild = true;
                    break;
                }
            }

            if (!foundInChild) {
                return nullptr;
            }
        }

        return node;
    }

    // Obter o nó raiz da trie
    TrieNode* get_root() {
        return root;
    }

private:
    TrieNode* root;

    // Deletar recursivamente os nós da trie
    void deleteRoot(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (TrieNode* child : node->children) {
            deleteRoot(child);
        }

        delete node;
    }
};

int main(int argc, char* argv[]) {
    std::string filename;
    std::string line;
    std::string dict;
    std::ifstream file;
    Trie tree;

    #ifndef MOODLE
    // Receber o argumento de entrada
    if (argc < 2) {
        std::cout << "Error: No input filename provided.\n";
        std::cout << "Usage: ./program [name_of_file.dic]\n";
        return 1;  // Retornar um código de erro
    }
    filename = argv[1];
    #endif

    #ifdef MOODLE
    std::cin >> filename;
    #endif

    // Abrir arquivo
    file.open(filename);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open the file.\n";
        return 1;  // Retornar um código de erro
    }

    // Ler palavras do dicionário do arquivo
    while (getline(file, line)) {
        dict += line + "\n";
    }

    file.close();   // Fechar arquivo

    // Extrair palavras do dicionário, posições e comprimentos
    size_t offset = 0;
    std::vector<std::string> dictWords;
    std::vector<unsigned long> positions;
    std::vector<unsigned long> lengths;

    while (true) {
        size_t begin = dict.find('[', offset);
        size_t end = dict.find(']', offset);

        if (begin == std::string::npos) {
            break;
        }

        std::string word = dict.substr(begin + 1, end - begin - 1);

        if (dict.find('\n', offset) == std::string::npos) {
            offset = dict.length() + 1;
        } else {
            offset = dict.find('\n', offset) + 1;
        }

        dictWords.push_back(word);
        positions.push_back(begin);
        lengths.push_back(offset - begin - 1);
    }

    // Inserir palavras do dicionário na trie
    for (size_t i = 0; i < dictWords.size(); i++) {
        tree.insert(tree.get_root(), dictWords[i], positions[i], lengths[i]);
    }

    std::vector<std::string> inputWords;
    // Ler palavras de entrada
    while (true) {
        std::string inputWord;
        std::cin >> inputWord;

        if (inputWord == "0") {
            break;
        }

        inputWords.push_back(inputWord);
    }

    // Processar palavras de entrada e encontrar prefixos na trie
    for (const std::string& word : inputWords) {
        TrieNode* tmp = tree.findPrefix(word);

        if (tmp) {
            int tmp_prefix = tmp->valid ? tmp->prefix : tmp->prefix - 1;
            std::cout << word << " is prefix of " << tmp_prefix << " words" << std::endl;

            if (tmp->length > 1) {
                std::cout << word << " is at (" << tmp->position << "," << tmp->length << ")" << std::endl;
            }
        } else {
            std::cout << word << " is not prefix" << std::endl;
        }
    }

    return 0;
}
