# MockAI

MockAI is a C++ program that generates text based on character distributions, including spaces and newline characters. It reads input text, builds a character distribution model, and generates random text based on the learned probabilities.

## Features
- Tracks occurrences of letters, spaces, and newline characters
- Uses a hashmap for efficient data storage and retrieval
- Generates text using a sliding window approach

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
Run the program:
```sh
./MockAI
```

Provide input parameters such as window size and output length when prompted.

## File Structure
```
MockAI/
│── main.cpp        # Main source file
│── merchant.txt    # Sample input text file
│── output.txt      # Generated output text
│── README.md       # Project documentation
│── .gitignore      # Ignored files for Git
```

## Contributions
Pull requests are welcome! If you have any improvements or bug fixes, feel free to submit a PR.

