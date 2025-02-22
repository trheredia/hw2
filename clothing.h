#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include "util.h"
#include <set>
#include <string>

using namespace std;

// derived clothing class from product
class Clothing : public Product {
private:
  // unique variables
  string size_;
  string brand_;
public:
  // constructor
  Clothing(const string& name_, double price_, int qty_, const string& size_, const string& brand_);
  // functions
  set<string> keywords() const override;
  string displayString() const override;
  void dump(ostream& os) const override;
};

#endif