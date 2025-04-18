
#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>

#include "Player.h"

template <typename T>
struct PlayerNode {
    Player& key;
    T value;
    PlayerNode* next;
};
template <typename T>
struct PlayerList {
    PlayerNode<T>* head;
    ~PlayerList() {
        PlayerNode<T>* current = head;
        while(current != nullptr) {
            PlayerNode<T>* del = current;
            current = current->next;
            delete del;
        }
    }
};

template <typename T>
class HashMap {
private:
    vector<PlayerList<T>*> map;
    int capacity;
    int size=0;
    const float maxLF = 0.6;
    int hashPlayer(Player player);
    void resize();
public:
    HashMap();
    HashMap(int capacity);
    ~HashMap();
    void insert(Player& player, T& value);
    T& operator[](Player& player);
    bool find(Player& player);
};



#endif //HASHMAP_H
