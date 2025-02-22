#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

using namespace std;

// derived mydatastore class
class MyDataStore : public DataStore {
private:
  vector<Product*> products;
  vector<User*> users;
  map<string, set<Product*>> keywordsMap;
  map<string, vector<Product*>> cartMap;

public:
  virtual ~MyDataStore();
  virtual void addProduct(Product* p) override;
  virtual void addUser(User* u) override;
  virtual vector<Product*> search(vector<string>& terms, int type) override;
  virtual void dump(ostream& ofile) override;

  void assignKeywords(Product* p);

  void viewCart(const string& username);
  void addToCart(const string& username, Product* p);
  void buyCart(const string& username);
};

#endif

