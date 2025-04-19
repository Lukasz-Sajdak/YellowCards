#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>

using namespace std;

class Note {
public:
    Note();
    Note(const string& title, const string& content);

    string getTitle() const;
    string getContent() const;

    friend istream& operator>>(istream& is, Note& note);
    friend ostream& operator<<(ostream& os, const Note& note);

private:
    string title;
    string content;
};

class NotesApp {
public:
    NotesApp();

    void displayMenu();
    void run();

private:
    map<int, Note> notes;
    int nextId = 1;

    void addNote();
    void viewNotes();
    void deleteNote();
    void loadNotes();
    void saveNotes();
};
