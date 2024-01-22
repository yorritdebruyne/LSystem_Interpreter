#include "LSystemInterpreter.hpp"


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

//LSystemInterpreter
/*template <typename SymbolType>
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

*/