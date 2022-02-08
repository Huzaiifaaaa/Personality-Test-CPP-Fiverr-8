//  TODO:  Write file header comment here.

#include <math.h>
#include <limits>
#include <string>
#include <map>
#include <set>
#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;  // Text of the question
    map<char, int> factors;   // Map from factors to +1 or -1
    friend bool operator< (const Question& lhs, const Question& rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator== (const Question& lhs, const Question& rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator!= (const Question& lhs, const Question& rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;      // Name of the person
    map<char, int> scores;  // Map from factors to +1 or -1
    friend bool operator< (const Person& lhs,   const Person& rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator== (const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator!= (const Person& lhs, const Person& rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
*/
Question randomElement(set<Question>& questions) {
    int ind = randomInteger(0, (int)questions.size()-1);
    int i = 0;
    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

// TODO: Write this function header comment.
Question randomQuestionFrom(set<Question>& questions) {
    // TODO: Delete this line and the next two, then implement this function.
    (void) questions;
    return {};
}

// TODO: Write this function header comment.
map<char, int> scoresFrom(map<Question, int>& answers) {
    // TODO: Delete this line and the next two, then implement this function.
    (void) answers;
    return {};
}

// TODO: Write this function header comment.
map<char, double> normalize(map<char, int>& scores) {
    // TODO: Delete this line and the next two, then implement this function.
    (void) scores;
    return {};
}

// TODO: Write this function header comment.
double cosineSimilarityOf(const map<char, double>& lhs,
                          const map<char, double>& rhs) {
    // TODO: Delete this line and the next three, then implement this function.
    (void) lhs;
    (void) rhs;
    return {};
}

// TODO: Write this function header comment.
Person mostSimilarTo(map<char, int>& scores, set<Person>& people) {
    // TODO: Delete this line and the next three, then implement this function.
    (void) scores;
    (void) people;
    return {};
}
