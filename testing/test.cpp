#include <iostream> // For std::cout and std::endl
#include "catch.hpp"

#include <unordered_set>
#include <vector>
#include "LSystemInterpreter.hpp"
#include <string>
#include <fstream>


TEST_CASE("isValidProduction") {
    using TestType = std::string;

    //Define productions and alphabet
    const auto invalid_production = Production<TestType>("Q", {"Q", "S"});
    const auto semi_invalid_production_1 = Production<TestType>("q", {"Q", "S"});
    const auto semi_invalid_production_2 = Production<TestType>("Q", {"q", "s"});
    const auto valid_production = Production<TestType>("q", {"s", "s"});
    const std::unordered_set<TestType> alphabet{"q", "s"};

    // Check if the productions are valid with the given alphabet
    CHECK(! isValidProduction(invalid_production, alphabet));
    CHECK(! isValidProduction(semi_invalid_production_1, alphabet));
    CHECK(! isValidProduction(semi_invalid_production_2, alphabet));
    CHECK(  isValidProduction(valid_production, alphabet));
}

TEST_CASE("Constructor") {
    using TestType = char;
    // Define axiom, productions and alphabet
    const std::vector<TestType> axiom = {'F'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('F', {'F', 'F', '-', '[', '-', 'F', '+', 'F', '+', 'F', ']', '+', '[', '+', 'F', '-', 'F', '-', 'F', ']'})
    };
    const std::unordered_set<TestType> alphabet{'F', '+', '-', '[', ']'};

    //create LSystemInterpreter object
    LSystemInterpreter<TestType> lsystem = LSystemInterpreter(axiom, productions, alphabet);
}

// Test case for one iteration of L-System
TEST_CASE("One Iteration") {
    using TestType = std::string;

    // Define axiom, productions, and alphabet
    const std::vector<TestType> axiom = {"F"};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>("F", {"F", "G", "G"})
    };
    const std::unordered_set<TestType> alphabet{"F", "G"};

    // Create an LSystemInterpreter object
    LSystemInterpreter<TestType> lsystem = LSystemInterpreter(axiom, productions, alphabet);
    std::vector<std::vector<TestType>> results(1);

    // Generate L-System output for one iteration
    std::generate(results.begin(), results.end(), lsystem);

    // Check if the result matches the expected output
    const std::vector<TestType> expected{"F", "G", "G"};
    CHECK(expected == results.at(0));
}

// Test case for 10 iterations of L-System
TEST_CASE("10 Iterations") {
    using TestType = std::string;

    // Define axiom, productions, and alphabet
    const std::vector<TestType> axiom = {"F"};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>("F", {"F", "G", "G"})
    };
    const std::unordered_set<TestType> alphabet{"F", "G"};

    // Create an LSystemInterpreter object
    LSystemInterpreter<TestType> lsystem = LSystemInterpreter(axiom, productions, alphabet);
    std::vector<std::vector<TestType>> results(5);

    // Generate L-System output for 10 iterations
    std::generate(results.begin(), results.end(), lsystem);

    // Check if the result matches the expected output
    const std::vector<TestType> expected{"F", "G", "G", "G", "G", "G", "G", "G", "G", "G", "G"};
    CHECK(expected == results.at(4));
}

// Test case for multiple productions
TEST_CASE("Multiple Productions") {
    using TestType = std::string;

    // Define axiom, productions, and alphabet
    const std::vector<TestType> axiom = {"a", "b", "a"};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>("a", {"a", "b"}),
            Production<TestType>("b", {"a"})
    };
    const std::unordered_set<TestType> alphabet{"a", "b"};

    // Create an LSystemInterpreter object
    LSystemInterpreter<TestType> lsystem = LSystemInterpreter(axiom, productions, alphabet);
    std::vector<std::vector<TestType>> results(1);

    // Generate L-System output for one iteration
    std::generate(results.begin(), results.end(), lsystem);

    // Check if the result matches the expected output
    const std::vector<TestType> expected{"a", "b", "a", "a", "b"};
    CHECK(expected == results.at(0));
}


// Test case for other types (using char)
TEST_CASE("Other testtypes") {
    using TestType = char;

    // Define axiom, productions, and alphabet
    const std::vector<TestType> axiom = {'a', 'b', 'a'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('a', {'a', 'b'}),
            Production<TestType>('b', {'a'})
    };
    const std::unordered_set<TestType> alphabet{'a', 'b'};

    // Create an LSystemInterpreter object
    LSystemInterpreter<TestType> lsystem = LSystemInterpreter(axiom, productions, alphabet);
    std::vector<std::vector<TestType>> results(3);

    // Generate L-System output for 3 iterations
    std::generate(results.begin(), results.end(), lsystem);

    // Check if the results match the expected outputs
    const std::vector<TestType> expected_first{'a', 'b', 'a', 'a', 'b'};
    const std::vector<TestType> expected_second{'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a'};
    const std::vector<TestType> expected_third{'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'a', 'b', 'a', 'a', 'b'};
    CHECK(expected_first == results.at(0));
    CHECK(expected_second == results.at(1));
    CHECK(expected_third == results.at(2));
}



//Test_Cases for tree, I still need to change them to work properly but these tests work too
TEST_CASE("Turtle Graphics L-System Test") {
    using TestType = char;

    // Definieer de L-System regels en het axiom
    const std::vector<TestType> axiom = {'F'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('F', {'F', '[', '+', 'F', ']', '-', 'F'})
    };
    const std::unordered_set<TestType> alphabet{'F', '+', '-', '[', ']'};

    // Maak een LSystemInterpreter-object aan met de gegeven regels en axiom
    LSystemInterpreter<TestType> lsystem(axiom, productions, alphabet);

    // Voer een paar iteraties uit om de L-System output te genereren
    std::vector<std::vector<TestType>> results(3);
    std::generate(results.begin(), results.end(), lsystem);

    // Schrijf de resultaten direct naar een bestand
    std::ofstream outputFile("C:\\\\Clion\\\\LSystem_Interpreter\\\\sources\\\\turtle.txt");
    if (outputFile.is_open()) {
        for (const auto &result : results) {
            for (const auto &symbol : result) {
                outputFile << symbol;
            }
            outputFile << '\n';  // Nieuwe regel na elke iteratie
        }
        outputFile.close();
    } else {
        // Handle fout bij het openen van het bestand
        std::cerr << "Kon het uitvoerbestand niet openen." << std::endl;
    }
}

TEST_CASE("Turtle Graphics Beautiful Tree Test") {
    using TestType = char;

    // Definieer de L-System regels en het axiom voor een mooie boom
    const std::vector<TestType> axiom = {'F'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('F', {'F', '[', '+', 'F', ']', '-', 'F'}),
            Production<TestType>('[', {'['}),
            Production<TestType>(']', {']'}),
            Production<TestType>('+', {'+', '+'}),
            Production<TestType>('-', {'-', '-'})
    };
    const std::unordered_set<TestType> alphabet{'F', '+', '-', '[', ']'};

    // Maak een LSystemInterpreter-object aan met de gegeven regels en axiom
    LSystemInterpreter<TestType> lsystem(axiom, productions, alphabet);

    // Voer een paar iteraties uit om de L-System output te genereren
    std::vector<std::vector<TestType>> results(5);
    std::generate(results.begin(), results.end(), lsystem);

    // Schrijf de resultaten direct naar een bestand
    std::ofstream outputFile("C:\\\\Clion\\\\LSystem_Interpreter\\\\sources\\\\beautiful_tree.txt");
    if (outputFile.is_open()) {
        for (const auto &result : results) {
            for (const auto &symbol : result) {
                outputFile << symbol;
            }
            outputFile << '\n';  // Nieuwe regel na elke iteratie
        }
        outputFile.close();
    } else {
        // Handle fout bij het openen van het bestand
        std::cerr << "Kon het uitvoerbestand niet openen." << std::endl;
    }
}

TEST_CASE("New Tree Test") {
    using TestType = char;

    // Definieer de L-System regels en het axiom voor een mooie boom
    const std::vector<TestType> axiom = {'F'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('F', {'F', 'F', '-', '[', '-', 'F', '+', 'F', '+', 'F', ']', '+', '[', '+', 'F', '-', 'F', '-', 'F', ']'})
    };
    const std::unordered_set<TestType> alphabet{'F', '+', '-', '[', ']'};

    // Maak een LSystemInterpreter-object aan met de gegeven regels en axiom
    LSystemInterpreter<TestType> lsystem(axiom, productions, alphabet);

    // Voer n iteraties uit om de L-System output te genereren
    const int n = 4;
    std::vector<std::vector<TestType>> results(n + 1);
    std::generate(results.begin(), results.end(), lsystem);


    // Schrijf de resultaten direct naar een bestand
    std::ofstream outputFile("C:\\\\Clion\\\\LSystem_Interpreter\\\\sources\\\\new_tree.txt");
    if (outputFile.is_open()) {
        for (const auto &result : results) {
            for (const auto &symbol : result) {
                outputFile << symbol;
            }
            outputFile << '\n';  // Nieuwe regel na elke iteratie
        }
        outputFile.close();
    } else {
        // Handle fout bij het openen van het bestand
        std::cerr << "Kon het uitvoerbestand niet openen." << std::endl;
    }
}

TEST_CASE("Turtle2 Test") {
    using TestType = char;

    // Definieer de L-System regels en het axiom voor een mooie boom
    const std::vector<TestType> axiom = {'X'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('X', {'F', '[', '+', 'X', ']','[','-','X',']','F','X'}),
            Production<TestType>('F', {'F','F'})
    };
    const std::unordered_set<TestType> alphabet{'X','F', '+', '-', '[', ']'};

    // Maak een LSystemInterpreter-object aan met de gegeven regels en axiom
    LSystemInterpreter<TestType> lsystem(axiom, productions, alphabet);

    // Voer een paar iteraties uit om de L-System output te genereren
    std::vector<std::vector<TestType>> results(5);
    std::generate(results.begin(), results.end(), lsystem);

    // Schrijf de resultaten direct naar een bestand
    std::ofstream outputFile("C:\\\\Clion\\\\LSystem_Interpreter\\\\sources\\\\tree2.txt");
    if (outputFile.is_open()) {
        for (const auto &result : results) {
            for (const auto &symbol : result) {
                outputFile << symbol;
            }
            outputFile << '\n';  // Nieuwe regel na elke iteratie
        }
        outputFile.close();
    } else {
        // Handle fout bij het openen van het bestand
        std::cerr << "Kon het uitvoerbestand niet openen." << std::endl;
    }
}

TEST_CASE("LastTry") {
    using TestType = char;

    // Definieer de L-System regels en het axiom voor een mooie boom
    const std::vector<TestType> axiom = {'X'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('X', {'F', '[', '+', 'X', ']','[','-','X',']','F','X'}),
            Production<TestType>('F', {'F','F'})
    };
    const std::unordered_set<TestType> alphabet{'X','F', '+', '-', '[', ']'};

    // Maak een LSystemInterpreter-object aan met de gegeven regels en axiom
    LSystemInterpreter<TestType> lsystem(axiom, productions, alphabet);

    // Voer een paar iteraties uit om de L-System output te genereren
    std::vector<std::vector<TestType>> results(5);
    std::generate(results.begin(), results.end(), lsystem);

    // Schrijf de resultaten direct naar een bestand
    std::ofstream outputFile("C:\\\\Clion\\\\LSystem_Interpreter\\\\sources\\\\beautiful_tree2.txt");
    if (outputFile.is_open()) {
        for (const auto &result : results) {
            for (const auto &symbol : result) {
                outputFile << symbol;
            }
            outputFile << '\n';  // Nieuwe regel na elke iteratie
        }
        outputFile.close();
    } else {
        // Handle fout bij het openen van het bestand
        std::cerr << "Kon het uitvoerbestand niet openen." << std::endl;
    }
}

TEST_CASE("NIEUWSTE POGING") {
    using TestType = char;

    // Definieer de L-System regels en het axiom voor een mooie boom
    const std::vector<TestType> axiom = {'X'};
    std::unordered_set<Production<TestType>> productions{
            Production<TestType>('X', {'F', '[', '+', 'X', ']','[','-','X',']','F','X'}),
            Production<TestType>('F', {'F','F'})
    };
    const std::unordered_set<TestType> alphabet{'X','F', '+', '-', '[', ']'};

    // Maak een LSystemInterpreter-object aan met de gegeven regels en axiom
    LSystemInterpreter<TestType> lsystem(axiom, productions, alphabet);

    // Voer een paar iteraties uit om de L-System output te genereren
    std::vector<std::vector<TestType>> results(5);
    std::generate(results.begin(), results.end(), lsystem);

    // Schrijf alleen de resultaten van de laatste iteratie naar het bestand
    std::ofstream outputFile("C:\\\\Clion\\\\LSystem_Interpreter\\\\sources\\\\beautiful_tree3.txt");
    if (outputFile.is_open()) {
        const auto& lastIteration = results.back();
        for (const auto &symbol : lastIteration) {
            outputFile << symbol;
        }
        outputFile << '\n';  // Nieuwe regel na de laatste iteratie
        outputFile.close();
    } else {
        // Handle fout bij het openen van het bestand
        std::cerr << "Kon het uitvoerbestand niet openen." << std::endl;
    }
}
