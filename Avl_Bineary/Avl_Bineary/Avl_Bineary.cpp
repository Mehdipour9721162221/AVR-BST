/*All Dveleoped By : AliMehdipour ==> Contact me : alimehdipourka@outlook.com
  I will publish this code under MIT LICENSE.
*/

#include <iostream>

#include <cmath>


//Utilities
void Worker(void);
void BST_Worker(void);
void AVL_Worker(void);
void AVL_VS_BST_Worker(void);
//


//Class Implementation
class Exception;
class GPrint;
template<class T>
class BT_Node;
template<class T>
class BS_Tree;
template<class T>
class AVL;
template <class T>
class Iterator;
//END

class Exception {
public:
    Exception(int error_type, std::string message) {
        this->error_number = error_type;
        this->error_message = message;
    }
    bool operator == (const Exception& b) {
        bool are_equal = false;
        if (this->error_number == b.error_number)
            are_equal = true;
        return are_equal;
    }

    std::string get_Message() {
        return this->error_message;
    }

    int get_error_type() {
        return this->error_number;
    }

private:
    int error_number = 0;
    std::string error_message = "";
};

class  GPrint
{
public:
    GPrint* before;
    std::string Container;

    GPrint(GPrint* prev, std::string str)
    {
        this->before = prev;
        this->Container = str;
    }

    void GPrinter(GPrint* new_print)
    {
        if (new_print == nullptr)
            return;

        GPrinter(new_print->before);
        std::cout << new_print->Container;
    }
};

template <class T>
class Iterator {
public:
    Iterator(void) {

    }

    Iterator(BT_Node<T>* root) {
        this->Current = root;
    }

    bool Has_Left_Child(void) {
        bool has_left = false;
        if (Current->Left_child != nullptr)
            has_left = true;
        return has_left;
    }
    bool Has_Right_Child(void) {
        bool has_right = false;
        if (Current->Right_child != nullptr)
            has_right = true;
        return has_right;
    }
    bool is_not_Root(void) {
        bool is_root = false;
        if (Current->Father == nullptr)
            is_root = true;
        return is_root;
    }

    //Return Current Value
    T& get_current_data(void) {
        if (Current != nullptr)
            return Current->data;
    }

    //Left_Node
    void go_left(void) {
        if (Has_Left_Child)
            Current = Current->Left_child;
    }
    //Right_Node
    void go_right(void) {
        if (Has_Right_Child())
            Current = Current->Left_child;
    }
    //Father_Node
    void go_back(void) {
        if (is_not_Root()) {
            Current = Current->Father;
        }
    }

    //Current Node
    BT_Node<T>& get_current(void) {
        if (Current != nullptr)
            return *Current;
    }

    //Goes to Right Node
    Iterator& operator ++(void) {
        if (Current->Right_child != nullptr)
            Current = Current->Right_child;
        return *Current;
    }

    Iterator& operator ++(int dummy) {
        BT_Node<T>* tmp = Current;
        if (Current->Right_child != nullptr)
            Current = Current->Right_child;
        return *tmp;
    }

    //Goes to Left Node
    Iterator& operator --() {
        if (Current->Left_Child != nullptr)
            Current = Current->Left_Child;
        return *Current;
    }

    Iterator& operator --(int dummy) {
        BT_Node<T>* tmp = Current;
        if (Current->Left_Child != nullptr)
            Current = Current->Left_Child;
        return *tmp;
    }

    //Check wether 2 Iterators are same or not
    bool operator == (const Iterator& b) {
        bool is_equal = false;
        if (b.Current == this->Current)
            is_equal = true;
        return is_equal;
    }

    //Assign operator
    Iterator& operator =(const Iterator& b) {
        this->Current = b.Current;
        return *this;
    }

    //Begin From Start of a Container
    Iterator begin(const BS_Tree<T>& container) {

        return Iterator(container.Root);
    }

    //Reset to the ROOT
    void Reset(const BS_Tree<T>& container) {
        this->Current = container->Root;
    }

    //go to Most Left Leaf
    Iterator Left_End(const BS_Tree<T>& container) {
        BT_Node<T>* tmp = container->Root;
        if (tmp != nullptr) {
            while (tmp->Left_child != nullptr) {
                tmp = tmp->Left_child;
            }
        }
        return tmp;

    }

    //go to Most Right Leaf
    Iterator Right_End(const BS_Tree<T>& container) {
        BT_Node<T>* tmp = container->Root;
        if (tmp != nullptr) {
            while (tmp->Rigt_child != nullptr) {
                tmp = tmp->Rigt_child;
            }
        }
        return tmp;
    }


private:
    BT_Node<T>* Current = nullptr;

};

template <class T>
class BT_Node {
public:
    BT_Node<T>* Right_child = nullptr;
    BT_Node<T>* Left_child = nullptr;
    BT_Node<T>* Father = nullptr;
    int B_Factor = 0;
    T data = { 0 };

    BT_Node(void) {}

    BT_Node(const T& mdata) {
        this->data = mdata;
    }

    //Copy Constructor

    BT_Node(const BT_Node<T>& b) {
        this->data = b.data;
        this->Father = b.Father;
        this->B_Factor = b.B_Factor;
        this->Left_child = b.Left_child;
        this->Right_child = b.Right_child;
        this->balance_factor = b.balance_factor;
    }

    BT_Node<T>& operator =(const BT_Node<T>& b) {
        this->data = b.data;
        this->Father = b.Father;
        this->B_Factor = b.B_Factor;
        this->Left_child = b.Left_child;
        this->Right_child = b.Right_child;
        return *this;
    }

    friend  std::ostream& operator <<(std::ostream& op, const BT_Node<T>& a) {
        op << a.data;
        //op << a.Left_child << "  " << a.data << "  " << a.Right_child;
        return op;
    }

    friend std::istream& operator >> (const std::istream& inp, BT_Node<T>& a) {
        std::cout << "Please Enter Data ";
        inp >> a.data;
        return inp;
    }

    bool operator == (const BT_Node<T>& b) {
        bool Duplicate = false;
        if (this->data == b.data) {
            Duplicate = true;
        }
        return Duplicate;
    }

};

template <class T>
class BS_Tree {
public:
    BT_Node<T>* Root = nullptr;
    Iterator<T> iterator;

    BS_Tree() {
        this->Root = new BT_Node<T>;
        iterator.begin(*this);
    }
    BS_Tree(BT_Node<T>* arr, int n) {
        if (arr != nullptr)
        {
            this->Root = new BT_Node<T>;
            iterator.begin(this);
            this->Root->data = arr[0].data;
            Array_to_BST(arr, n - 1);
        }
        else
            return;
    }
    BS_Tree(const BT_Node<T>* root) {

        this->Root = root;
        iterator.begin(this);

    }
    BS_Tree(const T& data) {
        Root = new BT_Node<T>;
        iterator.begin(*this);
        Root->data = data;

    }
    BS_Tree(const BS_Tree& b) {

        if (&b != nullptr) {
            BST_to_BST(b.Root);
            iterator.begin(this);

        }
        else
            return;


    }

    BT_Node<T>& operator [](const T& dt) {
        try { return Do_Search(this->Root, dt); }
        catch (...) {
            throw Exception(404,"Entity Not Founded In Tree !!");
        }
    }

    BT_Node<T>& operator ()(const T& dt) {
        try { return Do_Search(&this->Root, dt); }
        catch (...) {
            throw "Not Found";
        }
    }

    void Add(const BT_Node<T>& dt) {
        try { Add_Child(this->Root, dt); }

        catch (Exception my_exc) {
            throw my_exc;
        }
    }

    void Add(BT_Node<T>* arr, int n) {
        if (arr != nullptr && n >= 0) {
            Array_to_BST(arr, n);
        }
        else
            return;
    }

    void Add(BS_Tree<T>* bs_2) {
        if (&bs_2 != nullptr) {
            BST_to_BST(bs_2->Root);
        }
        else
            return;

    }

    BT_Node<T>& Search(const T& dt) {
        try { return Do_Search(this->Root, dt); }
        catch (Exception my_err) {
            throw my_err;
        }

    }

    void Remove(const T& dt) {
        try { Do_Remove(&(*this)[dt]); }

        catch (Exception my_error) {
            throw my_error;
        }

    }

    void Print(void) {
        if (&this->Root != nullptr) {
            Do_Print(this->Root);
        }
        else
            std::cout << "Tree is Empty ... \n";
    }

    int Height(const T& dt) {
        int height = 0;
        height = Do_Height(&this->Search(dt));
        return height - 1;
    }

    int Depth(const T& dt) {
        return Do_Depth(dt);
    }

    double Size(const BT_Node<T>* root, char Mode) {
        switch (Mode)
        {
        case 'A':
            return Do_Size_ALL(root);
            break;
        default:
            return Do_Size_Data(root);
            break;
        }
    }

    int Leaf_Count(const BT_Node<T>* root) {
        int counter = 0;
        if (root != nullptr) {
            if (root->Left_child == nullptr && root->Right_child == nullptr)
                counter += 1;

            counter += Leaf_Count(root->Right_child);
            counter += Leaf_Count(root->Left_child);
        }
        else {
            return counter;
        }


    }

    BT_Node<T>& Find_Min(BT_Node<T>* root) {
        if (root != nullptr) {
            if (root->Left_child != nullptr)
                Find_Min(root->Left_child);
            else
                return *root;
        }
        else {

        }
    }

    BT_Node<T>& Find_Min(BT_Node<T>* root, int n) {
        static int counter = 0;
        static BT_Node<T>* ptr = nullptr;
        if (root != nullptr) {

            Find_Min(root->Left_child, n);
            counter++;
            if (n == counter) {
                ptr = root;
            }
            Find_Min(root->Right_child, n);

        }
        else {
            return *ptr;
        }
    }

    BT_Node<T>& Find_Max(BT_Node<T>* root) {
        if (root != nullptr) {
            if (root->Right_child != nullptr)
                Find_Max(root->Right_child);
            else
                return *root;
        }
        else {

        }
    }

    BT_Node<T>& Find_Max(BT_Node<T>* root, int n) {
        static int counter = 0;
        static BT_Node<T>* ptr = nullptr;
        if (root != nullptr) {

            Find_Max(root->Right_child, n);
            counter++;
            if (n == counter) {
                ptr = root;
            }
            Find_Max(root->Left_child, n);

        }
        else {
            return *ptr;
        }
    }

    void In_ot(const BT_Node<T>* root) {
        if (root != nullptr) {

            In_ot(root->Left_child);
            std::cout << "{ " << *root << " }";
            In_ot(root->Right_child);

        }
        else {
            return;
        }
    }

    void Post_ot(const BT_Node<T>* root) {
        if (root != nullptr) {

            Post_ot(root->Left_child);
            Post_ot(root->Right_child);
            std::cout << "{ " << *root << " }";
        }
        else {
            return;
        }
    }

    void Pre_ot(const BT_Node<T>* root) {
        if (root != nullptr) {

            std::cout << "{ " << *root << " }";
            Pre_ot(root->Left_child);
            Pre_ot(root->Right_child);

        }
        else {
            return;
        }
    }

    void Level_ot(const BT_Node<T>* root) {
        if (root != nullptr) {
            const BT_Node<T>& m = *root;
            int H = Height_Max(root) + 1;
            std::cout << "Level Order Traversal :\n";
            for (int i = 1; i <= H; i++) {

                std::cout << "Level (" << i << ")th : {";
                Print_Level(root, i);
                std::cout << '}';
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Root is Empty ...";
        }
    }

    int Height_Max(const BT_Node<T>* root) {
        int val = Do_Height_Max(root, true);
        return val;
    }

    void Vertical_Print(BT_Node<T>* root) {
        std::cout << "===========================================\n";
        std::cout << "Maximum Height is : " << this->Do_Height(this->Root) - 1 << "\n";
        std::cout << "Totall  Tree Size  : " << this->Size(this->Root, 'A') << "(B)\n";
        std::cout << "Data    Tree Size  : " << this->Size(this->Root, ' ') << "(B)\n";
        std::cout << "LEAF's  Count     : " << this->Leaf_Count(this->Root) << "\n";
        std::cout << "ALL's  Count     : " << this->Size(this->Root, ' ') / sizeof(T) << "\n";
        std::cout << "& = Left\n* = Right\n\n";

        Do_Vertical_Print(root, nullptr, false);
        std::cout << "===========================================\n";

    }

    void Generate_Random_Integer_Tree(BT_Node<int>* root, int count) {
        if (root == nullptr)
        {
            root = new BT_Node<int>;
            root->data = 1;
            this->Root = root;
        }

        srand(time(0));
        int p = 100000;
        for (int i = 0; i < count; i++) {
            int val = rand() % p;
            this->Add(val);
        }
    }

protected:

    void Add_Child(BT_Node<T>* current, const BT_Node<T>& dt) {
        if (current != nullptr) {
            if (dt.data < current->data) {
                if (current->Left_child == nullptr) {
                    current->Left_child = new BT_Node<T>;
                    *(current->Left_child) = dt;
                    current->Left_child->Father = current;
                }
                else
                    Add_Child(current->Left_child, dt);
            }
            else if (dt.data > current->data) {
                if (current->Right_child == nullptr) {
                    current->Right_child = new BT_Node<T>;
                    *(current->Right_child) = dt;
                    current->Right_child->Father = current;

                }
                else {
                    Add_Child(current->Right_child, dt);

                }
            }

            //Duplicate Entity ==> raise Error Of Duplicate
            else {
                // throw Ecxception(202, "Duplicate Entity !");
            }
        }
        else {
            return;
        }

    }

    BT_Node<T>& Do_Search(BT_Node<T>* current, const T& dt) {
        {
            if (current != nullptr) {
                if (current->data == dt)
                    return *current;
                else {
                    if (dt < current->data) {
                        Do_Search(current->Left_child, dt);
                    }
                    else {
                        Do_Search(current->Right_child, dt);
                    }
                }
            }
            else {
                throw Exception(404, "Not Found !");
            }

        }
    }

    void Do_Remove(BT_Node<T>* rm) {
        try {
            BT_Node<T>* tmp = rm;
            if (tmp->Right_child == nullptr && tmp->Left_child == nullptr) {
                Update_Father(tmp, nullptr);
            }
            else if (tmp->Left_child == nullptr) {
                tmp->Right_child->Father = tmp->Father;
                Update_Father(tmp, (tmp->Right_child));

            }
            else if (tmp->Right_child == nullptr) {
                tmp->Left_child->Father = tmp->Father;
                Update_Father(tmp, (tmp->Left_child));
            }
            else {
                T s = Find_Min(tmp->Right_child).data;
                BT_Node<T>* New_delete = &((*this)[s]);
                tmp->data = s;
                if (tmp->Left_child != nullptr)
                    tmp->Left_child->Father = tmp;

                Do_Remove(New_delete);



            }
        }
        catch (...) {}


    }

    void Do_Print(BT_Node<T>* root) {
        static int l = 0;
        if (root != nullptr) {
            std::cout << std::endl;
            for (int i = 1; i <= l; i++) {
                std::cout << " ";
            }
            std::cout << '|' << *root << '|';
            l += 10;
            Do_Print(root->Left_child);
            Do_Print(root->Right_child);
            l -= 10;
        }
        else return;
    }

    double Do_Size_Data(const BT_Node<T>* root) {
        double size = 0;
        if (root != nullptr) {
            size += sizeof(root->data);
            size += Do_Size_Data(root->Left_child);
            size += Do_Size_Data(root->Right_child);
        }
        else {
            return size;
        }
    }

    double Do_Size_ALL(const BT_Node<T>* root) {
        double size = 0;
        if (root != nullptr) {
            size += sizeof(*root);
            size += Do_Size_ALL(root->Left_child);
            size += Do_Size_ALL(root->Right_child);
        }
        else {
            return size;
        }
    }

    void Print_Level(const BT_Node<T>* root, int level)
    {
        if (root == nullptr)
            return;

        if (level == 1)
            std::cout << "( " << root->data << " )";
        else if (level > 1)
        {
            Print_Level(root->Left_child, level - 1);
            Print_Level(root->Right_child, level - 1);
        }
    }

    int Do_Height_Max(const BT_Node<T>* root, bool initial) {
        int height = 0;
        int tmp = 0;

        if (root != nullptr) {

            tmp += Do_Height_Max(root->Left_child, false);
            height = tmp;
            tmp = 0;
            tmp += Do_Height_Max(root->Right_child, false);
            if (tmp > height)
                height = tmp;

            if (initial)
                height--;

            height++;

        }
        else {
            return height;
        }
    }

    void Update_Father(BT_Node<T>* Old, BT_Node<T>* New) {
        if (Old != nullptr && Old->Father != nullptr) {
            if (Old->Father->Right_child == Old) {
                Old->Father->Right_child = New;
                if (New != nullptr)
                {
                    New->Father = Old->Father;

                }
            }

            else if ((Old->Father->Left_child) == Old) {
                Old->Father->Left_child = New;
                if (New != nullptr) {
                    New->Father = Old->Father;

                }

            }

        }
        else if (Old != nullptr && Old->Father == nullptr) {
            this->Root = New;
        }
        else {
            return;
        }

    }

    int Do_Height(BT_Node<T>* root) {
        int heightl = 0;
        int heightr = 0;
        if (root != nullptr) {
            if (root->Left_child == nullptr && root->Right_child == nullptr) {
                return 1;
            }
            heightl = Do_Height(root->Left_child);
            heightr = Do_Height(root->Right_child);

            if (heightl > heightr)
                return heightl + 1;
            else
                return heightr + 1;
        }
        else {
            return 0;
        }

    }

    int Do_Depth(const T& dt) {
        if (&dt != nullptr) {
            BT_Node<T>* pivot = this->Root;
            int Height = 0;
            while (pivot != nullptr) {
                if (pivot->data == dt) { return Height; }
                Height++;
                if (dt < pivot->data)
                    pivot = pivot->Left_child;
                else
                    pivot = pivot->Right_child;
            }
        }
        else {
            return -1;
        }
    }

    void Do_Vertical_Print(BT_Node<T>* root, GPrint* before, bool isLeft) {
        if (root == nullptr) {
            return;
        }

        std::string before_string = "     ";
        GPrint* gprint = new GPrint(before, before_string);

        Do_Vertical_Print(root->Right_child, gprint, true);

        if (!before) {
            gprint->Container = "---";
        }
        else if (isLeft)
        {
            gprint->Container = "*---";
            before_string = "    |";
        }
        else {
            gprint->Container = "&---";
            before->Container = before_string;
        }

        gprint->GPrinter(gprint);
        std::cout << '(' << root->data << ')' << std::endl;

        if (before) {
            before->Container = before_string;
        }
        gprint->Container = "    |";

        Do_Vertical_Print(root->Left_child, gprint, false);


    }

private:

    void Array_to_BST(BT_Node<T>* arr, int n) {
        for (int i = 0; i < n; i++) {
            this->Add(arr[i].data);
        }
    }

    void BST_to_BST(BT_Node<T>* root) {
        if (root == nullptr)
            return;
        else {
            this->Add_Child(this->Root, *root);
            BST_to_BST(root->Left_child);
            BST_to_BST(root->Right_child);
        }

    }

};

template <class T>
class AVL : public BS_Tree<T> {

public:

    AVL() {}
    AVL(const T& dt) { this->Root->data = dt; }
    AVL(BT_Node<T>* Nodes_Array, int n) {
        if (Nodes_Array != nullptr) {
            this->Root->data = Nodes_Array->data;
            Array_to_AVL(Nodes_Array, n - 1);
        }
        else {
            return;
        }
    }
    AVL(BS_Tree<T>* binary_tree) {
        if (binary_tree != nullptr) {
            this->Root->data = binary_tree->Root->data;
            BST_to_AVL(binary_tree);
        }
        else
            return;
    }

    void Add(const T& dt) {
        //First Insert It
        this->Add_Child(this->Root, dt);
        //Then Update Heights
        Update_B_Factors(this->Root);
        BT_Node<T>* tmp = this->First_Unbalanced(this->Root, dt);
        int balance = 0;
        if (tmp != nullptr)
            balance = tmp->B_Factor;

        switch (balance)
        {
        case +2:
            //Rotate Right Or Right-Left Rotate:

            //Right Right Case
            if (tmp->Right_child->data < dt) { Rotate_Left(tmp, tmp->Right_child); }

            // Right-Left Case
            else if (tmp->Right_child->data > dt) { Right_Left_Rotation(tmp, tmp->Right_child, tmp->Right_child->Left_child); }

            break;
        case -2:
            //Rotate Left Or Left-Right Rotate

            //Left Left Case
            if (tmp->Left_child->data > dt) { Rotate_Right(tmp, tmp->Left_child); }

            // Left-Right Case

            else if (tmp->Left_child->data < dt) { Left_Right_Rotation(tmp, tmp->Left_child, tmp->Left_child->Right_child); }

            break;
        default:
            break;
        }
        Update_B_Factors(this->Root);
    }

    void Add(BT_Node<T>* arr, int n) {
        Array_to_AVL(arr, n);
    }

    void Add(BS_Tree<T>* bineary_tree) {
        BST_to_AVL(bineary_tree);
    }

    void Remove(const T& dt) {
        this->Do_Remove(&(*this)[dt]);

        Update_h(this->Root);
        BT_Node<T>* key = First_Unbalanced(this->Root, dt);
        while (key != nullptr) {
            int balance = key->B_Factor;
            BT_Node<T>* y = Larger_Height_Child(key);
            BT_Node<T>* x = Larger_Height_Child(y);
            switch (balance)
            {
            case +2:
                //Right Right Case
                if (y == key->Right_child && x == y->Right_child) { Rotate_Left(key, y); }

                //Right Left Case
                else if (y == key->Right_child && x == y->Left_child) {
                    Right_Left_Rotation(key, y, x);
                }
                break;
            case -2:
                //Left Left Case
                if (y == key->Left_child && x == y->Left_child) { Rotate_Right(key, y); }

                //Left Right Case
                else if (y == key->Left_child && x == y->Right_child) { Left_Right_Rotation(key, y, x); }
                break;
            default:
                break;
            }
            Update_h(this->Root);
            key = First_Unbalanced(this->Root, dt);
        }

    }

    void Generate_Random_Integer_Tree(BT_Node<int>* root, int count) {
        if (root == nullptr)
        {
            root = new BT_Node<int>;
            root->data = 1;
            this->Root = root;
        }

        srand(time(0));
        int p = 100000;
        for (int i = 0; i < count; i++) {
            int val = rand() % p;
            this->Add(val);
        }
    }

private:

    void Update_B_Factors(BT_Node<T>* root) {
        Update_h(root);
    }

    void Rotate_Left(BT_Node<T>* A, BT_Node<T>* B) {
        BT_Node<T>* C = A->Father;
        BT_Node<T>* B_Left = B->Left_child;
        this->Update_Father(A, B);
        A->Father = B;
        B->Father = C;
        B->Left_child = A;
        A->Right_child = B_Left;
        if (B_Left != nullptr)
            B_Left->Father = A;

        if (A == this->Root)
            this->Root = B;

    }

    void Rotate_Right(BT_Node<T>* A, BT_Node<T>* B) {
        BT_Node<T>* C = A->Father;
        BT_Node<T>* B_Right = B->Right_child;
        this->Update_Father(A, B);
        A->Father = B;
        B->Father = C;
        B->Right_child = A;

        A->Left_child = B_Right;
        if (B_Right != nullptr)
            B_Right->Father = A;

        if (A == this->Root)
            this->Root = B;
    }

    //ROTATE LEFT A,B
    //ROTATE RIGHT B,C

    void Left_Right_Rotation(BT_Node<T>* C, BT_Node<T>* A, BT_Node<T>* B) {
        Rotate_Left(A, B);
        Rotate_Right(C, B);
        if (C == this->Root)
            this->Root = B;
    }

    //ROTATE RIGHT C,B
    //ROTATE LEFT A,B

    void Right_Left_Rotation(BT_Node<T>* A, BT_Node<T>* C, BT_Node<T>* B) {
        Rotate_Right(C, B);
        Rotate_Left(A, B);
        if (A == this->Root)
            this->Root = C;
    }

    int Update_h(BT_Node<T>* root) {
        int H = 0;
        if (root != nullptr) {
            if (root->Left_child == nullptr && root->Right_child == nullptr) {
                root->B_Factor = 0;
                return 1;
            }
            H = Update_h(root->Right_child);
            int LH = Update_h(root->Left_child);
            int max = get_max(H, LH);
            H -= LH;
            root->B_Factor = H;
            return max + 1;
        }
        else {
            return 0;
        }

    }

    BT_Node<T>* First_Unbalanced(BT_Node<T>* root, const T& dt) {
        BT_Node<T>* tmp = nullptr;
        while (root != nullptr) {
            if (root->B_Factor == -2 || root->B_Factor == +2) {
                tmp = root;

            }
            if (root->data > dt) {
                root = root->Left_child;
            }
            else if (root->data < dt) {
                root = root->Right_child;
            }
            else { root = nullptr; }
        }


        return tmp;
    }

    BT_Node<T>* Larger_Height_Child(BT_Node<T>* root) {
        BT_Node<T>* max_child = nullptr;
        int Left_Height = 0;
        int Right_Height = 0;
        Left_Height = this->Do_Height(root->Left_child);
        Right_Height = this->Do_Height(root->Right_child);
        if (Left_Height > Right_Height)
            max_child = root->Left_child;
        else if (Right_Height >= Left_Height)
            max_child = root->Right_child;


        return max_child;
    }

    int get_max(int a, int b) {
        a = abs(a);
        b = abs(b);
        int max = a;
        if (a < b)
            max = b;
        return max;
    }

    void Array_to_AVL(BT_Node<T>* arr, int n) {
        for (int i = 0; i < n; i++) {
            this->Add(arr[i].data);
        }
    }

    void BST_to_AVL(BS_Tree<T>* bst_tree) {
        if (bst_tree != nullptr)
            Do_BST_AVL(bst_tree->Root);
        else
            return;
    }

    void Do_BST_AVL(BT_Node<T>* root) {
        if (root == nullptr)
            return;
        else {
            this->Add(root->data);
            Do_BST_AVL(root->Left_child);
            Do_BST_AVL(root->Right_child);
        }

    }


};

int main()
{
    Worker();
}

//TEST Functions :

void Worker(void) {
    std::cout << "++++++++++++++++++++\n";
    std::cout << "Welcome to AVL-BST Project :\nWhich one do yo want to work with ?\n";
    std::cout << "1-BST\n2-AVL\n3-AVL-VS-BST\n0-EXIT\n";
    char looper = '1';
    std::cout << "++++++++++++++++++++\n";
    while (looper != '0') {

        std::cout << "Choose From Menu : ";
        std::cin >> looper;
        switch (looper)
        {
        case '1':
            BST_Worker();
            break;
        case '2':
            AVL_Worker();
            break;
        case '3':
            AVL_VS_BST_Worker();
            break;
        case '0':
            exit(0);
            break;
        default:
            Worker();
            break;
        }


    }

}

void BST_Worker(void) {
    std::cout << "=============================================\n";
    std::cout << "You are on BST choose : \n";
    std::cout << "1-Insert Binary Search Tree Manually.\n";
    std::cout << "2-Insert Binary Search Tree Randomly.\n";
    std::cout << "3-COPY Array to BST.\n";
    std::cout << "4-COPY BST to BST\n";
    std::cout << "5-Get Tree Size\n";
    std::cout << "6-Get n(th) Maximum value of tree.\n";
    std::cout << "7-Get n(th) Minimum value of tree.\n";
    std::cout << "8-Get Height of data.\n";
    std::cout << "9-Get Depth of data.\n";
    std::cout << "A-Remove Data.\n";
    std::cout << "B-Get Leaf's Count.\n";
    std::cout << "C-Get All nodes Count. \n";
    std::cout << "D-Find Minimum Value.\n";
    std::cout << "E-Find Maximum Value.\n";
    std::cout << "F-Find specific data.\n";
    std::cout << "G-In-Order Traversal.\n";
    std::cout << "H-Pre-Order Traversal.\n";
    std::cout << "I-Post-Order Traversal.\n";
    std::cout << "J-Level-Order Traversal.\n";
    std::cout << "P-Print Tree Vertically.\n";
    std::cout << "S-Print Tree Simple.\n";
    std::cout << "X-CLEAR TREE\n";
    std::cout << "=============================================\n";

    //Samples:
    static BS_Tree<int> bs_tree(0);
    BT_Node<int> tmp;
    BT_Node<int>* kk;
    int data = 0;
    int data2 = 0;
    char looper = '1';
    char foo = 0;
    BS_Tree<int> bs_tree_test(0);

    while (looper != '0') {
        std::cout << "Choose : ";
        std::cin >> looper;
        switch (looper)
        {
        case '1':
            std::cout << "please enter data : ";
            std::cin >> data;
            bs_tree.Add(data);
            std::cout << "Added!\n";
            break;
        case '2':
            std::cout << "How Much data do you want to add ?(1-RAM(SIZE)): ";
            std::cin >> data;
            std::cout << "inserting ...\n";
            bs_tree.Generate_Random_Integer_Tree(bs_tree.Root, data);
            std::cout << "All Data Inserted Succefully\n";
            break;
        case '3':
            std::cout << "How Much data do you want to add ?(1-RAM(SIZE)): ";
            std::cin >> data2;
            std::cout << "inserting ...\n";
            kk = new BT_Node<int>[data2];
            for (int i = 0; i < data2; i++) {
                std::cin >> data;
                kk[i] = data;
            }
            bs_tree.Add(kk, data2);
            std::cout << "All Data Inserted Succefully\n";
            break;
        case '4':
            std::cout << "Make your Second BST First : \n1-Make BST Manually.\n2-Make BST Automatically.\nE-EXIT\n";
            data2 = 0;
            while (foo != 'E') {
                std::cout << "What do yo want to do ?\n";
                std::cin >> foo;
                switch (foo)
                {
                case '1':
                    std::cout << "input data : ";
                    std::cin >> data;
                    bs_tree_test.Add(data);
                    std::cout << "Added ! (E for Exit)\n";
                    break;
                case '2':
                    std::cout << "How Much data wanna add to BST : ";
                    std::cin >> data;
                    bs_tree_test.Generate_Random_Integer_Tree(bs_tree_test.Root, data);
                    std::cout << "Random BST tree generated succesfully !(E for Exit)\n";
                    break;
                case 'E':
                    break;
                default:

                    break;
                }
            }

            std::cout << "Copying BST to BST ...\n";
            bs_tree.Add(&bs_tree_test);
            std::cout << "Copied Successfuly\n";
            break;
        case '5':
            std::cout << "Totall  Tree Size  : " << bs_tree.Size(bs_tree.Root, 'A') << "(B)\n";
            std::cout << "Data    Tree Size  : " << bs_tree.Size(bs_tree.Root, ' ') << "(B)\n";
            break;
        case '6':
            try {
                std::cout << "Enter(n)th Maximum that you want : n= ";
                std::cin >> data2;
                std::cout << "It is : (" << bs_tree.Find_Max(bs_tree.Root, data2) << ") \n";
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '7':
            try {
                std::cout << "Enter(n)th Minimum that you want : n= ";
                std::cin >> data2;
                std::cout << "It is : (" << bs_tree.Find_Min(bs_tree.Root, data2) << ") \n";
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '8':
            try{
                std::cout << "Which value's Height do yo want : ";
                std::cin >> data2;
                std::cout << "The " << data2 << " node Height in BST is : " << bs_tree.Height(data2) << std::endl;
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '9':
            try{
                std::cout << "Which value's Depth do yo want : ";
                std::cin >> data2;
                std::cout << "The " << data2 << " node Depth in BST is : " << bs_tree.Depth(data2) << "\n";
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case 'A':
            try{
                std::cout << "Which Node  do yo want to remove ? : ";
                std::cin >> data2;
                bs_tree.Remove(data2);
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case 'B':
            std::cout << "Leaf Nodes count is : (" << bs_tree.Leaf_Count(bs_tree.Root) << ") \n";
            break;
        case 'C':
            std::cout << "All Nodes count is : (" << bs_tree.Size(bs_tree.Root, ' ') / sizeof(int) << ") \n";
            break;
        case 'D':
            std::cout << "Minimum value Node in this tree is :(" << bs_tree.Find_Min(bs_tree.Root) << ") \n";
            break;
        case 'E':
            std::cout << "Maximum value Node in this tree is :(" << bs_tree.Find_Max(bs_tree.Root) << ") \n";
            break;
        case 'F':
            try {
                std::cout << "Which Node  do yo want to Find ? : ";
                std::cin >> data2;
                tmp = bs_tree[data2];
                std::cout << "Finded\nNode Value is : " << tmp.data << "\nNode Address is : " << &bs_tree[data2] << "\nNode Father is : " << tmp.Father;
                std::cout << "\nNode Right_Child is : " << tmp.Right_child << "\nNode Left_Child is : " << tmp.Left_child << std::endl;
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case 'G':
            bs_tree.In_ot(bs_tree.Root);
            std::cout << std::endl;
            break;
        case 'H':
            bs_tree.Pre_ot(bs_tree.Root);
            std::cout << std::endl;
            break;
        case 'I':
            bs_tree.Post_ot(bs_tree.Root);
            std::cout << std::endl;
            break;
        case 'J':
            bs_tree.Level_ot(bs_tree.Root);
            break;
        case 'P':
            bs_tree.Vertical_Print(bs_tree.Root);
            break;
        case 'S':
            bs_tree.Print();
            std::cout << std::endl;
            break;
        case 'X':
            while (bs_tree.Root != nullptr)
                bs_tree.Remove(bs_tree.Root->data);
            break;
        default:
            Worker();
            break;
        }
    }
}

void AVL_Worker(void) {
    std::cout << "=============================================\n";
    std::cout << "You are on AVL choose : \n";
    std::cout << "1-Insert AVL Tree Manually.\n";
    std::cout << "2-Insert AVL Tree Randomly.\n";
    std::cout << "3-Insert(COPY) Array to AVL.\n";
    std::cout << "4-Insert(COPY) BST to AVL\n";
    std::cout << "5-Get Tree Size\n";
    std::cout << "6-Get n(th) Maximum value of tree.\n";
    std::cout << "7-Get n(th) Minimum value of tree.\n";
    std::cout << "8-Get Height of data.\n";
    std::cout << "9-Get Depth of data.\n";
    std::cout << "A-Remove Data.\n";
    std::cout << "B-Get Leaf's Count.\n";
    std::cout << "C-Get All nodes Count. \n";
    std::cout << "D-Find Minimum Value.\n";
    std::cout << "E-Find Maximum Value.\n";
    std::cout << "F-Find specific data.\n";
    std::cout << "G-In-Order Traversal.\n";
    std::cout << "H-Pre-Order Traversal.\n";
    std::cout << "I-Post-Order Traversal.\n";
    std::cout << "J-Level-Order Traversal.\n";
    std::cout << "P-Print Tree Vertically.\n";
    std::cout << "S-Print Tree Simple.\n";
    std::cout << "X-CLEAR TREE\n";
    std::cout << "0-EXIT.\n";
    std::cout << "=============================================\n";

    //Samples:
    static AVL<int> avl_tree(0);
    BS_Tree<int> bs_tree(0);
    BT_Node<int> tmp;
    BT_Node<int>* kk; 
    int data = 0;
    int data2 = 0;
    char foo = '1';
    char looper = '1';

    while (looper != '0') {
        std::cout << "Choose : ";
        std::cin >> looper;
        switch (looper)
        {
        case '1':
            std::cout << "please enter data : ";
            std::cin >> data;
            avl_tree.Add(data);
            std::cout << "Added!\n";
            break;
        case '2':
            std::cout << "How Much data do you want to add ?(1-RAM(SIZE)): ";
            std::cin >> data;
            std::cout << "inserting ...\n";
            avl_tree.Generate_Random_Integer_Tree(avl_tree.Root, data);
            std::cout << "All Data Inserted Succefully\n";
            break;
        case '3':
            std::cout << "How Much data do you want to add ?(1-RAM(SIZE)): ";
            std::cin >> data2;
            kk = new BT_Node<int>[data2];
            std::cout << "inserting ...\n";
            for (int i = 0; i < data2; i++) {
                std::cin >> data;
                kk[i] = data;
            }
            avl_tree.Add(kk, data2);
            std::cout << "All Data Inserted Succefully\n";
            break;
        case '4':
            std::cout << "Make your BST First : \n1-Make BST Manually.\n2-Make BST Automatically.\nE-EXIT\n";
            data2 = 0;
            while (foo != 'E') {
                std::cin >> foo;
                switch (foo)
                {
                case '1':
                    std::cout << "input data : ";
                    std::cin >> data;
                    bs_tree.Add(data);
                    std::cout << "Added ! (E for Exit)\n";
                    break;
                case '2':
                    std::cout << "How Much data wanna add to BST : ";
                    std::cin >> data;
                    bs_tree.Generate_Random_Integer_Tree(bs_tree.Root, data);
                    std::cout << "Random BST tree generated succesfully !(E for Exit)\n";
                    break;
                case 'E':
                    break;
                default:

                    break;
                }
            }

            avl_tree.Add(&bs_tree);
            break;
        case '5':
            std::cout << "Totall  Tree Size  : " << avl_tree.Size(avl_tree.Root, 'A') << "(B)\n";
            std::cout << "Data    Tree Size  : " << avl_tree.Size(avl_tree.Root, ' ') << "(B)\n";
            break;
        case '6':
            try{
                std::cout << "Enter(n)th Maximum that you want : n= ";
                std::cin >> data2;
                std::cout << "It is : (" << avl_tree.Find_Max(avl_tree.Root, data2) << ") \n";
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '7':
            try{
                std::cout << "Enter(n)th Minimum that you want : n= ";
                std::cin >> data2;
                std::cout << "It is : (" << avl_tree.Find_Min(avl_tree.Root, data2) << ") \n";
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '8':
            try{
                std::cout << "Which value's Height do yo want : ";
                std::cin >> data2;
                std::cout << "The " << data2 << " node Height in AVL is : " << avl_tree.Height(data2);
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '9':
            try{
                std::cout << "Which value's Depth do yo want : ";
                std::cin >> data2;
                std::cout << "The " << data2 << " node Depth in AVL is : " << avl_tree.Depth(data2) << "\n";
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case 'A':
            try{
                std::cout << "Which Node  do yo want to remove ? : ";
                std::cin >> data2;
                avl_tree.Remove(data2);
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case 'B':
            std::cout << "Leaf Nodes count is : (" << avl_tree.Leaf_Count(avl_tree.Root) << ") \n";
            break;
        case 'C':
            std::cout << "All Nodes count is : (" << avl_tree.Size(avl_tree.Root, ' ') / sizeof(int) << ") \n";
            break;
        case 'D':
            std::cout << "Minimum value Node in this tree is :(" << avl_tree.Find_Min(avl_tree.Root) << ") \n";
            break;
        case 'E':
            std::cout << "Maximum value Node in this tree is :(" << avl_tree.Find_Max(avl_tree.Root) << ") \n";
            break;
        case 'F':
            try{
                std::cout << "Which Node  do yo want to Find ? : ";
                std::cin >> data2;
                tmp = avl_tree[data2];
                std::cout << "Finded\nNode Value is : " << tmp.data << "\nNode Address is : " << &avl_tree[data2] << "\nNode Father is : " << tmp.Father;
                std::cout << "\nNode Right_Child is : " << tmp.Right_child << "\nNode Left_Child is : " << tmp.Left_child << std::endl;
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case 'G':
            avl_tree.In_ot(avl_tree.Root);
            std::cout << std::endl;
            break;
        case 'H':
            avl_tree.Pre_ot(avl_tree.Root);
            std::cout << std::endl;
            break;
        case 'I':
            avl_tree.Post_ot(avl_tree.Root);
            std::cout << std::endl;
            break;
        case 'J':
            avl_tree.Level_ot(avl_tree.Root);
            break;
        case 'P':
            avl_tree.Vertical_Print(avl_tree.Root);
            break;
        case 'S':
            avl_tree.Print();
            std::cout << std::endl;
            break;
        case 'X':
            while (avl_tree.Root != nullptr)
                avl_tree.Remove(avl_tree.Root->data);
            break;
        default:
            Worker();
            break;
        }


    }

}

void AVL_VS_BST_Worker(void) {
    std::cout << "=============================================\n";
    std::cout << "You are on AVL-VS-BST choose From Menu : \n";
    std::cout << "1-Insert Manually\n";
    std::cout << "2-Insert Random\n";
    std::cout << "3-Remove\n";
    std::cout << "4-Print\n";
    std::cout << "5-Find\n";
    std::cout << "6-Get Tree Size\n";
    std::cout << "7-Root Height\n";
    std::cout << "8-Worst Case Test .\n";
    std::cout << "X-Delete AVL Tree .\n";
    std::cout << "D-Delete BST Tree .\n";
    std::cout << "0-EXIT\n";
    std::cout << "=============================================\n";

    //Samples:
    static  AVL<int> avl_tree(0);
    static BS_Tree<int> bs_tree(0);
    BT_Node<int> tmp;
    BT_Node<int>* kk;
    int data = 0;
    int data2 = 0;
    char foo = '1';
    char looper = '1';

    while (looper != '0') {
        std::cout << "Choose : ";
        std::cin >> looper;
        switch (looper)
        {
        case '1':
            std::cout << "please enter data : ";
            std::cin >> data;
            avl_tree.Add(data);
            bs_tree.Add(data);
            std::cout << "Added to trees Successfully!\n";
            break;
        case '2':
            std::cout << "How Much data do you want to add to Trees ?(1-10000): ";
            std::cin >> data;
            std::cout << "Start insert to BST ...\n";
            bs_tree.Generate_Random_Integer_Tree(bs_tree.Root, data);
            std::cout << "END insert to BST\n";
            std::cout << "Start insert to AVL ...\n";
            avl_tree.Generate_Random_Integer_Tree(avl_tree.Root, data);
            std::cout << "END insert to AVL ...\n";
            std::cout << "All Data Inserted Succefully\n";
            break;
        case '3':
           
            std::cout << "Which Node  do yo want to remove ? : ";
            std::cin >> data2;
            try {
                avl_tree.Remove(data2);
                bs_tree.Remove(data2);
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
            break;
        case '4':
            std::cout << "BST :\n";
            bs_tree.Vertical_Print(bs_tree.Root);
            std::cout << "AVL :\n";
            avl_tree.Vertical_Print(avl_tree.Root);
            break;
        case '5':
            std::cout << "Which Node  do yo want to Find ? : ";
            std::cin >> data2;
            try {
                tmp = avl_tree[data2];
                std::cout << "Finded In AVL\nNode Value is : " << tmp.data << "\nNode Address is : " << &avl_tree[data2] << "\nNode Father is : " << tmp.Father;
                std::cout << "\nNode Right_Child is : " << tmp.Right_child << "\nNode Left_Child is : " << tmp.Left_child << std::endl;
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            try {
                tmp = bs_tree[data2];
                std::cout << "Finded In BST\nNode Value is : " << tmp.data << "\nNode Address is : " << &bs_tree[data2] << "\nNode Father is : " << tmp.Father;
                std::cout << "\nNode Right_Child is : " << tmp.Right_child << "\nNode Left_Child is : " << tmp.Left_child << std::endl;
            }
            catch (Exception e) {
                std::cout << e.get_Message() << "\t ERROR( " << e.get_error_type() << " )\n";
            }
            break;
        case '6':

            std::cout << "AVL:\nTotall  Tree Size  : " << avl_tree.Size(avl_tree.Root, 'A') << "(B)\n";
            std::cout << "Data    Tree Size  : " << avl_tree.Size(avl_tree.Root, ' ') << "(B)\n";
            std::cout << "==============================\n";
            std::cout << "BST:\nTotall  Tree Size  : " << bs_tree.Size(bs_tree.Root, 'A') << "(B)\n";
            std::cout << "Data    Tree Size  : " << bs_tree.Size(bs_tree.Root, ' ') << "(B)\n";
            break;
        case '7':
            std::cout << "AVL:Maximum Height is : " << avl_tree.Height_Max(avl_tree.Root) << "\n";
            std::cout << "BST:Maximum Height is : " << bs_tree.Height_Max(bs_tree.Root) << "\n";
            break;
        case '8':
            std::cout << "Enter Worst case Count That Want to Insert :(1-500)Stack Limitation For BST in Linked List Mode(WCase) \n";
            std::cin >> data;

            std::cout << "Start insert to BST ...\n";
            for (int i = 0; i < data; i++) {
                bs_tree.Add(i);

            }
            std::cout << "END insert to BST\n";

            std::cout << "Start insert to AVL ...\n";

            for (int i = 0; i < data; i++) {
                avl_tree.Add(i);
            }
            std::cout << "END insert to AVL ...\n";

            break;
        case 'X':
            while (avl_tree.Root != nullptr)
                avl_tree.Remove(avl_tree.Root->data);
            break;
        case 'D':
            while (bs_tree.Root != nullptr)
                bs_tree.Remove(bs_tree.Root->data);
            break;
        case '0':
            break;
        default:
            Worker();
            break;
        }
    }
}

