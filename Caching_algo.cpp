#include <bits/stdc++.h>
using namespace std;

#define int unsigned int

class Node{
    
    public:
    int v;
    Node* next;
    Node* prev;
    Node(int w){
        v =w;
        next = nullptr;
        prev = nullptr;
    }
};






class Linked_List{

    public:
    int cap;
    int sz;
    Node* head = nullptr;
    Node* lt = nullptr;
    unordered_map<int,bool> vis;
    unordered_map<int,pair<Node*,Node*>> cnt;
    Linked_List(int a ){
        cap =a;
        sz =0;
    }
    void fifo_add(int p){
        vis[p]=1;
        if(sz==0){
            sz++;
            head = new Node(p);
            lt = head;
        }
        else if(sz<cap){
            sz++;
            Node* nd = new Node(p);
            lt->next = nd;
            lt = lt->next;
        }
        else{
             if(cap==1){
                vis[head->v]=0;
                delete(head);
                head = new Node(p);
                lt = head;
                return;
              }
            Node* w = head->next;
            vis[head->v]=0;
            delete(head);
            head = w;
            Node* nd = new Node(p);
            lt->next =nd;
            lt = lt->next;
        }
    }
    void Lifo_add(int p){
        vis[p]=1;
        if(sz==0){
            sz++;
            head = new Node(p);
            lt = head;
        }
        else if(sz<cap){
            sz++;
            Node* nd = new Node(p);
            lt->next = nd;
            Node* u = lt;
            lt = lt->next;
            lt->prev =u;
        }
        else{
              if(cap==1){
                 vis[head->v]=0;
                 delete(head);
                head = new Node(p);
                lt = head;
                return;
              }
              vis[lt->v] =0;
              lt = lt->prev;
              delete(lt->next);
              Node* u = lt;
              lt->next = new Node(p);
              lt = lt->next;
              lt->prev = u;
        }
    }

    
};
// LRU Cache Implementation
class LRUCache {
public:
    int capacity;
    int hit;
    unordered_map<int, Node*> cache; // Unordered map to store page to node mapping
    Node* head; // Head of the doubly linked list (most recently used)
    Node* tail; // Tail of the doubly linked list (least recently used)

public:
    LRUCache(int size) : capacity(size), head(nullptr), tail(nullptr), hit(0) {}

    // Add the node to the front (most recently used)
    void addToFront(Node* node) {
        node->next = head;
        node->prev = nullptr;
        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
        if (tail == nullptr) { // If the list was empty, tail should also point to the new node
            tail = head;
        }
    }

    // Remove a node from the doubly linked list
    void removeNode(Node* node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next; // If node is the head
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev; // If node is the tail
        }
    }
    void removeNode2(Node* node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next; // If node is the head
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev; // If node is the tail
        }
        delete(node);
    }


    // Access the page
    void accessPage(int pageNumber) {
        if (cache.find(pageNumber) != cache.end()) {
            // If the page is in the cache (TLB), move it to the front
            Node* node = cache[pageNumber];
            removeNode(node);
            addToFront(node);
            hit++;
            // cout << "Page " << pageNumber << " accessed. Moved to front.\n";
        } else {
            // If page is not in the cache
            Node* newNode = new Node(pageNumber);
            if (cache.size() == capacity) {
                // If TLB is full, remove the least recently used (tail)
                cache.erase(tail->v); // Remove from map
                removeNode2(tail); // Remove from list
                // delete tail; // Free the memory
                // this->printTLB();
            }
            // Add new page to the front
            addToFront(newNode);
            cache[pageNumber] = newNode; // Add to map
            // cout << "Page " << pageNumber << " added to TLB.\n";
        }
    }

    // Print the current state of the TLB
    void printTLB() {
        Node* current = head;
        cout << "Current TLB: ";
        while (current != nullptr) {
            cout << current->v << " ";
            current = current->next;
        }
        cout << "\n";
    }
};


class queue_{
      
      public:
      Node* hd;
      Node* ltx;
      queue_(){
        hd =nullptr;
        ltx = nullptr;
      }
      void addq(int p){
        Node* we = new Node(p);
        if(hd==nullptr){
            hd =we;
            ltx = we;
        }
        else{
            ltx->next = we;
            ltx = ltx->next;
        }
      }

      void rem(){
        if(hd==nullptr) return;

        Node* w = hd->next;
        delete(hd);
        hd = w;
      }
      int top_(){
        if(hd==nullptr) return -1;
        return hd->v;
      }
      bool isempty(){
        return hd==nullptr;
      }
};


class MaxHeap {
public:
    int** heap; // Dynamically allocated array to store (next_access_time, page_number)
    int size;
    int capacity; // Capacity of the heap

public:
    // Constructor with dynamic heap allocation
    MaxHeap(int capacity) : size(0), capacity(capacity) {
        heap = new int*[capacity];  // Allocate memory for the heap
        for (int i = 0; i < capacity; ++i) {
            heap[i] = new int[2]; // Each heap element is a pair (next_access_time, page_number)
        }
    }

    // Destructor to free allocated memory
    ~MaxHeap() {
        for (int i = 0; i < capacity; ++i) {
            delete[] heap[i];
        }
        delete[] heap;
    }

    // Insert a new (next_access_time, page_number) pair into the heap
    void insert(int next_access_time, int page_number) {
        if (size == capacity) {
            // cout << "Heap is full. Cannot insert further elements.\n";
            return;
        }
        heap[size][0] = next_access_time;
        heap[size][1] = page_number;
        heapup(size);
        size++;
    }

    // Remove and return the page with the largest next_access_time
    int extractMax() {
    if (size == 0) return -1;  // Heap is empty

    int page = heap[0][1];  // The page number with the maximum next_access_time

    size--;  // Decrease heap size
    if (size > 0) {
        // Move the last element to the root
        heap[0][0] = heap[size][0];  
        heap[0][1] = heap[size][1];
        
        // Delete the last element (since it's moved to the root)
        heap[size][0] = 0;  // Optionally reset the element (not strictly necessary)
        heap[size][1] = 0;
        
        // Restore heap property
        heapdown(0);
    }
    return page;
}

    // heap up to maintain the heap property
    void heapup(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent][0] < heap[idx][0]) {
                swap(heap[parent], heap[idx]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    // heap down to maintain the heap property
    void heapdown(int idx) {
        while (2 * idx + 1 < size) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int largest = idx;

            if (left < size && heap[left][0] > heap[largest][0]) {
                largest = left;
            }
            if (right < size && heap[right][0] > heap[largest][0]) {
                largest = right;
            }
            if (largest != idx) {
                swap(heap[idx], heap[largest]);
                idx = largest;
            } else {
                break;
            }
        }
    }

    // Helper function to swap two heap elements
    void swap(int a[2], int b[2]) {
        int temp0 = a[0], temp1 = a[1];
        a[0] = b[0], a[1] = b[1];
        b[0] = temp0, b[1] = temp1;
    }
};






class Optimal_TLB{

   public:
   unordered_map<int,queue_> ind;
   MaxHeap* heap;
   int capac;
   unordered_map<int,bool> tlb;
   int hit;
   Optimal_TLB(int size, int heapcap){
    heap = new MaxHeap(heapcap);
    capac = size;
    hit =0;
   }




   void prepro(int* address , int n){
    for(int i =0;i<n;i++){
        ind[address[i]].addq(i);
    }
   }

   void access_page(int p){

    if(tlb.find(p)!=tlb.end()){
        hit++;
    }
    else{
        if(tlb.size()==capac){
            int pge_evict = heap->extractMax();
            // cout<<tlb.size()<<endl;
            tlb.erase(pge_evict);
            // cout<<pge_evict<<" Bye_Bye"<<endl;
        }
        tlb[p]=1;
    }
    ind[p].rem();
    int nxt_ind = ind[p].isempty() ? INT_MAX :ind[p].top_();
    heap->insert(nxt_ind,p);
   }






};



void hits(int * address , int c , int K){

  int fifo_hit =0;
  int lifo_hit =0;

  Linked_List  fifo(K);
  Linked_List lifo(K);
  LRUCache  lru(K);
  Optimal_TLB opt(K,c);
  opt.prepro(address,c);
  for(int i =0;i<c;i++){
      int y = address[i];
      if(fifo.vis[y]) fifo_hit++;
      else{
        fifo.fifo_add(y);
      }  
      if(lifo.vis[y]) lifo_hit++;
      else{
        lifo.Lifo_add(y);
      }
      lru.accessPage(y);
      opt.access_page(y);
    //   lru.printTLB();
  }

  cout<<fifo_hit<<" "<<lifo_hit<<" "<<lru.hit<<" "<<opt.hit<<endl;








}









signed main() {

  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin>>t;

  

    // addresses[0]=7;
    //  addresses[1]=0;
    //   addresses[2]=1;
    //    addresses[3]=2;
    //    addresses[4]=0;
    //    addresses[5]=3;
    //    addresses[6]=0;
    //    addresses[7]=4;
    //    addresses[8]=2;
    //    addresses[9]=3;
    //    addresses[10] = 0;
    //     addresses[11]=3;
    //      addresses[12]=2;
  while(t--){
    int S;
    int P;
    int K;
    int N;
    cin>>S>>P>>K>>N;
    int addresses[N]; // Array to store memory addresses

//  7 0 1 2 0 3 0 4 2 3 0 3 2

    for (int i = 0; i < N; ++i) {
            int u;
            cin>>hex>>u;
            int r = 10+log2(P);
            u = u>>r;
            addresses[i] =u; // Reading the memory addresses in hex format
            // cout<<u<<" check"<<endl;
    }
            cin>>dec;
    hits(addresses,N,K);
    // Linked_List lif(1);
    // LRUCache lru(4);
    // lru.accessPage(2);
    // lru.printTLB();
    // lru.accessPage(1);
    // lru.printTLB();
    // lru.accessPage(1);
    // lru.printTLB();
    // lru.accessPage(3);
    // lru.printTLB();
    // lru.accessPage(2);
    // lru.printTLB();
    // lru.accessPage(13);
    // lru.printTLB();
    // lru.accessPage(11);
    // lru.printTLB();  
    // lru.accessPage(4);
    // lru.printTLB();
    // lru.accessPage(3);
    // lru.printTLB();
    // lru.accessPage(1);
    // lru.printTLB();




    // lif.Lifo_add(1);
    // lif.Lifo_add(2);
    // lif.Lifo_add(3);
    // lif.Lifo_add(4);
    // lif.Lifo_add(5);
    // lif.Lifo_add(5);
    // cout<<lif.head->v<<endl;

    // hits(addresses,n,3);


//     hits(addresses,N);
  }


}
// #include <fstream>
// #include <chrono>
// #include <iomanip>

// signed main() {
//     ios_base::sync_with_stdio(0);
//     cin.tie(nullptr);
//     cout.tie(nullptr);

//     ifstream inFile("input.txt");
//     if (!inFile.is_open()) {
//         cerr << "Error opening input file" << endl;
//         return 1;
//     }

//     int t;
//     inFile >> t;

//     while (t--) {
//         int S, P, K, N;
//         inFile >> S >> P >> K >> N;
//         vector<int> addresses(N);

//         for (int i = 0; i < N; ++i) {
//             int u;
//             inFile >> hex >> u;
//             int r = 10 + log2(P);
//             u = u >> r;
//             addresses[i] = u;
//         }

//         auto start = chrono::high_resolution_clock::now();
//         hits(addresses.data(), N, K);
//         auto end = chrono::high_resolution_clock::now();

//         chrono::duration<double, milli> duration = end - start;
//         cout << "Time taken: " << fixed << setprecision(2) << duration.count() << " ms" << endl;
//     }

//     inFile.close();

//     return 0;
// }








