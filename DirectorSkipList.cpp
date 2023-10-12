#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;


// create head with default level
DirectorSkipList::DirectorSkipList() {
    levels = DEFAULT_LEVELS;
    capacity = DEFAULT_CAPACITY;
    head = new DirectorSLNode("",levels);
}
// create head with given level, set capa and level
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode("",levels);
}

// delete like regular LL, because Skip List is primarly vector
// and vector is a data in the node, deleting node delete vector too
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode *tracker = head;
    DirectorSLNode *prior = NULL;
    while (tracker->next[0] != NULL){
        prior = tracker;
        tracker = tracker->next[0];
        delete prior;
    }
    delete tracker;
}


// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // search for director
    // explain search first
    DirectorSLNode *check = search(director);
    
    // if we find the node, we just add the movie, if not
    // do the first if statement where it is NULL
    if(check == NULL){
        // check if capacity has been hit
        if (size >= capacity){
            cout << "Max limit reached" << endl;
            return;
        }
        // generate a level for the soon to be made node]
        // this was given to us on the project pdf
        int n_levels = 1;
        while(n_levels < levels && rand() % 2 == 0){
            n_levels++;
        }
        

        // starting at head, we also create an array of pointers
        // that will store pointers that will soon to point to the new node
        DirectorSLNode *tracker = head;
        DirectorSLNode *prior[levels];

        // same idea with the search, start from up top on level and work way down
        // until we find a valid position where the new node could be at relative
        // to it's alphabetical order
        // only difference is each level we go down, we also have to store it in the
        // same position in the prior array as those nodes will be pointing to the new node
        // it's better if I draw a visual of how this will look like
        // also it is not alway that everything in the prior array will point to the new node, it
        // depends of the level of the new node too
        for (int i = levels - 1; i >= 0; i--){
            while(tracker->next[i] != NULL && tracker->next[i]->director < director){
                tracker = tracker->next[i];
            }
            prior[i] = tracker;
        }


        // by now we should have the position figured out based off prior level 0
        // so we create the node and add the movie in
        DirectorSLNode *director_new = new DirectorSLNode(director,n_levels);
        director_new->addMovie(_movie);

        // now whatever n_levels is it the level of the new node, so n_levels could
        // be less than or equal to the level now, less than is fine it just means we won't use
        // whatever is in the high level of prior. But now, starting from the top level of the new
        // director, it will point to whatever the prior was pointing to because it kinda just
        // budges itself in. And now the prior will point to the director
        // I can draw a visual of this to since it's easier to explain that way
        for(int i = n_levels - 1; i >= 0; i--){
            director_new->next[i] = prior[i]->next[i];
            prior[i]->next[i] = director_new;
        }
        // add the size yk because we made a new node in the SL and yeah
        size++;
    }
    else{
        // already explained above
        check->addMovie(_movie);
    }
    
}

// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) {
    
    // start from head
    DirectorSLNode *tracker = head;

    // and the top level of head, working down, if what it points to next
    // is not a NULL and what is it pointing at is less than director, traverse there
    // because this SL is sorted from least to greatest (alphabetically), we only move
    // forward if the director we are looking for is greater than where we are at
    for(int i = levels - 1; i >= 0; i--){
        while(tracker->next[i] != NULL && tracker->next[i]->director < director){
            tracker = tracker->next[i];
        }
    }

    // by then, we will assumingly be one away from the director, so we go to the base of the SL
    // and if the following equals (we didn't do that in the while loop for a reason)
    // then we return that tracker, if not then that means it was never there so return NULL
    tracker = tracker->next[0];

    if ((tracker != NULL) && (tracker->director == director)){
        return tracker;
    }
    else{
        return NULL;
    }

}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    // starting from head
    DirectorSLNode *tracker = head;
    
    // similar to everthing above, but I started from
    // level 0 to whatever
    // but at level 0, I do what is below the cout << "Level"
    // (the tracker = tracker->next[i]; not in the while loop)
    // to skip over head always. But once done then while tracker doesn't
    // point to a NULL at whatever level it is, I print it's director,
    // and move foward until Null, reset tracker to head again, go down a level
    // rinse and repeat
    for (int i = 0; i < levels; i++){
        cout << "Level " << i << ": ";
        tracker = tracker->next[i];
        while(tracker != NULL){
            cout << tracker->director << ", ";
            tracker = tracker->next[i];
        }
        cout << endl;
        tracker = head;
    }
}

