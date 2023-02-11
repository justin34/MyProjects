// UMBC - CMSC 341 - Spring 2022 - Proj2
#include "fleet.h"
#include <random>
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
class Tester{
public:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
    bool insertTestPassed(){
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);

        Fleet* fleet = new Fleet;
        int fleetSize = 300;
        int ID = 0;
        for(int i=0;i < fleetSize;i++) {
            ID = idGen.getRandNum();
            Ship ship(ID, static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet->insert(ship);
        }

        if(isBST(fleet->m_root) && hightsCorrect(fleet->m_root) && isBalanced(fleet->m_root)){
            delete fleet;
            return true;
        }
        delete fleet;
        return false;
    }

    bool removeTestpassed(){
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);

        Fleet fleet;
        int fleetSize = 300;
        int fleetIds[300];
        int ID = 0;
        for(int i=0;i<fleetSize;i++) {
            ID = idGen.getRandNum();
            fleetIds[i] = ID;
            Ship ship(ID, static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        for (int i = 0; i < fleetSize/2; ++i) {
            fleet.remove(fleetIds[2*i]);
            if(!fleet.findShip(fleetIds[2*i])){
                return false;
            }
        }

        if(isBST(fleet.m_root) && hightsCorrect(fleet.m_root) &&isBalanced(fleet.m_root)){
            return true;
        }
        return false;
    }
    bool InsertErrorTestPassed(){
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);

        Fleet fleet;
        int fleetSize = 10;
        int fleetIds[10];
        int ID = 0;
        for(int i=0;i<fleetSize;i++) {
            ID = idGen.getRandNum();
            fleetIds[i] = ID;
            Ship ship(ID, static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }
        bool result = false;
        try{
            Ship ship(fleetIds[1], static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        } catch(const char* error){
            cout << error << endl;
            result = true;
        }

        return result;
    }

    bool removeErrorTestPassed(){
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);

        Fleet fleet;
        bool result = false;
        try{ fleet.remove(0); } catch (const char * error) {
            cout << error << endl;
            result = true;
        }
        int fleetSize = 10;
        int ID = 0;
        for(int i=0;i<fleetSize;i++) {
            ID = idGen.getRandNum();
            Ship ship(ID, static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        try{ fleet.remove(-1); } catch (const char * error) {
            cout << error << endl;
            if(result)
                result = true;
        }

        return result;
    }

    bool removeLostTest(){
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);

        Fleet fleet;
        int fleetSize = 10;
        int fleetIds[10];
        int ID = 0;
        for(int i=0;i<fleetSize;i++) {
            ID = idGen.getRandNum();
            fleetIds[i] = ID;
            Ship ship(ID, static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        for (int i = 0; i < fleetSize/2; ++i) {
            fleet.setState(fleetIds[2*i], LOST);
        }

        fleet.removeLost();
        return checkLost(fleet.m_root);
    }

    bool timeTestpassed(){
        clock_t start, stop;
        int n = 1000;
        double T1 = n * log(n);
        double T2 = (2*n) * log(2 * n);
        double ratio = T1/T2;

        Fleet* fleet;
        start = clock();
        fleet = fillFleat(n);
        stop = clock();
        double RealT1 = start - stop;
        delete fleet;
        Fleet* fleet2;
        start = clock();
        fleet2 = fillFleat(2 * n);
        stop = clock();
        double RealT2 = start - stop;
        delete fleet2;

        double realRatio = RealT1/RealT2;

        if (realRatio > (ratio + 0.4)){
            return false;
        } else if ( realRatio < (ratio - 0.4))
            return false;

        return true;

    }

private:
    bool isBalanced(Ship* ship){
        if (ship == nullptr)
            return true;

        // local vars to store height
        int Lheight;
        int Rheight;

        // if the left is null set it to -1 otherwise just set it to its height
        if(ship->m_left == nullptr)
            Lheight = -1;
        else
            Lheight = ship->m_left->m_height;

        // same for right
        if(ship->m_right == nullptr)
            Rheight = -1;
        else
            Rheight = ship->m_right->m_height;

        if(isBalanced(ship->m_left) && isBalanced(ship->m_right)){
            if ((Lheight - Rheight) <= 1){
                return true;
            }
        }

        return false;
    }

    bool isBST(Ship* ship)
    {
        if (ship == nullptr)
            return true;

        if (ship->m_left != nullptr && ship->m_left->m_id > ship->m_id)
            return false;

        if (ship->m_right != nullptr && ship->m_right->m_id < ship->m_id)
            return false;

        if (!isBST(ship->m_left) || !isBST(ship->m_right))
            return false;

        return true;
    }

    bool hightsCorrect(Ship* ship){
        if(ship == nullptr){
            return true;
        }

        bool isLCorrect = hightsCorrect(ship->m_left);
        bool isRCorrect = hightsCorrect(ship->m_right);

        if(isLCorrect && isRCorrect){
            // local vars to store height
            int Lheight;
            int Rheight;

            // if the left is null set it to -1 otherwise just set it to its height
            if(ship->m_left == nullptr)
                Lheight = -1;
            else
                Lheight = ship->m_left->m_height;

            // same for right
            if(ship->m_right == nullptr)
                Rheight = -1;
            else
                Rheight = ship->m_right->m_height;

            int biggerHight = (Lheight > Rheight)? Lheight : Rheight;
            if(ship->m_height == biggerHight+1)
                return true;
        }
        return false;
    }

    bool checkLost(Ship* ship){
        if(ship == nullptr)
            return true;
        if(ship->m_state == LOST){
            return false;
        } else {
            return checkLost(ship->m_left) && checkLost(ship->m_right);
        }
    }

    Fleet* fillFleat(int itemNum){
        Random idGen(MINID,MAXID);
        Random typeGen(0,4);

        Fleet* fleet = new Fleet;
        int fleetSize = itemNum;
        int ID = 0;
        for(int i=0;i<fleetSize;i++) {
            ID = idGen.getRandNum();
            Ship ship(ID, static_cast<SHIPTYPE>(typeGen.getRandNum()));
            try{  fleet->insert(ship);} catch(const char* error) {}// cout << error << endl;} // random cant make 2000 different numbers so it duplicates
        }

        return fleet;
    }


};

int main(){
    Tester tester;

    string result = tester.insertTestPassed() ? "True" : "False";
    cout << "Insert test passed?: " <<  result << endl;

    result = tester.removeTestpassed() ? "True" : "False";
    cout << "Remove test passed?: " <<  result << endl;

    result = tester.InsertErrorTestPassed() ? "True" : "False";
    cout << "Insert error test passed?: " <<  result << endl;

    result = tester.removeErrorTestPassed() ? "True" : "False";
    cout << "Remove error test passed?: " <<  result << endl;

    result = tester.removeLostTest() ? "True" : "False";
    cout << "Remove lost test passed?: " <<  result << endl;

    result = tester.timeTestpassed() ? "True" : "False";
    cout << "Time test passed?: " <<  result << endl;

}