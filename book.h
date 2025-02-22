#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"
#include <set>
#include <string>
#include <iomanip>

using namespace std;

// write the derived book class 
class Book : public Product {
private:
  string author_;
  string isbn_;
public:
  // constructor
  Book(const string& name_, double price_, int qty_, const string& isbn_, const string& author);
  // functions
  set<string> keywords() const override;
  string displayString() const override;
  void dump(ostream& os) const override;
};

#endif