#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

// constructor
Movie::Movie(const string& name_, double price_, int qty_, const string& genre_, const string& rating_) : Product("movie", name_, price_, qty_), genre_(genre_), rating_(rating_) {}

// returns relevant keywords
set<string> Movie::keywords() const {
  set<string> keywords;
  set<string> nameKeywords = parseStringToWords(convToLower(name_));
  keywords.insert(convToLower(genre_));
  keywords.insert(nameKeywords.begin(), nameKeywords.end());
  return keywords;
}

// returns string of info
string Movie::displayString() const {
  stringstream ss;
  ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

// outputs info to stream
void Movie::dump(ostream& os) const {
  os << "movie" << endl;
  os << name_ << endl;
  os << fixed << setprecision(2) << price_ << endl;
  os << qty_ << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}
