// UMBC - CMSC 341 - Spring 2022 - Proj2
#include "fleet.h"
Fleet::Fleet(){
    m_root = nullptr;
}
Fleet::~Fleet(){
    clear();
}
void Fleet::insert(const Ship& ship){
    if(findShip(ship.m_id)){ // check for dupicates;
        throw "Duplicate shipID";
    }
    insert(ship, m_root); // call recursive helper function for insert
    updateHeight(m_root);
    if (abs(checkImbalance(m_root)) > 1) // if the root is unbalanced rebalance it
        m_root = rebalance(m_root);
}

void Fleet::insert(const Ship& InsertShip, Ship*& ship) {
    if(ship == nullptr){ // when it reaches a null pointer it sets it to the value that needed inserting
        ship = new Ship(InsertShip.getID(),InsertShip.getType(), InsertShip.m_state);

    } else if (InsertShip.m_id < ship->m_id){ // when id is less than the current ship

        insert(InsertShip, ship->m_left); // insert to the left
        updateHeight(ship); // update height
        if (abs(checkImbalance(ship)) > 1) // check if it is unbalanced
            ship = rebalance(ship);

    } else if (InsertShip.m_id > ship->m_id){ // when id is higher than the current ship
        insert(InsertShip, ship->m_right); // insert to the right
        updateHeight(ship); // update height
        if (abs(checkImbalance(ship)) > 1) // check if unbalanced
            ship =  rebalance(ship);

    }
}

void Fleet::clear(){
    clear(m_root); // call helper function for clear
}

void Fleet::clear(Ship* ship) {
    if (ship != nullptr){ // if its not null
        clear(ship->m_left); // clear left
        clear(ship->m_right); // clear right
        delete ship; // delete current
        ship = nullptr; // set it to nullptr
    }
}

void Fleet::remove(int id){
    if (m_root == nullptr)
        throw "List Empty";
    if(!findShip(id))
        throw "ID doesn't exist in list";
    m_root = remove(id, m_root);
    updateHeight(m_root); // update height
    if (abs(checkImbalance(m_root)) > 1) // check if it is unbalanced
        m_root = rebalance(m_root);
}

Ship* Fleet::remove(int id, Ship* ship) {
    if(ship == nullptr)
        return ship;

    if (id < ship->m_id){ // move left if less
        ship->m_left = remove(id, ship->m_left); // remove left
        updateHeight(ship); // update height
        if (abs(checkImbalance(ship)) > 1) // check if it is unbalanced
            ship = rebalance(ship);
    } else if (id > ship->m_id){ // move right if greater
        ship->m_right = remove(id, ship->m_right);
        updateHeight(ship); // update height
        if (abs(checkImbalance(ship)) > 1) // check if it is unbalanced
            ship = rebalance(ship);
    } else {
        if (ship->m_height == 0){ // if the ship is a leaf node
            delete ship;
            return nullptr;
        }
        Ship* replace;
        if(ship->m_right == nullptr){ // get the info for what to replace the ship with
            replace = findMax(ship->m_left);
        } else {
            replace = findMin(ship->m_right);
        }

        // replace info
        ship->m_id = replace->m_id;
        ship->m_type = replace->m_type;
        ship->m_state = replace->m_state;

        if(replace->m_id < id){ // remove the replacement
            ship->m_left = remove(replace->m_id, ship->m_left);
        } else {
            ship->m_right = remove(replace->m_id, ship->m_right);
        }
        updateHeight(ship); // update height
        if (abs(checkImbalance(ship)) > 1) // check if it is unbalanced
            ship = rebalance(ship);
    }

    return ship;
}

void Fleet::updateHeightFull(Ship* ship) {
    if(ship == nullptr)
        return;

    updateHeightFull(ship->m_left);
    updateHeightFull(ship->m_right);
    updateHeight(ship);
}

Ship *Fleet::findMax(Ship *ship) {
    if(ship->m_right == nullptr){
        return ship;
    }
    return findMax(ship->m_right);
}

Ship* Fleet::findMin(Ship *ship) {
        if(ship->m_left == nullptr){
            return ship;
        }
        return findMax(ship->m_left);
}

void Fleet::updateHeight(Ship* aShip){
    // local vars to store height
    int Lheight;
    int Rheight;

    // if the left is null set it to -1 otherwise just set it to its height
    if(aShip->m_left == nullptr)
        Lheight = -1;
    else
        Lheight = aShip->m_left->m_height;

    // same for right
    if(aShip->m_right == nullptr)
        Rheight = -1;
    else
        Rheight = aShip->m_right->m_height;

    if(Rheight > Lheight){ // if right is greater set it to Rheight++
        aShip->m_height = Rheight + 1;
    } else { // otherwise set it to Lheight++
        aShip->m_height = Lheight + 1;
    }
}

int Fleet::checkImbalance(Ship* aShip){
    // local vars to store height
    int Lheight;
    int Rheight;

    // if the left is null set it to -1 otherwise just set it to its height
    if(aShip->m_left == nullptr)
        Lheight = -1;
    else
        Lheight = aShip->m_left->m_height;

    // same for right
    if(aShip->m_right == nullptr)
        Rheight = -1;
    else
        Rheight = aShip->m_right->m_height;

    return Rheight - Lheight; // return the difference
}

Ship* Fleet::rebalance(Ship* aShip){
    int shipImbalance = checkImbalance(aShip); // get balances in order to see what leg is longer

    int LShipImbalace = 0;
    if(aShip->m_left != nullptr)
        LShipImbalace = checkImbalance(aShip->m_left);

    int RShipImbalance = 0;
    if(aShip->m_right != nullptr)
        RShipImbalance = checkImbalance(aShip->m_right);

    if(shipImbalance < 0 && LShipImbalace <= 0){ // left-left
        Ship* Z = aShip;
        Ship* Y = aShip->m_left;
        Z->m_left = Y->m_right;
        Y->m_right = Z;
        updateHeight(Z);
        updateHeight(Y);
        return Y;

    } else if (shipImbalance > 0 && RShipImbalance > 0){ // right-right
        Ship* Z = aShip;
        Ship* Y = aShip->m_right;
        Z->m_right = Y->m_left;
        Y->m_left = Z;
        updateHeight(Z);
        updateHeight(Y);
        return Y;

    } else if (shipImbalance < 0 && LShipImbalace > 0){ // left-right
        Ship* Z = aShip;
        Ship* Y = aShip->m_left;
        Ship* X = Y->m_right;

        Y->m_right = X->m_left;
        X->m_left = Y;
        Z->m_left = X;

        Z->m_left = X->m_right;
        X->m_right = Z;

        updateHeight(Z);
        updateHeight(Y);
        updateHeight(X);
        return X;
    } else if (shipImbalance > 0 && RShipImbalance < 0) { // right-left
        Ship *Z = aShip;
        Ship *Y = aShip->m_right;
        Ship *X = Y->m_left;

        Y->m_left = X->m_right;
        X->m_right = Y;
        Z->m_right = X;

        Z->m_right = X->m_left;
        X->m_left = Z;

        updateHeight(Z);
        updateHeight(Y);
        updateHeight(X);

        return X;
    }

    return aShip;
}

void Fleet::dumpTree() {
    //dump(m_root);
    cout << "______________________" << endl;
    cout << endl;
    printBT("", m_root, false);
}
void Fleet::printBT(const string& prefix, const Ship* node, bool isLeft) // code to print tree visually
{
    if (node != nullptr)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L--");
        // print the value of the node
        std::cout << node->m_id << "(" << node->m_height << ")" << std::endl;
        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_right, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_left, false);
    }
}

void Fleet::dump(Ship* aShip) const{
    if (aShip != nullptr){
        cout << "(";
        dump(aShip->m_left);//first visit the left child
        cout << aShip->m_id << ":" << aShip->m_height;//second visit the node itself
        dump(aShip->m_right);//third visit the right child
        cout << ")";
    }
}
void Fleet::listShips() const {
    listShips(m_root);
}

void Fleet::listShips(Ship* ship) const {
    string states[2] =  {"ALIVE", "LOST"};
    string shipTypes[5] {"CARGO", "TELESCOPE", "COMMUNICATOR", "FUELCARRIER", "ROBOCARRIER"};
    if (ship == nullptr){
        return;
    }

    listShips(ship->m_left);
    cout << ship->m_id << ":" << states[ship->m_state] << ":" << shipTypes[ship->m_type] << endl;
    listShips(ship->m_right);
}
bool Fleet::setState(int id, STATE state){
    Ship* ship = getShip(id, m_root);
    ship->m_state = state;
    return false;
}

void Fleet::removeLost(){
    removeLost(m_root);
}
void Fleet::removeLost(Ship* ship) {
    if(ship == nullptr){
        return;
    }
    removeLost(ship->m_left);
    removeLost(ship->m_right);
    if(ship->m_state == LOST){
        remove(ship->m_id);
    }

}

bool Fleet::findShip(int id) const {
    Ship* ship = getShip(id, m_root);
    if(ship == nullptr)
        return false;
    return true;
}

Ship *Fleet::getShip(int id, Ship *ship) const {
    if(ship == nullptr){
        return nullptr;
    } else if (ship->m_id == id){
        return ship;
    }
    Ship* ship1 = getShip(id, ship->m_left);
    Ship* ship2 = getShip(id, ship->m_right);

    if(ship1 == nullptr){
        return ship2;
    } else {
        return ship1;
    }

}
