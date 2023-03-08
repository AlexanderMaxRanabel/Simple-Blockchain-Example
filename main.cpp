#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Block {
public:
    Block(std::string data, std::string prevHash) {
        this->data = data;
        this->prevHash = prevHash;
        this->hash = calcHash();
        this->next = nullptr;
    }

    std::string getData() {
        return data;
    }

    std::string getPrevHash() {
        return prevHash;
    }

    std::string getHash() {
        return hash;
    }

    Block* getNext() {
        return next;
    }

    void setNext(Block* block) {
        next = block;
    }

private:
    std::string data;
    std::string prevHash;
    std::string hash;
    Block* next;

    std::string calcHash() {
        std::stringstream ss;
        ss << data << prevHash;

        // Simple hash function: sum of ASCII codes of characters
        int hash = 0;
        for (int i = 0; i < ss.str().length(); i++) {
            hash += (int) ss.str()[i];
        }

        std::stringstream hashStr;
        hashStr << hash;

        return hashStr.str();
    }
};

class Blockchain {
public:
    Blockchain() {
        genesisBlock = new Block("Genesis Block", "");
        head = genesisBlock;
    }

    ~Blockchain() {
        Block* current = head;
        while (current != nullptr) {
            Block* next = current->getNext();
            delete current;
            current = next;
        }
    }

    void addBlock(std::string data) {
        Block* newBlock = new Block(data, head->getHash());
        head->setNext(newBlock);
        head = newBlock;
    }

    void printChain() {
        Block* current = genesisBlock;
        while (current != nullptr) {
            std::cout << "Data: " << current->getData() << std::endl;
            std::cout << "Hash: " << current->getHash() << std::endl;
            current = current->getNext();
        }
    }

private:
    Block* genesisBlock;
    Block* head;
};

int main() {
    Blockchain blockchain;
    std::cout << "Enter Index: ";
    int indexwant;
    std::cin >> indexwant;
    std::string Want[indexwant];
    if (indexwant < 2 || indexwant > 20) {
      return 1;
    } else {
      int i = 0;
      while (i < indexwant) {
        std::cout << "Enter Block String: ";
        int indexplace = 0;
        std::cin >> Want[indexplace];
        i = i + 1;
        blockchain.addBlock(Want[indexplace]);
        indexplace = indexplace + 1;
      }
    }
    
    /*blockchain.addBlock("Block 1");
    blockchain.addBlock("Block 2");
    blockchain.addBlock("Block 3");
    blockchain.addBlock("Block"); */

    blockchain.printChain();

    return 0;
  }
