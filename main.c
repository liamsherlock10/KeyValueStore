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

int put(int key, int value, hashmap *map){
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
    return 5;
}

int main(){
    hashmap *newMap = calloc(1, sizeof(hashmap));
    newMap->data = calloc(INITIAL_SIZE, sizeof(hashmap_element));
    newMap->table_size = INITIAL_SIZE;

    //This is the start of the initialization of my dummy key/data pair
    int myValue = 5;
    // This is the end of that initialization

    int x = put(2, myValue, newMap);

    for (int i = 0 ;i<1023;i++){
        printf("hashmap element: %d", newMap->data[i].value);
    }
    return 0;
}