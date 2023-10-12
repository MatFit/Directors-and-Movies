#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// create the hash table with default size
MovieHashTable::MovieHashTable() {
    table = new MovieNode*[table_size];
    for (int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Create hash table with parameter size
// basically make an array of movie node in heap
// each position at array is a pointer that points to null
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    table = new MovieNode*[table_size];
    for (int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() {
    // so to delete, start from the first position of table array
    // since I did chaining, I have to treat each position of table array like an LL
    // and delete it like an LL i don't feel like explaining more
    MovieNode* temp;
    MovieNode* temp_next;
    for(int i = 0; i < table_size; i++){ 
        temp = table[i];

        while(temp != NULL){
            temp_next = temp->next;
            delete temp;
            temp = temp_next;
        } 
        table[i] = NULL;
    } 
    // once it's cleared, i just delete the table
    delete[] table;
}

int MovieHashTable::convertStringtoNumber(string t){
    // this is a small function where I loop through a string
    // turn each character into an ascii number, sum it, and return it
    // that'll be it string to number, unique to it only (for the most part)
    int ascii_number = 0;
    for (int i = 0; i < t.length(); i++){
        ascii_number += int(t[i]);
    }
    return ascii_number;
}

// So i create this hash simply by converting the title and my identikey, take the sum, mod table size
// so i'll always have a number within the size of hashtable (no seg faults) and return that number
int MovieHashTable::hash(string title) { 
    return (convertStringtoNumber(title) + convertStringtoNumber(identikey)) % table_size;
}

// inserting title, i hash it, get an index
// go to the table with that index, see if there is anything
// if not then toss it in, if so then create a LL list, tossing it in the front
// so I don't have to traverse through the end of the LL
// increment collision too
void MovieHashTable::insert(string title, MovieNode* movie) {
    int index = hash(title);


    if(table[index] == NULL){
        table[index] = movie;
    }
    else if(table[index] != NULL){
        movie->next = table[index];
        table[index] = movie;
        setCollisions();
    }
}

// same idea, get index based off of title
// if there is nothing at that index, it means it wasn't in the hash table
// if there was then we have to assume it is a LL, so we start from whatever
// node is there, look to see if it is the same title, if so return that node,
// if not they traverse to the next node, if there is 
// if it hits NULL while loop stops, and return NULL meaning
// it's not in the hash table
MovieNode* MovieHashTable::search(string title) {
    int index = hash(title);

    if (table[index] == NULL){
        return NULL;
    }

    MovieNode *tracker = table[index];

    while (tracker != NULL){
        if (tracker->title == title){
            return tracker;
        }
        tracker = tracker->next;
    }
    return NULL;
}

// just return collision
int MovieHashTable::getCollisions() {
    return n_collisions;
}

// just add to collision
void MovieHashTable::setCollisions() {
    n_collisions++;
}

