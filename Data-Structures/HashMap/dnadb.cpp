// CMSC 341 - Spring 2022 - Project 4
#include "dnadb.h"
DnaDb::DnaDb(int size, hash_fn hash){
    if(isPrime(size)){
        m_currentCap = size < MINPRIME? MINPRIME : 0;
        m_currentCap = m_currentCap == 0 && size > MAXPRIME? MAXPRIME : size;
    } else {
        m_currentCap = findNextPrime(size);
    }
    m_hash = hash;

    m_currentTable = new DNA[m_currentCap];
    m_oldTable = nullptr;
    m_currNumDeleted = 0;
    m_currentSize = 0;
    m_oldCap = 0;
    m_oldNumDeleted = 0;
    m_oldSize = 0;
}

DnaDb::~DnaDb(){
    delete[] m_currentTable;
    delete[] m_oldTable;

}

bool DnaDb::insert(DNA dna){
    unsigned int index = m_hash(dna.m_sequence) % m_currentCap;

    int i = 0;
    while(!(m_currentTable[index] == EMPTY)) {
        index = ((m_hash(dna.m_sequence) % m_currentCap) + (i*i)) % m_currentCap;
        if((m_currentTable[index].m_location == dna.m_location) && (m_currentTable[index].m_sequence == dna.m_sequence)){
            return false;
        }
        i++;
    }
    m_currentTable[index] = dna;
    m_currentSize++;

    if(lambda() > 0.5){
        m_oldTable = m_currentTable;
        m_oldCap = m_currentCap;
        m_oldSize = m_currentSize;
        m_oldNumDeleted = m_currNumDeleted;
        m_currentCap = findNextPrime((m_currentSize - m_currNumDeleted)*4);
        m_currentTable = new DNA[m_currentCap];
        m_currentSize = 0;
        m_currNumDeleted = 0;

    }
    if(m_oldTable != nullptr){
        Transfer();
    }

    return true;
}

void DnaDb::TInsert(DNA dna) {
    unsigned int index = m_hash(dna.m_sequence) % m_currentCap;

    int i = 0;
    while(!m_currentTable[index].getSequence().empty()) {
        index = ((m_hash(dna.m_sequence) % m_currentCap) + (i*i)) % m_currentCap;
        i++;
    }
    m_currentTable[index] = dna;
    m_currentSize++;
}

void DnaDb::Transfer() {
    static int quarterNum = 1;
    int sizeQuart = m_oldCap * 0.25;
    int start = (sizeQuart * (quarterNum - 1));
    int end = sizeQuart * quarterNum;
    if(quarterNum == 4)
        end = m_oldCap;
    for (int i = start; i < end; ++i) {
        if (!(m_oldTable[i] == EMPTY) && !(m_oldTable[i] == DELETED)){
            DNA insertdna = m_oldTable[i];
            TInsert(insertdna);
            m_oldTable[i] = DELETED;
            m_oldNumDeleted++;
        }
    }

    if(quarterNum == 4){
        if(m_oldNumDeleted != m_oldSize){
            cout << "not all transfered" << endl;
        }
        delete[] m_oldTable;
        m_oldTable = nullptr;
        m_oldCap = 0;
        m_oldSize = 0;
        m_oldNumDeleted = 0;
        quarterNum = 0;
    }

    quarterNum++;

}

bool DnaDb::remove(DNA dna){
    unsigned int index = m_hash(dna.m_sequence) % m_currentCap;
    int i = 0;
    DNA returnDna = EMPTY;
    while(!m_currentTable[index].getSequence().empty()) {
        index = ((m_hash(dna.m_sequence) % m_currentCap) + (i*i)) % m_currentCap;
        if(m_currentTable[index].m_location == dna.m_location){
            m_currentTable[index] = DELETED;
            m_currNumDeleted++;
            if(m_oldTable != nullptr){
                Transfer();
            } else {
                if(deletedRatio() > 0.8){
                    m_oldTable = m_currentTable;
                    m_oldCap = m_currentCap;
                    m_oldSize = m_currentSize;
                    m_oldNumDeleted = m_currNumDeleted;
                    m_currentCap = findNextPrime((m_currentSize - m_currNumDeleted)*4);
                    m_currentTable = new DNA[m_currentCap];
                    m_currentSize = 0;
                    m_currNumDeleted = 0;
                    Transfer();
                }
            }
            return true;
        }
        i++;
    }

    if(m_oldTable != nullptr) {
        while (!m_oldTable[index].getSequence().empty()) {
            index = ((m_hash(dna.m_sequence) % m_currentCap) + (i * i)) % m_currentCap;
            if (m_oldTable[index].m_location == dna.m_location) {
                m_oldTable[index] = DELETED;
                m_oldNumDeleted++;
                Transfer();
                return true;
            }
            i++;
        }
    }

    return false;

}

DNA DnaDb::getDNA(string sequence, int location){
    unsigned int index = m_hash(sequence) % m_currentCap;
    int i = 0;
    DNA returnDna = EMPTY;
    while(!m_currentTable[index].getSequence().empty()) {
        index = ((m_hash(sequence) % m_currentCap) + (i*i)) % m_currentCap;
        if(m_currentTable[index].m_location == location){
            returnDna = m_currentTable[index];
            return returnDna;
        }
        i++;
    }
    if(m_oldTable != nullptr) {
        while (!m_oldTable[index].getSequence().empty()) {
            index = ((m_hash(sequence) % m_currentCap) + (i * i)) % m_currentCap;
            if (m_oldTable[index].m_location == location) {
                returnDna = m_oldTable[index];
                return returnDna;
            }
            i++;
        }
    }

    return returnDna;


}

float DnaDb::lambda() const {
    return (float) m_currentSize / (float) m_currentCap;
}

float DnaDb::deletedRatio() const {
    return (float) m_currNumDeleted / (float) m_currentSize;
}

void DnaDb::dump() const {
    cout << "Dump for current table: " << endl;
    if (m_currentTable != nullptr)
        for (unsigned int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for old table: " << endl;
    if (m_oldTable != nullptr)
        for (unsigned int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool DnaDb::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int DnaDb::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

DNA::DNA(string sequence, int location) {
    if ((location >= MINLOCID && location <= MAXLOCID) ||
        (location == 0 && sequence == "DELETED")){
        // this is a normal or a DELETED object
        m_sequence = sequence;
        m_location = location;
    }
    else{
        // this is the empty object
        m_sequence = "";
        m_location = 0;
    }
}

string DNA::getSequence() const {
    return m_sequence;
}

int DNA::getLocId() const {
    return m_location;
}

// Overloaded assignment operator
const DNA& DNA::operator=(const DNA& rhs){
    if (this != &rhs){
        m_sequence = rhs.m_sequence;
        m_location = rhs.m_location;
    }
    return *this;
}

// Overloaded insertion operator.  Prints DNA's sequence (key),
// and the location ID. This is a friend function in DNA class.
ostream& operator<<(ostream& sout, const DNA &dna ) {
    if (!dna.m_sequence.empty())
        sout << dna.m_sequence << " (Location ID " << dna.m_location << ")";
    else
        sout << "";
  return sout;
}

// Overloaded equality operator. This is a friend function in DNA class.
// To test inequality we may negate the results of this operator.
bool operator==(const DNA& lhs, const DNA& rhs){
    return ((lhs.m_sequence == rhs.m_sequence) && (lhs.m_location == rhs.m_location));
}