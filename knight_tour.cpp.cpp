#include <iostream>
#include <iomanip>

using namespace std;

//  8x8 تعريف حجم رقعة الشطرنج
#define N 8

//   لتمثيل نقطة او حركة على الرقعة حيث xهوة الصف و yهوة العمود(Struct) هنا نستخدم ال
struct Position {
    int x, y;
};

// هذه المصفوفات تمثل حركة الحصان القانونية  (حرفL)
int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

// وظيفتها التاكد من الحركة  لاتخرج خارج حدود الرقعة 2 - ان الخانة فارغة( تساوي -1 )ولم يزرها الحصان سابقا(validtion function)دالة التحقق 
bool isValid(int x, int y, int board[N][N]) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

// دالة حساب "الدرجة" (عدد الحركات المتاحة من هذه الخانة)
int getDegree(int x, int y, int board[N][N]) {
    int count = 0;
    for (int i = 0; i < 8; ++i)
        if (isValid(x + dx[i], y + dy[i], board))
            count++;
    return count;
}

//  الدالة الأساسية لحل المسألة باستخدام قاعدة Warnsdorff
bool solveKnightTour(int startX, int startY) {
    int board[N][N];

    // تهيئة الرقعة بقيمة -1
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    //تعيين نقطة البداية
    int curr_x = startX;
    int curr_y = startY;
    board[curr_x][curr_y] = 1; //الخطوة الأولى

    // ملء بقية الـ 63 خانة
    for (int step = 2; step <= N * N; ++step) {
        int min_deg_idx = -1;
        int min_deg = 9;

        //  البحث عن الحركة القادمة ذات أقل خيارات مستقبلية
        for (int i = 0; i < 8; ++i) {
            int next_x = curr_x + dx[i];
            int next_y = curr_y + dy[i];
            
            if (isValid(next_x, next_y, board)) {
                int degree = getDegree(next_x, next_y, board);
                if (degree < min_deg) {
                    min_deg_idx = i;
                    min_deg = degree;
                }
            }
        }

        // اذا لم نجد حركة مناسبة ,يعني انحبس الحصان (فشل الحل)
        if (min_deg_idx == -1) return false;

        // تنفيذ الحركة المختارة
        curr_x += dx[min_deg_idx];
        curr_y += dy[min_deg_idx];
        board[curr_x][curr_y] = step;
    }

    // طباعة النتيجة النهائية بشكل مرتب
    cout << "\n--- نتيجة جولة الحصان  ---\n" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(3) << board[i][j] << " ";
        cout << endl;
    }
    return true;
}

int main() {
    int sX, sY;
    cout << "Welcome to Knight's Tour Project (Warnsdorff's Rule)" << endl;
    cout << "Enter starting X (0-7): ";
    cin >> sX;
    cout << "Enter starting Y (0-7): ";
    cin >> sY;

    if (sX < 0 || sX >= N || sY < 0 || sY >= N) {
        cout << "Invalid starting position!" << endl;
    } else {
        if (!solveKnightTour(sX, sY)) {
            cout << "No solution found for this starting point." << endl;
        }
    }

    return 0;
}

