// michael9090124@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.h"

using namespace Matrix;

// בדיקות בנאים
TEST_CASE("Matrix Construction") {
    SUBCASE("Default Construction") {
        // בדיקת יצירת מטריצה ריקה
        SquareMat mat(0);
        CHECK(mat.getSize() == 0);
    }

    SUBCASE("Size Construction") {
        // בדיקת יצירת מטריצה בגודל נתון
        SquareMat mat(3);
        CHECK(mat.getSize() == 3);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                CHECK(mat[i][j] == 0);
            }
        }
    }

    SUBCASE("Copy Construction") {
        // בדיקת העתקת מטריצה
        SquareMat mat1(2);
        mat1[0][0] = 1;
        mat1[0][1] = 2;
        mat1[1][0] = 3;
        mat1[1][1] = 4;

        SquareMat mat2(mat1);
        CHECK(mat2.getSize() == 2);
        CHECK(mat2[0][0] == 1);
        CHECK(mat2[0][1] == 2);
        CHECK(mat2[1][0] == 3);
        CHECK(mat2[1][1] == 4);
    }
}

// בדיקות פעולות על מטריצות
TEST_CASE("Matrix Operations") {
    // יצירת מטריצות לבדיקות
    SquareMat mat1(2);
    SquareMat mat2(2);

    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;

    mat2[0][0] = 5;
    mat2[0][1] = 6;
    mat2[1][0] = 7;
    mat2[1][1] = 8;

    SUBCASE("Addition") {
        // בדיקת חיבור מטריצות
        SquareMat result = mat1 + mat2;
        CHECK(result[0][0] == 6);
        CHECK(result[0][1] == 8);
        CHECK(result[1][0] == 10);
        CHECK(result[1][1] == 12);
    }

    SUBCASE("Subtraction") {
        // בדיקת חיסור מטריצות
        SquareMat result = mat1 - mat2;
        CHECK(result[0][0] == -4);
        CHECK(result[0][1] == -4);
        CHECK(result[1][0] == -4);
        CHECK(result[1][1] == -4);
    }

    SUBCASE("Multiplication") {
        // בדיקת כפל מטריצות
        SquareMat result = mat1 * mat2;
        CHECK(result[0][0] == 19);
        CHECK(result[0][1] == 22);
        CHECK(result[1][0] == 43);
        CHECK(result[1][1] == 50);
    }

    SUBCASE("Scalar Multiplication") {
        // בדיקת כפל בסקלר
        SquareMat result = mat1 * 2.0;
        CHECK(result[0][0] == 2);
        CHECK(result[0][1] == 4);
        CHECK(result[1][0] == 6);
        CHECK(result[1][1] == 8);
    }

    SUBCASE("Element-wise Multiplication") {
        // בדיקת כפל איברי
        SquareMat result = mat1 % mat2;
        CHECK(result[0][0] == 5);
        CHECK(result[0][1] == 12);
        CHECK(result[1][0] == 21);
        CHECK(result[1][1] == 32);
    }

    SUBCASE("Modulo") {
        // בדיקת מודולו
        SquareMat result = mat1 % 3;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 2);
        CHECK(result[1][0] == 0);
        CHECK(result[1][1] == 1);
    }

    SUBCASE("Power") {
        // בדיקת חזקה
        SquareMat result = mat1 ^ 2;
        CHECK(result[0][0] == 7);
        CHECK(result[0][1] == 10);
        CHECK(result[1][0] == 15);
        CHECK(result[1][1] == 22);
    }

    SUBCASE("Transpose") {
        // בדיקת טרנספוז
        SquareMat result = ~mat1;
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 3);
        CHECK(result[1][0] == 2);
        CHECK(result[1][1] == 4);
    }

    SUBCASE("Determinant") {
        // בדיקת דטרמיננטה
        double det = !mat1;
        CHECK(det == -2);
    }

    SUBCASE("Increment/Decrement") {
        // בדיקת הגדלה והקטנה
        ++mat1;
        CHECK(mat1[0][0] == 2);
        CHECK(mat1[0][1] == 3);
        CHECK(mat1[1][0] == 4);
        CHECK(mat1[1][1] == 5);

        --mat1;
        CHECK(mat1[0][0] == 1);
        CHECK(mat1[0][1] == 2);
        CHECK(mat1[1][0] == 3);
        CHECK(mat1[1][1] == 4);
    }

    SUBCASE("Comparison") {
        // בדיקת השוואות
        SquareMat mat3(2);
        mat3[0][0] = 1;
        mat3[0][1] = 2;
        mat3[1][0] = 3;
        mat3[1][1] = 4;

        CHECK(mat1 == mat3);
        CHECK(!(mat1 == mat2));
        CHECK(mat1 != mat2);
        CHECK(!(mat1 != mat3));
        CHECK(mat1 < mat2);
        CHECK(!(mat2 < mat1));
        CHECK(mat2 > mat1);
        CHECK(!(mat1 > mat2));
    }
}

// בדיקות טיפול בשגיאות
TEST_CASE("Error Handling") {
    SUBCASE("Invalid Size") {
        // בדיקת גודל לא תקין
        CHECK_THROWS_AS(SquareMat(-1), std::invalid_argument);
    }

    SUBCASE("Size Mismatch") {
        // בדיקת אי-התאמה בגדלים
        SquareMat mat1(2);
        SquareMat mat2(3);
        CHECK_THROWS_AS(mat1 + mat2, std::invalid_argument);
        CHECK_THROWS_AS(mat1 - mat2, std::invalid_argument);
        CHECK_THROWS_AS(mat1 * mat2, std::invalid_argument);
        CHECK_THROWS_AS(mat1 % mat2, std::invalid_argument);
    }

    SUBCASE("Division by Zero") {
        // בדיקת חילוק באפס
        SquareMat mat(2);
        CHECK_THROWS_AS(mat / 0.0, std::invalid_argument);
    }

    SUBCASE("Modulo by Zero") {
        // בדיקת מודולו באפס
        SquareMat mat(2);
        CHECK_THROWS_AS(mat % 0, std::invalid_argument);
    }

    SUBCASE("Invalid Power") {
        // בדיקת חזקה לא תקינה
        SquareMat mat(2);
        CHECK_THROWS_AS(mat ^ -1, std::invalid_argument);
    }

    SUBCASE("Index Out of Range") {
        // בדיקת אינדקסים מחוץ לטווח
        SquareMat mat(2);
        CHECK_THROWS_AS(mat[2][0], std::out_of_range);
        CHECK_THROWS_AS(mat[0][2], std::out_of_range);
        CHECK_THROWS_AS(mat[-1][0], std::out_of_range);
        CHECK_THROWS_AS(mat[0][-1], std::out_of_range);
    }
}

// בדיקת בנאי עם גודל התחלתי
TEST_CASE("Constructor with size") {
    // יצירת מטריצה בגודל 3x3
    SquareMat mat(3);
    // בדיקה שהגודל נכון
    CHECK(mat.getSize() == 3);
    // בדיקה שכל האיברים מאותחלים ל-0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat[i][j] == 0);
        }
    }
}

// בדיקת בנאי העתקה
TEST_CASE("Copy constructor") {
    // יצירת מטריצה מקורית
    SquareMat mat1(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
        }
    }
    // יצירת מטריצה חדשה על ידי העתקה
    SquareMat mat2(mat1);
    // בדיקה שהגודל נכון
    CHECK(mat2.getSize() == 3);
    // בדיקה שכל האיברים הועתקו נכון
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat2[i][j] == mat1[i][j]);
        }
    }
}

// בדיקת אופרטור השמה
TEST_CASE("Assignment operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצה הראשונה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
        }
    }
    // העתקת המטריצה הראשונה לשנייה
    mat2 = mat1;
    // בדיקה שכל האיברים הועתקו נכון
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat2[i][j] == mat1[i][j]);
        }
    }
}

// בדיקת אופרטור חיבור והשמה
TEST_CASE("Addition assignment operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // חיבור המטריצות
    mat1 += mat2;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat1[i][j] == (i + j) + (i * j));
        }
    }
}

// בדיקת אופרטור חיסור והשמה
TEST_CASE("Subtraction assignment operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // חיסור המטריצות
    mat1 -= mat2;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat1[i][j] == (i + j) - (i * j));
        }
    }
}

// בדיקת אופרטור כפל והשמה
TEST_CASE("Multiplication assignment operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // כפל המטריצות
    mat1 *= mat2;
    // בדיקה שהתוצאה נכונה
    // חישוב התוצאה הצפויה
    double expected[3][3] = {
        {0, 0, 0},
        {0, 2, 4},
        {0, 4, 8}
    };
    // השוואת התוצאה עם הצפוי
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat1[i][j] == expected[i][j]);
        }
    }
}

// בדיקת אופרטור חילוק והשמה
TEST_CASE("Division assignment operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = (i + j) * 2;
        }
    }
    // חילוק בסקלר
    mat /= 2.0;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat[i][j] == (i + j));
        }
    }
}

// בדיקת אופרטור כפל איברי והשמה
TEST_CASE("Element-wise multiplication assignment operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // כפל איברי
    mat1 %= mat2;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat1[i][j] == (i + j) * (i * j));
        }
    }
}

// בדיקת אופרטור מודולו והשמה
TEST_CASE("Modulo assignment operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j + 1;
        }
    }
    // חישוב מודולו
    mat %= 3;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat[i][j] == (i + j + 1) % 3);
        }
    }
}

// בדיקות אופרטורים אריתמטיים
// בדיקת אופרטור חיבור
TEST_CASE("Addition operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // חיבור המטריצות
    SquareMat result = mat1 + mat2;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j) + (i * j));
        }
    }
}

// בדיקת אופרטור חיסור
TEST_CASE("Subtraction operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // חיסור המטריצות
    SquareMat result = mat1 - mat2;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j) - (i * j));
        }
    }
}

// בדיקת אופרטור כפל מטריצות
TEST_CASE("Multiplication operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // כפל המטריצות
    SquareMat result = mat1 * mat2;
    // בדיקה שהתוצאה נכונה
    // חישוב התוצאה הצפויה
    double expected[3][3] = {
        {0, 0, 0},
        {0, 2, 4},
        {0, 4, 8}
    };
    // השוואת התוצאה עם הצפוי
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == expected[i][j]);
        }
    }
}

// בדיקת אופרטור חילוק בסקלר
TEST_CASE("Division operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = (i + j) * 2;
        }
    }
    // חילוק בסקלר
    SquareMat result = mat / 2.0;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j));
        }
    }
}

// בדיקת אופרטור כפל איברי
TEST_CASE("Element-wise multiplication operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // כפל איברי
    SquareMat result = mat1 % mat2;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j) * (i * j));
        }
    }
}

// בדיקת אופרטור מודולו
TEST_CASE("Modulo operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j + 1;
        }
    }
    // חישוב מודולו
    SquareMat result = mat % 3;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j + 1) % 3);
        }
    }
}

// בדיקת אופרטור מינוס אונארי
TEST_CASE("Unary minus operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // היפוך סימן
    SquareMat result = -mat;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == -(i + j));
        }
    }
}

// בדיקות אופרטורי השוואה
// בדיקת אופרטור שוויון
TEST_CASE("Equality operator") {
    // יצירת שתי מטריצות זהות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים זהים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = mat2[i][j] = i + j;
        }
    }
    // בדיקת שוויון
    CHECK(mat1 == mat2);
}

// בדיקת אופרטור אי-שוויון
TEST_CASE("Inequality operator") {
    // יצירת שתי מטריצות שונות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים שונים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j;
        }
    }
    // בדיקת אי-שוויון
    CHECK(mat1 != mat2);
}

// בדיקת אופרטור קטן מ-
TEST_CASE("Less than operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j + 1;
        }
    }
    // בדיקת השוואה
    CHECK(mat1 < mat2);
}

// בדיקת אופרטור גדול מ-
TEST_CASE("Greater than operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j + 1;
            mat2[i][j] = i * j;
        }
    }
    // בדיקת השוואה
    CHECK(mat1 > mat2);
}

// בדיקת אופרטור קטן או שווה ל-
TEST_CASE("Less than or equal operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i * j + 1;
        }
    }
    // בדיקת השוואה
    CHECK(mat1 <= mat2);
}

// בדיקת אופרטור גדול או שווה ל-
TEST_CASE("Greater than or equal operator") {
    // יצירת שתי מטריצות
    SquareMat mat1(3);
    SquareMat mat2(3);
    // מילוי המטריצות בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat1[i][j] = i + j + 1;
            mat2[i][j] = i * j;
        }
    }
    // בדיקת השוואה
    CHECK(mat1 >= mat2);
}

// בדיקת אופרטור חזקה
TEST_CASE("Power operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // חישוב חזקה
    SquareMat result = mat ^ 2;
    // בדיקה שהתוצאה נכונה
    // חישוב התוצאה הצפויה
    double expected[3][3] = {
        {2, 3, 4},
        {3, 5, 7},
        {4, 7, 10}
    };
    // השוואת התוצאה עם הצפוי
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == expected[i][j]);
        }
    }
}

// בדיקת אופרטור טרנספוז
TEST_CASE("Transpose operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // חישוב טרנספוז
    SquareMat result = ~mat;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == mat[j][i]);
        }
    }
}

// בדיקת אופרטור דטרמיננטה
TEST_CASE("Determinant operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // חישוב דטרמיננטה
    double det = !mat;
    // בדיקה שהתוצאה נכונה
    // חישוב הדטרמיננטה הצפויה
    double expected = 0;
    // השוואת התוצאה עם הצפוי
    CHECK(det == expected);
}

// בדיקות אופרטורי הגדלה והקטנה
// בדיקת אופרטור הגדלה (prefix)
TEST_CASE("Prefix increment operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // הגדלת המטריצה
    ++mat;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat[i][j] == (i + j) + 1);
        }
    }
}

// בדיקת אופרטור הגדלה (postfix)
TEST_CASE("Postfix increment operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // הגדלת המטריצה
    SquareMat result = mat++;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j));
            CHECK(mat[i][j] == (i + j) + 1);
        }
    }
}

// בדיקת אופרטור הקטנה (prefix)
TEST_CASE("Prefix decrement operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // הקטנת המטריצה
    --mat;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(mat[i][j] == (i + j) - 1);
        }
    }
}

// בדיקת אופרטור הקטנה (postfix)
TEST_CASE("Postfix decrement operator") {
    // יצירת מטריצה
    SquareMat mat(3);
    // מילוי המטריצה בערכים
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = i + j;
        }
    }
    // הקטנת המטריצה
    SquareMat result = mat--;
    // בדיקה שהתוצאה נכונה
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK(result[i][j] == (i + j));
            CHECK(mat[i][j] == (i + j) - 1);
        }
    }
}

// בדיקות שגיאות
// בדיקת שגיאת גודל שלילי
TEST_CASE("Negative size error") {
    // ניסיון ליצור מטריצה בגודל שלילי
    CHECK_THROWS_AS(SquareMat(-1), std::invalid_argument);
}

// בדיקת שגיאת חילוק באפס
TEST_CASE("Division by zero error") {
    // יצירת מטריצה
    SquareMat mat(3);
    // ניסיון לחלק באפס
    CHECK_THROWS_AS(mat /= 0.0, std::invalid_argument);
}

// בדיקת שגיאת מודולו באפס
TEST_CASE("Modulo by zero error") {
    // יצירת מטריצה
    SquareMat mat(3);
    // ניסיון לחשב מודולו באפס
    CHECK_THROWS_AS(mat %= 0, std::invalid_argument);
}

// בדיקת שגיאת חזקה שלילית
TEST_CASE("Negative power error") {
    // יצירת מטריצה
    SquareMat mat(3);
    // ניסיון לחשב חזקה שלילית
    CHECK_THROWS_AS(mat ^ -1, std::invalid_argument);
}

// בדיקת שגיאת אינדקס מחוץ לטווח
TEST_CASE("Index out of range error") {
    // יצירת מטריצה
    SquareMat mat(3);
    // ניסיון לגשת לאינדקס מחוץ לטווח
    CHECK_THROWS_AS(mat[3][0], std::out_of_range);
    CHECK_THROWS_AS(mat[0][3], std::out_of_range);
    CHECK_THROWS_AS(mat[-1][0], std::out_of_range);
    CHECK_THROWS_AS(mat[0][-1], std::out_of_range);
}

// בדיקת שגיאת גודל לא תואם
TEST_CASE("Size mismatch error") {
    // יצירת שתי מטריצות בגדלים שונים
    SquareMat mat1(3);
    SquareMat mat2(2);
    // ניסיון לבצע פעולות על מטריצות בגדלים שונים
    CHECK_THROWS_AS(mat1 + mat2, std::invalid_argument);
    CHECK_THROWS_AS(mat1 - mat2, std::invalid_argument);
    CHECK_THROWS_AS(mat1 * mat2, std::invalid_argument);
    CHECK_THROWS_AS(mat1 %= mat2, std::invalid_argument);
} 
