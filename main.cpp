#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Size of the hash table (spellbook)
const int TABLE_SIZE = 10;

// Struct to represent a spell (key-value pair)
struct Spell {
    string spellName;
    string effect;
    Spell* next;  // Pointer for collision handling (chaining)

    // Constructor
    Spell(string name, string eff) : spellName(name), effect(eff), next(nullptr) {}
};

// Hash table (spellbook) class
class Spellbook {
private:
    vector<Spell*> table;  // The pages of the spellbook (hash table)

    int hashFunction(string spellName) {
        // Example: Return the sum of ASCII values of the spellName characters
        // as the hash value, then return the modulus of the hash and table size.
        int hash = 0;
        for (int i = 0; i < spellName.length(); i++) {
            hash += spellName[i];  // Sum of ASCII values of characters
        }
        return hash % TABLE_SIZE;        

    }

public:
    // Constructor
    Spellbook() {
        table.resize(TABLE_SIZE, nullptr);  // Initialize the spellbook with empty pages
    }

    // TODO: Complete the addSpell function to insert a spell into the hash table
    void addSpell(string spellName, string effect) {
        int index = hashFunction(spellName);
        Spell* newSpell = new Spell(spellName, effect);
        
        Spell* prev = nullptr;
        Spell* entry = table[index];

        while (entry != nullptr) { // traverse to end of linked list
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            if (prev == nullptr) {
                table[index] = newSpell; // no collision
            }
            else {
                prev->next = newSpell; // collision
            }
        }

        // Collision handling logic goes here (use chaining)
        // If no collision, insert the spell. If collision, handle it.
        
        cout << "The spell '" << spellName << "' has been added to the spellbook!\n";
    }

    // TODO: Complete the castSpell function to retrieve a spell from the hash table
    void castSpell(string spellName) {
        int index = hashFunction(spellName);
        Spell* current = table[index];
        bool flag = false;
        
        while (current != nullptr) {
            if (current->spellName == spellName) {
                cout << "Casting '" << spellName << "': " << current->effect << endl;
                return;
            }
            current = current->next;
        }
        if (flag == false)
        {
            cout << "The spell '" << spellName << "' was not found in the spellbook!\n";
        }


        // Traverse the linked list (chaining) at the index to find the spell
        // If found, print the spell's effect, else print "not found"

    }

    // TODO: Complete the removeSpell function to delete a spell from the hash table
    void removeSpell(string spellName) {
        int index = hashFunction(spellName);
        Spell* current = table[index];
        Spell* previous = nullptr;

        
        while (current != nullptr && current->spellName != spellName) {
            previous = current;
            current = current->next; // traverse through ll until spellname is found
        }

        if (current == nullptr) { // spell not found
            cout << spellName << "' was not found in the spellbook.\n";
            return;
        }

        if (previous == nullptr) {
            table[index] = current->next;
        }
        else {
            previous->next = current->next;
        }

        // Traverse the linked list and remove the spell if found

        delete current;
        cout << "The spell '" << spellName << "' has been removed from the spellbook.\n";
    }
};

int main() {
    // Create the spellbook
    Spellbook spellbook;

    // TODO: Add 6 test cases
    spellbook.addSpell("Fireball", "Deals 100 fire damage.");
    spellbook.addSpell("Healing Light", "Restores 50 health.");

    spellbook.addSpell("Thunderclap", "Stuns enemies for 2 seconds."); // 1
    spellbook.addSpell("Arcane Blast", "Deals 35 arcane damage."); // 2
    spellbook.addSpell("Venomous Bite", "Inflicts 30 poison damage over time."); // 3
    spellbook.addSpell("Blizzard", "Deals 20 cold damage to all enemies."); // 4
    spellbook.addSpell("Levitation", "Allows you to levitate for 10 seconds."); // 5
    spellbook.addSpell("Summon Phoenix", "Summons a phoenix to fight for you."); // 6

    // Test 3 retrievals
    spellbook.castSpell("Fireball");

    spellbook.castSpell("Venomous Bite"); // 1
    spellbook.castSpell("Summon Phoenix"); // 2
    spellbook.castSpell("Levitation"); // 3

    // Test 2 spell deletion
    spellbook.removeSpell("Fireball");
    spellbook.castSpell("Fireball");

    spellbook.removeSpell("Blizzard"); // 1
    spellbook.castSpell("Blizzard");

    spellbook.removeSpell("Thunderclap"); // 2
    spellbook.castSpell("Thunderclap");


    return 0;
}
