#pragma once        //Used so that header file gets included only once
//Importing necessary libraries
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// Template function
template <typename T>
T readValue(const string& prompt) {
    cout << prompt;
    T value;
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw runtime_error("Invalid input!");
    }
    return value;
}

// Base Class
class Parts {
protected:
    int id;
    string name;
    string material;
    double diameter;

public:
    Parts(int i, string n, string m, double d);
    virtual ~Parts();

    virtual void display() const = 0;
    virtual string getType() const = 0;

    int getID() const;
    string getName() const;
};

//Derived Class:Pipes
class Pipes : public Parts {
private:
    double length;

public:
    Pipes(int i, string n, string m, double d, double l);
    ~Pipes();

    string getType() const override;
    void display() const override;
};

//Derived Class:Valves
class Valves : public Parts {
private:
    double thickness;

public:
    Valves(int i, string n, string m, double d, double t);
    ~Valves();

    string getType() const override;
    void display() const override;
};

//Derived Class:Elbows
class Elbows : public Parts {
public:
    Elbows(int i, string n, string m, double d);
    ~Elbows();

    string getType() const override;
    void display() const override;
};

//Derived Class:Flanges
class Flanges : public Parts {
public:
    Flanges(int i, string n, string m, double d);
    ~Flanges();

    string getType() const override;
    void display() const override;
};

//Helper Functions
void AddParts(vector<unique_ptr<Parts>>& items);
void ViewParts(const vector<unique_ptr<Parts>>& items);
void SearchParts(const vector<unique_ptr<Parts>>& items);
void DeleteParts(vector<unique_ptr<Parts>>& items);


