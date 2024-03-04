#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

// Structure to represent a symbol table entry
typedef struct SymbolTableEntry {
    char *key;
    int value;
    struct SymbolTableEntry *next;
} SymbolTableEntry;

// Structure to represent a symbol table
typedef struct SymbolTable {
    SymbolTableEntry *table[SIZE];
} SymbolTable;

// Function to create a new symbol table entry
SymbolTableEntry *createEntry(char *key, int value) {
    SymbolTableEntry *newEntry = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    if (newEntry == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->next = NULL;
    return newEntry;
}

// Function to create a new symbol table
SymbolTable *createSymbolTable() {
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (table == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < SIZE; i++) {
        table->table[i] = NULL;
    }
    return table;
}

// Function to calculate hash value
int hash(char *key) {
    int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];
    }
    return hashValue % SIZE;
}

// Function to insert a key-value pair into the symbol table
void insert(SymbolTable *table, char *key, int value) {
    int index = hash(key);
    SymbolTableEntry *newEntry = createEntry(key, value);
    if (table->table[index] == NULL) {
        table->table[index] = newEntry;
    } else {
        SymbolTableEntry *temp = table->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newEntry;
    }
}

// Function to search for a key in the symbol table
int search(SymbolTable *table, char *key) {
    int index = hash(key);
    SymbolTableEntry *entry = table->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return -1;
}

// Function to delete a key from the symbol table
void delete(SymbolTable *table, char *key) {
    int index = hash(key);
    SymbolTableEntry *current = table->table[index];
    SymbolTableEntry *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                table->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to display the symbol table
void display(SymbolTable *table) {
    printf("Symbol Table:\n");
    for (int i = 0; i < SIZE; i++) {
        SymbolTableEntry *entry = table->table[i];
        printf("[%d]: ", i);
        while (entry != NULL) {
            printf("(%s, %d) -> ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("NULL\n");
    }
}

// Function to free memory allocated to symbol table
void destroy(SymbolTable *table) {
    for (int i = 0; i < SIZE; i++) {
        SymbolTableEntry *entry = table->table[i];
        while (entry != NULL) {
            SymbolTableEntry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

int main() {
    SymbolTable *table = createSymbolTable();

    // Insert some entries
    insert(table, "x", 10);
    insert(table, "y", 20);
    insert(table, "z", 30);
    insert(table, "a", 40);

    // Display the symbol table
    display(table);

    // Search for a key
    printf("Value of 'x': %d\n", search(table, "x"));

    // Delete a key
    delete(table, "y");
    printf("After deleting 'y':\n");
    display(table);

    // Free memory
    destroy(table);

    return 0;
}

