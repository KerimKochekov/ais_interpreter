/**
 * @copyright Copyright © 2018 IntervalAbstractDomain. All rights reserved.
 *
 * @license{<blockquote>
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * </blockquote>}
 *
 * @authors Marco Colognese, Mattia Rossini <br> Univerity of Verona, Dept. of
 * Computer Science                      <br> marco.colognese@studenti.univr.it,
 * mattia.rossini@studenti.univr.it
 * @date October, 2018
 * @version v1.0
 */

#include "AbstractInterval.hpp"
#include "Bound.hpp"
#include "FloatingPointAbstractInterval.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * @brief variable-value map.
 */
std::map<std::string, double> assegnamenti;

/**
 * @brief interval-value map for if statement.
 */
std::map<std::string, domain::FloatingPointAbstractInterval> intervals_if;

/**
 * @brief interval-value map for if statement.
 */
std::map<std::string, domain::FloatingPointAbstractInterval> intervals_if_false;

/**
 * @brief interval-value map.
 */
std::map<std::string, domain::FloatingPointAbstractInterval> intervals;

/**
 * @brief interval-value map for loops.
 */
std::map<std::string, domain::FloatingPointAbstractInterval> intervals_loop;

/**
 * @brief interval-value map for loops.
 */
std::map<std::string, domain::FloatingPointAbstractInterval>
    intervals_loop_false;

/**
 * @brief iterator for interval's map.
 */
std::map<std::string, domain::FloatingPointAbstractInterval>::iterator it;

/**
 * @brief interval to check fixpoint.
 */
domain::FloatingPointAbstractInterval fix_supp;

/**
 * @brief string to save condition variable.
 */
std::string fix_var;

/**
 * @brief support variable for if statement.
 */
bool if_false = false;

/**
 * @brief support variable for loop statement.
 */
bool loop_false = false;

/**
 * @brief code line read from file.
 */
std::string line;

/**
 * @brief code line splitted by spaces.
 */
std::vector<std::string> split_line;

/**
 * @brief couter for loop iterations.
 */
int ct_loop = 0;

/**
 * @brief variables for arithmetic operations.
 */
double value1, value2;

/**
 * @brief variables for bounds.
 */
domain::Bound bound1, bound2;

/**
 * @brief intervals for operations.
 */
domain::FloatingPointAbstractInterval interval1, interval2;

/**
 * @brief counters for "if" and "while" statements.
 */
int count_endif = 0, count_endwhile = 0;

/**
 * @brief cursor's position.
 */
int current_pos = 0;

/**
 * @brief variable for the file input stream.
 */
std::ifstream in;

/**
 * @brief Performs the split operation by an input char of a string.
 *
 * @param s input string
 * @param delim char used to split the input string
 * @param v split's output
 */
void split(const std::string& s, char delim, std::vector<std::string>& v) {
    int i   = 0;
    int pos = s.find(delim);
    while (pos != (int) std::string::npos) {
        v.push_back(s.substr(i, pos - i));
        i   = ++pos;
        pos = s.find(delim, pos);

        if (pos == (int) std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

/**
 * @brief Performs the convertion from a string to a double
 *
 * @param s string to convert to double
 * @return the string converted
 */
double stod1(std::string& s) {
    if (s.at(0) == '-') {
        return -stod(s.substr(1, s.size()));
    } else
        return stod(s);
}

/**
 * @brief Performs the trim operation of an input string.
 *
 * @param str input string
 * @return the trimmed string
 */
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/**
 * @brief Performs a choosen arithmetic operation between intervals and values.
 *
 * @param i first value
 * @param ii second value
 * @param op arithmetic operation
 * @return resulting interval
 */
domain::FloatingPointAbstractInterval calculator(double i, double ii, char op) {

    switch (op) {
        case '+':
            assegnamenti[split_line[0]] = i + ii;
            return interval1 + interval2;
            break;
        case '-':
            assegnamenti[split_line[0]] = i - ii;
            return interval1 - interval2;
            break;
        case '*':
            assegnamenti[split_line[0]] = i * ii;
            return interval1 * interval2;
            break;
        case '/':
            if (ii == 0) {
                std::cerr << "\tUndefined operation" << std::endl;
                exit(1);
            }
            assegnamenti[split_line[0]] = i / ii;
            return interval1 / interval2;
            break;
        default:
            std::cerr << "\tUndefined operation" << std::endl;
            exit(1);
    }
}

/**
 * @brief finds and skips dead-code when the condition of "if" and "while"
 * statements is false.
 */
void find() {

    while (true) {
        getline(in, line);
        line = trim(line);
        split_line.clear();
        split(line, ' ', split_line);

        if (line.compare("endif") == 0) {
            if_false = false;
            return;
        }

        if (line.compare("endwhile") == 0) {
            if (loop_false) {
                for (it = intervals_loop_false.begin();
                     it != intervals_loop_false.end();
                     it++) {
                    std::map<std::string,
                             domain::FloatingPointAbstractInterval>::iterator
                        it1;
                    it1 = intervals.find(it->first);
                    if (it1 != intervals.end())
                        intervals.at(it->first) =
                            intervals_loop_false.at(it->first).lub(
                                intervals_loop_false.at(it->first),
                                intervals.at(it->first));
                    else
                        intervals[it->first] = it->second;
                }

                loop_false = false;
            }
            return;
        }
    }
}

/**
 * @brief checks the condition in a "if" or "while" statements. If the condition
 * is false, it calls the find() function.
 *
 * @param ctr string containing "endif" or "endwhile"
 * @param expr operator's code using in condition clause
 */
void fun(std::string ctr, int expr) {

    if (!isdigit(split_line[3].at(0)) &&
        split_line[3].at(0) != '-') { // se viene fatto riferimento ad una
                                      // variabile, ne prendo il valore
        value2    = assegnamenti.at(split_line[3]);
        interval2 = intervals.at(split_line[3]);

    } else { // se si fa riferimento ad un valore
        value2    = stod1(split_line[3]);
        interval2 = domain::FloatingPointAbstractInterval(
            domain::Bound(stod1(split_line[3])),
            domain::Bound(stod1(split_line[3])));
    }

    if (!isdigit(split_line[1].at(0)) &&
        split_line[1].at(0) != '-') { // se viene fatto riferimento ad una
                                      // variabile, ne prendo il valore
        value1    = assegnamenti.at(split_line[1]);
        interval1 = intervals.at(split_line[1]);

    } else { // se si fa riferimento ad un valore
        value1    = stod1(split_line[1]);
        interval1 = domain::FloatingPointAbstractInterval(
            domain::Bound(stod1(split_line[1])),
            domain::Bound(stod1(split_line[1])));
    }

    fix_supp = intervals[split_line[1]];
    fix_var  = split_line[1];

    switch (expr) {
        case 3: // operatore >
            if (interval2.getLowerBound() >= interval1.getUpperBound()) {
                do {
                    find();
                } while (line.compare(ctr) != 0);
                if (ctr.compare("endif") == 0)
                    count_endif--;
                else {
                    count_endwhile--;
                    ct_loop = 0;
                    intervals_loop.clear();
                }
            } else if (ctr.compare("endif") == 0 &&
                       intervals[split_line[1]]
                               .getLowerBound()
                               .getFloatValue() <= stod1(split_line[3])) {
                if_false = true;
                for (it = intervals_if.begin(); it != intervals_if.end();
                     it++) {
                    intervals_if_false.at(it->first) = intervals.at(it->first);
                }
                intervals_if_false[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        intervals[split_line[1]].getLowerBound(),
                        domain::Bound(stod1(split_line[3])));
            } else if (ctr.compare("endwhile") == 0 &&
                       intervals[split_line[1]]
                               .getLowerBound()
                               .getFloatValue() <= stod1(split_line[3])) {

                if (!loop_false) {
                    loop_false = true;
                    intervals_loop_false[split_line[1]] =
                        domain::FloatingPointAbstractInterval(
                            intervals[split_line[1]].getLowerBound(),
                            domain::Bound(stod1(split_line[3])));
                }
                intervals_loop[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[3]) + 1),
                        domain::Bound(intervals[split_line[1]]
                                          .getUpperBound()
                                          .getFloatValue()));
            }
            break;

        case 4: // operatore <
            if (interval1.getLowerBound() >= interval2.getUpperBound()) {
                do {
                    find();
                } while (line.compare(ctr) != 0);
                if (ctr.compare("endif") == 0)
                    count_endif--;
                else {
                    count_endwhile--;
                    ct_loop = 0;
                    intervals_loop.clear();
                }
            } else if (ctr.compare("endif") == 0 &&
                       interval1.getUpperBound().getFloatValue() >=
                           stod1(split_line[3])) {
                if_false = true;
                for (it = intervals_if.begin(); it != intervals_if.end();
                     it++) {
                    intervals_if_false.at(it->first) = intervals.at(it->first);
                }
                intervals_if_false[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[3])),
                        intervals[split_line[1]].getUpperBound());
            } else if (ctr.compare("endwhile") == 0 &&
                       interval1.getUpperBound().getFloatValue() >=
                           stod1(split_line[3])) {

                if (!loop_false) {
                    loop_false = true;
                    intervals_loop_false[split_line[1]] =
                        domain::FloatingPointAbstractInterval(
                            domain::Bound(stod1(split_line[3])),
                            intervals[split_line[1]].getUpperBound());
                }
                intervals_loop[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        intervals[split_line[1]].getLowerBound(),
                        domain::Bound(stod1(split_line[3]) - 1));
            }
            break;

        case 5: // operatore <=
            if (interval1.getLowerBound() > interval2.getUpperBound()) {
                do {
                    find();
                } while (line.compare(ctr) != 0);
                if (ctr.compare("endif") == 0)
                    count_endif--;
                else {
                    count_endwhile--;
                    ct_loop = 0;
                    intervals_loop.clear();
                }
            } else if (ctr.compare("endif") == 0 &&
                       intervals[split_line[1]]
                               .getUpperBound()
                               .getFloatValue() > stod1(split_line[3])) {
                if_false = true;
                for (it = intervals_if.begin(); it != intervals_if.end();
                     it++) {
                    intervals_if_false.at(it->first) = intervals.at(it->first);
                }
                intervals_if_false[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[3]) + 1),
                        intervals[split_line[1]].getUpperBound());
                intervals_if[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        intervals[split_line[1]].getLowerBound(),
                        domain::Bound(stod1(split_line[3])));

            } else if (ctr.compare("endwhile") == 0 &&
                       intervals[split_line[1]]
                               .getUpperBound()
                               .getFloatValue() > stod1(split_line[3])) {
                if (!loop_false) {
                    loop_false = true;
                    intervals_loop_false[split_line[1]] =
                        domain::FloatingPointAbstractInterval(
                            domain::Bound(stod1(split_line[3]) + 1),
                            intervals[split_line[1]].getUpperBound());
                }
                intervals_loop[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        intervals[split_line[1]].getLowerBound(),
                        domain::Bound(stod1(split_line[3])));
            }
            break;

        case 6: // operatore >=
            if (interval2.getUpperBound() < interval1.getLowerBound()) {
                do {
                    find();
                } while (line.compare(ctr) != 0);
                if (ctr.compare("endif") == 0)
                    count_endif--;
                else {
                    count_endwhile--;
                    ct_loop = 0;
                    intervals_loop.clear();
                }
            } else if (ctr.compare("endif") == 0 &&
                       intervals[split_line[1]]
                               .getLowerBound()
                               .getFloatValue() < stod1(split_line[3])) {
                if_false = true;
                for (it = intervals_if.begin(); it != intervals_if.end();
                     it++) {
                    intervals_if_false.at(it->first) = intervals.at(it->first);
                }
                intervals_if_false[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        intervals[split_line[1]].getLowerBound(),
                        domain::Bound(stod1(split_line[3]) - 1));
                intervals_if[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[3])),
                        intervals[split_line[1]].getUpperBound());

            } else if (ctr.compare("endwhile") == 0 &&
                       intervals[split_line[1]]
                               .getLowerBound()
                               .getFloatValue() < stod1(split_line[3])) {
                if (!loop_false) {
                    loop_false = true;
                    intervals_if_false[split_line[1]] =
                        domain::FloatingPointAbstractInterval(
                            intervals[split_line[1]].getLowerBound(),
                            domain::Bound(stod1(split_line[3]) - 1));
                }
                intervals_loop[split_line[1]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[3])),
                        intervals[split_line[1]].getUpperBound());
            }
            break;
    }
}

/**
 * @brief manages "while" statements. Calls fun() function to check the
 * condition
 */
void gestione_while() {

    if (split_line.size() == 2 &&
        split_line[1].compare("false") == 0) { // se la clausola dell'if è FALSE
        do {
            find(); // cerco altre clausole che non devo conteggiare
        } while (line.compare("endwhile") != 0 && count_endwhile == 1);
        count_endwhile--;

    } else if (split_line.size() == 2 && split_line[1].compare("true") == 0) {
        ct_loop = 9;
    } // se la clausola dell'if è TRUE

    else if (split_line[2].compare(">") == 0) {
        fun("endwhile",
            3); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // while e il codice dell'operatore ">"
    } else if (split_line[2].compare("<") == 0) {
        fun("endwhile",
            4); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // while e il codice dell'operatore "<"
    } else if (split_line[2].compare("<=") == 0) {
        fun("endwhile",
            5); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // while e il codice dell'operatore "<="
    } else if (split_line[2].compare(">=") == 0) {
        fun("endwhile",
            6); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // while e il codice dell'operatore ">="
    }
}

/**
 * @brief manages "if" statements. Calls fun() function to check the condition.
 */
void gestione_if() {

    if (split_line.size() == 2 &&
        split_line[1].compare("false") == 0) { // se la clausola dell'if è FALSE
        do {
            find(); // cerco altre clausole che non devo conteggiare
        } while (line.compare("endif") != 0 && count_endif == 1);
        count_endif--;
    } else if (split_line.size() == 2 && split_line[1].compare("true") == 0) {
    } // se la clausola dell'if è TRUE

    else if (split_line[2].compare(">") == 0) {
        fun("endif",
            3); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // if e il codice dell'operatore ">"
    } else if (split_line[2].compare("<") == 0) {
        fun("endif",
            4); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // if e il codice dell'operatore "<"
    } else if (split_line[2].compare("<=") == 0) {
        fun("endif",
            5); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // if e il codice dell'operatore "<="
    } else if (split_line[2].compare(">=") == 0) {
        fun("endif",
            6); // passo le posizioni 1 e 3 dei due valori, lo statement di fine
                // if e il codice dell'operatore ">="
    }
}

/**
 * @brief manages all types of assignment: simple assignment and complex
 * assignment (with an operation in the right-hand).
 */
void gestione_assegnamento() {

    if (split_line.size() >
        3) { // se ci sono operazioni nel lato dx dell'assegnamento

        if (!isdigit(split_line[2].at(0)) &&
            split_line[2].at(0) != '-') { // se viene fatto riferimento ad una
                                          // variabile, ne prendo il valore
            value1 = assegnamenti.at(split_line[2]);
            std::map<std::string,
                     domain::FloatingPointAbstractInterval>::iterator it1,
                it2;
            it1 = intervals_loop.find(split_line[2]);
            it2 = intervals_if.find(split_line[2]);
            if (count_endwhile > 0 && it1 != intervals_loop.end())
                interval1 = intervals_loop.at(split_line[2]);
            else if (count_endif > 0 && it2 != intervals_if.end())
                interval1 = intervals_if.at(split_line[2]);
            else
                interval1 = intervals.at(split_line[2]);
        } else { // se si fa riferimento ad un valore
            value1    = stod1(split_line[2]);
            interval1 = domain::FloatingPointAbstractInterval(
                domain::Bound(stod1(split_line[2])),
                domain::Bound(stod1(split_line[2])));
        }

        if (!isdigit(split_line[4].at(0)) &&
            split_line[4].at(0) != '-') { // se viene fatto riferimento ad una
                                          // variabile, ne prendo il valore
            value2 = assegnamenti.at(split_line[4]);
            std::map<std::string,
                     domain::FloatingPointAbstractInterval>::iterator it1,
                it2;
            it1 = intervals_loop.find(split_line[4]);
            it2 = intervals_if.find(split_line[4]);
            if (count_endwhile > 0 && it1 != intervals_loop.end())
                interval2 = intervals_loop.at(split_line[4]);
            else if (count_endif > 0 && it2 != intervals_if.end())
                interval2 = intervals_if.at(split_line[4]);
            else
                interval2 = intervals.at(split_line[4]);

        } else { // se si fa riferimento ad un valore
            value2    = stod1(split_line[4]);
            interval2 = domain::FloatingPointAbstractInterval(
                domain::Bound(stod1(split_line[4])),
                domain::Bound(stod1(split_line[4])));
        }

        if (ct_loop == 0 && count_endif == 0)
            intervals[split_line[0]] =
                calculator(value1, value2, split_line[3].at(0));
        else if (count_endif != 0)
            intervals_if[split_line[0]] =
                calculator(value1, value2, split_line[3].at(0));
        else
            intervals_loop[split_line[0]] =
                calculator(value1, value2, split_line[3].at(0));

    } else { // se è un assegnamento
        if (!isdigit(split_line[2].at(0)) &&
            split_line[2].at(0) != '-') { // se viene creato un alias
            assegnamenti[split_line[0]] = assegnamenti.at(split_line[2]);

            std::map<std::string,
                     domain::FloatingPointAbstractInterval>::iterator it1,
                it2;
            it1 = intervals_loop.find(split_line[2]);
            it2 = intervals_if.find(split_line[2]);
            if (count_endwhile > 0 && it1 != intervals_loop.end())
                intervals_loop[split_line[0]] =
                    intervals_loop.at(split_line[2]);
            else if (count_endif > 0 && it2 != intervals_if.end())
                intervals_if[split_line[0]] = intervals_if.at(split_line[2]);
            else if (count_endwhile > 0)
                intervals_loop[split_line[0]] = intervals.at(split_line[2]);
            else if (count_endif > 0)
                intervals_if[split_line[0]] = intervals.at(split_line[2]);
            else
                intervals[split_line[0]] = intervals.at(split_line[2]);

        } else { // se viene effettuato un assegnamento semplice
            assegnamenti[split_line[0]] = stod1(split_line[2]);
            if (ct_loop == 0 && count_endif == 0)
                intervals[split_line[0]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[2])),
                        domain::Bound(stod1(split_line[2])));
            else if (count_endif != 0)
                intervals_if[split_line[0]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[2])),
                        domain::Bound(stod1(split_line[2])));
            else
                intervals_loop[split_line[0]] =
                    domain::FloatingPointAbstractInterval(
                        domain::Bound(stod1(split_line[2])),
                        domain::Bound(stod1(split_line[2])));
        }
    }
}

/**
 * @brief read line-by-line the input.txt file. It identify and manage all kind
 * of statement calling:
 *  - gestione_assegnamento() to manage assignments;
 *  - gestione_if() to manage "if" statements;
 *  - gestione_while() to manage "while" statements.
 * At the end prints all intervals corresponding to program's variables.
 *
 * @return 0 if the program exits without errors
 */
int main() {

    bool fix = false;
    in.open("../input.txt");

    while (!in.eof()) {

        if (count_endwhile == 0)
            current_pos = in.tellg(); // prende la posizione fino alla riga
                                      // precedente al primo while

        getline(in, line);
        line = trim(line);
        if (count_endwhile == 0 && count_endif == 0 &&
            (line.find("while") != std::string::npos)) {
            std::cout << "\nPROGRAM LINE: " << line << "  (loop n."
                      << ct_loop + 1 << ")" << std::endl;
        } else
            std::cout << "\nPROGRAM LINE: " << line << std::endl;

        split_line.clear();
        split(line, ' ', split_line);

        if (split_line.size() > 1) {
            if (split_line[0].compare("while") == 0) {
                count_endwhile++;
                ct_loop++;
                if (fix) {
                    do { // esco dal ciclo while
                        find();
                    } while (line.compare("endwhile") != 0 &&
                             count_endwhile == 1);
                    ct_loop = 0;
                    intervals_loop.clear();
                    count_endwhile--;
                    fix = false;
                }
                if (ct_loop < 10)
                    gestione_while();

                if (ct_loop == 10) {
                    for (it = intervals_loop.begin();
                         it != intervals_loop.end();
                         it++) {
                        intervals.at(it->first) =
                            intervals.at(it->first).widening(
                                intervals_loop.at(it->first));
                    }
                    if (loop_false)
                        for (it = intervals.begin(); it != intervals.end();
                             it++)
                            intervals.at(it->first) =
                                intervals.at(it->first).lub(
                                    intervals.at(it->first),
                                    intervals_loop_false.at(it->first));
                    loop_false = false;
                    do { // esco dal ciclo while
                        find();
                    } while (line.compare("endwhile") != 0 &&
                             count_endwhile == 1);
                    ct_loop = 0;
                    intervals_loop.clear();
                    count_endwhile--;
                }

            } else if (split_line[0].compare("if") == 0) {
                gestione_if();
                count_endif++;

            } else if (split_line[1].compare("=") == 0) { // assegnamento
                if (isdigit(split_line[0].at(0)) &&
                    split_line[0].at(0) !=
                        '-') { // la variabile non può iniziare con un numero
                    std::cerr << "\tVariable should not be a digit"
                              << std::endl;
                    exit(1);
                }
                gestione_assegnamento();
            }
        } else if (line.compare("endif") == 0) {
            count_endif--;
            for (it = intervals_if.begin(); it != intervals_if.end(); it++) {
                std::map<std::string,
                         domain::FloatingPointAbstractInterval>::iterator it1;
                it1 = intervals.find(it->first);
                if (it1 != intervals.end() && if_false)
                    intervals.at(it->first) =
                        intervals_if_false.at(it->first).lub(
                            intervals_if.at(it->first),
                            intervals_if_false.at(it->first));
                else
                    intervals[it->first] = it->second;
            }
            if_false = false;
        } else if (line.compare("endwhile") == 0 && count_endwhile != 0) {
            count_endwhile--;
            if (ct_loop > 0 && ct_loop < 9) {
                for (it = intervals_loop.begin(); it != intervals_loop.end();
                     it++) {
                    std::map<std::string,
                             domain::FloatingPointAbstractInterval>::iterator
                        it1;
                    it1 = intervals.find(it->first);
                    if (it1 != intervals.end())
                        intervals.at(it->first) =
                            intervals_loop.at(it->first).lub(
                                intervals_loop.at(it->first),
                                intervals.at(it->first));
                    else
                        intervals[it->first] = it->second;
                }

                if (fix_supp == intervals[fix_var])
                    fix = true;
            }

            in.seekg(current_pos); // riposizionamento del cursore nella riga
                                   // del while
        }

        // Stampa a video degli intervalli corrispondenti alle variabili
        if (count_endwhile == 0 && count_endif == 0) {
            for (it = intervals.begin(); it != intervals.end(); it++) {
                printf("%s:\t", it->first.c_str());
                if (intervals.at(it->first).getLowerBound().is_infinity()) {
                    if (intervals.at(it->first)
                            .getLowerBound()
                            .getInfinityValue()
                            .getSign() == 0)
                        printf("[ -inf; ");
                    else
                        printf("[ +inf; ");
                } else
                    printf("[ %.2f; ",
                           intervals.at(it->first)
                               .getLowerBound()
                               .getFloatValue());

                if (intervals.at(it->first).getUpperBound().is_infinity()) {
                    if (intervals.at(it->first)
                            .getUpperBound()
                            .getInfinityValue()
                            .getSign() == 0)
                        printf("-inf ]\n");
                    else
                        printf("+inf ]\n");
                } else
                    printf("%.2f ]\n",
                           intervals.at(it->first)
                               .getUpperBound()
                               .getFloatValue());
            }
            std::cout << "" << std::endl;
        }
    }

    if (count_endif != 0) {
        std::cerr << "\tError: uncorrect use of \"endif\" keyword" << std::endl;
        exit(1);
    }

    if (count_endwhile != 0) {
        std::cerr << "\tError: uncorrect use of \"endwhile\" keyword"
                  << std::endl;
        exit(1);
    }

    // Stampa a video degli intervalli corrispondenti alle variabili
    std::cout << "\n\nAt the end of the program, intervals corresponding to "
                 "variables are:"
              << std::endl;
    for (it = intervals.begin(); it != intervals.end(); it++) {
        printf("%s:\t", it->first.c_str());
        if (intervals.at(it->first).getLowerBound().is_infinity()) {
            if (intervals.at(it->first)
                    .getLowerBound()
                    .getInfinityValue()
                    .getSign() == 0)
                printf("[ -inf; ");
            else
                printf("[ +inf; ");
        } else
            printf("[ %.2f; ",
                   intervals.at(it->first).getLowerBound().getFloatValue());

        if (intervals.at(it->first).getUpperBound().is_infinity()) {
            if (intervals.at(it->first)
                    .getUpperBound()
                    .getInfinityValue()
                    .getSign() == 0)
                printf("-inf ]\n");
            else
                printf("+inf ]\n");
        } else
            printf("%.2f ]\n",
                   intervals.at(it->first).getUpperBound().getFloatValue());
    }
    std::cout << "" << std::endl;

    return 0;
}
