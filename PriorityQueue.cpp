#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int ID;
    int key;

    Node() {}

    Node(int ID, int key) : ID(ID), key(key) {}

    int compareTo(const Node &node2) const
    {
        if (key < node2.key)
        {
            return -1;
        }
        else if (key > node2.key)
        {
            return 1;
        }
        return 0;
    }
};

class Heap
{
public:
    vector<Node> heap;
    int heapsize;
    vector<int> location;

    // Constructors for Heap
    Heap() : heapsize(0)
    {
        heap.resize(20); // Default size 20
        location.resize(20);
    }

    Heap(int n) : heapsize(0)
    {
        heap.resize(n);
        location.resize(n);
    }

    Heap(vector<Node> a) : heapsize(a.size())
    {
        heap = a;
        location.resize(a.size());
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int leftChild(int i)
    {
        return (2 * i) + 1;
    }

    int rightChild(int i)
    {
        return (2 * i) + 2;
    }

    void Max_heapify(int i)
    {
        int l = leftChild(i);
        int r = rightChild(i);
        int largest = i;

        if (l < heapsize && heap[l].compareTo(heap[largest]) > 0)
        {
            largest = l;
        }

        if (r < heapsize && heap[r].compareTo(heap[largest]) > 0)
        {
            largest = r;
        }

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            swap(location[heap[i].ID], location[heap[largest].ID]);
            Max_heapify(largest);
        }
    }

    void buildheap(vector<Node> arr)
    {
        heap = arr;
        heapsize = arr.size();

        for (int i = (heapsize / 2) - 1; i >= 0; i--)
        {
            Max_heapify(i);
        }
    }
};

class PriorityQueue : public Heap
{
public:
    PriorityQueue(int maxsize) : Heap(maxsize)
    {
        // Create a priority queue of size maxsize
    }

    void insert(Node newNode)
    {
        if (heapsize == heap.size())
        {
            // Resize the heap and location vectors if needed
            heap.resize(heapsize * 2);
            location.resize(heapsize * 2);
        }

        heap[heapsize] = newNode;
        location[newNode.ID] = heapsize;
        heapsize++;

        int i = heapsize - 1;
        while (i > 0 && heap[parent(i)].compareTo(heap[i]) < 0)
        {
            swap(heap[i], heap[parent(i)]);
            swap(location[heap[i].ID], location[heap[parent(i)].ID]);
            i = parent(i);
        }
    }

    Node peek()
    {
        if (heapsize > 0)
        {
            return heap[0];
        }
        throw runtime_error("Priority queue is empty.");
    }

    Node extract()
    {
        if (heapsize == 0)
        {
            throw runtime_error("Priority queue is empty.");
        }

        Node maxNode = heap[0];
        location[maxNode.ID] = -1;

        if (heapsize > 1)
        {
            heap[0] = heap[heapsize - 1];
            location[heap[0].ID] = 0;
            heapsize--;
            Max_heapify(0);
        }
        else
        {
            heapsize--;
        }

        return maxNode;
    }

    void changeKey(int i, int k)
    {
        if (i >= 0 && i < heapsize)
        {
            int oldKey = heap[i].key;
            heap[i].key = k;

            if (k > oldKey)
            {
                // Increase key
                while (i > 0 && heap[parent(i)].compareTo(heap[i]) < 0)
                {
                    swap(heap[i], heap[parent(i)]);
                    swap(location[heap[i].ID], location[heap[parent(i)].ID]);
                    i = parent(i);
                }
            }
            else if (k < oldKey)
            {
                // Decrease key
                Max_heapify(i);
            }
        }
        else
        {
            throw out_of_range("Invalid index.");
        }
    }
};

int main()
{
    PriorityQueue pq(7);
    pq.insert(Node(0, 3));
    pq.insert(Node(1, 14));
    pq.insert(Node(2, 7));
    pq.insert(Node(3, 9));
    pq.insert(Node(4, 99));
    pq.insert(Node(5, 2));
    pq.insert(Node(6, 46));

    cout << "Heap Array:" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << pq.heap[i].key << " ";
    }
    cout << "\n"
         << endl;

    cout << "location array: " << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << pq.location[i] << " ";
    }
    cout << "\n"
         << endl;
    ;
    cout << "Priority Queue extracted:" << endl;
    for (int i = 0; i < 7; i++)
    {
        Node maxNode = pq.extract();
        cout << maxNode.key << " ";
    }

    return 0;
}