
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

TEST(BT_Node, Assignment_Operator_Test) {
    BT_Node<int> a(10);
    BT_Node<int> b(20);
    a = b;
  EXPECT_EQ(20,a.data);
  EXPECT_EQ(b.Father, a.Father);
  EXPECT_EQ(b.Left_child, a.Left_child);
  EXPECT_EQ(b.Right_child, a.Right_child);
  EXPECT_NE(&b, &a);
  EXPECT_TRUE(true);
}

TEST(BT_Node, EqualEqual_Opereator_test) {
    BT_Node<int> a(10);
    BT_Node<int> b(10);
    BT_Node<int> d(20);

    bool c = a == b;
    bool m = a == d;
    EXPECT_EQ(true, c);
    EXPECT_EQ(false,m );

}

TEST(BT_Node, Constructor_Test) {
    BT_Node<std::string> ll("This_Test");
    EXPECT_EQ("This_Test", ll.data);
}