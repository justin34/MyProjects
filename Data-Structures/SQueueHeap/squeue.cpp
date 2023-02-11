// CMSC 341 - Spring 2022 - Project 3
#include "squeue.h"
SQueue::SQueue(prifn_t priFn, HEAPTYPE heapType)
{
  m_priorFunc = priFn;
  m_heapType = heapType;
  m_heap = nullptr;
  m_size = 0;
}

SQueue::~SQueue()
{
  clear();
}

SQueue::SQueue(const SQueue& rhs)
{
    m_priorFunc = rhs.m_priorFunc;
    m_heapType = rhs.m_heapType;
    m_heap = nullptr;
    m_size = 0;

    postOrderCopy(rhs.m_heap);
}

SQueue& SQueue::operator=(const SQueue& rhs)
{
    if(&rhs == this) return *this;

    clear();
    m_priorFunc = rhs.m_priorFunc;
    m_heapType = rhs.m_heapType;
    postOrderCopy(rhs.m_heap);

    return * this;
}

void SQueue::postOrderCopy(Node *aNode) {
    if(aNode == nullptr){
        return;
    }

    insertPost(aNode->m_post);
    postOrderCopy(aNode->m_left);
    postOrderCopy(aNode->m_right);
}

void SQueue::insertPost(const Post& post) {
    Node* newNode = new Node(post);
    if(m_heapType == MAXHEAP) { m_heap = mergeMax(m_heap, newNode);}
    else m_heap = mergeMin(m_heap, newNode);
    m_size++;
}

Node *SQueue::mergeMin(Node *node1, Node *node2) {
    if(node1 == nullptr) return node2;
    if(node2 == nullptr) return node1;
    int priorNode1 = m_priorFunc(node1->m_post);
    int priorNode2 = m_priorFunc(node2->m_post);

    if(priorNode1 <= priorNode2){
        Node* temp = node1->m_right;
        node1->m_right = node1->m_left;
        node1->m_left = temp;
        node1->m_left = mergeMin(node2, node1->m_left);
        return node1;
    } else {
        Node* temp = node1->m_right;
        node1->m_right = node1->m_left;
        node1->m_left = temp;
        return mergeMin(node2, node1);
    }

}
Node *SQueue::mergeMax(Node *node1, Node *node2) {
    if(node1 == nullptr) return node2;
    if(node2 == nullptr) return node1;
    int priorNode1 = m_priorFunc(node1->m_post);
    int priorNode2 = m_priorFunc(node2->m_post);

    if(priorNode1 >= priorNode2){
        Node* temp = node1->m_right;
        node1->m_right = node1->m_left;
        node1->m_left = temp;
        node1->m_left = mergeMax(node2, node1->m_left);
        return node1;
    } else return mergeMax(node2, node1);

}
Post SQueue::getNextPost() {
    if(m_size == 0 ) throw out_of_range("list empty");
    Post returnPost = m_heap->m_post;
    Node* temp = m_heap;
    if(m_heapType == MAXHEAP) m_heap = mergeMax(m_heap->m_right, m_heap->m_left);
    else m_heap = mergeMin(m_heap->m_right, m_heap->m_left);
    delete temp;
    m_size--;
    return returnPost;
}

void SQueue::mergeWithQueue(SQueue& rhs) {
    if(rhs.m_size == 0)
        return;
    if(&rhs == this)
        return;
    if(rhs.m_heapType != m_heapType)
        throw domain_error("DIFFERENT HEAP TYPES");

    if(m_heapType == MAXHEAP) m_heap = mergeMax(m_heap, rhs.m_heap);
    else m_heap = mergeMin(m_heap, rhs.m_heap);
    rhs.m_heap = nullptr;
    rhs.m_size = 0;
}

void SQueue::clear() {
    clear(m_heap);
    m_heap = nullptr;
    m_size = 0;
}

void SQueue::clear(Node *aNode) {
    if(aNode == nullptr)
        return;

    if(aNode->m_left != nullptr){
        clear(aNode->m_left);
    }
    if(aNode->m_right != nullptr){
        clear(aNode->m_right);
    }

    delete aNode;
    aNode = nullptr;

}

int SQueue::numPosts() const
{
    return m_size;
}

void SQueue::printPostsQueue() const {
    cout << "Contents of posts queue:" << endl;
  printPosts(m_heap);
}

void SQueue::printPosts(Node *node) const {
    if(node == nullptr)
        return;

    cout << node->m_post << endl;

    printPosts(node->m_left);
    printPosts(node->m_right);
}

prifn_t SQueue::getPriorityFn() const {
    return  m_priorFunc;
}

void SQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
   /* SQueue newheap(priFn, heapType);
    newheap.postOrderCopy(m_heap);
    operator=(newheap); */

   int num = numPosts();
   Post posts[num];
   for(int i = 0; i < num; i++){
       posts[i] = getNextPost();
   }

    m_priorFunc = priFn;
    m_heapType = heapType;

    for(int i = num-1; i >= 0; i--) {
        insertPost(posts[i]);
    }


}


void SQueue::dump() const
{
  if (m_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(m_heap);
    cout << endl;
    printBT("", m_heap, false);
    cout << endl;
  }
}

void SQueue::printBT(const string& prefix, const Node* node, bool isLeft) const
{
    if (node != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        // print the value of the node
        cout << m_priorFunc(node->m_post) << endl;
        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_right, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_left, false);
    }
}


void SQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    cout << m_priorFunc(pos->m_post) << ":" << pos->m_post.getPostID();
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Post& post) {
  sout << "Post ID: " << post.getPostID() 
        << ", number of likes: " << post.getNumLikes()
        << ", interest level: " << post.getInterestLevel() 
        << ", connection level: " << post.getConnectLevel()
        << ", post time: " << post.getPostTime();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPost();
  return sout;
}
