#include <iostream>
#include <cmath>
using namespace std;
// 多項式項的結構 
struct Term // 每個Term都代表了多項式的一項
{
    int coefficient; // 係數
    int exponent;    // 指數
    Term *next;      // 一個指向下一個的指針，名為next
    // constructor///
    Term(int coef, int exp)
    {
        coefficient = coef;
        exponent = exp;
        next = nullptr;
    }
};

class Polynomial //建立一個Polynomial class,詳細操作情形請見Ipad
{
public:
    Polynomial() // constructor
    {
        head = nullptr; // 初始化head這個指針為nullptr
    }
    // 新增一個多項式（帶有排序功能）
    void addTerm(int coefficient, int exponent)
    {
        Term *newTerm = new Term(coefficient, exponent);

        if (head == nullptr || exponent > head->exponent)
        {
            // 如果多項式是空的或者新項的指數比頭部的大，將新項設置為頭部
            newTerm->next = head;
            head = newTerm;
        }
        else
        {
            Term *current = head;

            while (current->next != nullptr && current->next->exponent >= exponent)
            {
                current = current->next;
            }

            // 插入新項
            newTerm->next = current->next;
            current->next = newTerm;
        }
    }

    //// 新增一個多項式項
    // void addTerm(int coefficient, int exponent)
    //{
    //     Term *newTerm = new Term(coefficient, exponent); // 動態分配記憶體以創建一個新的多項式項（Term)，並將其地址分配給名為"newTerm"的指標 //動態分配記憶體要記得three amigo
    //     if (head == nullptr)                             // 檢查linked lsit的head（頭指標）是否為空，也就是檢查此linked list是否為空
    //     {
    //         head = newTerm; // 如果是空，那我們剛創造（new)出來的newTerm就變成了linked list的第一項
    //     }
    //     else
    //     {
    //         Term *current = head; // 將head指標指向的地址指派給指向term結構的Current指標，從頭開始進行遍歷，找出最後一項的位置（這邊可參考老師講義最後面，有提到要注意的）
    //         while (current->next != nullptr)
    //         {
    //             current = current->next; // 如果要對指標進行存取,要使用->符號
    //         }
    //         current->next = newTerm; // 如果下一項為nullptr，就代表現在到了最後一項
    //                                  // 所以把current->next指到剛剛新增的那一項的位置(也就是newTerm的位置)
    //     }
    // }

    // 多項式相加
    Polynomial operator+(const Polynomial &other) const
    {
        Polynomial result;        // 創造一個新的Polynomial來存放相加的結果
        Term *term1 = head;       // 一個指向Term結構的指針，名為term1，指向第一個多項式的head
        Term *term2 = other.head; // 一個指向Term結構的指針，名為term2，指向第二個多項式的head

        while (term1 != nullptr || term2 != nullptr) // 當term1或term2其中一個不為0，就會一直重複執行以下內容(while loop)
        {
            // 獲取兩個多項式項的係數和指數，如果沒有項，將係數設為0
            int coef1 = (term1 != nullptr) ? term1->coefficient : 0; // 如果term1不是nullptr，就把coef1設置為term1的coefficient
            int coef2 = (term2 != nullptr) ? term2->coefficient : 0;
            int exp1 = (term1 != nullptr) ? term1->exponent : 0;
            int exp2 = (term2 != nullptr) ? term2->exponent : 0;

            if (exp1 == exp2)
            {
                result.addTerm(coef1 + coef2, exp1);
                term1 = (term1 != nullptr) ? term1->next : nullptr;
                term2 = (term2 != nullptr) ? term2->next : nullptr;
            }
            else if (exp1 > exp2)
            {
                result.addTerm(coef1, exp1);
                term1 = (term1 != nullptr) ? term1->next : nullptr;
            }
            else
            {
                result.addTerm(coef2, exp2);
                term2 = (term2 != nullptr) ? term2->next : nullptr;
            }
        }

        return result;
    }

    // 多項式相減
    Polynomial operator-(const Polynomial &other) const
    {
        Polynomial result;        // 創造一個新的Polynomial來存放相加的結果
        Term *term1 = head;       // 一個指向Term結構的指針，名為term1，指向第一個多項式的head
        Term *term2 = other.head; // 一個指向Term結構的指針，名為term2，指向第二個多項式的head

        while (term1 != nullptr || term2 != nullptr) // 當term1或term2其中一個不為0，就會一直重複執行以下內容(while loop)
        {
            // 獲取兩個多項式項的係數和指數，如果沒有項，將係數設為0
            int coef1 = (term1 != nullptr) ? term1->coefficient : 0; // 如果term1不是nullptr，就把coef1設置為term1的coefficient
            int coef2 = (term2 != nullptr) ? term2->coefficient : 0;
            int exp1 = (term1 != nullptr) ? term1->exponent : 0;
            int exp2 = (term2 != nullptr) ? term2->exponent : 0;

            if (exp1 == exp2)
            {
                result.addTerm(coef1 - coef2, exp1);
                term1 = (term1 != nullptr) ? term1->next : nullptr;
                term2 = (term2 != nullptr) ? term2->next : nullptr;
            }
            else if (exp1 > exp2)
            {
                result.addTerm(coef1, exp1);
                term1 = (term1 != nullptr) ? term1->next : nullptr;
            }
            else // 當poly1的係數比poly2小的時候，poly2 addTerm的時候要加負號
            {
                result.addTerm(0 - coef2, exp2);
                term2 = (term2 != nullptr) ? term2->next : nullptr;
            }
        }

        return result;
    }

    // 多項式相乘
    Polynomial operator*(const Polynomial &other) const // 流程圖去看ipad
    {
        Polynomial result;  // 創造一個新的Polynomial來存放相加的結果
        Polynomial mul_add; // 創造三個用來存放係數相乘後的結果，以便後續將他們相加得到最終結果
        Term *term1 = head; // 一個指向Term結構的指針，名為term1，指向第一個多項式的head
        // Term *term2 = other.head; // 一個指向Term結構的指針，名為term2，指向第二個多項式的head

        while (term1 != nullptr) // 當term1不為0，就會一直重複執行以下內容(while loop)
        {

            Term *term2 = other.head; // 寫在while內部是因為每做完poly1一個項的乘法，就要把poly2的指針移回到poly2的頭
            // 獲取多項式項的係數和指數，如果沒有項，將係數設為0
            int coef1 = (term1 != nullptr) ? term1->coefficient : 0; // 如果term1不是nullptr，就把coef1設置為term1的coefficient
            int exp1 = (term1 != nullptr) ? term1->exponent : 0;
            while (term2 != nullptr)
            {
                int coef2 = (term2 != nullptr) ? term2->coefficient : 0;
                int exp2 = (term2 != nullptr) ? term2->exponent : 0;
                mul_add.addTerm(coef1 * coef2, exp1 + exp2);
                term2 = term2->next;
            }
            result = result + mul_add;
            mul_add = Polynomial(); // 相加完要把暫存的設置為空多項是，用於下一次計算

            term1 = term1->next;
        }

        return result;
    }

    // 多項式未知數帶入求值
    int evaluation(int a)
    {
        int result = 0;
        Term *term1 = head; // 一個指向Term結構的指針，名為term1，指向第一個多項式的head
        while (term1 != nullptr)
        {
            int add = 0; // 每次做完一個項的代入，都要把暫存的結果清空
            // 獲取兩個多項式項的係數和指數，如果沒有項，將係數設為0
            int coef1 = (term1 != nullptr) ? term1->coefficient : 0; // 如果term1不是nullptr，就把coef1設置為term1的coefficient
            int exp1 = (term1 != nullptr) ? term1->exponent : 0;
            add = coef1 * pow(a, exp1); // 使用 pow 函數計算 a 的 exp1 次方
            result = result + add;
            term1 = term1->next;
        }
        return result;
    }

    // 多項式輸出
    void print() const
    {
        Term *current = head;
        while (current != nullptr) // 當current不為nullptr，就會一直執行以下內容（while loop)
        {
            cout << current->coefficient;
            if (current->exponent >= 0)
            {
                cout << "x^" << current->exponent;
            }
            if (current->next != nullptr)
            {
                if (current->next->coefficient < 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << " + ";
                }
            }
            current = current->next;
        }
        cout << endl;
    }

    // 清除多項式
    void clear()
    {
        while (head != nullptr)
        {
            Term *temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Term *head; // 一個指向term結構的指針，名為head
};

// x的0次方項是否也要打出來（print那邊改 次方 >= 0 的都要顯示出 X^次方）
int main()
{
    Polynomial poly1, poly2;
    int evaluation_num;

    cout << "Enter Polynomial 1 (3 terms, coefficient and exponent):" << endl;
    for (int i = 0; i < 3; i++)
    {
        int coef, exp;
        cin >> coef >> exp;
        poly1.addTerm(coef, exp);
        // 可能需要新增一個排序的功能，來讓他們的次方從大到小排序，排序完再進行運算的操作
        // 這樣輸入的順序才不會影響最後運算的值
    }

    cout << "Enter Polynomial 2 (3 terms, coefficient and exponent):" << endl;
    for (int i = 0; i < 3; i++)
    {
        int coef, exp;
        cin >> coef >> exp;
        poly2.addTerm(coef, exp);
    }
    cout << "x = ";
    cin >> evaluation_num;

    cout << "Polynomial 1: ";
    poly1.print();

    cout << "Polynomial 2: ";
    poly2.print();

    Polynomial result_of_addition = poly1 + poly2;
    Polynomial result_of_substraction = poly1 - poly2;
    Polynomial result_of_multiplication = poly1 * poly2;
    cout << "Result of Addition: ";
    result_of_addition.print();
    cout << "Result of substraction: ";
    result_of_substraction.print();
    cout << "Result of multiplicaiton: ";
    result_of_multiplication.print();
    cout << "Evaluation of Polynomial 1 at x = " << evaluation_num << " is: " << poly1.evaluation(evaluation_num) << endl;
    cout << "Evaluation of Polynomial 2 at x = " << evaluation_num << " is: " << poly2.evaluation(evaluation_num);

    return 0;
}
