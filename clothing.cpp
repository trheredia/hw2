#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

// constructor
Clothing::Clothing(const string& name_, double price_, int qty_, const string& size_, const string& brand_) : Product("clothing", name_, price_, qty_), size_(size_), brand_(brand_){}

// returns relevant keywords by parsing
set<string> Clothing::keywords() const {
  set<string> keywords;
  set<string> brandKeywords = parseStringToWords(convToLower(brand_));
  set<string> nameKeywords = parseStringToWords(convToLower(name_));
  keywords.insert(brandKeywords.begin(), brandKeywords.end());
  keywords.insert(nameKeywords.begin(), nameKeywords.end());
  return keywords;
}

// returns clothing info in a string
string Clothing::displayString() const {
  stringstream ss;
  ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
  return ss.str();
}

// outputs clothing info to stream
void Clothing::dump(ostream& os) const {
  os << "clothing" << endl;
  os << name_ << endl;
  os << fixed << setprecision(2) << price_ << endl;
  os << qty_ << endl;
  os << size_ << endl;
  os << brand_ << endl;
}