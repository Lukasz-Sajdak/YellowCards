#include "notes.h"

Note::Note() = default;

Note::Note(const string& title, const string& content)
    : title(title), content(content) {}

string Note::getTitle() const {
    return title;
}

string Note::getContent() const {
    return content;
}

istream& operator>>(istream& is, Note& note) {
    getline(is, note.title);
    getline(is, note.content);
    return is;
}

ostream& operator<<(ostream& os, const Note& note) {
    os << note.title << "\n" << note.content;
    return os;
}

NotesApp::NotesApp() {
    loadNotes();
}

void NotesApp::displayMenu() {
    cout << "1. Dodaj notatke\n";
    cout << "2. Wyswietl notatki\n";
    cout << "3. Usun notatke\n";
    cout << "4. Wyjscie\n";
}

void NotesApp::run() {
    int choice;

    do {
        displayMenu();
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addNote();
            break;
        case 2:
            viewNotes();
            break;
        case 3:
            deleteNote();
            break;
        case 4:
            saveNotes();
            cout << "Zamykanie programu.\n";
            break;
        default:
            cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        }
    } while (choice != 4);
}

void NotesApp::addNote() {
    string title, content;
    cin.ignore();
    cout << "Podaj tytul notatki: ";
    getline(cin, title);
    cout << "Podaj tresc notatki: ";
    getline(cin, content);

    notes[nextId++] = Note{ title, content };
    cout << "Notatka dodana pomyslnie!\n";
}

void NotesApp::viewNotes() {
    if (notes.empty()) {
        cout << "Brak dostepnych notatek.\n";
        return;
    }

    cout << "=== Notatki ===\n";
    for (const auto& pair : notes) {
        cout << "ID: " << pair.first << "\n";
        cout << "Tytul: " << pair.second.getTitle() << '\n';
        cout << "Tresc: " << pair.second.getContent() << "\n\n";
    }
}

void NotesApp::deleteNote() {
    if (notes.empty()) {
        cout << "Brak dostępnych notatek do usuniecia.\n";
        return;
    }

    viewNotes();
    int idToDelete;
    cout << "Podaj ID notatki do usuniecia: ";
    cin >> idToDelete;

    auto it = notes.find(idToDelete);
    if (it != notes.end()) {
        notes.erase(it);
        cout << "Notatka o ID " << idToDelete << " usunieta pomyslnie!\n";
    }
    else {
        cout << "Notatka o ID " << idToDelete << " nie znaleziona.\n";
    }
}

void NotesApp::loadNotes() {
    ifstream inputFile("notes.txt");
    if (inputFile.is_open()) {
        Note note;
        while (inputFile >> note) {
            notes[nextId++] = note;
        }
        inputFile.close();
    }
}

void NotesApp::saveNotes() {
    ofstream outputFile("notes.txt");
    if (outputFile.is_open()) {
        for (const auto& pair : notes) {
            outputFile << pair.second << "\n";
        }
        outputFile.close();
    }
}

int main() {
    NotesApp notesApp;
    notesApp.run();

    return 0;
}
