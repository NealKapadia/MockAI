# MockAI

MockAI is a C++ program that generates text based on character distributions, including spaces and newline characters. It reads input text, builds a character distribution model, and generates random text based on the learned probabilities.

## Features
- Tracks occurrences of letters, spaces, and newline characters
- Uses a hashmap for efficient data storage and retrieval
- Generates text using a sliding window approach

## Window Size
The **window size** determines how many consecutive characters are considered when building the character distribution model. 

- A **larger window size** captures more context, making the generated text more structured.
- A **smaller window size** results in more random text but can still maintain some coherence.
- The program scans the input text in overlapping segments of length equal to the window size and records the frequency of the next character.

Example:
For input text: `hello world` and window size = 3, the program considers:
```
hel -> next: l
ell -> next: o
llo -> next:  
lo  -> next: w
...
```
This builds a probability distribution for predicting the next character.

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/MockAI.git
   cd MockAI
   ```
2. Compile the program using g++:
   ```sh
   g++ -o MockAI main.cpp
   ```

## Usage
Run the program with test files:
```sh
./MockAI
```

By default, the program reads from `tests/input.txt` and writes output to `tests/output.txt`.

## File Structure
```
MockAI/
│── main.cpp        # Main source file
│── tests/          # Directory for test files
│   ├── input.txt   # Input test file
│   ├── output.txt  # Output generated from test input
│── README.md       # Project documentation
│── .gitignore      # Ignored files for Git
```

## Testing
To run the program with test input:
1. Place your input text inside `tests/input.txt`.
2. Run the program:
   ```sh
   ./MockAI
   ```
3. The generated output will be saved in `tests/output.txt`.

## Contributions
Pull requests are welcome! If you have any improvements or bug fixes, feel free to submit a PR.

