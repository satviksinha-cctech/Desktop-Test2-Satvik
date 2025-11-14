//Importing necessary libraries and header file
#include"header.h"
#include<iostream>
#include<algorithm>
#include<vector>

//Parts body
Parts::Parts(int i, string n, string m, double d)
    : id(i), name(n), material(m), diameter(d)
{
    cout << "[Construct] Parts: " << name << endl;
}

Parts::~Parts()
{
    cout << "[Destruct] Parts: " << name << endl;
}

int Parts::getID() const {
    return id;
}
string Parts::getName() const {
    return name;
}

//Pipes body
Pipes::Pipes(int i, string n, string m, double d, double l)
    : Parts(i, n, m, d), length(l)
{
    cout << "[Construct] Pipes" << endl;
}

Pipes::~Pipes()
{
    cout << "[Destruct] Pipes" << endl;
}

string Pipes::getType() const { return "Pipe"; }

void Pipes::display() const {
    cout << "Pipe | ID: " << id << " | Name: " << name << 
        " | Material: " << material << " | Diameter: " << diameter
        << " | Length: " << length << endl;
}

//Valves Body
Valves::Valves(int i, string n, string m, double d, double t)
    : Parts(i, n, m, d), thickness(t)
{
    cout << "[Construct] Valves" << endl;
}

Valves::~Valves()
{
    cout << "[Destruct] Valves" << endl;
}

string Valves::getType() const { return "Valve"; }

void Valves::display() const {
    cout << "Valve | ID: " << id
        << " | Name: " << name
        << " | Material: " << material << " | Diameter: " << diameter
        << " | Thickness: " << thickness << endl;
}

//Elbows Body
Elbows::Elbows(int i, string n, string m, double d)
    : Parts(i, n, m, d)
{
    cout << "[Construct] Elbows" << endl;
}

Elbows::~Elbows()
{
    cout << "[Destruct] Elbows" << endl;
}

string Elbows::getType() const {
    return "Elbow";
}

void Elbows::display() const {
    cout << "Elbow | ID: " << id
        << " | Name: " << name
        << " | Material: " << material << " | Diameter: " << diameter << endl;
}

//Flanges body
Flanges::Flanges(int i, string n, string m, double d)
    : Parts(i, n, m, d)
{
    cout << "[Construct] Flanges" << endl;
}

Flanges::~Flanges()
{
    cout << "[Destruct] Flange" << endl;
}

string Flanges::getType() const {
    return "Flange";
}

void Flanges::display() const {
    cout << "Flange | ID: " << id
        << " | Name: " << name
        << " | Material: " << material << " | Diameter: " << diameter << endl;
}

//Helper Functions Body
//Adding
void AddParts(vector<unique_ptr<Parts>>& items) {
    cout << "\nSelect Part Type:\n"
        << "1. Pipe\n"
        << "2. Valve\n"
        << "3. Elbow\n"
        << "4. Flange\n"
        << "Choice: ";

    int type;
    cin >> type;

    try {
        int id = readValue<int>("Enter ID: ");
        string name = readValue<string>("Enter Name: ");
        string material = readValue<string>("Enter Material: ");
        double diameter = readValue<double>("Enter Diameter: ");

        if (diameter <= 0) throw runtime_error("Diameter must be positive!");
        
        if (type == 1) {
            double l = readValue<double>("Enter Length: ");
            items.push_back(make_unique<Pipes>(id, name, material, diameter, l));
        }
        else if (type == 2) {
            double t = readValue<double>("Enter Thickness: ");
            items.push_back(make_unique<Valves>(id, name, material, diameter, t));
        }
        else if (type == 3) {
            items.push_back(make_unique<Elbows>(id, name, material, diameter));
        }
        else if (type == 4) {
            items.push_back(make_unique<Flanges>(id, name, material, diameter));
        }
        else {
            cout << "Invalid type." << endl;
        }
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

//Viewing
void ViewParts(const vector<unique_ptr<Parts>>& items)
{
    cout << "\nCAD Parts Inventory \n";
    if (items.empty()) {
        cout << "No parts available. \n";
        return;
    }
    for (const auto& part : items)
        part->display();
}

//Searching
void SearchParts(const vector<unique_ptr<Parts>>& items)
{
    string key;
    cout << "Enter name to search: ";
    cin >> key;

    auto it = find_if(items.begin(), items.end(),
        [&](const unique_ptr<Parts>& part)
        {
            return part->getName() == key;
        });

    if (it != items.end()) {
        cout << "Part Found: " << endl;
        (*it)->display();
    }
    else {
        cout << "No part found with name: " << key << endl;
    }
}



//Deleting
void DeleteParts(vector<unique_ptr<Parts>>& items)
{
    int key;
    cout << "Enter ID to delete: ";
    cin >> key;

    auto it = find_if(items.begin(), items.end(),
        [&](const unique_ptr<Parts>& part)
        {
            return part->getID() == key;
        });

    if (it != items.end()) {
        cout << "Deleting: " << (*it)->getName() << endl;
        items.erase(it);
        cout << "Deleted successfully." << endl;
    }
    else {
        cout << "Part not found." << endl;
    }
}

int main()
{
    vector<unique_ptr<Parts>> parts;
    bool running = true;

    while (running) {
        cout << "CAD Parts Menu: \n"
            << "1. Add Part\n"
            << "2. View Parts\n"
            << "3. Search a Part\n"
            << "4. Delete a Part\n"
            << "5. Exit\n"
            << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            AddParts(parts);
            break;
        case 2:
            ViewParts(parts);
            break;
        case 3:
            SearchParts(parts);
            break;
        case 4:
            DeleteParts(parts);
            break;
        case 5:
            running = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }

    cout << "Exiting, parts destructed." << endl;
    return 0;
}



