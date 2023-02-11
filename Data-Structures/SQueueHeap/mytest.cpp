#include "squeue.h"
#include <random>

int priorityFn1(const Post &post);// works with a MAXHEAP
int priorityFn2(const Post &post);// works with a MINHEAP

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
    bool insertionTestMax(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn1, MAXHEAP);
        for (int i=0;i<300;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }

        return isMaxHeap(queue1.m_heap);
    }

    bool insertionTestMin(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn2, MINHEAP);
        for (int i=0;i<300;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }

        return isMinHeap(queue1.m_heap);
    }

    bool orderTestMin(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn2, MINHEAP);
        for (int i=0;i<300;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }

        int previousPriority = priorityFn2(queue1.getNextPost());
        int currentPriority;
        while (queue1.m_size > 0){
            currentPriority = priorityFn2(queue1.getNextPost());
            if(previousPriority > currentPriority)
                return false;
            previousPriority = currentPriority;
        }

        return true;
    }

    bool orderTestMax(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn1, MAXHEAP);
        for (int i=0;i<300;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }

        int previousPriority = priorityFn1(queue1.getNextPost());
        int currentPriority;
        while (queue1.m_size > 0){
            currentPriority = priorityFn1(queue1.getNextPost());
            if(previousPriority < currentPriority)
                return false;
            previousPriority = currentPriority;
        }

        return true;
    }

    bool changePriority(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn1, MAXHEAP);
        for (int i=0;i<300;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }

        queue1.setPriorityFn(priorityFn2, MINHEAP);
        return isMinHeap(queue1.m_heap);
    }

    bool mergeTest(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn1, MAXHEAP);
        for (int i=0;i<150;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }
        SQueue queue2(priorityFn1, MAXHEAP);
        for (int i=0;i<150;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue2.insertPost(aPost);
        }

        queue1.mergeWithQueue(queue2);
        queue1.mergeWithQueue(queue2);

        return isMaxHeap(queue1.m_heap) && queue2.m_size == 0;
    }

    bool assignmentOperator(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn2, MINHEAP);
        for (int i=0;i<17;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }
        SQueue queue2(priorityFn1, MAXHEAP);
        for (int i=0;i<15;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue2.insertPost(aPost);
        }

        queue1 = queue2;

        return areEqual(queue1, queue2);


    }

    bool copyConstructor(){
        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        SQueue queue1(priorityFn2, MINHEAP);
        for (int i=0;i<17;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
        }
        SQueue queue2(queue1);


        return areEqual(queue1, queue2);

    }

    bool errorCase(){
        SQueue queue1(priorityFn2, MINHEAP);
        SQueue queue2(priorityFn1, MAXHEAP);

        try{queue1.getNextPost(); } catch (out_of_range & e) {/*cout << &e << endl;*/}

        Random idGen(MINPOSTID,MAXPOSTID);
        Random likesGen(MINLIKES,MAXLIKES);
        Random timeGen(MINTIME,MAXTIME);
        Random conLevelGen(MINCONLEVEL,MAXCONLEVEL);
        Random interestGen(MININTERESTLEVEL,MAXINTERESTLEVEL);
        for (int i=0;i<5;i++){
            Post aPost(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue1.insertPost(aPost);
            Post aPost2(idGen.getRandNum(),
                       likesGen.getRandNum(),
                       conLevelGen.getRandNum(),
                       timeGen.getRandNum(),
                       interestGen.getRandNum());
            queue2.insertPost(aPost2);
        }

        try{queue1.mergeWithQueue(queue2); } catch (domain_error & e) { /*cout << &e << endl;*/}

        return true;
    }



private:
    bool isMaxHeap(Node* node)
    {
        if (node == nullptr)
            return true;

        if (node->m_left != nullptr && priorityFn1(node->m_left->m_post) > priorityFn1(node->m_post))
            return false;

        if (node->m_right != nullptr && priorityFn1(node->m_right->m_post) > priorityFn1(node->m_post))
            return false;

        if (!isMaxHeap(node->m_left) || !isMaxHeap(node->m_right))
            return false;

        return true;
    }
    bool isMinHeap(Node* node)
    {
        if (node == nullptr)
            return true;

        if (node->m_left != nullptr && priorityFn2(node->m_left->m_post) < priorityFn2(node->m_post))
            return false;

        if (node->m_right != nullptr && priorityFn2(node->m_right->m_post) < priorityFn2(node->m_post))
            return false;

        if (!isMinHeap(node->m_left) || !isMinHeap(node->m_right))
            return false;

        return true;
    }
    bool areEqual(SQueue &queue1, SQueue &queue2){
        if(queue1.m_size != queue2.m_size || queue1.m_heapType != queue2.m_heapType ||
        queue1.getPriorityFn() != queue2.getPriorityFn())
            return false;

        while (queue1.m_size > 0){
            if(queue1.getNextPost().m_postID != queue2.getNextPost().m_postID)
                return false;
        }

        return true;
    }

};

int main() {
    Tester tester;

    string result = tester.insertionTestMax() ? "True" : "False";
    cout << "Insert test passed?: " <<  result << endl;

    result = tester.insertionTestMin() ? "True" : "False";
    cout << "Insert test passed 2?: " <<  result << endl;

    result = tester.orderTestMax() ? "True" : "False";
    cout << "Order test passed?: " <<  result << endl;

    result = tester.orderTestMin() ? "True" : "False";
    cout << "Order test passed 2?: " <<  result << endl;

    result = tester.changePriority() ? "True" : "False";
    cout << "Priority change test passed?: " <<  result << endl;

    result = tester.mergeTest() ? "True" : "False";
    cout << "merge test passed?: " <<  result << endl;

    result = tester.assignmentOperator() ? "True" : "False";
    cout << "assignment test passed?: " <<  result << endl;

    result = tester.copyConstructor()? "True" : "False";
    cout << "Copy test passed?: " <<  result << endl;

    result = tester.errorCase()? "True" : "False";
    cout << "Error test passed?: " <<  result << endl;
}


int priorityFn1(const Post &post) {
    //needs MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [1-510]
    //the highest priority would be 500+10 = 510
    //the lowest priority would be 0+1 = 1
    //the larger value means the higher priority
    int priority = post.getNumLikes() + post.getInterestLevel();
    return priority;
}

int priorityFn2(const Post &post) {
    //needs MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [2-55]
    //the highest priority would be 1+1 = 2
    //the lowest priority would be 5+50 = 55
    //the smaller value means the higher priority
    int priority = post.getPostTime() + post.getConnectLevel();
    return priority;
}