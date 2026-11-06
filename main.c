/*
 * CodeQuest - an interactive C / C++ learning app
 * Written in C with raylib.
 *
 * Features: lessons with syntax-highlighted code, quizzes with explanations,
 * progress tracking saved to progress.dat, mouse + keyboard navigation.
 *
 * Build (Linux):   gcc main.c -o codequest -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
 * Build (macOS):   gcc main.c -o codequest -lraylib -framework OpenGL -framework Cocoa -framework IOKit
 * Build (Windows): gcc main.c -o codequest.exe -lraylib -lopengl32 -lgdi32 -lwinmm
 *
 * Controls: mouse to click, mouse wheel to scroll, LEFT/RIGHT arrows to change
 *           lesson page, ESC to go back (or quit from the menu).
 */

#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define W 1100
#define H 720
#define NLESSONS 5

 /* ------------------------------------------------------------------ */
 /*  Data types                                                         */
 /* ------------------------------------------------------------------ */
typedef struct { const char* title, * text, * code; } Page;

typedef struct {
    const char* q;
    const char* opts[4];
    int correct;
    const char* expl;
} Question;

typedef struct {
    const char* name;
    int nPages;
    Page pages[3];
    int nQ;
    Question qs[3];
} Lesson;

/* ------------------------------------------------------------------ */
/*  Lesson content: C                                                  */
/* ------------------------------------------------------------------ */
static const Lesson C_LESSONS[NLESSONS] = {
{ "1. Hello, C!", 2,
  {
    { "The shape of a C program",
      "Every C program starts running at main(). The #include line pulls in a header so the compiler knows about functions like printf. Statements end with a semicolon and blocks are wrapped in { }.\n"
      "Compile with:  gcc hello.c -o hello   then run  ./hello",
      "#include <stdio.h>\n\nint main(void) {\n    printf(\"Hello, World!\\n\");\n    return 0;\n}" },
    { "Variables and types",
      "C is statically typed: you declare a variable's type before using it. Common types are int, float, double and char. printf uses format specifiers: %d for int, %f for float/double, %c for char and %s for strings.\n"
      "scanf reads input and needs the ADDRESS of the variable (&age).",
      "int age = 20;\nfloat gpa = 3.5f;\nchar grade = 'A';\n\nprintf(\"Age: %d\\n\", age);\nprintf(\"GPA: %.1f, grade %c\\n\", gpa, grade);\nscanf(\"%d\", &age);" }
  },
  3,
  {
    { "Which header declares printf?",
      { "<stdlib.h>", "<stdio.h>", "<string.h>", "<math.h>" }, 1,
      "printf, scanf and friends live in <stdio.h> (standard input/output)." },
    { "What does return 0; in main usually signal?",
      { "An error occurred", "The program should loop", "The program finished successfully", "Nothing at all" }, 2,
      "By convention 0 means success; non-zero values tell the OS something went wrong." },
    { "Which format specifier prints an int?",
      { "%f", "%c", "%s", "%d" }, 3,
      "%d prints a decimal int. %f is for floating point, %c for a char, %s for a string." }
  }
},
{ "2. Control Flow", 2,
  {
    { "Decisions: if, else and switch",
      "A condition is true when it is non-zero. Use == to compare and = to assign (a classic bug!). Chain choices with else if. switch selects on an int or char; each case needs a break, otherwise execution FALLS THROUGH into the next case.",
      "int score = 72;\n\nif (score >= 70) {\n    printf(\"Pass\\n\");\n} else {\n    printf(\"Fail\\n\");\n}\n\nswitch (grade) {\n    case 'A': printf(\"Great\\n\"); break;\n    default:  printf(\"Keep going\\n\");\n}" },
    { "Loops",
      "for is ideal when you know how many times to repeat; while checks the condition before each pass; do-while always runs at least once. break leaves the loop and continue skips to the next iteration.",
      "for (int i = 0; i < 5; i++) {\n    printf(\"%d \", i);   // 0 1 2 3 4\n}\n\nint n = 3;\nwhile (n > 0) {\n    n--;\n}\n\ndo {\n    printf(\"runs once\\n\");\n} while (0);" }
  },
  3,
  {
    { "How many times does for (int i = 0; i < 5; i++) run?",
      { "4", "5", "6", "Forever" }, 1,
      "i takes the values 0, 1, 2, 3, 4 - that is 5 iterations." },
    { "What happens if a switch case has no break?",
      { "Compile error", "The program exits", "Execution falls through to the next case", "Only that case runs anyway" }, 2,
      "Without break, C keeps executing the statements of the following cases until it hits a break or the end." },
    { "What does if (x = 5) do?",
      { "Compares x with 5", "Assigns 5 to x; the condition is true", "Causes a compile error", "Assigns 5 only if x is 0" }, 1,
      "= is assignment. The expression evaluates to 5 (non-zero), so the condition is always true. You almost certainly meant ==." }
  }
},
{ "3. Functions & Arrays", 2,
  {
    { "Functions",
      "A function has a return type, a name and parameters. Put a prototype before main so the compiler knows the signature. C passes arguments BY VALUE - the function receives a copy.",
      "#include <stdio.h>\n\nint square(int n);   // prototype\n\nint main(void) {\n    printf(\"%d\\n\", square(6));  // 36\n    return 0;\n}\n\nint square(int n) {\n    return n * n;\n}" },
    { "Arrays and strings",
      "Arrays are fixed-size and zero-indexed, and C does NOT check bounds. A string is a char array ended by the null terminator '\\0', so \"Hi\" needs 3 bytes. Use <string.h> for strlen, strcpy and strcmp.",
      "int nums[5] = {10, 20, 30, 40, 50};\nprintf(\"%d\\n\", nums[0]);   // 10\n\nchar name[] = \"Hi\";          // 'H', 'i', '\\0'\nprintf(\"%zu\\n\", strlen(name)); // 2\n\nif (strcmp(name, \"Hi\") == 0) {\n    printf(\"equal\\n\");\n}" }
  },
  3,
  {
    { "What is the index of the first element of an array?",
      { "1", "0", "-1", "It depends" }, 1,
      "C arrays are zero-indexed: nums[0] is the first element." },
    { "How many bytes does char s[] = \"Hi\"; occupy?",
      { "2", "3", "4", "1" }, 1,
      "Two characters plus the null terminator = 3 bytes (strlen would still say 2)." },
    { "How does C pass function arguments?",
      { "By reference", "By value (copies)", "By name", "Always as pointers" }, 1,
      "C is pass-by-value. To modify the caller's variable you pass a pointer to it." }
  }
},
{ "4. Pointers", 2,
  {
    { "Addresses and pointers",
      "A pointer stores a memory address. &x gives the address of x and *p follows the pointer to the value (dereferencing). Declare one with a star: int *p. A pointer that points nowhere should be NULL.",
      "int x = 42;\nint *p = &x;     // p holds x's address\n\nprintf(\"%d\\n\", *p);   // 42\n*p = 7;               // x is now 7\n\nint *q = NULL;        // points to nothing" },
    { "Pointers in action",
      "Passing a pointer lets a function modify the caller's variable. An array name decays to a pointer to its first element, so arr[i] is the same as *(arr + i).",
      "void swap(int *a, int *b) {\n    int tmp = *a;\n    *a = *b;\n    *b = tmp;\n}\n\nint main(void) {\n    int x = 1, y = 2;\n    swap(&x, &y);    // x = 2, y = 1\n    return 0;\n}" }
  },
  3,
  {
    { "What does &x give you?",
      { "The value of x", "The address of x", "The size of x", "A copy of x" }, 1,
      "The & operator gives the memory address of a variable." },
    { "If int *p = &x; what does *p mean?",
      { "The address of p", "The value stored at the address held in p", "p multiplied by something", "A pointer to p" }, 1,
      "*p dereferences the pointer: it reads or writes the value at the address in p." },
    { "Why does swap take int * parameters?",
      { "It is faster", "C has no int", "So it can change the caller's variables", "To avoid using return" }, 2,
      "Arguments are copied, so only by passing addresses can swap change the originals." }
  }
},
{ "5. Structs & Memory", 2,
  {
    { "Structs",
      "A struct groups related fields under one type. Access fields with . on a value and -> on a pointer (p->age is the same as (*p).age). typedef lets you drop the struct keyword.",
      "typedef struct {\n    char name[20];\n    int  age;\n} Student;\n\nStudent s = {\"Ada\", 21};\nStudent *p = &s;\n\nprintf(\"%s %d\\n\", s.name, s.age);\nprintf(\"%d\\n\", p->age);" },
    { "Dynamic memory",
      "malloc reserves bytes on the heap and returns a void * (or NULL on failure). You own that memory: call free exactly once when finished, otherwise you get a memory leak. Never use memory after freeing it.",
      "#include <stdlib.h>\n\nint n = 5;\nint *arr = malloc(n * sizeof(int));\nif (arr == NULL) return 1;\n\nfor (int i = 0; i < n; i++)\n    arr[i] = i * i;\n\nfree(arr);\narr = NULL;" }
  },
  3,
  {
    { "Which operator accesses a member through a struct pointer?",
      { ".", "->", "::", "&" }, 1,
      "p->age is shorthand for (*p).age." },
    { "What does malloc return if it cannot allocate memory?",
      { "0 bytes", "NULL", "-1", "It always crashes" }, 1,
      "Always check the result of malloc against NULL before using it." },
    { "What happens if you never free() memory you malloc'd?",
      { "Nothing, ever", "A memory leak", "A compile error", "A double free" }, 1,
      "The memory stays reserved until the program exits - a leak. In long-running programs leaks add up." }
  }
}
};

/* ------------------------------------------------------------------ */
/*  Lesson content: C++                                                */
/* ------------------------------------------------------------------ */
static const Lesson CPP_LESSONS[NLESSONS] = {
{ "1. C++ Basics", 2,
  {
    { "Hello, C++",
      "C++ uses streams for I/O: std::cout << prints and std::cin >> reads. Standard library names live in the std namespace. Use \"\\n\" or std::endl to end a line.",
      "#include <iostream>\n#include <string>\n\nint main() {\n    std::string name;\n    std::cout << \"Your name? \";\n    std::cin >> name;\n    std::cout << \"Hello, \" << name << \"\\n\";\n    return 0;\n}" },
    { "Strings, auto and bool",
      "std::string replaces fiddly char arrays: it grows automatically and supports + and ==. auto lets the compiler deduce a type, and C++ has a real bool type.\n"
      "Compile with:  g++ -std=c++17 main.cpp -o main",
      "std::string a = \"C\";\nstd::string b = a + \"++\";   // \"C++\"\nauto len = b.size();       // 3\nbool ok = (b == \"C++\");    // true\n\nfor (char c : b) {\n    std::cout << c << ' ';\n}" }
  },
  3,
  {
    { "Which operator sends output to std::cout?",
      { ">>", "<<", "->", "::" }, 1,
      "<< is the stream insertion operator. >> (extraction) is used with std::cin." },
    { "Why prefer std::string over char arrays?",
      { "It is always faster", "It manages memory and length for you", "It needs no header", "C++ forbids char arrays" }, 1,
      "std::string handles allocation, resizing and comparison so you avoid many classic C bugs." },
    { "What does the auto keyword do?",
      { "Deletes the variable automatically", "Lets the compiler deduce the type", "Makes the variable constant", "Declares a pointer" }, 1,
      "With auto the type is deduced from the initialiser: auto n = 5; makes n an int." }
  }
},
{ "2. References & Vectors", 2,
  {
    { "References",
      "A reference is an alias for an existing variable. Unlike a pointer it cannot be null or re-pointed. Passing by reference avoids copies and lets a function modify its argument; use const & for read-only access to large objects.",
      "void addOne(int &n) {\n    n++;\n}\n\nvoid print(const std::string &s) {\n    std::cout << s << \"\\n\";\n}\n\nint x = 5;\naddOne(x);      // x is now 6\nint &r = x;     // r is another name for x" },
    { "std::vector",
      "vector is a resizable array from <vector>. It tracks its own size, grows with push_back and cleans up after itself - no malloc/free needed. Use a range-based for loop to go through it.",
      "#include <vector>\n\nstd::vector<int> v = {3, 1, 4};\nv.push_back(1);\n\nstd::cout << v.size() << \"\\n\";   // 4\nstd::cout << v[0] << \"\\n\";       // 3\n\nfor (int n : v) {\n    std::cout << n << ' ';\n}" }
  },
  3,
  {
    { "What is a reference?",
      { "A copy of a variable", "An alias for an existing variable", "A pointer that can be null", "A new heap allocation" }, 1,
      "A reference is another name for the same variable; changes through it affect the original." },
    { "Which call adds an element to the end of a vector?",
      { "v.add(x)", "v.push_back(x)", "v.append(x)", "v.insert_end(x)" }, 1,
      "push_back appends and grows the vector automatically." },
    { "Why take a parameter as const std::string &s?",
      { "It avoids copying and promises not to modify it", "It is quicker to type", "C++ requires it", "It allows null" }, 0,
      "const & gives cheap read-only access to the caller's object." }
  }
},
{ "3. Classes & Objects", 2,
  {
    { "Classes",
      "A class bundles data and the functions that use it. Members are private by default in a class (public in a struct). A constructor runs automatically when an object is created and initialises its members. Mark methods that don't change the object as const.",
      "class Player {\nprivate:\n    std::string name;\n    int score;\npublic:\n    Player(std::string n) : name(n), score(0) {}\n\n    void addPoints(int p) { score += p; }\n    int getScore() const { return score; }\n};\n\nPlayer p(\"Ada\");\np.addPoints(10);" },
    { "Encapsulation and destructors",
      "Keep data private and expose behaviour through public methods - that is encapsulation. A destructor (~ClassName) runs automatically when an object goes out of scope; it is the place to release resources. This idea is called RAII.",
      "class Buffer {\n    int *data;\npublic:\n    Buffer(int n) { data = new int[n]; }\n    ~Buffer()     { delete[] data; }\n};\n\nint main() {\n    Buffer b(100);   // constructor runs\n}                    // destructor runs here" }
  },
  3,
  {
    { "What is the default access level for members of a class?",
      { "public", "private", "protected", "There is none" }, 1,
      "In a class everything is private unless you say otherwise. In a struct it is public." },
    { "When does a constructor run?",
      { "When the object is created", "When the program ends", "When you call delete", "Only when called manually" }, 0,
      "Constructors run automatically at object creation." },
    { "What does ~Buffer() represent?",
      { "A constructor", "A destructor - cleanup when the object dies", "A copy function", "An operator overload" }, 1,
      "The ~ prefix marks the destructor, which runs when the object is destroyed." }
  }
},
{ "4. Inheritance", 2,
  {
    { "Inheritance",
      "A derived class reuses and extends a base class: class Dog : public Animal. It inherits the public and protected members of the base. Use protected for members that derived classes may use but outside code may not.",
      "class Animal {\npublic:\n    void eat() { std::cout << \"nom\\n\"; }\n};\n\nclass Dog : public Animal {\npublic:\n    void bark() { std::cout << \"woof\\n\"; }\n};\n\nDog d;\nd.eat();    // inherited\nd.bark();" },
    { "Virtual functions",
      "Mark a base method virtual and override it in derived classes. Calling it through a base pointer or reference then runs the derived version (runtime polymorphism). A pure virtual function (= 0) makes the class abstract, and polymorphic bases need a virtual destructor.",
      "class Shape {\npublic:\n    virtual double area() const = 0;   // pure virtual\n    virtual ~Shape() {}\n};\n\nclass Circle : public Shape {\n    double r;\npublic:\n    Circle(double r) : r(r) {}\n    double area() const override { return 3.14159 * r * r; }\n};\n\nShape *s = new Circle(2);\nstd::cout << s->area();\ndelete s;" }
  },
  3,
  {
    { "How do you make Dog publicly inherit from Animal?",
      { "class Dog extends Animal", "class Dog : public Animal", "class Dog -> Animal", "class Dog inherits Animal" }, 1,
      "C++ uses a colon followed by the access specifier and base class name." },
    { "What does the virtual keyword enable?",
      { "Faster function calls", "Calling the derived version through a base pointer", "Private access", "Template instantiation" }, 1,
      "virtual turns on dynamic dispatch, so the actual object's type decides which function runs." },
    { "What makes a class abstract?",
      { "Having a constructor", "Having at least one pure virtual function (= 0)", "Being defined in a header", "Using protected members" }, 1,
      "A class with a pure virtual function cannot be instantiated; derived classes must implement it." }
  }
},
{ "5. Templates & STL", 2,
  {
    { "Templates",
      "Templates let you write code once for many types. The compiler generates a version for every type you use. Standard containers such as vector and map are templates too.",
      "template <typename T>\nT maxOf(T a, T b) {\n    return (a > b) ? a : b;\n}\n\nint main() {\n    std::cout << maxOf(3, 7);        // int\n    std::cout << maxOf(2.5, 1.5);    // double\n}" },
    { "STL containers and algorithms",
      "map stores key/value pairs sorted by key. <algorithm> provides sort, find, count and more, working on iterator ranges. Smart pointers such as std::unique_ptr free memory for you.",
      "#include <map>\n#include <algorithm>\n#include <memory>\n\nstd::map<std::string, int> ages;\nages[\"Ada\"] = 36;\n\nstd::vector<int> v = {5, 2, 9};\nstd::sort(v.begin(), v.end());   // 2 5 9\n\nauto p = std::make_unique<int>(5);   // freed automatically" }
  },
  3,
  {
    { "What does template <typename T> allow?",
      { "Code that works with many types", "Faster loops", "Private data", "Multiple inheritance" }, 0,
      "T is a placeholder type; the compiler fills it in for each use." },
    { "Which container stores key/value pairs sorted by key?",
      { "std::vector", "std::map", "std::string", "std::array" }, 1,
      "std::map keeps its keys sorted and lets you look values up by key." },
    { "What is the main benefit of std::unique_ptr?",
      { "The memory is freed automatically", "It allows null dereferences", "It makes copies cheap", "It is a reference" }, 0,
      "unique_ptr owns its object and deletes it when it goes out of scope - no manual delete." }
  }
}
};

static const Lesson* LESSONS[2] = { C_LESSONS, CPP_LESSONS };
static const char* LANG_NAME[2] = { "C", "C++" };

/* ------------------------------------------------------------------ */
/*  Colours and global state                                           */
/* ------------------------------------------------------------------ */
static const Color BG = { 24, 26, 38, 255 };
static const Color PANEL = { 38, 42, 62, 255 };
static const Color DIM = { 150, 155, 180, 255 };
static const Color GOOD = { 46, 160, 100, 255 };
static const Color BAD = { 200, 70, 80, 255 };
static const Color ACCENTS[2] = { { 88, 130, 255, 255 }, { 255, 125, 100, 255 } };

typedef enum { SCR_MENU, SCR_LESSON, SCR_QUIZ, SCR_RESULT } Screen;

static Screen screen = SCR_MENU;
static int lang = 0, lessonIdx = 0, page = 0;
static int qi = 0, sel = -1, score = 0;
static float scroll = 0.0f;
static bool quit = false;

static struct {
    unsigned char read[2][NLESSONS];
    int best[2][NLESSONS];
} prog;

/* ------------------------------------------------------------------ */
/*  Progress save / load                                               */
/* ------------------------------------------------------------------ */
static void ResetProgress(void)
{
    memset(&prog, 0, sizeof prog);
    for (int l = 0; l < 2; l++)
        for (int i = 0; i < NLESSONS; i++) prog.best[l][i] = -1;
}

static void LoadProgress(void)
{
    ResetProgress();
    FILE* f = fopen("progress.dat", "rb");
    if (!f) return;
    if (fread(&prog, sizeof prog, 1, f) != 1) ResetProgress();
    fclose(f);
}

static void SaveProgress(void)
{
    FILE* f = fopen("progress.dat", "wb");
    if (!f) return;
    fwrite(&prog, sizeof prog, 1, f);
    fclose(f);
}

/* ------------------------------------------------------------------ */
/*  UI helpers                                                         */
/* ------------------------------------------------------------------ */
static bool Button(Rectangle r, const char* label, Color col, int fs)
{
    bool hover = CheckCollisionPointRec(GetMousePosition(), r);
    DrawRectangleRounded(r, 0.3f, 8, hover ? ColorBrightness(col, 0.2f) : col);
    int w = MeasureText(label, fs);
    DrawText(label, (int)(r.x + (r.width - w) / 2), (int)(r.y + (r.height - fs) / 2), fs, WHITE);
    return hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

/* Draw word-wrapped text; '\n' forces a line break. Returns the y after the text. */
static int DrawWrapped(const char* t, int x, int y, int maxW, int fs, Color c)
{
    char line[512] = "";
    int len = 0;
    const char* p = t;
    while (*p) {
        char word[128];
        int wl = 0;
        while (*p && *p != ' ' && *p != '\n' && wl < 127) word[wl++] = *p++;
        word[wl] = 0;

        char test[700];
        snprintf(test, sizeof test, "%s%s%s", line, len ? " " : "", word);
        if (len && MeasureText(test, fs) > maxW) {
            DrawText(line, x, y, fs, c);
            y += fs + 6;
            snprintf(line, sizeof line, "%s", word);
        }
        else {
            snprintf(line, sizeof line, "%s", test);
        }
        len = (int)strlen(line);

        if (*p == '\n') {
            DrawText(line, x, y, fs, c);
            y += fs + 6;
            line[0] = 0;
            len = 0;
            p++;
        }
        else if (*p == ' ') {
            p++;
        }
    }
    if (len) {
        DrawText(line, x, y, fs, c);
        y += fs + 6;
    }
    return y;
}

/* ---- tiny syntax highlighter ---- */
static bool IsKeyword(const char* w)
{
    static const char* kw[] = {
        "int", "char", "float", "double", "void", "bool", "long", "short", "unsigned", "const",
        "static", "struct", "typedef", "enum", "if", "else", "for", "while", "do", "switch",
        "case", "default", "break", "continue", "return", "sizeof", "class", "public",
        "private", "protected", "virtual", "override", "new", "delete", "template",
        "typename", "namespace", "using", "auto", "true", "false", "nullptr", "NULL", NULL
    };
    for (int i = 0; kw[i]; i++)
        if (strcmp(w, kw[i]) == 0) return true;
    return false;
}

static int Tok(const char* s, int len, int x, int y, int fs, Color c)
{
    char buf[256];
    if (len > 255) len = 255;
    memcpy(buf, s, len);
    buf[len] = 0;
    DrawText(buf, x, y, fs, c);
    return MeasureText(buf, fs);
}

static void HighlightLine(const char* line, int x, int y, int fs)
{
    int n = (int)strlen(line), i = 0, f = 0;
    while (line[f] == ' ') f++;
    while (i < n) {
        char c = line[i];
        int j = i + 1;
        Color col = { 215, 218, 235, 255 };
        if (c == ' ') {
            while (j < n && line[j] == ' ') j++;
        }
        else if (c == '#' && i == f) {
            j = n; col = (Color){ 190, 140, 255, 255 };
        }
        else if (c == '/' && i + 1 < n && line[i + 1] == '/') {
            j = n; col = (Color){ 110, 190, 120, 255 };
        }
        else if (c == '"') {
            j = i + 1;
            while (j < n && line[j] != '"') { if (line[j] == '\\') j++; j++; }
            if (j < n) j++;
            if (j > n) j = n;
            col = (Color){ 240, 170, 100, 255 };
        }
        else if (isalpha((unsigned char)c) || c == '_') {
            while (j < n && (isalnum((unsigned char)line[j]) || line[j] == '_')) j++;
            char w[64];
            int wl = j - i;
            if (wl > 63) wl = 63;
            memcpy(w, line + i, wl);
            w[wl] = 0;
            if (IsKeyword(w)) col = (Color){ 100, 160, 255, 255 };
            else if (j < n && line[j] == '(') col = (Color){ 235, 220, 130, 255 };
        }
        else if (isdigit((unsigned char)c)) {
            while (j < n && (isdigit((unsigned char)line[j]) || line[j] == '.')) j++;
            col = (Color){ 130, 220, 220, 255 };
        }
        x += Tok(line + i, j - i, x, y, fs, col);
        i = j;
    }
}

/* Draws a code panel; returns the y below it. */
static int DrawCode(const char* code, int x, int y, int w, int fs)
{
    int lines = 1;
    for (const char* p = code; *p; p++) if (*p == '\n') lines++;
    int lh = fs + 6, h = lines * lh + 24;
    DrawRectangleRounded((Rectangle) { (float)x, (float)y, (float)w, (float)h }, 0.04f, 8, (Color) { 14, 16, 26, 255 });

    int cy = y + 12;
    const char* p = code;
    while (*p) {
        char line[256];
        int n = 0;
        while (*p && *p != '\n' && n < 255) line[n++] = *p++;
        line[n] = 0;
        if (*p == '\n') p++;
        HighlightLine(line, x + 16, cy, fs);
        cy += lh;
    }
    return y + h;
}

static void GoMenu(void) { screen = SCR_MENU; scroll = 0; }

static void StartQuiz(void)
{
    screen = SCR_QUIZ; qi = 0; sel = -1; score = 0;
}

static void StartLesson(int idx)
{
    lessonIdx = idx; page = 0; scroll = 0; screen = SCR_LESSON;
}

/* ------------------------------------------------------------------ */
/*  Screens                                                            */
/* ------------------------------------------------------------------ */
static void DrawMenu(Color accent)
{
    DrawText("CodeQuest", 40, 24, 44, WHITE);
    DrawText("Interactive C & C++ learning app", 42, 76, 20, DIM);

    /* overall progress */
    int done = 0, total = 2 * NLESSONS * 2;
    for (int l = 0; l < 2; l++)
        for (int i = 0; i < NLESSONS; i++) {
            done += prog.read[l][i] ? 1 : 0;
            done += prog.best[l][i] >= 0 ? 1 : 0;
        }
    DrawText(TextFormat("Overall progress: %d%%", done * 100 / total), 720, 34, 20, DIM);
    DrawRectangleRounded((Rectangle) { 720, 66, 340, 14 }, 0.5f, 8, PANEL);
    if (done) DrawRectangleRounded((Rectangle) { 720, 66, 340.0f * done / total, 14 }, 0.5f, 8, accent);

    /* language tabs */
    for (int l = 0; l < 2; l++) {
        Rectangle r = { 40.0f + l * 150, 118, 140, 44 };
        if (Button(r, LANG_NAME[l], l == lang ? ACCENTS[l] : PANEL, 24)) lang = l;
    }

    /* lesson cards */
    for (int i = 0; i < NLESSONS; i++) {
        const Lesson* L = &LESSONS[lang][i];
        float y = 182.0f + i * 100;
        DrawRectangleRounded((Rectangle) { 40, y, 1020, 88 }, 0.15f, 8, PANEL);
        DrawCircle(80, (int)y + 44, 22, accent);
        DrawText(TextFormat("%d", i + 1), 74, (int)y + 33, 24, WHITE);
        DrawText(L->name + 3, 125, (int)y + 14, 26, WHITE);
        DrawText(TextFormat("%d pages  |  %d quiz questions", L->nPages, L->nQ), 125, (int)y + 50, 18, DIM);

        DrawText(prog.read[lang][i] ? "Lesson read" : "Not started", 560, (int)y + 20, 18,
            prog.read[lang][i] ? GOOD : DIM);
        if (prog.best[lang][i] >= 0)
            DrawText(TextFormat("Best quiz: %d/%d", prog.best[lang][i], L->nQ), 560, (int)y + 50, 18, GOOD);
        else
            DrawText("Quiz not taken", 560, (int)y + 50, 18, DIM);

        if (Button((Rectangle) { 810, y + 20, 110, 48 }, "Learn", accent, 22)) StartLesson(i);
        if (Button((Rectangle) { 935, y + 20, 100, 48 }, "Quiz", (Color) { 90, 95, 125, 255 }, 22)) {
            lessonIdx = i; StartQuiz();
        }
    }
}

static void DrawLesson(Color accent)
{
    const Lesson* L = &LESSONS[lang][lessonIdx];
    const Page* P = &L->pages[page];

    /* header */
    if (Button((Rectangle) { 30, 18, 110, 42 }, "< Menu", PANEL, 20)) GoMenu();
    DrawText(TextFormat("%s  -  %s", LANG_NAME[lang], L->name), 160, 26, 26, WHITE);
    const char* pg = TextFormat("Page %d / %d", page + 1, L->nPages);
    DrawText(pg, W - 30 - MeasureText(pg, 20), 30, 20, DIM);
    DrawLine(0, 76, W, 76, PANEL);

    /* scrollable content */
    BeginScissorMode(0, 80, W, 560);
    int y = 96 - (int)scroll;
    DrawText(P->title, 60, y, 32, accent);
    y += 52;
    y = DrawWrapped(P->text, 60, y, 980, 21, (Color) { 225, 228, 240, 255 });
    y += 16;
    y = DrawCode(P->code, 60, y, 980, 20);
    EndScissorMode();

    float maxScroll = (float)(y + (int)scroll - 620);
    if (maxScroll < 0) maxScroll = 0;
    scroll -= GetMouseWheelMove() * 45.0f;
    if (scroll < 0) scroll = 0;
    if (scroll > maxScroll) scroll = maxScroll;

    /* footer */
    DrawLine(0, 648, W, 648, PANEL);
    bool last = (page == L->nPages - 1);
    if (last && !prog.read[lang][lessonIdx]) { prog.read[lang][lessonIdx] = 1; SaveProgress(); }

    if (page > 0 && (Button((Rectangle) { 30, 660, 140, 46 }, "< Previous", PANEL, 20) || IsKeyPressed(KEY_LEFT))) {
        page--; scroll = 0;
    }
    if (!last) {
        if (Button((Rectangle) { W - 170, 660, 140, 46 }, "Next >", accent, 20) || IsKeyPressed(KEY_RIGHT)) {
            page++; scroll = 0;
        }
    }
    else {
        if (Button((Rectangle) { W - 200, 660, 170, 46 }, "Take the quiz", GOOD, 20)) StartQuiz();
    }
}

static void DrawQuiz(Color accent)
{
    const Lesson* L = &LESSONS[lang][lessonIdx];
    const Question* Q = &L->qs[qi];

    if (Button((Rectangle) { 30, 18, 110, 42 }, "< Menu", PANEL, 20)) GoMenu();
    DrawText(TextFormat("Quiz: %s", L->name), 160, 26, 26, WHITE);
    const char* info = TextFormat("Question %d of %d   Score: %d", qi + 1, L->nQ, score);
    DrawText(info, W - 30 - MeasureText(info, 20), 30, 20, DIM);
    DrawRectangle(0, 76, W, 4, PANEL);
    DrawRectangle(0, 76, W * (qi + (sel >= 0 ? 1 : 0)) / L->nQ, 4, accent);

    DrawWrapped(Q->q, 60, 110, 980, 28, WHITE);

    for (int i = 0; i < 4; i++) {
        Rectangle r = { 60, 200.0f + i * 72, 980, 60 };
        bool hover = CheckCollisionPointRec(GetMousePosition(), r);
        Color col = PANEL;
        if (sel < 0 && hover) col = (Color){ 55, 60, 88, 255 };
        if (sel >= 0) {
            if (i == Q->correct) col = GOOD;
            else if (i == sel) col = BAD;
        }
        DrawRectangleRounded(r, 0.2f, 8, col);
        DrawText(TextFormat("%c)   %s", 'A' + i, Q->opts[i]), 84, (int)r.y + 18, 22, WHITE);
        if (sel < 0 && hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            sel = i;
            if (i == Q->correct) score++;
        }
    }

    if (sel >= 0) {
        bool ok = (sel == Q->correct);
        DrawText(ok ? "Correct!" : "Not quite.", 60, 500, 26, ok ? (Color) { 90, 210, 140, 255 } : (Color) { 240, 110, 120, 255 });
        DrawWrapped(Q->expl, 60, 540, 800, 20, (Color) { 215, 218, 235, 255 });

        bool lastQ = (qi == L->nQ - 1);
        if (Button((Rectangle) { W - 200, 640, 160, 50 }, lastQ ? "Finish" : "Next >", accent, 22)) {
            if (lastQ) {
                if (score > prog.best[lang][lessonIdx]) prog.best[lang][lessonIdx] = score;
                SaveProgress();
                screen = SCR_RESULT;
            }
            else {
                qi++; sel = -1;
            }
        }
    }
}

static void DrawResult(Color accent)
{
    const Lesson* L = &LESSONS[lang][lessonIdx];
    const char* t = "Quiz complete!";
    DrawText(t, (W - MeasureText(t, 44)) / 2, 150, 44, WHITE);

    const char* s = TextFormat("%d / %d", score, L->nQ);
    DrawText(s, (W - MeasureText(s, 96)) / 2, 230, 96, accent);

    const char* msg = score == L->nQ ? "Perfect score - great work!"
        : score * 2 >= L->nQ ? "Nice! Review the lesson to lock it in."
        : "Keep going - re-read the lesson and try again.";
    DrawText(msg, (W - MeasureText(msg, 24)) / 2, 360, 24, DIM);

    if (Button((Rectangle) { 190, 450, 220, 56 }, "Retry quiz", accent, 22)) StartQuiz();
    if (Button((Rectangle) { 440, 450, 220, 56 }, "Review lesson", PANEL, 22)) StartLesson(lessonIdx);
    if (Button((Rectangle) { 690, 450, 220, 56 }, "Back to menu", PANEL, 22)) GoMenu();
}

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */
int main(void)
{
    InitWindow(W, H, "CodeQuest - Learn C & C++");
    SetExitKey(KEY_NULL);          /* we handle ESC ourselves */
    SetTargetFPS(60);
    LoadProgress();

    while (!quit && !WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (screen == SCR_MENU) quit = true;
            else GoMenu();
        }

        Color accent = ACCENTS[lang];
        BeginDrawing();
        ClearBackground(BG);
        switch (screen) {
        case SCR_MENU:   DrawMenu(accent);   break;
        case SCR_LESSON: DrawLesson(accent); break;
        case SCR_QUIZ:   DrawQuiz(accent);   break;
        case SCR_RESULT: DrawResult(accent); break;
        }
        EndDrawing();
    }

    SaveProgress();
    CloseWindow();
    return 0;
}