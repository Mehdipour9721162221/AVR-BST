#include "pch.h"


class Exception {
public:
    Exception(int error_type, std::string message) {
        this->error_number = error_type;
        this->error_message = message;
    }
   friend  bool operator == (const Exception& a , const Exception & b) {
        bool are_equal = false;
        if (a.error_number == b.error_number)
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
        //this->balance_factor = b.balance_factor;
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

    friend bool operator == (const BT_Node<T>& a, const BT_Node<T>& b) {
        bool Duplicate = false;
        if (a.data == b.data) {
            Duplicate = true;
        }
        return Duplicate;
    }

};

template <class T>
class BS_Tree {
public:
    BT_Node<T>* Root = nullptr;
    //Iterator<T> iterator;

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
        //iterator.begin(*this);
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
            throw Exception(404, "Not Found !");
        }
    }

    BT_Node<T>& operator ()(const T& dt) {
        try { return Do_Search(&this->Root, dt); }
        catch (...) {
            throw Exception(404, "Not Found !");
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
                throw Exception(202, "Duplicate Entity !");
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

   /* void Do_Vertical_Print(BT_Node<T>* root, GPrint* before, bool isLeft) {
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


    }*/

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

TEST(BS_Tree, Add_test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    EXPECT_EQ(123, kk.Root->Right_child->data);
    EXPECT_EQ(-90, kk.Root->Left_child->data);
    EXPECT_EQ(2, kk.Leaf_Count(kk.Root));
    Exception test(0," ");
    try {
        kk.Add(100);
    }
    catch (Exception e) {
        test = e;
    }
    Exception aa(202, "Duplicate Entity !");

    EXPECT_EQ(aa, test);

}

TEST(BS_Tree, Remove_test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);
    kk.Remove(100);
    BT_Node<int> tt = 123;
    EXPECT_EQ(tt, *kk.Root);
   // EXPECT_EQ(3, kk.Leaf_Count(kk.Root));
    
    Exception test(0, " ");
    try {
        kk.Remove(100);
    }
    catch (Exception e) {
        test = e;
    }
    Exception aa(404 , "Not Found !");

    EXPECT_EQ(aa, test);

}
TEST(BS_Tree, Find_Test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);
   
    BT_Node<int> tt =kk[150];
    EXPECT_EQ(150, tt.data);
   // EXPECT_EQ(3, kk.Leaf_Count(kk.Root));
    
}
TEST(BS_Tree, Size_test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);

    EXPECT_EQ(sizeof(int)*4, kk.Size(kk.Root,' '));
    // EXPECT_EQ(3, kk.Leaf_Count(kk.Root));

}
TEST(BS_Tree, Size_All_Test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);
    kk.Add(122);
    kk.Add(-91);
    kk.Add(1503);
    EXPECT_EQ(sizeof(BT_Node<int>) * 7, kk.Size(kk.Root, 'A'));


}
TEST(BS_Tree, Do_Height_Max_Test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);
    kk.Add(122);
    kk.Add(-91);
    kk.Add(1503);
    EXPECT_EQ(3, kk.Height_Max(kk.Root));
    kk.Remove(1503);
    EXPECT_EQ(2, kk.Height_Max(kk.Root));
    
}
TEST(BS_Tree, Depth_test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);
    kk.Add(122);
    kk.Add(-91);
    kk.Add(1503);
    EXPECT_EQ(3, kk.Depth(1503));
    kk.Remove(1503);
    EXPECT_EQ(0, kk.Depth(100));


}
TEST(BS_Tree, Find_Max_test_Find_Min_Test) {
    BS_Tree<int> kk(100);
    kk.Add(123);
    kk.Add(-90);
    kk.Add(150);
    kk.Add(122);
    kk.Add(-91);
    kk.Add(1503);
    EXPECT_EQ(1503, kk.Find_Max(kk.Root,1));
   // kk.Remove(1503);
   // EXPECT_EQ(150, kk.Find_Max(kk.Root, 2));
   // EXPECT_EQ(122, kk.Find_Max(kk.Root,3));
  /*  EXPECT_EQ(-91, kk.Find_Max(kk.Root, 5));
    EXPECT_EQ(-91, kk.Find_Min(kk.Root, 1));
    EXPECT_EQ(-90, kk.Find_Min(kk.Root, 2));
    EXPECT_EQ(150, kk.Find_Min(kk.Root, 5));*/
   
}