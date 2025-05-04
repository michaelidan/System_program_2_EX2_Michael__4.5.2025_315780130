// michael9090124@gmail.com

#include "SquareMat.h"
#include <iostream>

using namespace Matrix;

int main() {
    try {
        // יצירת שתי מטריצות בגודל 3x3
        // מטריצה ראשונה: כל איבר הוא סכום האינדקסים שלו
        // מטריצה שנייה: כל איבר הוא מכפלת האינדקסים שלו
        SquareMat mat1(3);
        SquareMat mat2(3);

        // מילוי המטריצות בערכים
        // מטריצה ראשונה: mat1[i][j] = i + j
        // מטריצה שנייה: mat2[i][j] = i * j
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat1[i][j] = i + j;  // מטריצה ראשונה: סכום האינדקסים
                mat2[i][j] = i * j;  // מטריצה שנייה: מכפלת האינדקסים
            }
        }

        // הדפסת המטריצות המקוריות
        // מטריצה ראשונה תראה כך:
        // 0 1 2
        // 1 2 3
        // 2 3 4
        std::cout << "Matrix 1:" << std::endl;
        std::cout << mat1 << std::endl;

        // מטריצה שנייה תראה כך:
        // 0 0 0
        // 0 1 2
        // 0 2 4
        std::cout << "Matrix 2:" << std::endl;
        std::cout << mat2 << std::endl;

        // הדגמת חיבור מטריצות
        // כל איבר במטריצה החדשה הוא סכום האיברים המתאימים בשתי המטריצות
        SquareMat sum = mat1 + mat2;
        std::cout << "Matrix 1 + Matrix 2:" << std::endl;
        std::cout << sum << std::endl;

        // הדגמת חיסור מטריצות
        // כל איבר במטריצה החדשה הוא הפרש האיברים המתאימים בשתי המטריצות
        SquareMat diff = mat1 - mat2;
        std::cout << "Matrix 1 - Matrix 2:" << std::endl;
        std::cout << diff << std::endl;

        // הדגמת כפל מטריצות
        // כל איבר במטריצה החדשה הוא מכפלה סקלרית של השורה המתאימה במטריצה הראשונה
        // והעמודה המתאימה במטריצה השנייה
        SquareMat prod = mat1 * mat2;
        std::cout << "Matrix 1 * Matrix 2:" << std::endl;
        std::cout << prod << std::endl;

        // הדגמת כפל בסקלר
        // כל איבר במטריצה החדשה הוא מכפלת האיבר המתאים במטריצה המקורית בסקלר
        SquareMat scalarProd = mat1 * 2.0;
        std::cout << "Matrix 1 * 2.0:" << std::endl;
        std::cout << scalarProd << std::endl;

        // הדגמת כפל איברי
        // כל איבר במטריצה החדשה הוא מכפלת האיברים המתאימים בשתי המטריצות
        SquareMat elemProd = mat1 % mat2;
        std::cout << "Matrix 1 % Matrix 2:" << std::endl;
        std::cout << elemProd << std::endl;

        // הדגמת מודולו
        // כל איבר במטריצה החדשה הוא שארית החלוקה של האיבר המתאים במטריצה המקורית במספר
        SquareMat mod = mat1 % 3;
        std::cout << "Matrix 1 % 3:" << std::endl;
        std::cout << mod << std::endl;

        // הדגמת חזקה
        // המטריצה החדשה היא מכפלת המטריצה המקורית בעצמה מספר פעמים
        // במקרה זה, mat1^2 = mat1 * mat1
        SquareMat power = mat1 ^ 2;
        std::cout << "Matrix 1 ^ 2:" << std::endl;
        std::cout << power << std::endl;

        // הדגמת טרנספוז
        // המטריצה החדשה היא הטרנספוז של המטריצה המקורית
        // כלומר, השורות הופכות לעמודות והעמודות הופכות לשורות
        SquareMat trans = ~mat1;
        std::cout << "~Matrix 1:" << std::endl;
        std::cout << trans << std::endl;

        // הדגמת חישוב דטרמיננטה
        // הדטרמיננטה היא מספר המאפיין את המטריצה
        // למטריצה 3x3, הדטרמיננטה מחושבת לפי נוסחת סרוס
        double det = !mat1;
        std::cout << "Determinant of Matrix 1: " << det << std::endl;

        // הדגמת הגדלה והקטנה
        // הגדלת כל איברי המטריצה באחד
        ++mat1;
        std::cout << "++Matrix 1:" << std::endl;
        std::cout << mat1 << std::endl;

        // הקטנת כל איברי המטריצה באחד
        --mat1;
        std::cout << "--Matrix 1:" << std::endl;
        std::cout << mat1 << std::endl;

        // הדגמת השוואות
        // השוואת מטריצות לפי סכום האיברים
        std::cout << "Matrix 1 == Matrix 2: " << (mat1 == mat2) << std::endl;
        std::cout << "Matrix 1 != Matrix 2: " << (mat1 != mat2) << std::endl;
        std::cout << "Matrix 1 < Matrix 2: " << (mat1 < mat2) << std::endl;
        std::cout << "Matrix 1 > Matrix 2: " << (mat1 > mat2) << std::endl;

    } catch (const std::exception& e) {
        // טיפול בשגיאות
        // במקרה של שגיאה (למשל, חילוק באפס או גודל לא תקין),
        // נדפיס הודעת שגיאה ונחזיר 1
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // החזרת 0 בסיום תקין של התוכנית
    return 0;
} 
