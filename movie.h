#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <set>
#include <string>

using namespace std;

// writing derived movie class from product 
class Movie : public Product {
private:
  // unique to movie
  string genre_;
  string rating_;
public:
  // constructor
  Movie(const string& name_, double price_, int qty_, const string& genre_, const string& rating_);
  // functions
  set<string> keywords() const override;
  string displayString() const override;
  void dump(ostream& os) const override;
};

#endif