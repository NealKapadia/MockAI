#include <iostream>
#include <fstream>

using namespace std;

// Constant array size, 26 letters + space + newline
const int CHAR_SIZE = 28;

// Function to map character to an index by checking for space otherwise checking the letter
int charToIndex(char c)
{
    if (c == ' ')
        return 26;
    else if (c == '\n')
        return 27;
    else
        return c - 'a';
}

// Function to map index to character (opposite of above function)
char indexToChar(int index)
{
    if (index == 26)
        return ' ';
    else if (index == 27)
        return '\n';
    else
        return 'a' + index;
}

// Class for Character Distribution
class CharDistribution
{
private:
    int counts[CHAR_SIZE]; // initialize array for char distribution
    int totalCount;        // total number of characters

public:
    // Constructor for the CharDistribution class
    // Initialize counts and totalcount
    CharDistribution()
    {
        for (int i = 0; i < CHAR_SIZE; i++)
            counts[i] = 0;
        totalCount = 0;
    }

    // Increment count for character c every time it occurs
    void occurs(char c)
    {
        int index = charToIndex(c);
        counts[index]++;
        totalCount++;
    }

    // Get a random character based on distribution
    // Used the implementation from documentation
    // Returns a random character based on the distribution of characters in the text
    char getRandomChar()
    {
        if (totalCount == 0)
        {
            // Return a random character if no data
            return indexToChar(rand() % CHAR_SIZE);
        }
        int r = rand() % totalCount + 1; // Random number between 1 to total characters
        int sum = 0;
        for (int i = 0; i < CHAR_SIZE; i++)
        {
            sum += counts[i];
            if (sum >= r)
            {
                return indexToChar(i); // Return random char based on distribution
            }
        }
        // Fallback
        return indexToChar(CHAR_SIZE - 1);
    }
};

// Abstract Map class that defines the interface for map-based operations
// Not necessary but helpful when implementing both map structures in 1 file
class Map
{
public:
    virtual int Size() = 0;                                      // Get the size of the map
    virtual bool Empty() = 0;                                    // Check if the map is empty
    virtual CharDistribution *Find(const char *k) = 0;           // Find a value by key
    virtual void Insert(const char *k, CharDistribution *v) = 0; // Insert a key-value pair
    virtual void Remove(const char *k) = 0;                      // Remove a key-value pair
    virtual ~Map() {}                                            // Destructor
};

// Node for HashMap chaining
struct HashNode
{
    char *key;
    CharDistribution *value;
    HashNode *next;

    HashNode(const char *k, CharDistribution *v)
    {
        key = new char[strlen(k) + 1];
        strcpy(key, k);
        value = v;
        next = nullptr;
    }

    ~HashNode()
    {
        delete[] key;
        delete value;
    }
};

// Map implementation using Hash Table with Separate Chaining
class HashMap : public Map
{
private:
    int TABLE_SIZE;                           // Size of the table
    HashNode **table;                         // Seperate chaining hashmap
    int size;                                 // Amount of words inserted
    const float LOAD_FACTOR_THRESHOLD = 0.75; // Load factor

    // Hash function
    int hash(const char *s, int tableSize)
    {
        unsigned long hash = 5381;
        int c;
        while ((c = *s++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % tableSize;
    }

    // Rehash function to resize the table
    void rehash()
    {
        int newTableSize = TABLE_SIZE * 2; // Double the table size
        HashNode **newTable = new HashNode *[newTableSize];

        // Initialize the new table
        for (int i = 0; i < newTableSize; i++)
            newTable[i] = nullptr;

        // Re-insert all elements from the old table into the new table
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode *node = table[i];
            while (node != nullptr)
            {
                HashNode *nextNode = node->next;

                // Compute new hash index based on new table size
                int newIndex = hash(node->key, newTableSize);
                node->next = newTable[newIndex];
                newTable[newIndex] = node;

                node = nextNode;
            }
        }

        // Delete the old table
        delete[] table;

        // Update table and table size
        table = newTable;
        TABLE_SIZE = newTableSize;
    }

public:
    // Constructor for the table
    HashMap()
    {
        TABLE_SIZE = 10007; // Initial table size
        table = new HashNode *[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
        size = 0;
    }
    // Destructor for the table
    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode *node = table[i];
            while (node != nullptr)
            {
                HashNode *prev = node;
                node = node->next;
                delete prev;
            }
        }
        delete[] table;
    }
    // Get function to return size
    int Size()
    {
        return size;
    }
    // Checks if the hashtable is empty
    bool Empty()
    {
        return size == 0;
    }
    // Finds a node in the hashtable given the character
    CharDistribution *Find(const char *k)
    {
        int index = hash(k, TABLE_SIZE);
        HashNode *node = table[index];
        while (node != nullptr)
        {
            if (strcmp(node->key, k) == 0)
                return node->value;
            node = node->next;
        }
        return nullptr;
    }
    // Inserts a new node as well as creates a char distribution for that node and checks for rehash
    void Insert(const char *k, CharDistribution *v)
    {
        int index = hash(k, TABLE_SIZE);
        HashNode *node = table[index];
        while (node != nullptr)
        {
            if (strcmp(node->key, k) == 0)
            {
                // Key exists, replace value
                delete node->value;
                node->value = v;
                return;
            }
            node = node->next;
        }
        // Insert new node
        HashNode *newNode = new HashNode(k, v);
        newNode->next = table[index];
        table[index] = newNode;
        size++;

        // Rehash if load factor exceeds threshold
        if ((float)size / TABLE_SIZE > LOAD_FACTOR_THRESHOLD)
        {
            rehash();
        }
    }
    // Removes a node from the hashtable given the node to remove
    void Remove(const char *k)
    {
        int index = hash(k, TABLE_SIZE);
        HashNode *node = table[index];
        HashNode *prev = nullptr;

        while (node != nullptr && strcmp(node->key, k) != 0)
        {
            prev = node;
            node = node->next;
        }

        if (node == nullptr)
            return;

        if (prev == nullptr)
        {
            table[index] = node->next;
        }
        else
        {
            prev->next = node->next;
        }

        delete node;
        size--;
    }
};

// Main function
int main()
{
    srand(time(NULL)); // Seed random number generator

    // Prompt for input file name
    string inputFileName = "tests/input.txt";

    // Read input text
    ifstream inputFile(inputFileName.c_str());
    if (!inputFile)
    {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    string text;
    char c;
    while (inputFile.get(c))
    {
        // Convert to lower case and keep only 'a'-'z' and ' '
        if ((c >= 'a' && c <= 'z') || c == ' ' || c == '\n')
            text += c;
    }
    inputFile.close();

    // Prompt for window size
    int w;
    cout << "Enter window size: ";
    cin >> w;
    if (w <= 0)
    {
        cerr << "Window size must be positive." << endl;
        return 1;
    }

    // Prompt for output length
    int outputLength;
    cout << "Enter output length: ";
    cin >> outputLength;
    if (outputLength <= 0)
    {
        cerr << "Output length must be positive." << endl;
        return 1;
    }

    // Initialize map to Hashmap
    Map *map = new HashMap();

    // Build the map
    int textLength = text.length();
    for (int i = 0; i <= textLength - w - 1; i++)
    {
        // Extract window
        char *window = new char[w + 1];
        strncpy(window, text.c_str() + i, w);
        window[w] = '\0';

        // Get next character
        char nextChar = text[i + w];

        // Find or create CharDistribution
        CharDistribution *cd = map->Find(window);
        if (cd == nullptr)
        {
            cd = new CharDistribution();
            map->Insert(window, cd);
        }
        cd->occurs(nextChar);

        delete[] window;
    }

    // Generate output text
    string output = text.substr(0, w); // Start with first w characters
    while ((int)output.length() < outputLength)
    {
        // Get last w characters as window
        char *window = new char[w + 1];
        strncpy(window, output.c_str() + output.length() - w, w);
        window[w] = '\0';

        // Find CharDistribution
        CharDistribution *cd = map->Find(window);
        char nextChar;
        if (cd != nullptr)
        {
            nextChar = cd->getRandomChar();
        }
        else
        {
            // If window not found, choose random character
            nextChar = indexToChar(rand() % CHAR_SIZE);
        }
        output += nextChar;

        delete[] window;
    }

    // Write output to file
    ofstream outputFile("tests/output.txt");
    if (!outputFile)
    {
        cerr << "Error opening output file." << endl;
        return 1;
    }
    outputFile << output;
    outputFile.close();

    cout << "Output written to output.txt" << endl;

    delete map;
    return 0;
}
