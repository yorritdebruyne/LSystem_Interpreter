#pragma once //File doesn't compile more than we want to

#ifndef LSYSTEM_INTERPRETER_LSYSTEMINTERPRETER_HPP
#define LSYSTEM_INTERPRETER_LSYSTEMINTERPRETER_HPP

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <stdexcept> //common exceptions such as invalid_argument
#include <fstream> //use of files



// This class represents a single production.
// A production is a replacement rule, it tells us which symbol
// to look for, and what (sequence of) symbol(s) to replace it with.
// The original symbol is usually called a “predecessor”.
// The (sequence of) symbol(s) is usually called a “successor”.
template <typename SymbolType>
class Production {
public:


    // constructor w/o inputs
    //Production();
    Production(SymbolType predecessor, const std::vector<SymbolType> &successor);

    //Production(SymbolType predecessor, const std::vector<SymbolType> &successor) //: predecessor(predecessor),
                                                                                       //successor(successor) {}


    // Define the equality operator for Production objects
    bool operator==(const Production& other) const {
        // Define your logic to compare two Production objects
        // For example, compare the predecessor and successor
        return this->predecessor == other.predecessor &&
               this->successor == other.successor;
    }

    SymbolType getPredecessor() const {
        return predecessor;
    }

    const std::vector<SymbolType> &getSuccessor() const {
        return successor;
    }
private:
    SymbolType predecessor;
    std::vector<SymbolType> successor;
};

//Constructor

//Constructor
template<typename SymbolType>
Production<SymbolType>::Production(SymbolType predecessor, const std::vector<SymbolType> &successor):predecessor(
        predecessor), successor(successor) {}

/*hash function hash<SymbolType>{} for SymbolType to calculate the hash value
of the predecessor attribute of the Production object.
Without this the unordered_set wouldn't work.*/

template <typename SymbolType>
struct std::hash<Production<SymbolType>>{
    size_t operator()(const Production<SymbolType> &production) const{
        return hash<SymbolType>{}(production.getPredecessor()); //Calculates hash value for Production<SymbolType>-object
    }
};




// This function verifies that all symbols in the production
// (Predecessor and all symbols in the successor) are
// in the given alphabet.
// If all symbols are in the alphabet, this function returns true,
// otherwise, this function returns false.
// The time-complexity of this function should be be O(N)
// where N is the total number of symbols in the production
// (predecessor + successors)
template <typename SymbolType>
bool isValidProduction(
        const Production<SymbolType>& production,
        const std::unordered_set<SymbolType>& alphabet
){
    //Get predecessor and successor from production
    //ORIGINEEL: const std::vector<SymbolType>& predecessor = production.getPredecessor();
    //VERVANGING:
    const SymbolType& predecessor = production.getPredecessor();
    const std::vector<SymbolType>& successor = production.getSuccessor();

    //Check if every symbol in the predecessor is in the alphabet
    /*ORIGINEEL:for (const auto& symbol : predecessor) {
        //Look for symbol in alphabet
        if (alphabet.find(symbol) == alphabet.end()) {
            //If symbol isn't found: IsValidProduction = false
            return false; //Symbol in predecessor not in alphabet
        }
    }*/
    //VERVANGING:
    // Check if the predecessor symbol is in the alphabet
    if (alphabet.find(predecessor) == alphabet.end()) {
        return false; // Symbol in predecessor not in alphabet
    }

    //Same for successor
    for (const auto& symbol : successor) {
        //Look for symbol in alphabet
        if (alphabet.find(symbol) == alphabet.end()) {
            //If symbol isn't found: IsValidProduction = false
            return false; //Symbol in successor not in alphabet
        }
    }
    //If all symbols were in predecessor and successor in alphabet
    //IsValidProduction = true
    return true;
}

// This class represents the actual L-System.
// It contains an axiom (Initial state), A set of productions
// (Replacement rules) and an alphabet (List of allowed symbols).
template <typename SymbolType>
class LSystemInterpreter {
    public:
    // This constructor takes an axiom, a set of productions and
    // an alphabet and stores these in the fields.
    // It should check that all productions are valid using
    // the “isValidProduction” function above.
    // If any of the productions are invalid,
    // it should throw an exception.
    // The constructor should also check that
    // every production has a unique predecessor.
    // It should also check that there is a Production for
    // each symbol in the alphabet.
    // If there is a symbol in the alphabet without a production,
    // you can decide what to do:
    // 1. Throw an exception
    // 2. Add an identity production (A -> A)
    LSystemInterpreter(
            const std::vector<SymbolType>& axiom,
            const std::unordered_set<Production<SymbolType>>& productions,
            const std::unordered_set<SymbolType>& alphabet
    );

    // After `operator()` has been called one or more times,
    // the L-system will have accumulated an internal state.
    // This method should reset this internal state,
    // so the next call to `operator()` starts from
    // the L-system’s axiom again.
    void reset(){
        this->current = this->axiom; //Reset current state to axiom state
    }

    // This function should execute a single iteration of the L-System.
    // When this method is called twice,
    // the second call should use the result of the first call
    // as its starting point.
    // This allows us to use `std::generate()` to iteratively
    // execute the L-System.
    //
    // Be careful when applying your productions!
    // Your productions should always be applied at the same time!
    // An example:
    // We have 2 productions: A -> AB, B -> A, and an axiom “ABA”
    // We can apply the first production first, and get:
    // “ABBAB”
    // And then we can apply the second production, to get:
    // “AAAAA”
    // THIS IS WRONG!
    //
    // You should always execute all productions on the original text!
    // So, in this case, the correct output would be:
    // “ABAAB”
    // (The first and last A’s were replaced by AB,
    // and the middle B by A)
    std::vector<SymbolType> operator() () const;

    /*
    //WriteToFile for turtle
    void writeToFile(const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& symbol : current) {
                outputFile << symbol;
            }
            outputFile.close();
        } else {
            throw std::runtime_error("Unable to open file for writing.");
        }
    }*/


private:
    std::unordered_set<SymbolType> alphabet;
    std::vector<SymbolType> axiom;
    std::unordered_set<Production<SymbolType>> productions;
    /*
     We want to be able to modify current even though they include member functions whom are const
     */
    mutable std::vector<SymbolType> current;
    //std::vector<SymbolType> current;
};


//Initially I put this in a separate LSystem.cpp file, but then some problems occurred with linking the template functions
template <typename SymbolType>
LSystemInterpreter<SymbolType>::LSystemInterpreter(const std::vector<SymbolType> &axiom,
                                                   const std::unordered_set<Production<SymbolType>> &productions,
                                                   const std::unordered_set<SymbolType> &alphabet): axiom(axiom), alphabet(alphabet), current(axiom) {
    for(const auto&production: productions){
        if(!isValidProduction(production, alphabet)){
            throw std::invalid_argument("Production not valid.");
        }
    }
    //If it was valid, we assign productions
    this->productions = productions;

}

template<typename SymbolType>
std::vector<SymbolType> LSystemInterpreter<SymbolType>::operator()() const {
    //We make a copy of the current state to apply changes
    std::vector<SymbolType> updated_state; //was= current;

    //Iterate through each symbol in the current state
    //and apply productions simultaneously.
    for (const auto &symbol: this->current) { //was : updated_state
        bool productionFound = false;

        //Find the production matching the current symbol
        for (const auto &production: productions) {
            //Check if the current symbol matches the predecessor of a production
            if (production.getPredecessor() == symbol) {//== std::vector<SymbolType>{symbol}){
                // Replace the current symbol with the first symbol in the successor of the production
                //symbol = production.getSuccessor().front();

                //if (!production.getSuccessor().empty()){
                updated_state.insert(updated_state.end(), production.getSuccessor().begin(),
                                     production.getSuccessor().end());
                //}

                productionFound = true;
                //We use 'break' to jump out of the loop
                //and move to the next symbol in the state
                break;
            }
        }

        //If no production was found for the symbol
        //we add the symbol itself to out updated_state
        if (!productionFound) {
            updated_state.push_back(symbol);
        }
    }
    current = updated_state;
/*
    std::ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        throw std::runtime_error("Unable to open output file.");
    }

    for (const auto& symbol : updated_state) {
        outputFile << symbol;
    }

    outputFile.close();
    */

    //Return updatedState after applying the productions
    return updated_state;

}


#endif //LSYSTEM_INTERPRETER_LSYSTEMINTERPRETER_HPP
