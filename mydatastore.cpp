#include "mydatastore.h"
#include "util.h"
#include "user.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// declare displayProduct from amazon.cpp here
void displayProducts(vector<Product*>& hits);

// destructor that loops through all stored products and users and deletes them
MyDataStore::~MyDataStore() {
  for(size_t i = 0; i < products.size(); i++){ 
    delete products[i];
  }
  for(size_t i = 0; i < users.size(); i++){
    delete users[i];
  }
}

// add product function that makes sure the product doesn't already exist, and then adds the product and calls
// the keywords function to map its keywords
void MyDataStore::addProduct(Product* p) {
  for(size_t i = 0; i < products.size(); i++){
    if(products[i] == p){
      return; 
    }
  }
  products.push_back(p); 
  assignKeywords(p); 
}

// add user function that makes sure the user doesn't already exist and then
// adds it to the back of the users list
void MyDataStore::addUser(User* u) {
  for(size_t i = 0; i < users.size(); i++){
    if(users[i] == u){
      return;
    }
  }
  users.push_back(u);
}

// assign keywords function that takes the keywords from a given product and stores them in a map
void MyDataStore::assignKeywords(Product* p) {
  set<string> keywords = p->keywords();
  for(set<string>::iterator it = keywords.begin(); it != keywords.end(); it++){
    keywordsMap[*it].insert(p);
  }
}

// search function for AND and OR searches.
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
  set<Product*> searchResults;
  if(terms.empty()){
    return vector<Product*>();
  }
  if(type == 0){ // AND search
    for(size_t i = 0; i < terms.size(); i++){
      set<Product*> matches;
      for(map<string, set<Product*>>::iterator it = keywordsMap.begin(); it != keywordsMap.end(); it++){
        if(it->first == terms[i]){
          matches = it->second;
          break;
        }
      }
      if(i == 0){
        searchResults = matches;
      }
      else {
        searchResults = setIntersection(searchResults, matches);
      }
    }
  }
  else { // OR search
    for(size_t i = 0; i < terms.size(); i++){
      set<Product*> matches = keywordsMap[terms[i]];
      searchResults.insert(matches.begin(), matches.end());
    }
  }
  return vector<Product*>(searchResults.begin(), searchResults.end());
}

// dump to write database to output file
void MyDataStore::dump(ostream& ofile) {
  if(!ofile){ // make sure stream is valid 
    return;
  }
  ofile << "<products>" << endl; // print the products start header
  for(size_t i = 0; i < products.size(); i++){ // loop through and print all the products
    products[i]->dump(ofile);
  }
  ofile << "</products>" << endl; // print the products end header
  ofile << "<users>" << endl; // print the users start header
  ofile << fixed << setprecision(2); // make sure decimals are to two places
  for(size_t i = 0; i < users.size(); i++){ // loop through and print all the users
    users[i]->dump(ofile);
  }
  ofile << "</users>" << endl; // print the users end header
}

// view cart function for user
void MyDataStore::viewCart(const string& username) {
  bool validUser = false; // make sure that the user is one in the database
  string lowercaseUsername = convToLower(username); // this may be redundant... but it's here! and staying?
  for(size_t i = 0; i < users.size(); i++){ // loop through all the users
    if(convToLower(users[i]->getName()) == lowercaseUsername){
      validUser = true; // if the username matches an existing user, good to go!
      break;
    }
  }
  if(!validUser){ // if not, print statement
    cout << "Invalid username" << endl;
    return;
  }
  if(cartMap[lowercaseUsername].empty() ){ // if cart doesn't have items just return
    return;
  }
  displayProducts(cartMap[lowercaseUsername]); // display the products in the user's cart!
}

// function for adding a product to the cart
void MyDataStore::addToCart(const string& username, Product* p) {
  bool validUser = false; 
  string lowercaseUsername = convToLower(username);
  for(size_t i = 0; i < users.size(); i++){ // loop through the users to make sure that the username is valid
    if(convToLower(users[i]->getName()) == lowercaseUsername){
      validUser = true; // yay!
      break;
    }
  }
  if(!validUser){ // invalid statement print
    cout << "Invalid request" << endl;
    return;
  }
  cartMap[username].push_back(p); // add the product to the user's cart in the map
}

// function for buying the cart!!!!!!!!!
void MyDataStore::buyCart(const string& username) {
  bool validUser = false; 
  User* currentUser = nullptr;
  string lowercaseUsername = convToLower(username);
  for(size_t i = 0; i < users.size(); i++){ // loop through all the users to make sure username is valid
    if(convToLower(users[i]->getName()) == lowercaseUsername){
      validUser = true; // let's gooooooo
      currentUser = users[i]; // make this valid user the current user
      break;
    }
  }
  if(!validUser){ // uh oh!
    cout << "Invalid username" << endl;
    return;
  }
  vector<Product*>& cart = cartMap[lowercaseUsername]; // get the user's cart
  vector<Product*> itemsLeft; // keep track of item's that had to be left behind :(
  for(size_t i = 0; i < cart.size(); i++){ // loop through all the items in the cart
    Product* item = cart[i];
    if(item->getQty() > 0 && currentUser->getBalance() >= item->getPrice()){ // make sure item is in stock and user has enough money
      item->subtractQty(1); // subtract from the inventory quantity if purchased
      currentUser->deductAmount(item->getPrice()); // subtract amount spent from the user's credit
    }
    else {
      itemsLeft.push_back(item); // or else put the item back 
    }
  }
  cart = itemsLeft; // cart now just has unpurchased items
}