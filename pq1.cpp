#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

class KVP : public pair<char, int> {
  private:
  public:
	KVP() : pair<char, int>('a',0) { }
	KVP(int p,char v) : pair<char,int>(v,p) { }
	~KVP() {};

	int key() {return this->second;}
	char value() {return this->first;}
	void print() { cout << "(" << key() << "," << value() << ")" << endl; }
};

class MaxHeap {

  private:
	int lSize;  // size of heap
	int aCapacity;  // capacity of array
	KVP * pArray;

  public:
	MaxHeap();
	~MaxHeap();

	// ADT functions
	int size();
	// you will need more functions here
	void printHeap(){
		for(int i = 0; i < lSize; i++){
			pArray[i].print();
		}
	}
	void deleteMax(){
		if(lSize != 0){
			pArray[0].print();
			pArray[0] = pArray[lastIndex()];
			lSize -= 1;
			fixDown(0);
		}
	}
	void printMax(){
		if(lSize != 0){
			pArray[0].print();
		}
	}

	// accessor methods
	int parentIndex(int i) {return ((i-1)/3);}
	int leftChildIndex(int i) {return (3*i+1);}
	int middleChildIndex(int i) {return (3*i+2);}
	int rightChildIndex(int i) {return (3*i+3);}
	int lastIndex() {return (lSize-1);}

	// other useful methods 
	void add(int i, char c);
	void fixDown(int j);
	void PQSort();
};

MaxHeap::MaxHeap() { // MaxHeap constructor
	aCapacity = 10;
	pArray = new KVP[aCapacity]; // pointer to array on heap
	lSize = 0;
}

MaxHeap::~MaxHeap() { // MaxHeap destructor
	delete [] pArray;
	pArray = NULL;
	lSize = 0;
    aCapacity = 10;
}


int MaxHeap::size() {
	return lSize;
}

void MaxHeap::add(int i, char c) { // adds a new KVP to the MaxHeap
	KVP k = KVP(i,c);

	if (lSize == aCapacity) {
		// double array if it's full
		int newCapacity = 2 * aCapacity;
		KVP * pNewArray = new KVP[newCapacity];
        for (int j = 0; j < aCapacity; j++) {
			pNewArray[j] = pArray[j];
		}

		delete [] pArray; // delete old heap-allocated array
		pArray = pNewArray; // points to new doubled heap size
		aCapacity = newCapacity;
        }

	// insert new item at end
	pArray[size()] = k;
	lSize += 1;
}

void MaxHeap::fixDown(int j) { // fixDown starting at index j
    int maxIndex = j;
    while (1) {
		int lC = leftChildIndex(j);
		// pArray[j] returns character at element index j, we need to compare key/priority
		if (lC < lSize && pArray[lC].key() > pArray[j].key()) {
			maxIndex = lC;
		}
		int mC = middleChildIndex(j);
		if(mC < lSize && pArray[mC].key() > pArray[maxIndex].key()){
			maxIndex = mC;
		}
		int rC = rightChildIndex(j);
		if (rC < lSize && pArray[rC].key() > pArray[maxIndex].key()) {
			maxIndex = rC;
		}
		if (maxIndex == j) { // reached last level in heap or key > keys of both childs (heap-order restored)
			break;
		}
		// swap key with child with higher key
		KVP tmp = pArray[j];
		pArray[j] = pArray[maxIndex];
		pArray[maxIndex] = tmp;
		j = maxIndex; // update fixDown index j
	}
}

void MaxHeap::PQSort() {
// prints all items in array in sorted order, destroys the heap in the process
	for (int i = parentIndex(lastIndex()); i >= 0; i--) {
		fixDown(i);
	}
	int n = size();
	for (int i = n-1; i >= 0; i--) {
		// swap current KVP with root KVP
		KVP tmp = pArray[i];
		pArray[i] = pArray[0];
        pArray[0] = tmp;
        lSize -= 1;
        fixDown(0);
	}
	for (int i = 0; i < n; i++){
		pArray[i].print();
	}
}

// g++ pq1.cpp -o pq1
// marmoset_submit cs240 PQ1 pq1.cpp

int main() {
	MaxHeap * pq = new MaxHeap();
// toggle the value below between 0 and 1 depending on which one you want to do
#if 0
	// hard-code a small test for heapsort
	pq->add(1,'a');
	pq->add(10,'f');
	pq->add(8,'c');
	pq->add(6,'d');
	pq->add(2,'v');
	pq->add(2,'c');
	pq->add(9,'i');
	pq->add(3,'b');
	pq->add(9,'w');
	pq->add(4,'x');
	pq->add(11,'m');
	pq->add(15,'j');
	pq->add(13,'p');
	pq->add(16,'q');
	pq->printHeap();
	for(int i = pq->parentIndex(pq->lastIndex()); i >= 0; i--){
		pq->fixDown(i);
	}
	cout << endl;
	pq->printHeap();
	cout << endl;
	pq->deleteMax();
	cout << endl;
	pq->printHeap();
	//pq->PQSort();
#else 
// the following is here to get you started on the reading-in interface
    string line;
    while (true) {
        getline(cin, line); // read in input per line
        char cmd = line[0];
        if (cmd == 'x') { // terminates the program
            break;
        }
		else if(cmd == 'p'){ // prints KVPs in the order they appear in array (need not be sorted/in heap-order)
			pq->printHeap();
		}
        else if (cmd == 'a') { // adds KVP with priority num and value char at end of array, not changing anything else
			istringstream iss = istringstream(line);
			int num;
			char c;
			iss >> cmd >> num >> c;  // no error control here
            pq->add(num,c);
		}
		else if(cmd == 'h'){ // heapify, restores the heap-order property
			for(int i = pq->parentIndex(pq->lastIndex()); i >= 0; i--){
				pq->fixDown(i);
			}
		}
		else if(cmd == 'd'){ // deletes item w/ highest priority and prints to output
			pq->deleteMax();
		}
		else if(cmd == 'i'){ // adds KVP (num, c) and restores the heap-order property
			istringstream iss = istringstream(line);
			int num;
			char c;
			iss >> cmd >> num >> c;
			pq->add(num, c);
			for(int i = pq->parentIndex(pq->lastIndex()); i >= 0; i--){
				pq->fixDown(i);
			}
		}
		else if(cmd == 'f'){
			pq->printMax();
		} else {
            cout << "Unknown command. Please try again." << endl;
        }
    }
#endif
	delete pq;
    return 0;
}
