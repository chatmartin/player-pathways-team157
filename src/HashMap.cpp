

#include "HashMap.h"

template<typename T>
int HashMap<T>::hashPlayer(Player player) {
    string name = player.getName();
    int hash = 0;
    for(int i = 0; i < name.length(); i++) {
        if(hash + int(name[i])*(i+1) < 0) {
            hash = 0;
        }
        hash += int(name[i])*(i+1);
    }
    return hash%capacity;
}

template<typename T>
HashMap<T>::HashMap() {
    capacity = 10;
}

template<typename T>
HashMap<T>::HashMap(int capacity):capacity(capacity) {
}

template<typename T>
HashMap<T>::~HashMap() {
    for(int i = 0; i < capacity; i++) {
        delete map[i];
    }
}

template<typename T>
void HashMap<T>::insert(Player& player, T& value) {
    int ind = hashPlayer(player);
    if(map[ind] == nullptr) {
        map[ind] = new PlayerList<T>();
        map[ind].head = new PlayerNode<T>();
        map[ind].head->key = player;
        map[ind].head->value = value;
    }
    else {
        PlayerNode<T>* curr = map[ind].head;
        while(curr->next != nullptr) {
            if(curr->key == player) {
                return;
            }
            curr = curr->next;
        }
        curr->next = new PlayerNode<T>();
        curr->next->key = player;
        curr->next->value = value;
    }
    size++;
    if(float(size)/capacity >= maxLF) {
        resize();
    }
}

template<typename T>
bool HashMap<T>::find(Player& player) {
    int ind = hashPlayer(player);
    if(map[ind] == nullptr) {
        return false;
    }
    PlayerNode<T>* curr = map[ind].head;
    while(curr != nullptr) {
        if(curr->key == player) {
            return true;
        }
        curr= curr->next;
    }
    return false;
}

template<typename T>
T &HashMap<T>::operator[](Player &player) {
    int ind = hashPlayer(player);
    PlayerNode<T>* curr = map[ind].head;
    while(curr != nullptr) {
        if(curr->key == player) {
            return curr->value;
        }
        curr= curr->next;
    }
    try {
        return T(nullptr);
    }
    catch(...) {
        return T();
    }
}

template<typename T>
void HashMap<T>::resize() {
    capacity*=2;
    vector<PlayerList<T>*> newMap(capacity);
    for(int i = 0; i < capacity/2; i++) {
        if(map[i]) {
            PlayerNode<T>* curr = map[i].head;
            int ind = hashPlayer(curr->key);
            if(!newMap[ind]) {
                newMap[ind] = new PlayerList<T>();
                newMap[ind].head = new PlayerNode<T>();
                newMap[ind].head->key = curr->key;
                newMap[ind].head->value = curr->value;
            }
            else {
                PlayerNode<T>* newCurr = newMap[ind].head;
                while(newCurr->next != nullptr) {
                    newCurr = newCurr->next;
                }
                newCurr->next = new PlayerNode<T>();
                newCurr->next->key = curr->key;
                newCurr->next->value = curr->value;
            }
        }
    }
    map = newMap;
}

template<typename T>
HashMap<T>& HashMap<T>::operator=(const HashMap &other) {
    capacity = other.capacity;
    size = other.size;
    maxLF = other.maxLF;
    for(int i = 0; i < capacity; i++) {
        delete map[i];
        map[i] = new PlayerList<T>();
        map[i].head = other.map[i].head;
        PlayerNode<T>* curr = map[i].head;
        PlayerNode<T>* otherCurr = other.map[i].head;
        while(otherCurr != nullptr) {
            curr->next = new PlayerNode<T>();
            curr->next->key = otherCurr->key;
            curr->next->value = otherCurr->value;
            otherCurr = otherCurr->next;
            curr = curr->next;
        }
    }
    return *this;
}
