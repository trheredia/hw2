#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

// constructor
Book::Book(const std::string& name_, double price_, int qty_, const std::string& isbn_, const std::string& author_) 
: Product("book", name_, price_, qty_), author_(author_), isbn_(isbn_) {}

// returns relevant set of keywords by parsing 
set<string> Book::keywords() const {
  set<string> keywords;
  set<string> nameKeywords = parseStringToWords(convToLower(name_));
  set<string> authorKeywords = parseStringToWords(convToLower(author_));
  keywords.insert(nameKeywords.begin(), nameKeywords.end());
  keywords.insert(authorKeywords.begin(), authorKeywords.end());
  keywords.insert(isbn_);
  return keywords;
}

// returns a string of the book info
string Book::displayString() const {
  stringstream ss;
  ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n"; 
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

// writes book info to output 
void Book::dump(ostream& os) const {
  os << "book" << endl;
  os << name_ << endl;
  os << fixed << setprecision(2) << price_ << endl;
  os << qty_ << endl;
  os << isbn_ << endl;
  os << author_ << endl;
}
