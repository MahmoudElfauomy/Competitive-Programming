#include <iostream>
#include <vector>

using namespace std;

class FenwickTree2D 
{
private:
    int rows, cols;
    vector<vector<int>> tree;

public:
    // بناء الشجرة بحجم (rows + 1) x (cols + 1) لأن شجرة فينويك تبدأ من Index 1
    FenwickTree2D(int r, int c) : rows(r), cols(c) {
        tree.assign(rows + 1, vector<int>(cols + 1, 0));
    }

    // إضافة قيمة (val) للخلية (x, y)
    void update(int x, int y, int val) {
        for (int i = x; i <= rows; i += i & (-i)) {
            for (int j = y; j <= cols; j += j & (-j)) {
                tree[i][j] += val;
            }
        }
    }

    // حساب المجموع من (1, 1) إلى (x, y)
    int query(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= i & (-i)) {
            for (int j = y; j > 0; j -= j & (-j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // حساب مجموع مستطيل محدد بين الزاوية (x1, y1) والزاوية (x2, y2)
    int queryRange(int x1, int y1, int x2, int y2) {
        return query(x2, y2) 
             - query(x1 - 1, y2) 
             - query(x2, y1 - 1) 
             + query(x1 - 1, y1 - 1);
    }
};

int main() 
{
    int r = 4, c = 4;
    FenwickTree2D ft(r, c);

    // مصفوفة أبعادها 4x4
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {1, 1, 1, 1},
        {2, 2, 2, 2}
    };

    // ملء الشجرة بالقيم الأولية (تحويل الإحداثيات لتبدأ من 1)
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            ft.update(i + 1, j + 1, grid[i][j]);
        }
    }

    // 1. حساب مجموع المستطيل من (1, 1) إلى (2, 2)
    cout << "Sum [1,1] to [2,2]: " << ft.queryRange(1, 1, 2, 2) << endl;

    // 2. حساب المجموع الكلي للمصفوفة من (1, 1) إلى (4, 4)
    cout << "Total Sum [1,1] to [4,4]: " << ft.queryRange(1, 1, 4, 4) << endl;

    // 3. تحديث الخلية (2, 2) وإضافة 4 إليها (تتحول قيمتها من 6 إلى 10)
    ft.update(2, 2, 4);

    // 4. إعادة حساب مجموع المستطيل من (1, 1) إلى (2, 2) بعد التعديل
    cout << "Sum [1,1] to [2,2] after update: " << ft.queryRange(1, 1, 2, 2) << endl;

    return 0;
}
