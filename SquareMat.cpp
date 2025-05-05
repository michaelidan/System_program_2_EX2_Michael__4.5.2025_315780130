// michael9090124@gmail.com

#include "SquareMat.h"
#include <stdexcept>
#include <cmath>

namespace Matrix {

// בנאים
// בנאי עם גודל התחלתי
// יוצר מטריצה בגודל size x size
// כל האיברים מאותחלים ל-0
SquareMat::SquareMat(int size) : size(size) {
    // בדיקת תקינות הגודל - לא מאפשרים גודל שלילי
    if (size < 0) {
        throw std::invalid_argument("Matrix size cannot be negative");
    }
    // הקצאת זיכרון למטריצה
    allocateMemory();
}

// בנאי העתקה
// יוצר מטריצה חדשה זהה למטריצה אחרת
SquareMat::SquareMat(const SquareMat& other) : size(other.size) {
    // הקצאת זיכרון למטריצה החדשה
    allocateMemory();
    // העתקת הערכים מהמטריצה המקורית
    copyMatrix(other);
}

// מחלץ
// משחרר את הזיכרון שהוקצה למטריצה
SquareMat::~SquareMat() {
    deallocateMemory();
}

// פונקציות עזר
// הקצאת זיכרון למטריצה
void SquareMat::allocateMemory() {
    // אם הגודל הוא 0, לא מקצים זיכרון
    if (size == 0) {
        matrix = nullptr;
        return;
    }
    // הקצאת מערך של שורות
    matrix = new double*[size];
    // לכל שורה מקצים מערך של עמודות
    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size]();  // האיברים מאותחלים ל-0
    }
}

// שחרור זיכרון של המטריצה
void SquareMat::deallocateMemory() {
    // בדיקה שיש זיכרון לשחרר
    if (matrix != nullptr) {
        // שחרור הזיכרון של כל שורה
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        // שחרור המערך הראשי
        delete[] matrix;
        matrix = nullptr;
    }
}

// העתקת ערכים ממטריצה אחרת
void SquareMat::copyMatrix(const SquareMat& other) {
    // העתקת כל האיברים אחד אחד
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

// אופרטורי השמה
// אופרטור השמה - מעתיק מטריצה אחרת למטריצה הנוכחית
SquareMat& SquareMat::operator=(const SquareMat& other) {
    // בדיקת השמה עצמית (a = a)
    if (this != &other) {
        // שחרור הזיכרון הקיים
        deallocateMemory();
        // עדכון הגודל
        size = other.size;
        // הקצאת זיכרון חדש
        allocateMemory();
        // העתקת הערכים
        copyMatrix(other);
    }
    return *this;
}

// אופרטור חיבור והשמה
SquareMat& SquareMat::operator+=(const SquareMat& other) {
    // בדיקת התאמת גדלים
    if (size != other.size) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    // חיבור איברים
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

// אופרטור חיסור והשמה
SquareMat& SquareMat::operator-=(const SquareMat& other) {
    // בדיקת התאמת גדלים
    if (size != other.size) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    // חיסור איברים
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

// אופרטור כפל והשמה
SquareMat& SquareMat::operator*=(const SquareMat& other) {
    // בדיקת התאמת גדלים
    if (size != other.size) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    // יצירת מטריצה זמנית לשמירת התוצאה
    SquareMat temp(size);
    // כפל מטריצות
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double sum = 0;
            // חישוב האיבר החדש
            for (int k = 0; k < size; k++) {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            temp.matrix[i][j] = sum;
        }
    }
    // העתקת התוצאה למטריצה הנוכחית
    *this = temp;
    return *this;
}

// אופרטור חילוק והשמה
SquareMat& SquareMat::operator/=(double scalar) {
    // בדיקת חילוק באפס
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero");
    }
    // חילוק כל האיברים בסקלר
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] /= scalar;
        }
    }
    return *this;
}

// אופרטור כפל איברי והשמה
SquareMat& SquareMat::operator%=(const SquareMat& other) {
    // בדיקת התאמת גדלים
    if (size != other.size) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    // כפל איברים
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] *= other.matrix[i][j];
        }
    }
    return *this;
}

// אופרטור מודולו והשמה
SquareMat& SquareMat::operator%=(int scalar) {
    // בדיקת מודולו באפס
    if (scalar == 0) {
        throw std::invalid_argument("Modulo by zero");
    }
    // חישוב מודולו לכל איבר
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = fmod(matrix[i][j], scalar);
        }
    }
    return *this;
}

// אופרטורים אריתמטיים
// אופרטור חיבור
SquareMat SquareMat::operator+(const SquareMat& other) const {
    // יצירת מטריצה חדשה
    SquareMat result(*this);
    // חיבור המטריצה האחרת
    result += other;
    return result;
}

// אופרטור חיסור
SquareMat SquareMat::operator-(const SquareMat& other) const {
    // יצירת מטריצה חדשה
    SquareMat result(*this);
    // חיסור המטריצה האחרת
    result -= other;
    return result;
}

// אופרטור כפל מטריצות
SquareMat SquareMat::operator*(const SquareMat& other) const {
    // בדיקת התאמת גדלים
    if (size != other.size) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    // יצירת מטריצה חדשה
    SquareMat result(size);
    // כפל מטריצות
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double sum = 0;
            for (int k = 0; k < size; k++) {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
    return result;
}

// אופרטור חילוק בסקלר
SquareMat SquareMat::operator/(double scalar) const {
    // יצירת מטריצה חדשה
    SquareMat result(*this);
    // חילוק בסקלר
    result /= scalar;
    return result;
}

// אופרטור כפל איברי
SquareMat SquareMat::operator%(const SquareMat& other) const {
    // יצירת מטריצה חדשה
    SquareMat result(*this);
    // כפל איברי
    result %= other;
    return result;
}

// אופרטור מודולו
SquareMat SquareMat::operator%(int scalar) const {
    // יצירת מטריצה חדשה
    SquareMat result(*this);
    // חישוב מודולו
    result %= scalar;
    return result;
}

// אופרטור מינוס אונארי
SquareMat SquareMat::operator-() const {
    // יצירת מטריצה חדשה
    SquareMat result(*this);
    // היפוך סימן כל האיברים
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.matrix[i][j] = -matrix[i][j];
        }
    }
    return result;
}

// אופרטורי השוואה
// אופרטור שוויון
bool SquareMat::operator==(const SquareMat& other) const {
    // בדיקת התאמת גדלים
    if (size != other.size) return false;
    // חישוב סכום האיברים של שתי המטריצות
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum1 += matrix[i][j];
            sum2 += other.matrix[i][j];
        }
    }
    // השוואת הסכומים
    return sum1 == sum2;
}

// אופרטור אי-שוויון
bool SquareMat::operator!=(const SquareMat& other) const {
    return !(*this == other);
}

// אופרטור קטן מ-
bool SquareMat::operator<(const SquareMat& other) const {
    // בדיקת התאמת גדלים
    if (size != other.size) {
        throw std::invalid_argument("Matrices must be of the same size");
    }
    // השוואת האיברים אחד אחד
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] < other.matrix[i][j]) {
                return true;
            }
            if (matrix[i][j] > other.matrix[i][j]) {
                return false;
            }
        }
    }
    return false;  // המטריצות שוות
}

// אופרטור גדול מ-
bool SquareMat::operator>(const SquareMat& other) const {
    return other < *this;
}

// אופרטור קטן או שווה ל-
bool SquareMat::operator<=(const SquareMat& other) const {
    return !(other < *this);
}

// אופרטור גדול או שווה ל-
bool SquareMat::operator>=(const SquareMat& other) const {
    return !(*this < other);
}

// אופרטורים נוספים
// אופרטור חזקה
SquareMat SquareMat::operator^(int power) const {
    // בדיקת תקינות החזקה
    if (power < 0) {
        throw std::invalid_argument("Power cannot be negative");
    }
    // אם החזקה היא 0, מחזירים מטריצת יחידה
    if (power == 0) {
        SquareMat result(size);
        for (int i = 0; i < size; i++) {
            result.matrix[i][i] = 1;
        }
        return result;
    }
    // אם החזקה היא 1, מחזירים את המטריצה המקורית
    if (power == 1) {
        return *this;
    }
    // חישוב החזקה
    SquareMat result = *this;
    SquareMat base = *this;
    power--;  // כבר הכפלנו פעם אחת
    while (power > 0) {
        if (power % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        power /= 2;
    }
    return result;
}

// אופרטור טרנספוז
SquareMat SquareMat::operator~() const {
    // יצירת מטריצה חדשה
    SquareMat result(size);
    // החלפת שורות ועמודות
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.matrix[i][j] = matrix[j][i];
        }
    }
    return result;
}

// אופרטור דטרמיננטה
double SquareMat::operator!() const {
    return calculateDeterminant();
}

// Proxy classes for safe element access

double& SquareMat::RowProxy::operator[](int col) {
    if (col < 0 || col >= mat.size) {
        throw std::out_of_range("Column index out of range");
    }
    return mat.matrix[row][col];
}

const double& SquareMat::ConstRowProxy::operator[](int col) const {
    if (col < 0 || col >= mat.size) {
        throw std::out_of_range("Column index out of range");
    }
    return mat.matrix[row][col];
}

SquareMat::RowProxy SquareMat::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Row index out of range");
    }
    return RowProxy(*this, index);
}

SquareMat::ConstRowProxy SquareMat::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Row index out of range");
    }
    return ConstRowProxy(*this, index);
}

// אופרטורי הגדלה והקטנה
// אופרטור הגדלה (prefix)
SquareMat& SquareMat::operator++() {
    // הגדלת כל האיברים באחד
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j]++;
        }
    }
    return *this;
}

// אופרטור הגדלה (postfix)
SquareMat SquareMat::operator++(int) {
    // שמירת המטריצה המקורית
    SquareMat temp(*this);
    // הגדלת המטריצה
    ++(*this);
    // החזרת המטריצה המקורית
    return temp;
}

// אופרטור הקטנה (prefix)
SquareMat& SquareMat::operator--() {
    // הקטנת כל האיברים באחד
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j]--;
        }
    }
    return *this;
}

// אופרטור הקטנה (postfix)
SquareMat SquareMat::operator--(int) {
    // שמירת המטריצה המקורית
    SquareMat temp(*this);
    // הקטנת המטריצה
    --(*this);
    // החזרת המטריצה המקורית
    return temp;
}

// פונקציות עזר
// שינוי גודל המטריצה
void SquareMat::setSize(int newSize) {
    // בדיקת תקינות הגודל החדש
    if (newSize < 0) {
        throw std::invalid_argument("Matrix size cannot be negative");
    }
    // שחרור הזיכרון הקיים
    deallocateMemory();
    // עדכון הגודל
    size = newSize;
    // הקצאת זיכרון חדש
    allocateMemory();
}

// הגדרת ערך באיבר ספציפי
void SquareMat::setValue(int i, int j, double value) {
    // בדיקת תקינות האינדקסים
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw std::out_of_range("Index out of range");
    }
    matrix[i][j] = value;
}

// קבלת ערך מאיבר ספציפי
double SquareMat::getValue(int i, int j) const {
    // בדיקת תקינות האינדקסים
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw std::out_of_range("Index out of range");
    }
    return matrix[i][j];
}

// חישוב דטרמיננטה
double SquareMat::calculateDeterminant() const {
    // מקרים מיוחדים
    if (size == 0) return 0;
    if (size == 1) return matrix[0][0];
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    
    // חישוב דטרמיננטה למטריצות גדולות יותר
    // שימוש בפיתוח לפי שורה ראשונה
    double det = 0;
    for (int j = 0; j < size; j++) {
        // יצירת מטריצה קטנה יותר
        SquareMat subMatrix(size - 1);
        // העתקת האיברים הרלוונטיים
        for (int i = 1; i < size; i++) {
            for (int k = 0; k < size; k++) {
                if (k < j) {
                    subMatrix.matrix[i-1][k] = matrix[i][k];
                } else if (k > j) {
                    subMatrix.matrix[i-1][k-1] = matrix[i][k];
                }
            }
        }
        // חישוב הדטרמיננטה באופן רקורסיבי
        det += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * subMatrix.calculateDeterminant();
    }
    return det;
}

// אופרטורים חיצוניים
// כפל סקלר משמאל
SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar;
}

// כפל סקלר מימין
SquareMat operator*(const SquareMat& mat, double scalar) {
    // יצירת מטריצה חדשה
    SquareMat result(mat);
    // כפל כל איבר בסקלר
    for (int i = 0; i < mat.getSize(); i++) {
        for (int j = 0; j < mat.getSize(); j++) {
            result[i][j] *= scalar;
        }
    }
    return result;
}

// אופרטור הדפסה
std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    // הדפסת כל שורה
    for (int i = 0; i < mat.getSize(); i++) {
        // הדפסת כל איבר בשורה
        for (int j = 0; j < mat.getSize(); j++) {
            os << mat[i][j] << " ";
        }
        // מעבר לשורה חדשה
        os << std::endl;
    }
    return os;
}

} // namespace Matrix
