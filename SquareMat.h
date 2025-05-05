// michael9090124@gmail.com

#ifndef SQUARE_MAT_H
#define SQUARE_MAT_H

#include <iostream>

// מרחב השמות Matrix מכיל את כל הקוד הקשור למטריצות
namespace Matrix {

// מחלקה המייצגת מטריצה ריבועית של מספרים ממשיים
// מטריצה ריבועית היא מטריצה שיש לה אותו מספר שורות ועמודות
class SquareMat {
private:
    // מערך דו-מימדי המייצג את המטריצה
    // matrix[i][j] מייצג את האיבר בשורה i ועמודה j
    double** matrix;
    
    // גודל המטריצה (מספר השורות/עמודות)
    // למשל, אם size = 3, אז המטריצה היא 3x3
    int size;

    // פונקציות עזר פרטיות
    // הקצאת זיכרון למטריצה בגודל size x size
    // כל האיברים מאותחלים ל-0
    void allocateMemory();
    
    // שחרור הזיכרון שהוקצה למטריצה
    // חשוב לקרוא לפונקציה זו לפני מחיקת המטריצה
    void deallocateMemory();
    
    // העתקת ערכים ממטריצה אחרת
    // הפונקציה מניחה שהמטריצה הנוכחית כבר הוקצה זיכרון
    void copyMatrix(const SquareMat& other);
    
    // חישוב הדטרמיננטה של המטריצה
    // הדטרמיננטה היא מספר המאפיין את המטריצה
    double calculateDeterminant() const;

public:
    // בנאים
    // בנאי עם גודל התחלתי
    // אם לא מצוין גודל, נוצרת מטריצה ריקה (גודל 0)
    SquareMat(int size = 0);
    
    // בנאי העתקה - יוצר מטריצה חדשה זהה למטריצה אחרת
    SquareMat(const SquareMat& other);
    
    // מחלץ - משחרר את הזיכרון שהוקצה למטריצה
    ~SquareMat();

    // אופרטורי השמה
    // אופרטור השמה - מעתיק מטריצה אחרת למטריצה הנוכחית
    SquareMat& operator=(const SquareMat& other);
    
    // אופרטור חיבור והשמה - מוסיף מטריצה אחרת למטריצה הנוכחית
    SquareMat& operator+=(const SquareMat& other);
    
    // אופרטור חיסור והשמה - מחסר מטריצה אחרת מהמטריצה הנוכחית
    SquareMat& operator-=(const SquareMat& other);
    
    // אופרטור כפל והשמה - מכפיל את המטריצה הנוכחית במטריצה אחרת
    SquareMat& operator*=(const SquareMat& other);
    
    // אופרטור חילוק והשמה - מחלק את כל איברי המטריצה במספר
    SquareMat& operator/=(double scalar);
    
    // אופרטור כפל איברי והשמה - מכפיל כל איבר באיבר המתאים במטריצה אחרת
    SquareMat& operator%=(const SquareMat& other);
    
    // אופרטור מודולו והשמה - מחשב את המודולו של כל איבר במספר
    SquareMat& operator%=(int scalar);

    // אופרטורים אריתמטיים
    // אופרטור חיבור - מחזיר מטריצה חדשה שהיא סכום שתי מטריצות
    SquareMat operator+(const SquareMat& other) const;
    
    // אופרטור חיסור - מחזיר מטריצה חדשה שהיא הפרש שתי מטריצות
    SquareMat operator-(const SquareMat& other) const;
    
    // אופרטור כפל מטריצות - מחזיר מטריצה חדשה שהיא מכפלת שתי מטריצות
    SquareMat operator*(const SquareMat& other) const;
    
    // אופרטור חילוק בסקלר - מחזיר מטריצה חדשה שכל איבריה מחולקים במספר
    SquareMat operator/(double scalar) const;
    
    // אופרטור כפל איברי - מחזיר מטריצה חדשה שכל איבריה הם מכפלת האיברים המתאימים
    SquareMat operator%(const SquareMat& other) const;
    
    // אופרטור מודולו - מחזיר מטריצה חדשה שכל איבריה הם המודולו של האיברים המקוריים
    SquareMat operator%(int scalar) const;
    
    // אופרטור מינוס אונארי - מחזיר מטריצה חדשה שכל איבריה הם הנגדיים של האיברים המקוריים
    SquareMat operator-() const;

    // אופרטורי השוואה
    // אופרטור שוויון - משווה בין שתי מטריצות לפי סכום האיברים
    bool operator==(const SquareMat& other) const;
    
    // אופרטור אי-שוויון - מחזיר את ההיפך מאופרטור השוויון
    bool operator!=(const SquareMat& other) const;
    
    // אופרטור קטן מ- - משווה בין סכומי האיברים של שתי מטריצות
    bool operator<(const SquareMat& other) const;
    
    // אופרטור גדול מ- - מחזיר את ההיפך מאופרטור קטן מ-
    bool operator>(const SquareMat& other) const;
    
    // אופרטור קטן או שווה ל- - מחזיר את ההיפך מאופרטור גדול מ-
    bool operator<=(const SquareMat& other) const;
    
    // אופרטור גדול או שווה ל- - מחזיר את ההיפך מאופרטור קטן מ-
    bool operator>=(const SquareMat& other) const;

    // אופרטורים נוספים
    // אופרטור חזקה - מעלה את המטריצה בחזקה נתונה
    // למשל, mat^2 מחשב את mat*mat
    SquareMat operator^(int power) const;
    
    // אופרטור טרנספוז - מחזיר מטריצה חדשה שהיא הטרנספוז של המטריצה המקורית
    // בטרנספוז, השורות הופכות לעמודות והעמודות הופכות לשורות
    SquareMat operator~() const;
    
    // אופרטור דטרמיננטה - מחשב את הדטרמיננטה של המטריצה
    double operator!() const;
    
    // אופרטור גישה לאיברים - מאפשר גישה לאיבר ספציפי במטריצה
    // למשל, mat[i][j] מחזיר את האיבר בשורה i ועמודה j
    class RowProxy {
        SquareMat& mat;
        int row;
    public:
        RowProxy(SquareMat& m, int r) : mat(m), row(r) {}
        double& operator[](int col);
    };
    class ConstRowProxy {
        const SquareMat& mat;
        int row;
    public:
        ConstRowProxy(const SquareMat& m, int r) : mat(m), row(r) {}
        const double& operator[](int col) const;
    };
    RowProxy operator[](int index);
    ConstRowProxy operator[](int index) const;

    // אופרטורי הגדלה והקטנה
    // אופרטור הגדלה (prefix) - מגדיל את כל איברי המטריצה באחד
    SquareMat& operator++();
    
    // אופרטור הגדלה (postfix) - מגדיל את כל איברי המטריצה באחד
    // מחזיר את המטריצה המקורית לפני ההגדלה
    SquareMat operator++(int);
    
    // אופרטור הקטנה (prefix) - מקטין את כל איברי המטריצה באחד
    SquareMat& operator--();
    
    // אופרטור הקטנה (postfix) - מקטין את כל איברי המטריצה באחד
    // מחזיר את המטריצה המקורית לפני ההקטנה
    SquareMat operator--(int);

    // פונקציות עזר
    // מחזירה את גודל המטריצה
    int getSize() const { return size; }
    
    // משנה את גודל המטריצה
    // אם הגודל החדש שונה מהנוכחי, כל האיברים מאותחלים ל-0
    void setSize(int newSize);
    
    // משנה את הערך של איבר ספציפי במטריצה
    void setValue(int i, int j, double value);
    
    // מחזירה את הערך של איבר ספציפי במטריצה
    double getValue(int i, int j) const;
};

// אופרטורים חיצוניים
// אופרטור כפל סקלר משמאל - מכפיל את כל איברי המטריצה במספר
// למשל, 2 * mat מכפיל את כל איברי mat ב-2
SquareMat operator*(double scalar, const SquareMat& mat);

// אופרטור כפל סקלר מימין - מכפיל את כל איברי המטריצה במספר
// למשל, mat * 2 מכפיל את כל איברי mat ב-2
SquareMat operator*(const SquareMat& mat, double scalar);

// אופרטור הדפסה - מדפיס את המטריצה בצורה מסודרת
// למשל, cout << mat מדפיס את המטריצה
std::ostream& operator<<(std::ostream& os, const SquareMat& mat);

} // namespace Matrix

#endif // SQUARE_MAT_H 
