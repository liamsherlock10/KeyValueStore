#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 4


typedef struct hashmap_element{
    int keyNumber;
    char *key;
    int value; //type hashmap_element *value. Does value make sense as name for a pointer to an array of many elements?
    int in_use; //used for collision_handling strat. collision happens when two keys go to the same array slot.
    struct hashmap_element* next;
} hashmap_element;

typedef struct hashmap{
    int table_size;
    int size;
    hashmap_element *data;
} hashmap;

hashmap *put();
hashmap *rehash();

int keyify(char keyword[], int tableSize){
    unsigned long hash = 5381;
    int c;

    while ((c = *keyword++)){
        hash = (hash << 5) + c;
    }
    return hash % tableSize;
}

hashmap *put(int keyNumber, char key[], int value, hashmap *map){
    /*
    NOTE: Adding to a pointer's value adds in units of the pointed-to's size, so you dont have to calculate that yourself. nice. 
    */
    hashmap_element* newItem = (hashmap_element *)malloc(sizeof(hashmap_element));
    newItem->key = key;
    newItem->keyNumber = keyNumber;
    newItem->value = value;
    newItem->in_use = 1;
    newItem->next = NULL;

   if (map->data[keyNumber].in_use != 1){
        map->data[keyNumber] = *newItem;
        map->size = (map->size)+1;
        free(newItem);
        return map;
   }else{
        //hashmap_element *current = malloc(sizeof(hashmap_element)) map->data[keyNumber]; // Need to malloc here I believe.
        hashmap_element *current = (hashmap_element *)malloc(sizeof(hashmap_element));
        *current = map->data[keyNumber];
        while(current->next){
            current = current->next;
        }
        current->next = newItem;
        map->size = (map->size)+1;
   }
   if(map->size >= (0.75*map->table_size)){
        printf("map->size before: %d\n", map->table_size);
        hashmap *newMap = calloc(1, sizeof(hashmap));
        newMap->data = calloc((map->table_size)*2, sizeof(hashmap_element)); 
        newMap->table_size = (map->table_size)*2;
        newMap->size = 0;
        newMap = rehash(map, map->table_size);
        printf("map->size after: %d\n", newMap->table_size);
        return newMap;
   }
   return map;
}

hashmap *rehash(hashmap *map, int tableSize){
    //dont rly know if those parameters are actually what we will need
    //This function will be called by put if the size/tableSize ratio gets high enough
    //This will pretty much just consist of a looping mechanism that runs keyify and put on entries with a new table size. Hopefully it works

    int newSize = tableSize*2;
    hashmap *newMap = calloc(1, sizeof(hashmap));//UNDERSTAND THIS BETTER
    newMap->data = calloc(newSize, sizeof(hashmap_element));
    newMap->table_size = newSize;
    newMap->size = 0;
    hashmap_element *current; //= (hashmap_element*)malloc(sizeof(hashmap_element));
    for (int i =0; i<map->table_size; i++){
        current = &map->data[i];
        while (current){
            if(current->key){
                int newIndex = keyify(current->key, newSize);
                //newMap = 
                put(newIndex, current->key, current->value, newMap);
            }
            current = current->next;
        }
        
    }
    printf("we have exited the for loop of rehash\n");
    return newMap;
}

int main(){
    hashmap *newMap = calloc(1, sizeof(hashmap));
    newMap->data = calloc(INITIAL_SIZE, sizeof(hashmap_element));
    newMap->table_size = INITIAL_SIZE;

    for(int i =0; i < 5; i++){
        char keywordExample[] = "balls";
        int keywordNumber = keyify(keywordExample, INITIAL_SIZE);

        printf("keyword number: %d\n", keywordNumber);
        //This is the start of the initialization of my dummy key/data pair
        int myValue = 5;
        // This is the end of that initialization
        
        newMap = put(keywordNumber, keywordExample, myValue, newMap);
    }
    //for (int i = 0; i< INITIAL_SIZE; i++){printf("hashmap element: %d\n", newMap->data[i].value);}

    return 0;
}

/*
next we will design the resize and rehash logic. Once the size of the table reaches 75% or so of the tablesize, we will call this.

It will double? the size of the hash table and then take all of the elements and run the 'keyify' function on each of them and
then call the put function to replace them using the new size. 

Should honestly be relatively easy. 
*/