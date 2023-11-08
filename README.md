# EzDB
***EZDB is a command-line-like DBMS system that is implemented in C. It supports basic CRUD operations and data structure algorithms in a DBMS system.***
## Getting Started
To compile using GCC, run `make` then `./ezdb` in terminal.
> For windows environment, it is adviced to run program in github codespace [here](https://github.com/codespaces)

---

# Hashtable Implementation Overview
## How It Works
A hashtable essentially transforms a `key` into an integer using a hash function. This integer serves as the index position that determines where the struct is located within an array.

### Traditional Approach: Adding to Struct
When we add data to a struct using traditional methods, it simply adds from index 0, leading to a time complexity of `O(n)` when searching for specific data like "marry."

```c
table = [struct[tom, 1234], struct[name, number], struct[name, number], struct[marry, 5434], struct[name, number]
print(table[3]) // Output: struct[marry, 5434]
```

This means that if we want to find "marry," we have to loop through the list, resulting in a time complexity of `O(n)`.

### Improved Approach: Using Hashtable
By using a hashtable, we can achieve `O(1)` time complexity because it uses the `key` as the index value.

1. First, initialize an empty table with a length of 5:
   ```
   table = [NULL, NULL, NULL, NULL, NULL]
   ```

2. Use a hash function to convert the key to an integer:
   ```c
   unsigned long simple_hash(char *str) {
       return SUM([char for char in str]) % MAX_TABLE_LEN;
   }
   ```

   - To convert a character array to an unsigned long, we add the ASCII values of all characters in a string.
   - To ensure that the hash value stays within the predefined table length, we use the `%` operator.

3. With the hashed value, we can store our data:
   ```c
   hashed_key = simple_hash("marry") // Output: 3
   table[hashed_key] = struct[marry, 5434]
   ```

4. For queries, we can use the following:
   ```c
   hashed_key = simple_hash("marry") // Output: 3
   printf("---%s-%s---", table[hashed_key]->name, table[hashed_key]->number) // Output: ---marry-5434---
   ```

By calling `table[hashed_key]`, we achieve a time complexity of `O(1)`.

## Collision Handling

### What Is Collision?
Collision occurs when two keys processed by a hash function return the same result. For example:

```c
tom = hash("tom") // Output: 5
table[tom] = "yay"
jerry = hash("jerry") // Output: 5
table[jerry] = "Nooo"
```

Here, both "Tom" and "Jerry" have the same hash value, and storing one overwrites the other.

### How to Tackle Collision
To handle collisions, we use chaining to store collided keys. Chaining involves using a single-linked list, where a struct points to another struct. 

**Normal struct:**
```c
typedef struct person
{
    char name[MAX_CHAR_LEN];   // The key
    char number[MAX_CHAR_LEN]; // The value
    struct person *next;       // Chaining to tackle collision
} person;
```

**Struct with Linked List (Three Levels):**
```c
struct person
{
    char name[MAX_CHAR_LEN];   // The key
    char number[MAX_CHAR_LEN]; // The value
    struct person *next = struct person  // Level 1 chaining to tackle collision
    {
        char name[MAX_CHAR_LEN];   // The key
        char number[MAX_CHAR_LEN]; // The value
        struct person *next = struct person  // Level 2 chaining to tackle collision
        {
            char name[MAX_CHAR_LEN];   // The key
            char number[MAX_CHAR_LEN]; // The value
            struct person *next = struct person *next;  // Level 3 chaining to tackle collision
        }
    }
}
```

When a collision occurs, we create a new node and link it to the previous node. This way, we can keep the size of our table small and minimize the time taken to retrieve collided data.
