#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 1024


typedef struct hashmap_element{
    int key;
    int value; //type hashmap_element *value. Does value make sense as name for a pointer to an array of many elements?
    int in_use; //used for collision_handling strat. collision happens when two keys go to the same array slot. 
} hashmap_element;

typedef struct hashmap{
    int table_size;
    int size;
    hashmap_element *data;
} hashmap;

int keyify(char keyword[], int tableSize){
    unsigned long hash = 5381;
    int c;

    while ((c = *keyword++)){
        printf("this is our character: %c\n", c);
        hash = (hash << 5) + c;
    }
    return hash % tableSize;
}

void put(int key, int value, hashmap *map){
    /*
    NOTE: Adding to a pointer's value adds in units of the pointed-to's size, so you dont have to calculate that yourself. nice. 
    */

    //1) Take the key and translate it into a slot number 0-1023
    hashmap_element newItem;
    newItem.key = key;
    newItem.value = value;
    newItem.in_use = 1;
    
    //arrow dereferences AND accesses a field. just a '.' accesses a field without dereferencing. 
    map->data[key] = newItem;
    map->size = map->size+1;
}

int main(){
    hashmap *newMap = calloc(1, sizeof(hashmap));
    newMap->data = calloc(INITIAL_SIZE, sizeof(hashmap_element));
    newMap->table_size = INITIAL_SIZE;

    char keywordExample[] = "balls";
    int keywordNumber = keyify(keywordExample, INITIAL_SIZE);

    //printf("keyword number: %d\n", keywordNumber);
    //This is the start of the initialization of my dummy key/data pair
    int myValue = 5;
    // This is the end of that initialization

    put(keywordNumber, myValue, newMap);

    for (int i = 0; i< INITIAL_SIZE; i++){printf("hashmap element: %d\n", newMap->data[i].value);}

    return 0;
}

//We now have a common algorithm for placement in the map. Our next thing to do is figure out what to do for collisions.
//How do we want to handle collisions? How do we use shifting a value over if a spot is taken but theres another one thats free? 
//Do we have eviction policy or chaining or both? 

/*
Ok so the next part of this workflow is going to be storing the key and value in each slot that we store something. Then, we
are going to add chaining. This means that each entry into the hash will have a pointer called *next that will point to the 
next entry that has the same index in the hashmap. 
*/