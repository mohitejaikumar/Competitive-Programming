

template <typename Node, typename Update>
struct SegTree
{
    vector<Node> tree;
    int n;
    int s;
    vector<int> arr;
    SegTree(int n, vector<int> &a)
    {
        this->n = n;
        this->arr = a;
        this->s = 1;
        while (s < 2 * n)
        {
            s = s << 1;
        }
        tree.resize(s);
        fill(tree.begin(), tree.end(), Node());
        build(0, n - 1, 1);
    }

    void build(int start, int end, int index)  // Never Change
    {
        if (start == end)
        {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
        return;
    }

    Node query(int start, int end, int index, int left, int right)  // Never Change
    {
        if (right < start || left > end)
            return Node();
        if (start >= left && end <= right)
            return tree[index];
        int mid = (start + end) / 2;
        Node leftNode = query(start, mid, 2 * index, left, right);
        Node rightNode = query(mid + 1, end, 2 * index + 1, left, right);
        Node ans;
        ans.merge(leftNode, rightNode);
        return ans;
    }

    void update(int start, int end, int index, int pos, Update &u)  // Never Change 
    {
        if (start == end)
        {
            u.apply(tree[index]);
            return;
        }
        int mid = (start + end) / 2;
        if (mid < pos)
        {
            update(mid + 1, end, 2 * index + 1, pos, u);
        }
        else
        {
            update(start, mid, 2 * index, pos, u);
        }
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }

    void make_update(int &pos, int &val)
    {
        Update temp = Update(val);
        update(0, n - 1, 1, pos, temp);
        return;
    }

    Node make_query(int &start, int &end)
    {
        return query(0, n - 1, 1, start, end);
    }
};


// changes ->> 
struct Node1
{
    int data;
    Node1()
    {
        data = 0; // default value
    }
    Node1(int &val)
    {
        data = val;
    }
    void merge(Node1 &l, Node1 &r)
    {
        data = l.data ^ r.data;
    }
};

struct Update1
{
    int val;
    Update1(int &v)
    {
        val = v;
    }
    void apply(Node1 &node)
    {
        node.data = val;
    }
};

void solve()
{
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    SegTree<Node1, Update1> segTree = SegTree<Node1, Update1>(n, arr);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << segTree.make_query(l, r).data << endl;
    }
    return;
}

