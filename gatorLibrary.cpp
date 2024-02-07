// HeaderFiles & Libraries
#include <bits/stdc++.h>

// Namespace Declaration
using namespace std;

/*
Global declaration of colorFlips to keep track of the total color changes in the
Red-Black tree nodes during tree operations, such as insertion, deletion, and rotations
*/
int colorFlips = 0;

// Reservations Declaration
struct Reservations
{
    int resPriority;
    int resPatronID;
    int resTimeStamp;
};

// Node Declaration
struct Node
{
    int color;

    Node *left;
    Node *parent;
    Node *right;

    int BookId;
    string BookName;
    string AuthorName;
    int BorrowedBy;
    bool AvailabilityStatus;
    vector<Reservations> ReservationHeap;

    set<int> patronsReserved;
};

typedef Node *nodePointer;

// Red-Black Tree Declaration
class RedBlackTree
{
private:
    nodePointer root;
    nodePointer TNULL;

    // Node initialized to NULL
    void initializeNode(nodePointer n1, nodePointer parent)
    {
        n1->BookId = 0;
        n1->parent = parent;
        int BorrowedBy = 0;
        n1->left = nullptr;
        n1->right = nullptr;
        n1->color = 0;
    }

    // Returns greatest smaller value and smallest greater value
    pair<int, int> getGreatestAndSmallest(vector<int> &a, int n, int x)
    {
        int start = 0;
        int end = n - 1;
        int result = -1;
        pair<int, int> greatestAndSmallest;

        while (start <= end)
        {
            int mid = (start + end) / 2;
            if (a[mid] <= x)
            {
                result = a[mid];
                start = mid + 1;
            }
            else
                end = mid - 1;
        }

        greatestAndSmallest.first = result;
        start = 0, end = n - 1, result = -1;

        while (start <= end)
        {
            int mid = (start + end) / 2;
            if (a[mid] >= x)
            {
                result = a[mid];
                end = mid - 1;
            }
            else
                start = mid + 1;
        }

        greatestAndSmallest.second = result;
        return greatestAndSmallest;
    }

    // Iterate to search a node which matches with 'key'
    nodePointer searchTreeFind(nodePointer n1, int key)
    {
        if (n1 == TNULL || key == n1->BookId)
        {
            return n1;
        }

        if (key < n1->BookId)
        {
            return searchTreeFind(n1->left, key);
        }

        return searchTreeFind(n1->right, key);
    }

    // Exchanges sub-trees of Red-Black Tree
    void redBlackTreeTransplant(nodePointer p1, nodePointer p2)
    {
        if (p1->parent == nullptr)
        {
            root = p2;
        }

        else if (p1 == p1->parent->left)
        {
            p1->parent->left = p2;
        }

        else
        {
            p1->parent->right = p2;
        }

        p2->parent = p1->parent;
    }

    // Insertion Method
    void insertion(nodePointer key)
    {
        nodePointer p1;
        while (key->parent->color == 1)
        {
            if (key->parent == key->parent->parent->right)
            {
                p1 = key->parent->parent->left;

                if (p1 != NULL && p1->color == 1)
                {
                    colorFlips += key->color == 0 ? 0 : 1;
                    p1->color = 0;
                    colorFlips += key->parent->color == 0 ? 0 : 1;
                    key->parent->color = 0;
                    colorFlips += key->parent->parent->color == 1 ? 0 : 1;
                    key->parent->parent->color = 1;
                    key = key->parent->parent;
                }

                else
                {
                    if (key == key->parent->left)
                    {
                        key = key->parent;
                        rightRotate(key);
                    }

                    colorFlips += key->parent->color == 0 ? 0 : 1;
                    key->parent->color = 0;
                    colorFlips += key->parent->parent->color == 1 ? 0 : 1;
                    key->parent->parent->color = 1;
                    leftRotate(key->parent->parent);
                }
            }

            else
            {
                p1 = key->parent->parent->right;

                if (p1 != NULL && p1->color == 1)
                {
                    colorFlips += key->color == 0 ? 0 : 1;
                    p1->color = 0;
                    colorFlips += key->parent->color == 0 ? 0 : 1;
                    key->parent->color = 0;
                    colorFlips += key->parent->parent->color == 1 ? 0 : 1;
                    key->parent->parent->color = 1;
                    key = key->parent->parent;
                }

                else
                {
                    if (key == key->parent->right)
                    {
                        key = key->parent;
                        leftRotate(key);
                    }
                    colorFlips += key->parent->color == 0 ? 0 : 1;
                    key->parent->color = 0;
                    colorFlips += key->parent->parent->color == 1 ? 0 : 1;
                    key->parent->parent->color = 1;
                    rightRotate(key->parent->parent);
                }
            }

            if (key == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    // Deletion Method
    void deletion(nodePointer p1)
    {
        nodePointer p2;
        while (p1 != root && p1->color == 0)
        {
            if (p1 == p1->parent->left)
            {
                p2 = p1->parent->right;

                if (p2->color == 1)
                {
                    colorFlips += p2->color == 0 ? 0 : 1;
                    p2->color = 0;
                    colorFlips += p1->parent->color == 1 ? 0 : 1;
                    p1->parent->color = 1;
                    leftRotate(p1->parent);
                    p2 = p1->parent->right;
                }

                if (p2->left->color == 0 && p2->right->color == 0)
                {
                    colorFlips += p2->color == 1 ? 0 : 1;
                    p2->color = 1;
                    p1 = p1->parent;
                }

                else
                {
                    if (p2->right->color == 0)
                    {
                        colorFlips += p2->left->color == 0 ? 0 : 1;
                        p2->left->color = 0;
                        colorFlips += p2->color == 1 ? 0 : 1;
                        p2->color = 1;
                        rightRotate(p2);
                        p2 = p1->parent->right;
                    }

                    p2->color = p1->parent->color;
                    colorFlips += p1->parent->color == 0 ? 0 : 1;
                    p1->parent->color = 0;
                    colorFlips += p2->right->color == 0 ? 0 : 1;
                    p2->right->color = 0;
                    leftRotate(p1->parent);
                    p1 = root;
                }
            }

            else
            {
                p2 = p1->parent->left;

                if (p2->color == 1)
                {
                    colorFlips += p2->color == 0 ? 0 : 1;
                    p2->color = 0;
                    colorFlips += p1->parent->color == 1 ? 0 : 1;
                    p1->parent->color = 1;
                    rightRotate(p1->parent);
                    p2 = p1->parent->left;
                }

                if (p2->right->color == 0)
                {
                    colorFlips += p2->color == 0 ? 0 : 1;
                    p2->color = 1;
                    p1 = p1->parent;
                }

                else
                {
                    if (p2->left->color == 0)
                    {
                        colorFlips += p2->right->color == 0 ? 0 : 1;
                        p2->right->color = 0;
                        colorFlips += p2->color == 1 ? 0 : 1;
                        p2->color = 1;
                        leftRotate(p2);
                        p2 = p1->parent->left;
                    }

                    colorFlips += p2->color == p1->parent->color ? 0 : 1;
                    p2->color = p1->parent->color;
                    colorFlips += p1->parent->color == 0 ? 0 : 1;
                    p1->parent->color = 0;
                    colorFlips += p2->left->color == 0 ? 0 : 1;
                    p2->left->color = 0;
                    rightRotate(p1->parent);
                    p1 = root;
                }
            }
        }
        p1->color = 0;
    }

    // Fixes min-heap after insertion of new reservation
    void fixMinHeap(vector<Reservations> &resHeap)
    {
        for (int i = resHeap.size() - 1; i > 0; i = (i - 1) / 2)
        {
            if (resHeap[i].resPriority < resHeap[(i - 1) / 2].resPriority)
            {
                Reservations temp = resHeap[i];
                resHeap[i] = resHeap[(i - 1) / 2];
                resHeap[(i - 1) / 2] = temp;
            }

            else if (resHeap[i].resPriority == resHeap[(i - 1) / 2].resPriority)
            {
                if (resHeap[i].resTimeStamp < resHeap[(i - 1) / 2].resTimeStamp)
                {
                    Reservations temp = resHeap[i];
                    resHeap[i] = resHeap[(i - 1) / 2];
                    resHeap[(i - 1) / 2] = temp;
                }
            }
        }
    }

    // Deletion of topmost node form min-heap
    void deleteMinimum(vector<Reservations> &resHeap)
    {
        int i = 0;

        if (resHeap.size() == 1)
        {
            resHeap.pop_back();
            return;
        }

        resHeap[0] = resHeap[resHeap.size() - 1];
        resHeap.pop_back();

        while ((2 * i + 1) < resHeap.size())
        {
            int smallerChild = 2 * i + 1;

            if (((2 * i + 2) < resHeap.size()) && (resHeap[2 * i + 2].resPriority < resHeap[smallerChild].resPriority))
            {
                smallerChild = 2 * i + 2;
            }

            if (resHeap[i].resPriority <= resHeap[smallerChild].resPriority)
            {
                break;
            }

            swap(resHeap[i], resHeap[smallerChild]);
            i = smallerChild;
        }
    }

    // Find the node and deletes it from the tree
    void deleteNodeFind(nodePointer n1, int key)
    {
        nodePointer p1;
        nodePointer p2;
        nodePointer p3 = TNULL;

        while (n1 != TNULL)
        {
            if (n1->BookId == key)
            {
                cout << "\nBook " << n1->BookId << " is no longer available.";
                if (n1->ReservationHeap.size() != 0)
                {
                    cout << "\nReservations made by patrons: ";
                    for (int i = 0; i < n1->ReservationHeap.size(); i++)
                    {
                        cout << n1->ReservationHeap[i].resPatronID;
                        if (i < n1->ReservationHeap.size() - 1)
                            cout << ",";
                        cout << " ";
                    }
                    cout << " have been cancelled!";
                }

                p2 = n1;
            }

            if (n1->BookId <= key)
            {
                n1 = n1->right;
            }

            else
            {
                n1 = n1->left;
            }
        }

        if (p3 == TNULL)
        {
            cout << "\nKey is not found in the tree";
            return;
        }

        p2 = p3;
        int p2OriginalColor = p2->color;

        if (p3->left == TNULL)
        {
            p1 = p3->right;
            redBlackTreeTransplant(p3, p3->right);
        }

        else if (p3->right == TNULL)
        {
            p1 = p3->left;
            redBlackTreeTransplant(p3, p3->left);
        }
        else
        {
            p2 = maximum(p3->left);
            p2OriginalColor = p2->color;
            p1 = p2->left;

            if (p2->parent == p3)
            {
                p1->parent = p2;
            }

            else
            {
                redBlackTreeTransplant(p2, p2->left);
                p2->right = p3->left;
                p2->left->parent = p2;
            }

            redBlackTreeTransplant(p3, p2);
            p2->right = p3->right;
            p2->right->parent = p2;
            p2->color = p3->color;
        }

        delete p3;

        if (p2OriginalColor == 0)
        {
            deletion(p1);
        }
    }

    // Inorder Traversal of Tree
    void inorderTraversal(nodePointer n1, vector<int> &inord)
    {
        if (n1 != TNULL)
        {
            inorderTraversal(n1->left, inord);
            inord.push_back(n1->BookId);
            inorderTraversal(n1->right, inord);
        }
    }

    // Iterate to print Books
    void printBooksFind(nodePointer n1, int start, int end)
    {
        if (n1 != TNULL)
        {
            printBooksFind(n1->left, start, end);

            if (n1->BookId >= start && n1->BookId <= end)
            {
                printNode(n1);
            }

            printBooksFind(n1->right, start, end);
        }
    }

    // Prints the node values
    void printNode(nodePointer n1)
    {
        if (n1 == TNULL)
        {
            return;
        }
        cout << "\nBook ID:  " << n1->BookId;
        cout << "\nTitle: " << n1->BookName;
        cout << "\nAvailiability: " << n1->AuthorName;
        cout << "\nBorrowed by: " << (n1->BorrowedBy == 0 ? 0 : n1->BorrowedBy);
        cout << "\nReserved by: [";

        for (int i = 0; i < n1->ReservationHeap.size(); i++)
        {
            cout << n1->ReservationHeap[i].resPatronID;

            if (i < n1->ReservationHeap.size() - 1)
                cout << ",";

            cout << " ";
        }
        cout << "]";
    }

    // Prints Red-Black Tree
    void printTreeFind(nodePointer root, string indent, bool last)
    {
        if (root != TNULL)
        {
            cout << indent;

            if (last)
            {
                cout << "R----";
                indent += "   ";
            }

            else
            {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->BookId << "(" << sColor << ")";

            printTreeFind(root->left, indent, false);
            printTreeFind(root->right, indent, true);
        }
    }

public:
    // Constructor declaration
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    // Search for BookID in Tree
    void searchClosestBookID(int key);

    // Inorder Traversal
    vector<int> inOrder()
    {
        vector<int> inorder;
        inorderTraversal(this->root, inorder);
        return inorder;
    }

    // Fetches the root node of the Red-Black Tree
    nodePointer getRoot()
    {
        return this->root;
    }

    // Deletes the node passed in the argument if it exists in the tree
    void deleteNode(int BookId)
    {
        deleteNodeFind(this->root, BookId);
    }

    // Prints the Red-Black Tree
    void printTree()
    {
        if (root)
        {
            printTreeFind(this->root, "", true);
        }
    }

    // Search and matches for a node using 'Key'
    nodePointer searchTree(int key)
    {
        return searchTreeFind(this->root, key);
    }

    // Finds the leftmost node (min)
    nodePointer minimum(nodePointer n1)
    {
        while (n1->left != TNULL)
        {
            n1 = n1->left;
        }
        return n1;
    }

    // Finds the rightmost node (max)
    nodePointer maximum(nodePointer n1)
    {
        while (n1->right != TNULL)
        {
            n1 = n1->right;
        }
        return n1;
    }

    // Returns the successor of the node
    nodePointer successor(nodePointer p1)
    {
        if (p1->right != TNULL)
        {
            return minimum(p1->right);
        }

        nodePointer p2 = p1->parent;

        while (p2 != TNULL && p1 == p2->right)
        {
            p1 = p2;
            p2 = p2->parent;
        }
        return p2;
    }

    // Returns the predecessor of the node
    nodePointer predecessor(nodePointer p1)
    {
        if (p1->left != TNULL)
        {
            return maximum(p1->left);
        }

        nodePointer p2 = p1->parent;

        while (p2 != TNULL && p1 == p2->left)
        {
            p1 = p2;
            p2 = p2->parent;
        }

        return p2;
    }

    // Method to perform left rotate
    void leftRotate(nodePointer p1)
    {
        nodePointer p2 = p1->right;
        p1->right = p2->left;

        if (p2->left != TNULL)
        {
            p2->left->parent = p1;
        }

        p2->parent = p1->parent;

        if (p1->parent == nullptr)
        {
            this->root = p2;
        }

        else if (p1 == p1->parent->left)
        {
            p1->parent->left = p2;
        }

        else
        {
            p1->parent->right = p2;
        }

        p2->left = p1;
        p1->parent = p2;
    }

    // Method to perform right-rotate
    void rightRotate(nodePointer p1)
    {
        nodePointer p2 = p1->left;
        p1->left = p2->right;

        if (p2->right != TNULL)
        {
            p2->right->parent = p1;
        }

        p2->parent = p1->parent;

        if (p1->parent == nullptr)
        {
            this->root = p2;
        }

        else if (p1 == p1->parent->right)
        {
            p1->parent->right = p2;
        }

        else
        {
            p1->parent->left = p2;
        }

        p2->right = p1;
        p1->parent = p2;
    }

    // Method to insert a new book
    void insertBook(int key, string book, string AuthorName, string AvailabilityStatus)
    {
        nodePointer n1 = new Node;
        n1->parent = nullptr;
        n1->BookId = key;
        n1->AuthorName = AuthorName;
        n1->AvailabilityStatus = true;
        n1->BorrowedBy = 0;
        n1->BookName = book;
        n1->left = TNULL;
        n1->right = TNULL;
        n1->color = 1;

        nodePointer p1 = this->root;
        nodePointer p2 = nullptr;

        while (p1 != TNULL)
        {
            p2 = p1;

            if (n1->BookId == p1->BookId)
            {
                cout << "\nBook already exists in our BookIdbase!";
                return;
            }

            if (n1->BookId < p1->BookId)
            {
                p1 = p1->left;
            }

            else
            {
                p1 = p1->right;
            }
        }

        n1->parent = p2;

        if (p2 == nullptr)
        {
            root = n1;
        }

        else if (n1->BookId < p2->BookId)
        {
            p2->left = n1;
        }

        else
        {
            p2->right = n1;
        }

        if (n1->parent == nullptr)
        {
            n1->color = 0;
            return;
        }

        if (n1->parent->parent == nullptr)
        {
            return;
        }

        insertion(n1);
    }

    // Method to borrow a book from the library
    void borrowBook(int patronID, int bookID, int resPriority)
    {
        nodePointer n1 = searchTree(bookID);

        if (n1 == TNULL)
        {
            cout << "\nBook " << bookID << " is not found in library.";
            return;
        }

        if (n1->AvailabilityStatus == true)
        {
            n1->AvailabilityStatus = false;
            n1->BorrowedBy = patronID;
            cout << "\nBook " << bookID << " borrowed by patron " << patronID;
            return;
        }

        else if (n1->AvailabilityStatus == false)
        {
            if (n1->BorrowedBy == patronID)
            {
                cout << "\nBook has already been borrowed by you. Kindly return before due date!";
                return;
            }

            else
            {
                if (n1->patronsReserved.find(patronID) != n1->patronsReserved.end())
                {
                    cout << "\nBook has already been reserved by you. Kindly check out!";
                    return;
                }

                else
                {
                    n1->patronsReserved.insert(patronID);
                    Reservations res;
                    res.resPatronID = patronID;
                    res.resPriority = resPriority;
                    res.resTimeStamp = time(0);
                    n1->ReservationHeap.push_back(res);
                    fixMinHeap(n1->ReservationHeap);
                    cout << "\nBook " << bookID << " reserved by patron " << patronID;
                }
            }
        }
    }

    // Method used to keep track of the books returned
    void returnBook(int patronID, int bookID)
    {
        nodePointer n1 = searchTree(bookID);

        if (n1->BorrowedBy == patronID)
        {
            cout << n1->BookId << "\nBook " << bookID << " returned by patron " << patronID;

            if (n1->ReservationHeap.size() != 0)
            {
                cout << n1->BookId << "\nBook " << bookID << " allotted to patron " << n1->ReservationHeap[0].resPatronID;
                n1->BorrowedBy == n1->ReservationHeap[0].resPatronID;
                deleteMinimum(n1->ReservationHeap);
            }

            else
            {
                n1->BorrowedBy = 0;
                n1->AvailabilityStatus = true;
            }
        }

        else
        {
            cout << "\nBook is not borrowed by you";
        }
    }

    // Prints all the books between the given range (start to end)
    void printBooks(int start, int end)
    {
        printBooksFind(this->root, start, end);
    }
};

// Scope Resolution Operator used on searchClosestBookID
void RedBlackTree::searchClosestBookID(int key)
{
    nodePointer n1 = this->root;
    vector<int> inord = inOrder();
    pair<int, int> result = getGreatestAndSmallest(inord, inord.size(), key);

    if (result.first == -1)
    {
        nodePointer n1 = searchTree(result.second);
        printNode(n1);
    }

    else if (result.second == -1)
    {
        nodePointer n1 = searchTree(result.first);
        printNode(n1);
    }

    else
    {
        if (key - result.first < result.second - key)
        {
            nodePointer n1 = searchTree(result.first);
            printNode(n1);
        }
        else if (key - result.first > result.second - key)
        {
            nodePointer n1 = searchTree(result.second);
            printNode(n1);
        }
        else
        {
            nodePointer n1 = searchTree(result.first);
            nodePointer n2 = searchTree(result.second);
            printNode(n1);
            printNode(n2);
        }
    }
}

// Method to print books
void printBook(RedBlackTree bst, int key)
{
    nodePointer n1 = bst.searchTree(key);

    if (n1 == NULL)
    {
        cout << "\nBook " << key << " not found in the library";
        return;
    }

    cout << "\nBook ID:  " << n1->BookId;
    cout << "\nTitle: " << n1->BookName;
    cout << "\nAvailiability: " << n1->AuthorName;
    cout << "\nBorrowed by: " << (n1->BorrowedBy == 0 ? 0 : n1->BorrowedBy);
    cout << "\nReserved by: [";
    for (int i = 0; i < n1->ReservationHeap.size(); i++)
    {
        cout << n1->ReservationHeap[i].resPatronID;

        if (i < n1->ReservationHeap.size() - 1)
        {
            cout << ",";
        }

        cout << " ";
    }
    cout << "]";
}

// Main method of the project
int main(int argc, char *argv[])
{
    RedBlackTree bst;

    ifstream file(argv[1]);
    string line;
    string command;

    string fname = string(argv[1]).substr(0, string(argv[1]).length() - 4);
    string outputFileName = fname + "_output_file.txt";

    ofstream outputFile(outputFileName);
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());

    while (!file.eof())
    {
        getline(file, line);
        istringstream iss(line);
        getline(iss, command, '(');

        if (command == "InsertBook")
        {
            int key;
            string titleOfBook, AuthorName, availabilityOfBook;
            iss >> key;
            getline(iss, titleOfBook, ',');
            getline(iss, titleOfBook, ',');
            getline(iss, AuthorName, ',');
            getline(iss, availabilityOfBook, ')');
            bst.insertBook(key, titleOfBook, AuthorName, availabilityOfBook);
        }

        else if (command == "SearchClosest")
        {
            int key;
            iss >> key;
            bst.searchClosestBookID(key);
        }

        else if (command == "FindClosestBook")
        {
            int key;
            iss >> key;
            bst.searchClosestBookID(key);
        }

        else if (command == "BorrowBook")
        {
            int patronID, bookID, resPriority;
            string args;

            getline(iss, args);

            for (char &c : args)
            {
                if (c == '(' || c == ')' || c == ',')
                {
                    c = ' ';
                }
            }

            istringstream argsStream(args);
            argsStream >> patronID >> bookID >> resPriority;
            bst.borrowBook(patronID, bookID, resPriority);
        }

        else if (command == "ReturnBook")
        {
            string args;
            getline(iss, args);

            for (char &c : args)
            {
                if (c == ',' || c == '(' || c == ')')
                {
                    c = ' ';
                }
            }

            istringstream argsStream(args);
            int bookID, patronID;
            argsStream >> bookID >> patronID;
            bst.returnBook(bookID, patronID);
        }

        else if (command == "PrintBook")
        {
            int key;
            iss >> key;
            printBook(bst, key);
        }

        else if (command == "PrintBooks")
        {
            string args;
            getline(iss, args);

            for (char &c : args)
            {
                if (c == '(' || c == ')' || c == ',')
                {
                    c = ' ';
                }
            }

            std::istringstream argsStream(args);
            int start, end;
            argsStream >> start >> end;
            bst.printBooks(start, end);
        }

        else if (command == "DeleteBook")
        {
            int key;
            iss >> key;
            bst.deleteNode(key);
        }

        else if (command == "ColorFlipCount")
        {
            cout << "\nColor flip count: " << colorFlips;
        }

        else if (command == "Quit")
        {
            cout << "\nProgram Terminated!!";
            return 0;
        }

        else
        {
            cout << "\nCommand Given is Invalid. \nGiven Command: " << command;
        }
    }
    return 0;
}
