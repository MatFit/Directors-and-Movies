#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) {
    // TODO
    // more stuff, pass the right nasdoiasdasoin 
    if (argc != 4){
        cout << "Invalid number of arguments" << endl;
        return 0;
    }
    // stuff
    string choice = "";
    string movie_title = "";
    string director_name = "";
    MovieNode *temp2 = NULL;

    // Creating DS
    MovieHashTable movies(atoi(argv[2]));
    DirectorSkipList director(atoi(argv[3]),10);
    // inserting it through this
    readMovieCSV(argv[1],movies,director);

    director.prettyPrint();

    // print stuff
    cout << "Number of collisions: " << movies.getCollisions() << endl;
    display_menu();

    
    // a stupid menu
    // alot of it is just search, find it, print the data values
    // if NULL say it doesn't exist and yea
    while (choice != "5"){
        getline(cin,choice);
        if (choice == "1"){
            cout << "Enter movie name: ";
            getline(cin,movie_title);
            temp2 = movies.search(movie_title);
            if (temp2 != NULL){
                cout << "Movie: " << temp2->title << " Director: " << temp2->director << endl;
            }
            else if (temp2 == NULL){
                cout << "The movie does not exist in the database" << endl;
            }
        }
        else if (choice == "2"){
            cout << "Enter director name: " << endl;
            getline(cin,director_name);
            DirectorSLNode *temp3 = director.search(director_name);
            if (temp3 == NULL){
                cout << "The director does not exist in the database" << endl;
            }
            else{
                cout << "Number of Movies: " << temp3->movies.size() << endl;
            }
        }
        else if (choice == "3"){
            cout << "Enter movie name: ";
            getline(cin,movie_title);
            temp2 = movies.search(movie_title);
            if (temp2 != NULL){
                cout << "Summary: " << temp2->title << " is a " << temp2->year << " film featuring '" << temp2->actors << "'." << endl;
                cout << "Description: " << temp2->description << endl;
            }
            else if (temp2 == NULL){
                cout << "The movie does not exist in the database" << endl;
            }
        }
        else if (choice == "4"){
            cout << "Enter director name: " << endl;
            getline(cin,director_name);
            DirectorSLNode *temp4 = director.search(director_name);
            if(temp4 == NULL){
                cout << "The director does not exist in the database" << endl;
            }
            else{
                cout << "Movies: ";
                for (int i = 0; i < temp4->movies.size(); i++){
                    cout << " | " << temp4->movies[i]->title << " | ";
                }
                cout << endl;
            }
        }
        else if (choice == "5"){
            cout << "Goodbye!" << endl;
            return 0;
        }
        else{
            cout << "Invalid Input, try again" << endl;
        }
        choice = "";
        cout << endl;
        cout << endl;
        cout << "Number of collisions: " << movies.getCollisions() << endl;
        display_menu();
    }

    return 0;
}


// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
// Ok so yk what we did when we parsed and added into the hashtable, we do it in this function
// and we'll do it as well for the director skip list
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    string line;
    ifstream file(filename);
    getline(file,line);


    while(getline(file,line)){
        MovieNode* temp = parseMovieLine(line);
        movieTable.insert(temp->title,temp);
        directorList.insert(temp->director,temp);
    }
    file.close();
}

// Function to display the menu options
// kinda said already
void display_menu() {

    // MovieHashtable class variable "n_collisions"
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
    cout << endl;
    cout << "Enter an Option: " << endl;
    
}
