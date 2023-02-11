// CMSC 341 - Spring 2022 - Project 4
#include "dnadb.h"
#include <random>
#include <vector>
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
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
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



unsigned int hashCode(const string str);
string sequencer(int size, int seedNum);



class Tester{
    class LinkedList{
        struct Node{
            Node(DNA dna) {
                value = dna;
                next = nullptr;
            }
            Node(DNA dna, Node* pNode) {
                value = dna;
                next = pNode;
            }

            DNA value;
            Node* next;
        };
    public:
        LinkedList(){
            m_head = nullptr;
        }


        void clear(){
            while (!isEmpty()){
                pop();
            }
        }

        void push(DNA dna){
            Node* newNode = new Node(dna, m_head);
            m_head = newNode;
        };

        DNA pop(){
            if(m_head == nullptr)
                return EMPTY;
            DNA returnDna = m_head->value;
            Node* temp = m_head;
            m_head = m_head->next;
            delete temp;
            return returnDna;
        }

        bool isEmpty() {
            return m_head == nullptr;
        }

    private:
        Node* m_head;
    };

public:
    bool noColInsertTest(){
        DnaDb dnadb(MINPRIME, hashCode);
        getNoConlision();
        while (!dnaValues.isEmpty()){
            DNA insert = dnaValues.pop();
            dnadb.insert(insert);
            if(dnadb.getDNA(insert.m_sequence, insert.m_location) == EMPTY){
                return false;
            }
        }
        if(indexCheck.size() == dnadb.m_currentSize)
            return true;
        else return false;
    }

    bool ColInsertTest(){
        DnaDb dnadb(MINPRIME, hashCode);
        getConlision();
        while (!dnaValues.isEmpty()){
            DNA insert = dnaValues.pop();
            dnadb.insert(insert);
            if(dnadb.getDNA(insert.m_sequence, insert.m_location) == EMPTY){
                return false;
            }
        }

        return true;
    }

    bool rehashInsertTest(){
        vector<DNA> dataList;
        Random RndLocation(MINLOCID,MAXLOCID);
        DnaDb dnadb(MINPRIME, hashCode);
        for (int i=0;i<300;i++){
            // generating random data
            DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
            // saving data for later use
            dataList.push_back(dataObj);
            // inserting data in to the DnaDb object
            dnadb.insert(dataObj);
        }

        for (auto & i : dataList) {
            if(dnadb.getDNA(i.m_sequence, i.m_location) == EMPTY){
                return false;
            }
        }

        return true;
    }

    bool removeTest(){
        vector<DNA> dataList;
        Random RndLocation(MINLOCID,MAXLOCID);
        DnaDb dnadb(MINPRIME, hashCode);
        for (int i=0;i<100;i++){
            // generating random data
            DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
            // saving data for later use
            dataList.push_back(dataObj);
            // inserting data in to the DnaDb object
            dnadb.insert(dataObj);
        }

        for (unsigned int i = 0; i < dataList.size() / 2; ++i) {
            dnadb.remove(dataList[i * 2]);
        }

        for (unsigned int i = 0; i < dataList.size() / 2; ++i) {
            if (!(dnadb.getDNA(dataList[i * 2].m_sequence, dataList[i * 2].m_location) == EMPTY)){
                return false;
            }
        }

        return true;
    }

    bool removeReHash(){
        vector<DNA> dataList;
        Random RndLocation(MINLOCID,MAXLOCID);
        DnaDb dnadb(MINPRIME, hashCode);
        for (int i=0;i<300;i++){
            // generating random data
            DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
            // saving data for later use
            dataList.push_back(dataObj);
            // inserting data in to the DnaDb object
            dnadb.insert(dataObj);
        }

        unsigned int preHashCap = dnadb.m_currentCap;

        for (unsigned int i = 0; i < dataList.size() - 40; ++i) {
            dnadb.remove(dataList[i]);
        }

        if((dnadb.m_currentCap + dnadb.m_oldCap) < preHashCap)
            return true;

        return false;

    }



private:
    void getNoConlision(){
        Random RndLocation(MINLOCID,MAXLOCID);
        for (int i=0;i<49;i++){
            bool insertValue = true;
            // generating random data
            DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
            // saving data for later use
            for (unsigned int j = 0; j < indexCheck.size(); ++j) {
                if((hashCode(dataObj.m_sequence) % MINPRIME) == indexCheck[j])
                    insertValue = false;
            }

            if(insertValue) {
                dnaValues.push(dataObj);
                indexCheck.push_back((hashCode(dataObj.m_sequence) % MINPRIME));
            }
        }
    }

    void getConlision(){
        Random RndLocation(MINLOCID,MAXLOCID);
        unsigned int colIndex;
        for (int i=0;i<49;i++){
            bool insertValue = false;
            // generating random data
            DNA dataObj = DNA(sequencer(5, i), RndLocation.getRandNum());
            // saving data for later use
            if(i == 0)
                colIndex = (hashCode(dataObj.m_sequence) % MINPRIME);

            for (unsigned int j = 0; j < indexCheck.size(); ++j) {
                if((hashCode(dataObj.m_sequence) % MINPRIME) == colIndex)
                    insertValue = true;
            }

            if(insertValue) {
                dnaValues.push(dataObj);

            }
        }
    }
    LinkedList dnaValues;
    vector<unsigned int> indexCheck;
};

int main(){
    Tester tester;

    string result = tester.noColInsertTest() ? "True" : "False";
    cout << "Insert test no Col passed?: " <<  result << endl;

    result = tester.ColInsertTest() ? "True" : "False";
    cout << "Insert test Col passed?: " <<  result << endl;

    result = tester.rehashInsertTest() ? "True" : "False";
    cout << "insert rehash test passed?: " <<  result << endl;

    result = tester.removeTest() ? "True" : "False";
    cout << "remove test passed?: " <<  result << endl;

    result = tester.removeReHash() ? "True" : "False";
    cout << "remove rehash test passed?: " <<  result << endl;

    return 0;
}




unsigned int hashCode(const string str) {
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook
    for (long unsigned int i = 0 ; i < str.length(); i++)
        val = val * thirtyThree + str[i] ;
    return val ;
}
string sequencer(int size, int seedNum){
    //this function returns a random DNA sequence
    string sequence = "";
    Random rndObject(0,3);
    rndObject.setSeed(seedNum);
    for (int i=0;i<size;i++){
        sequence = sequence + ALPHA[rndObject.getRandNum()];
    }
    return sequence;
}

