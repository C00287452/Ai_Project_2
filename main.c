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
 * Fonts: Liberation Serif (a Times New Roman look-alike, UI) + DejaVu Sans Mono (code) are loaded from the fonts/ folder
 *        next to the executable (run the program from the folder containing fonts/).
 *        If they are missing, raylib's built-in font is used instead.
 *
 * Campus mode: click "Walk the campus" on the menu to explore as a student. Enter C Hall or
 *   C++ Hall through the door, walk into a classroom and press Space next to a teacher.
 *
 * Battle Arena: the orange building. Challenge a rival to a head-to-head coding duel.
 *
 * Controls: mouse to click, mouse wheel to scroll, LEFT/RIGHT arrows to change
 *           lesson page, ESC to go back (or quit from the menu).
 */

#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define W 1200
#define H 760
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
/*  Theme and global state                                             */
/* ------------------------------------------------------------------ */
static const Color BG = { 15, 17, 23, 255 };
static const Color SURF = { 23, 27, 38, 255 };
static const Color SURF2 = { 33, 38, 54, 255 };
static const Color BORDER = { 44, 50, 70, 255 };
static const Color TXT = { 232, 236, 245, 255 };
static const Color DIM = { 139, 148, 170, 255 };
static const Color GOOD = { 52, 199, 120, 255 };
static const Color BAD = { 240, 92, 104, 255 };
static const Color CODEBG = { 11, 13, 19, 255 };
static const Color ACCENTS[2] = { { 64, 156, 255, 255 }, { 160, 112, 255, 255 } };

#define SPC 0.2f          /* letter spacing for the UI font */
#define UI_SCALE 1.14f    /* serif fonts look smaller than sans at the same size */

typedef enum { SCR_MENU, SCR_LESSON, SCR_QUIZ, SCR_RESULT, SCR_WORLD, SCR_BATTLE } Screen;

static Screen screen = SCR_MENU;
static int lang = 0, lessonIdx = 0, page = 0;
static int qi = 0, sel = -1, score = 0;
static float scroll = 0.0f;
static bool quit = false;
static bool fromWorld = false;            /* lesson/quiz opened from the campus? */
#define BACKL (fromWorld ? "< Campus" : "< Menu")
static void WorldEnter(void);
static bool hand = false;                 /* show pointer cursor this frame */
static Font fReg, fMed, fBold, fCode;     /* Liberation Serif + DejaVu Sans Mono */

static struct {
    unsigned char read[2][NLESSONS];
    int best[2][NLESSONS];
    unsigned char won[3];          /* arena rivals beaten */
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
/*  Fonts and text helpers                                             */
/* ------------------------------------------------------------------ */
static Font LoadF(const char* file, int size)
{
    char path[512];
    snprintf(path, sizeof path, "fonts/%s", file);
    if (!FileExists(path))
        snprintf(path, sizeof path, "%sfonts/%s", GetApplicationDirectory(), file);
    /* if the file is missing raylib falls back to its built-in font */
    Font f = LoadFontEx(path, size, NULL, 0);
    SetTextureFilter(f.texture, TEXTURE_FILTER_BILINEAR);
    return f;
}

static float TxtW(Font f, const char* s, float sz) { return MeasureTextEx(f, s, sz * UI_SCALE, SPC).x; }

static void Txt(Font f, const char* s, float x, float y, float sz, Color c)
{
    DrawTextEx(f, s, (Vector2) { x, y }, sz* UI_SCALE, SPC, c);
}

static void CenterTxt(Font f, const char* s, float cx, float y, float sz, Color c)
{
    Txt(f, s, cx - TxtW(f, s, sz) / 2, y, sz, c);
}

/* shrink the text (if needed) so it never gets wider than maxW */
static float FitSize(Font f, const char* s, float sz, float maxW)
{
    float w = TxtW(f, s, sz);
    return (w > maxW && w > 0) ? sz * maxW / w : sz;
}

static void TxtFit(Font f, const char* s, float x, float y, float sz, float maxW, Color c)
{
    float fs = FitSize(f, s, sz, maxW);
    Txt(f, s, x, y + (sz - fs) * 0.5f, fs, c);
}

static void CenterFit(Font f, const char* s, float cx, float y, float sz, float maxW, Color c)
{
    float fs = FitSize(f, s, sz, maxW);
    CenterTxt(f, s, cx, y + (sz - fs) * 0.5f, fs, c);
}

static bool wrapDry = false;   /* true = only measure, don't draw */
static bool wrapTyped = false;  /* true = reveal only wrapLeft characters */
static int wrapLeft = 0;

static void EmitLine(Font f, const char* line, float x, float y, float fs, Color c)
{
    if (wrapDry) return;
    if (!wrapTyped) { Txt(f, line, x, y, fs, c); return; }
    if (wrapLeft <= 0) return;
    int L = (int)strlen(line), n = wrapLeft < L ? wrapLeft : L;
    char buf[512];
    memcpy(buf, line, n);
    buf[n] = 0;
    Txt(f, buf, x, y, fs, c);
    wrapLeft -= L + 1;
}

/* word-wrapped text; '\n' starts a new paragraph. returns y below the text */
static int Wrapped(Font f, const char* t, float x, float y, float maxW, float fs, Color c)
{
    char line[512] = "";
    int len = 0;
    const char* p = t;
    float lh = fs * 1.6f;
    while (*p) {
        char word[128];
        int wl = 0;
        while (*p && *p != ' ' && *p != '\n' && wl < 127) word[wl++] = *p++;
        word[wl] = 0;

        char test[700];
        snprintf(test, sizeof test, "%s%s%s", line, len ? " " : "", word);
        if (len && TxtW(f, test, fs) > maxW) {
            EmitLine(f, line, x, y, fs, c);
            y += lh;
            snprintf(line, sizeof line, "%s", word);
        }
        else {
            snprintf(line, sizeof line, "%s", test);
        }
        len = (int)strlen(line);

        if (*p == '\n') {
            EmitLine(f, line, x, y, fs, c);
            y += lh + fs * 0.4f;
            line[0] = 0;
            len = 0;
            p++;
        }
        else if (*p == ' ') {
            p++;
        }
    }
    if (len) {
        EmitLine(f, line, x, y, fs, c);
        y += lh;
    }
    return (int)y;
}

/* typewriter text: the whole text is wrapped first, then only n characters are shown,
   so the line breaks never jump around while it types */
static int WrappedTyped(Font f, const char* t, float x, float y, float maxW, float fs, Color c, int n)
{
    wrapTyped = true; wrapLeft = n;
    int e = Wrapped(f, t, x, y, maxW, fs, c);
    wrapTyped = false;
    return e;
}

static int WrapH(Font f, const char* t, float maxW, float fs)
{
    wrapDry = true;
    int e = Wrapped(f, t, 0, 0, maxW, fs, WHITE);
    wrapDry = false;
    return e;
}

/* ------------------------------------------------------------------ */
/*  Widgets                                                            */
/* ------------------------------------------------------------------ */
static void Panel(Rectangle r, float rd, Color fill, Color border)
{
    DrawRectangleRounded(r, rd, 10, border);
    Rectangle in = { r.x + 1, r.y + 1, r.width - 2, r.height - 2 };
    DrawRectangleRounded(in, rd, 10, fill);
}

static bool Button(Rectangle r, const char* label, Color col, float fs)
{
    bool hov = CheckCollisionPointRec(GetMousePosition(), r);
    if (hov) hand = true;
    DrawRectangleRounded(r, 0.28f, 10, hov ? ColorBrightness(col, 0.18f) : col);
    fs = FitSize(fBold, label, fs, r.width - 20);
    CenterTxt(fBold, label, r.x + r.width / 2, r.y + (r.height - fs * UI_SCALE) / 2 - 1, fs, WHITE);
    return hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

static void Pill(const char* label, float x, float y, Color col)
{
    float w = TxtW(fMed, label, 14) + 28;
    DrawRectangleRounded((Rectangle) { x, y, w, 28 }, 0.5f, 10, Fade(col, 0.16f));
    Txt(fMed, label, x + 14, y + 5, 14, col);
}

static void TopBar(void)
{
    DrawRectangle(0, 0, W, 72, SURF);
    DrawLine(0, 72, W, 72, BORDER);
}

/* ---- syntax highlighting (monospace) ---- */
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

/* draw each character in its own fixed-width cell so code always lines up */
static void Tok(const char* s, int len, float x, float y, float fs, float cw, Color c)
{
    for (int k = 0; k < len; k++) {
        if (s[k] == ' ') continue;
        char b[2] = { s[k], 0 };
        DrawTextEx(fCode, b, (Vector2) { x + k * cw, y }, fs, 0, c);
    }
}

static void HighlightLine(const char* line, float x, float y, float fs, float cw)
{
    int n = (int)strlen(line), i = 0, f = 0;
    while (line[f] == ' ') f++;
    while (i < n) {
        char c = line[i];
        int j = i + 1;
        Color col = { 215, 218, 235, 255 };
        if (c == ' ') {
            while (j < n && line[j] == ' ') j++;
            x += (j - i) * cw;
            i = j;
            continue;
        }
        else if (c == '#' && i == f) {
            j = n; col = (Color){ 190, 140, 255, 255 };
        }
        else if (c == '/' && i + 1 < n && line[i + 1] == '/') {
            j = n; col = (Color){ 106, 153, 85, 255 };
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
            if (IsKeyword(w)) col = (Color){ 86, 156, 255, 255 };
            else if (j < n && line[j] == '(') col = (Color){ 235, 220, 130, 255 };
        }
        else if (isdigit((unsigned char)c)) {
            while (j < n && (isdigit((unsigned char)line[j]) || line[j] == '.')) j++;
            col = (Color){ 130, 220, 220, 255 };
        }
        Tok(line + i, j - i, x, y, fs, cw, col);
        x += (j - i) * cw;
        i = j;
    }
}

/* editor-style code panel with line numbers; returns y below it */
static int DrawCode(const char* code, float x, float y, float w, float fs, const char* fileName)
{
    int lines = 1;
    for (const char* p = code; *p; p++) if (*p == '\n') lines++;
    float lh = fs * 1.65f, h0 = 40, h = h0 + lines * lh + 28;
    float cw = MeasureTextEx(fCode, "M", fs, 0).x;

    Panel((Rectangle) { x, y, w, h }, 0.03f, CODEBG, BORDER);
    DrawCircle((int)x + 24, (int)y + 20, 6, (Color) { 255, 95, 86, 255 });
    DrawCircle((int)x + 44, (int)y + 20, 6, (Color) { 255, 189, 46, 255 });
    DrawCircle((int)x + 64, (int)y + 20, 6, (Color) { 39, 201, 63, 255 });
    float fw = MeasureTextEx(fCode, fileName, 14, 0).x;
    DrawTextEx(fCode, fileName, (Vector2) { x + w / 2 - fw / 2, y + 12 }, 14, 0, DIM);
    DrawLine((int)x + 1, (int)(y + h0), (int)(x + w - 1), (int)(y + h0), BORDER);

    float cy = y + h0 + 16;
    int ln = 1;
    const char* p = code;
    while (*p) {
        char line[256];
        int n = 0;
        while (*p && *p != '\n' && n < 255) line[n++] = *p++;
        line[n] = 0;
        if (*p == '\n') p++;
        const char* num = TextFormat("%d", ln++);
        float nw = MeasureTextEx(fCode, num, fs, 0).x;
        DrawTextEx(fCode, num, (Vector2) { x + 48 - nw, cy }, fs, 0, (Color) { 76, 84, 108, 255 });
        HighlightLine(line, x + 70, cy, fs, cw);
        cy += lh;
    }
    return (int)(y + h);
}

/* ------------------------------------------------------------------ */
/*  Navigation helpers                                                 */
/* ------------------------------------------------------------------ */
static void GoMenu(void) { screen = fromWorld ? SCR_WORLD : SCR_MENU; scroll = 0; }
static void StartQuiz(void) { screen = SCR_QUIZ; qi = 0; sel = -1; score = 0; }
static void StartLesson(int idx) { lessonIdx = idx; page = 0; scroll = 0; screen = SCR_LESSON; }

/* ------------------------------------------------------------------ */
/*  Screens                                                            */
/* ------------------------------------------------------------------ */
static void DrawMenu(Color accent)
{
    fromWorld = false;
    TopBar();
    DrawRectangleRounded((Rectangle) { 36, 16, 40, 40 }, 0.3f, 10, accent);
    CenterTxt(fCode, "</>", 56, 27, 16, WHITE);
    Txt(fBold, "CodeQuest", 90, 10, 28, TXT);
    Txt(fReg, "Learn C & C++ interactively", 92, 46, 12, DIM);

    int done = 0, total = 2 * NLESSONS * 2;
    for (int l = 0; l < 2; l++)
        for (int i = 0; i < NLESSONS; i++) {
            done += prog.read[l][i] ? 1 : 0;
            done += prog.best[l][i] >= 0 ? 1 : 0;
        }
    const char* pt = TextFormat("Overall progress  %d%%", done * 100 / total);
    Txt(fMed, pt, W - 36 - 300, 14, 15, DIM);
    DrawRectangleRounded((Rectangle) { W - 36 - 300, 42, 300, 8 }, 0.5f, 10, SURF2);
    if (done) DrawRectangleRounded((Rectangle) { W - 36 - 300, 42, 300.0f * done / total, 8 }, 0.5f, 10, accent);

    /* segmented language control */
    Panel((Rectangle) { 36, 96, 300, 48 }, 0.3f, SURF, BORDER);
    for (int l = 0; l < 2; l++) {
        Rectangle r = { 40.0f + l * 146, 100, 146, 40 };
        bool hov = CheckCollisionPointRec(GetMousePosition(), r);
        if (hov) hand = true;
        if (l == lang) DrawRectangleRounded(r, 0.3f, 10, ACCENTS[l]);
        CenterTxt(fMed, LANG_NAME[l], r.x + r.width / 2, r.y + 8, 20, l == lang ? WHITE : DIM);
        if (hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) lang = l;
    }
    Txt(fReg, TextFormat("%d lessons  |  %d quiz questions", NLESSONS, NLESSONS * 3), 362, 108, 16, DIM);
    if (Button((Rectangle) { W - 36 - 260, 96, 260, 48 }, "Walk the campus  >", accent, 16)) WorldEnter();

    /* lesson cards */
    for (int i = 0; i < NLESSONS; i++) {
        const Lesson* L = &LESSONS[lang][i];
        float y = 168.0f + i * 108;
        Rectangle card = { 36, y, W - 72, 96 };
        bool hov = CheckCollisionPointRec(GetMousePosition(), card);
        Panel(card, 0.14f, hov ? SURF2 : SURF, hov ? accent : BORDER);
        DrawRectangleRounded((Rectangle) { 36, y + 18, 5, 60 }, 0.5f, 6, accent);

        DrawCircle(92, (int)y + 48, 24, Fade(accent, 0.18f));
        CenterTxt(fBold, TextFormat("%d", i + 1), 92, y + 35, 22, accent);
        TxtFit(fBold, L->name + 3, 138, y + 16, 23, 400, TXT);
        Txt(fReg, TextFormat("%d pages  -  %d questions", L->nPages, L->nQ), 138, y + 55, 15, DIM);

        if (prog.read[lang][i]) Pill("Lesson read", 560, y + 14, GOOD);
        else                    Pill("Not started", 560, y + 14, DIM);
        if (prog.best[lang][i] >= 0) Pill(TextFormat("Best %d/%d", prog.best[lang][i], L->nQ), 560, y + 54, GOOD);
        else                         Pill("Quiz not taken", 560, y + 54, DIM);

        if (Button((Rectangle) { 900, y + 24, 112, 48 }, "Learn", accent, 17)) StartLesson(i);
        if (Button((Rectangle) { 1026, y + 24, 112, 48 }, "Quiz", SURF2, 17)) { lessonIdx = i; StartQuiz(); }
    }
}

static void DrawLesson(Color accent)
{
    const Lesson* L = &LESSONS[lang][lessonIdx];
    const Page* P = &L->pages[page];
    const float x0 = 150, cw = 900;

    /* header */
    TopBar();
    if (Button((Rectangle) { 24, 14, 104, 44 }, BACKL, SURF2, 16)) GoMenu();
    TxtFit(fMed, TextFormat("%s  /  %s", LANG_NAME[lang], L->name + 3), 150, 20, 22, 760, TXT);
    for (int p = 0; p < L->nPages; p++) {
        int cx = W - 48 - (L->nPages - 1 - p) * 26;
        DrawCircle(cx, 36, p == page ? 7 : 5, p == page ? accent : BORDER);
    }

    /* scrollable content */
    BeginScissorMode(0, 73, W, 611);
    float y = 108 - scroll;
    Txt(fBold, TextFormat("LESSON %d   -   PAGE %d OF %d", lessonIdx + 1, page + 1, L->nPages), x0, y, 14, accent);
    y += 28;
    TxtFit(fBold, P->title, x0, y, 36, cw, TXT);
    y += 66;
    y = (float)Wrapped(fReg, P->text, x0, y, cw, 19, (Color) { 205, 211, 228, 255 });
    y += 18;
    y = (float)DrawCode(P->code, x0, y, cw, 18, lang == 0 ? "main.c" : "main.cpp");
    y += 40;
    EndScissorMode();

    float maxScroll = y + scroll - 684;
    if (maxScroll < 0) maxScroll = 0;
    scroll -= GetMouseWheelMove() * 45.0f;
    if (scroll < 0) scroll = 0;
    if (scroll > maxScroll) scroll = maxScroll;
    if (maxScroll > 0) {                               /* scrollbar */
        float trackH = 590, thumbH = trackH * 611.0f / (611.0f + maxScroll);
        float thumbY = 84 + (trackH - thumbH) * scroll / maxScroll;
        DrawRectangleRounded((Rectangle) { W - 14, thumbY, 6, thumbH }, 0.5f, 6, BORDER);
    }

    /* footer */
    DrawRectangle(0, 684, W, H - 684, SURF);
    DrawLine(0, 684, W, 684, BORDER);
    CenterTxt(fReg, "Use the left / right arrow keys to change page", W / 2.0f, 710, 14, DIM);

    bool last = (page == L->nPages - 1);
    if (last && !prog.read[lang][lessonIdx]) { prog.read[lang][lessonIdx] = 1; SaveProgress(); }

    if (page > 0 && (Button((Rectangle) { 36, 698, 150, 48 }, "< Previous", SURF2, 16) || IsKeyPressed(KEY_LEFT))) {
        page--; scroll = 0;
    }
    if (!last) {
        if (Button((Rectangle) { W - 186, 698, 150, 48 }, "Next >", accent, 16) || IsKeyPressed(KEY_RIGHT)) {
            page++; scroll = 0;
        }
    }
    else {
        if (Button((Rectangle) { W - 216, 698, 180, 48 }, "Take the quiz", GOOD, 16)) StartQuiz();
    }
}

static void DrawQuiz(Color accent)
{
    const Lesson* L = &LESSONS[lang][lessonIdx];
    const Question* Q = &L->qs[qi];
    const float x0 = 150, cw = 900;

    TopBar();
    if (Button((Rectangle) { 24, 14, 104, 44 }, BACKL, SURF2, 16)) GoMenu();
    TxtFit(fMed, TextFormat("Quiz  /  %s", L->name + 3), 150, 20, 22, 640, TXT);
    const char* info = TextFormat("Score  %d", score);
    Txt(fMed, info, W - 36 - TxtW(fMed, info, 18), 22, 18, accent);
    DrawRectangle(0, 72, W, 4, SURF2);
    DrawRectangle(0, 72, W * (qi + (sel >= 0 ? 1 : 0)) / L->nQ, 4, accent);

    Txt(fBold, TextFormat("QUESTION %d OF %d", qi + 1, L->nQ), x0, 106, 14, accent);
    int qEnd = Wrapped(fBold, Q->q, x0, 134, cw, 28, TXT);
    float yOpt = qEnd + 14 > 240 ? (float)(qEnd + 14) : 240;

    for (int i = 0; i < 4; i++) {
        Rectangle r = { x0, yOpt + i * 72, cw, 60 };
        bool hov = CheckCollisionPointRec(GetMousePosition(), r);
        Color fill = SURF, border = BORDER, badge = SURF2, text = TXT;
        if (sel < 0 && hov) { fill = SURF2; border = accent; hand = true; }
        if (sel >= 0) {
            if (i == Q->correct) { fill = Fade(GOOD, 0.13f); border = GOOD; badge = GOOD; }
            else if (i == sel) { fill = Fade(BAD, 0.13f);  border = BAD;  badge = BAD; }
            else { text = DIM; }
        }
        Panel(r, 0.22f, fill, border);
        DrawCircle((int)r.x + 38, (int)r.y + 30, 18, badge);
        CenterTxt(fBold, TextFormat("%c", 'A' + i), r.x + 38, r.y + 19, 18, sel >= 0 && badge.a == 255 && (i == Q->correct || i == sel) ? WHITE : DIM);
        TxtFit(fReg, Q->opts[i], r.x + 74, r.y + 16, 20, cw - 100, text);

        if (sel < 0 && ((hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ||
            IsKeyPressed(KEY_ONE + i) || IsKeyPressed(KEY_A + i))) {
            sel = i;
            if (i == Q->correct) score++;
        }
    }

    DrawRectangle(0, 684, W, H - 684, SURF);
    DrawLine(0, 684, W, 684, BORDER);
    if (sel < 0) {
        CenterTxt(fReg, "Click an answer, or press 1-4", W / 2.0f, 710, 14, DIM);
    }
    else {
        bool ok = (sel == Q->correct);
        Color col = ok ? GOOD : BAD;
        float fy = yOpt + 4 * 72 - 4;
        float ph = 46 + WrapH(fReg, Q->expl, cw - 44, 16) + 8;
        Panel((Rectangle) { x0, fy, cw, ph }, 0.12f, Fade(col, 0.10f), col);
        Txt(fBold, ok ? "Correct!" : "Not quite", x0 + 22, fy + 12, 20, col);
        Wrapped(fReg, Q->expl, x0 + 22, fy + 44, cw - 44, 16, (Color) { 205, 211, 228, 255 });

        bool lastQ = (qi == L->nQ - 1);
        if (Button((Rectangle) { W - 196, 698, 160, 48 }, lastQ ? "Finish" : "Next >", accent, 16)
            || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
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
    TopBar();
    Txt(fMed, "Quiz results", 36, 20, 22, TXT);

    float cx = W / 2.0f;
    Panel((Rectangle) { cx - 320, 110, 640, 540 }, 0.05f, SURF, BORDER);
    CenterTxt(fBold, "Quiz complete", cx, 140, 32, TXT);
    CenterFit(fReg, L->name + 3, cx, 188, 18, 560, DIM);

    Vector2 c = { cx, 340 };
    DrawRing(c, 80, 98, 0, 360, 80, SURF2);
    if (score > 0) DrawRing(c, 80, 98, -90, -90 + 360.0f * score / L->nQ, 80, score == L->nQ ? GOOD : accent);
    CenterTxt(fBold, TextFormat("%d / %d", score, L->nQ), cx, 316, 44, TXT);

    const char* msg = score == L->nQ ? "Perfect score - great work!"
        : score * 2 >= L->nQ ? "Nice! Review the lesson to lock it in."
        : "Keep going - re-read the lesson and try again.";
    CenterFit(fReg, msg, cx, 470, 20, 560, DIM);

    float bx = cx - 284;
    if (Button((Rectangle) { bx, 550, 180, 52 }, "Retry quiz", accent, 16)) StartQuiz();
    if (Button((Rectangle) { bx + 194, 550, 180, 52 }, "Review lesson", SURF2, 16)) StartLesson(lessonIdx);
    if (Button((Rectangle) { bx + 388, 550, 180, 52 }, (fromWorld ? "Campus" : "Menu"), SURF2, 16)) GoMenu();
}

/* ------------------------------------------------------------------ */
/*  Campus mode: walk around, enter a hall, talk to teachers           */
/* ------------------------------------------------------------------ */
#define TS 48            /* tile size in pixels */
#define CW 36            /* campus width/height in tiles */
#define CH 24
#define IW 31            /* hall interior width/height in tiles */
#define IH 12
#define TROW 3           /* row where teachers / rivals stand */
#define AW 21            /* battle arena size in tiles */
#define AH 11

typedef struct { const char* name, * greet; Color shirt, hair; int dir; } Teacher;

static Teacher TEACH[2][5] = {
  { { "Ms. Byte",       "Every program has to start somewhere! Ready to write your first line of C?",        { 230, 120, 160, 255 }, { 60, 40, 30, 255 }, 0 },
    { "Mr. Loop",       "Decisions and loops... that's where programs get their power. Shall we begin?",     { 90, 170, 120, 255 },  { 30, 30, 40, 255 }, 0 },
    { "Dr. Func",       "Functions and arrays are the building blocks of tidy code. Take a seat!",           { 230, 170, 70, 255 },  { 150, 90, 50, 255 }, 0 },
    { "Prof. Pointer",  "Pointers scare everyone at first. Let me show you they are just addresses.",        { 150, 110, 220, 255 }, { 200, 200, 210, 255 }, 0 },
    { "Mrs. Heap",      "Structs and memory - handle with care, and always free what you malloc!",           { 220, 100, 90, 255 },  { 110, 60, 40, 255 }, 0 } },
  { { "Mr. Stream",     "Welcome to C++! Today we talk about streams, strings and auto.",                    { 80, 170, 200, 255 },  { 40, 30, 30, 255 }, 0 },
    { "Dr. Vector",     "References and vectors will make your life so much easier. Ready?",                 { 120, 190, 110, 255 }, { 220, 190, 90, 255 }, 0 },
    { "Ms. Object",     "Classes let you model the real world. Come in and take a seat!",                    { 235, 140, 190, 255 }, { 50, 35, 30, 255 }, 0 },
    { "Prof. Virtual",  "Inheritance and polymorphism - the heart of object-oriented programming.",          { 170, 120, 230, 255 }, { 190, 190, 200, 255 }, 0 },
    { "Mr. Template",   "Write it once, use it for every type. Templates are pure magic.",                   { 235, 190, 80, 255 },  { 90, 60, 40, 255 }, 0 } }
};

static const struct { int x, y, lang; const char* name; } BLD[3] = {
    { 5, 4, 0, "C HALL" }, { 24, 4, 1, "C++ HALL" }, { 14, 4, 2, "BATTLE ARENA" }
};
static const Color ROOFC[3] = { { 58, 110, 200, 255 }, { 125, 84, 205, 255 }, { 225, 95, 70, 255 } };
static const Color ARENA_C = { 240, 120, 80, 255 };

static Teacher RIVT[3] = {
  { "Rookie Ron",    "I just started coding too! Let's see who solves problems faster.",   { 110, 190, 120, 255 }, { 120, 80, 50, 255 }, 0 },
  { "Rival Rex",     "Think you can out-code me? The first correct answer takes the round!", { 80, 120, 230, 255 }, { 30, 30, 40, 255 }, 0 },
  { "Champion Cora", "I haven't lost a round in weeks. Show me what you've learned.",        { 230, 80, 100, 255 }, { 220, 200, 120, 255 }, 0 }
};

static void StartBattle(int r);

static const int DX[4] = { 0, -1, 1, 0 };     /* dir: 0 down, 1 left, 2 right, 3 up */
static const int DY[4] = { 1, 0, 0, -1 };

typedef enum { DLG_NONE, DLG_TEXT, DLG_MENU } DlgState;

static char campus[CH][CW + 1];
static char inter[IH][IW + 1];
static char arena[AH][AW + 1];
#define INHALL (inside == 0 || inside == 1)
static int inside = -1;                 /* -1 campus, 0 = C Hall, 1 = C++ Hall */
static int wx = 17, wy = 21, wdir = 3;  /* player tile and facing */
static int wtx, wty;                    /* target tile while stepping */
static float wt = 0, walkPhase = 0;
static bool wmoving = false, wrun = false;
static int doorX = 8, doorY = 7;
static float fade = 0;
static int fadeDir = 0, fadeAct = 0;
static const char* toast = NULL;
static float toastT = 0;
static DlgState dlg = DLG_NONE;
static int dlgTeacher = 0, dlgSel = 0;
static float dlgChars = 0;

static void PlaceBuilding(int x, int y, char roof, char wall, char door)
{
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 7; i++) campus[y + j][x + i] = (j < 2) ? roof : wall;
    campus[y + 3][x + 3] = door;
}

static void BuildMaps(void)
{
    for (int y = 0; y < CH; y++) {
        for (int x = 0; x < CW; x++)
            campus[y][x] = (x == 0 || y == 0 || x == CW - 1 || y == CH - 1) ? 'T' : '.';
        campus[y][CW] = 0;
    }
    PlaceBuilding(5, 4, 'R', 'k', 'D');
    PlaceBuilding(24, 4, 'r', 'l', 'E');
    PlaceBuilding(14, 4, 'Q', 'm', 'A');
    for (int y = 8; y <= 14; y++) { campus[y][8] = '_'; campus[y][17] = '_'; campus[y][27] = '_'; }
    for (int x = 8; x <= 27; x++) { campus[14][x] = '_'; campus[15][x] = '_'; }
    for (int y = 16; y <= 22; y++) { campus[y][17] = '_'; campus[y][18] = '_'; }
    for (int y = 18; y <= 21; y++) for (int x = 22; x <= 27; x++) campus[y][x] = 'w';
    campus[13][12] = 'B'; campus[13][23] = 'B';
    static const int trees[][2] = {
        {2,3},{3,5},{2,8},{3,11},{2,14},{4,18},{2,20},{7,11},{9,11},{13,3},{16,3},
        {21,3},{20,9},{15,10},{29,11},{32,3},{33,6},{32,9},{33,12},{31,16},{33,19},{30,21},
        {12,18},{14,20},{10,19},{6,17},{9,21},{4,15},{29,9}
    };
    for (size_t i = 0; i < sizeof trees / sizeof trees[0]; i++) campus[trees[i][1]][trees[i][0]] = 'T';

    /* hall interior: 2 wall rows (blackboards), 5 classrooms, a hallway below */
    for (int y = 0; y < IH; y++) {
        for (int x = 0; x < IW; x++) inter[y][x] = '#';
        inter[y][IW] = 0;
    }
    for (int r = 0; r < 5; r++) {
        int x0 = 1 + r * 6;
        for (int y = 2; y <= 6; y++) for (int i = 0; i < 5; i++) inter[y][x0 + i] = '.';
        inter[7][x0 + 2] = '.';
        inter[4][x0] = inter[5][x0] = inter[4][x0 + 4] = inter[5][x0 + 4] = 'h';
        inter[3][x0 + 1] = inter[3][x0 + 3] = 'h';
    }
    for (int y = 8; y <= 10; y++) for (int x = 1; x <= 29; x++) inter[y][x] = ',';
    inter[11][15] = 'X';

    /* battle arena */
    for (int y = 0; y < AH; y++) {
        for (int x = 0; x < AW; x++) arena[y][x] = '#';
        arena[y][AW] = 0;
    }
    for (int x = 1; x <= AW - 2; x++) arena[1][x] = 'u';
    for (int y = 2; y <= 9; y++) for (int x = 1; x <= AW - 2; x++) arena[y][x] = '.';
    for (int y = 5; y <= 8; y++) for (int x = 7; x <= 13; x++) arena[y][x] = 'o';
    arena[10][10] = 'X';
}

static int MapW(void) { return inside < 0 ? CW : (inside == 2 ? AW : IW); }
static int MapH(void) { return inside < 0 ? CH : (inside == 2 ? AH : IH); }

static char TileAt(int x, int y)
{
    if (x < 0 || y < 0 || x >= MapW() || y >= MapH()) return '#';
    return inside < 0 ? campus[y][x] : (inside == 2 ? arena[y][x] : inter[y][x]);
}

static bool IsSolid(char c) { return c == 0 || strchr("TwkRlrQm#hBu", c) != NULL; }

/* index of the teacher / rival standing on tile (x, y), or -1 */
static int NpcAt(int x, int y)
{
    if (inside < 0 || y != TROW) return -1;
    if (INHALL) {
        if (x >= 3 && x <= 27 && (x - 3) % 6 == 0) return (x - 3) / 6;
    }
    else if (inside == 2) {
        if (x == 4) return 0;
        if (x == 10) return 1;
        if (x == 16) return 2;
    }
    return -1;
}

static unsigned Hash(int x, int y)
{
    unsigned h = ((unsigned)x * 73856093u) ^ ((unsigned)y * 19349663u);
    h ^= h >> 13; h *= 0x5bd1e995u; h ^= h >> 15;
    return h;
}

static void WorldEnter(void)
{
    fromWorld = true;
    screen = SCR_WORLD;
    dlg = DLG_NONE;
    wmoving = false; wt = 0;
    if (inside >= 0) lang = inside;
}

/* ---- gameplay ---- */
static Teacher* Speaker(void) { return inside == 2 ? &RIVT[dlgTeacher] : &TEACH[inside][dlgTeacher]; }

static void DlgChoose(int i)
{
    if (inside == 2) {                       /* arena: 0 = battle, 1 = later */
        if (i == 0) { fromWorld = true; StartBattle(dlgTeacher); }
        dlg = DLG_NONE;
        return;
    }
    if (i == 0) { lang = inside; fromWorld = true; StartLesson(dlgTeacher); dlg = DLG_NONE; }
    else if (i == 1) { lang = inside; fromWorld = true; lessonIdx = dlgTeacher; StartQuiz(); dlg = DLG_NONE; }
    else { dlg = DLG_NONE; }
}

static void OnArrive(void)
{
    char c = TileAt(wx, wy);
    if (inside < 0) {
        if (c == 'D') { fadeDir = 1; fadeAct = 1; }
        else if (c == 'E') { fadeDir = 1; fadeAct = 2; }
        else if (c == 'A') { fadeDir = 1; fadeAct = 3; }
    }
    else if (c == 'X') {
        fadeDir = 1; fadeAct = 4;
    }
}

static void UpdateWorld(float dt)
{
    if (toastT > 0) toastT -= dt;

    if (fadeDir != 0) {
        if (fadeDir == 1) {
            fade += dt * 3.5f;
            if (fade >= 1) {
                fade = 1; fadeDir = -1;
                wmoving = false; wt = 0;
                if (fadeAct >= 1 && fadeAct <= 3) {
                    doorX = wx; doorY = wy;
                    inside = fadeAct - 1;
                    wdir = 3;
                    if (inside == 2) {
                        wx = 10; wy = 9;
                        toast = "Welcome to the Battle Arena";
                    }
                    else {
                        lang = inside; wx = 15; wy = 10;
                        toast = inside == 0 ? "Welcome to C Hall" : "Welcome to C++ Hall";
                    }
                    toastT = 2.2f;
                }
                else {
                    inside = -1; wx = doorX; wy = doorY + 1; wdir = 0;
                    toast = "Back on campus"; toastT = 1.6f;
                }
            }
        }
        else {
            fade -= dt * 3.5f;
            if (fade <= 0) { fade = 0; fadeDir = 0; }
        }
        return;
    }

    bool confirm = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER);

    if (dlg == DLG_TEXT) {
        int len = (int)strlen(Speaker()->greet);
        dlgChars += dt * 45.0f;
        if (confirm) {
            if (dlgChars < len) dlgChars = (float)len;
            else { dlg = DLG_MENU; dlgSel = 0; }
        }
        return;
    }
    if (dlg == DLG_MENU) {
        int n = (inside == 2) ? 2 : 3;
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) dlgSel = (dlgSel + 1) % n;
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))   dlgSel = (dlgSel + n - 1) % n;
        if (IsKeyPressed(KEY_ONE))                    DlgChoose(0);
        else if (IsKeyPressed(KEY_TWO))               DlgChoose(1);
        else if (IsKeyPressed(KEY_THREE) && n == 3)   DlgChoose(2);
        else if (confirm) DlgChoose(dlgSel);
        return;
    }

    if (wmoving) {
        wt += dt * (wrun ? 9.0f : 5.5f);
        walkPhase += dt * (wrun ? 15.0f : 10.0f);
        if (wt >= 1) {
            wt = 0; wmoving = false; wx = wtx; wy = wty;
            OnArrive();
            if (fadeDir) return;
        }
    }
    if (!wmoving) {
        wrun = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        int d = -1;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))       d = 0;
        else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  d = 1;
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) d = 2;
        else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))    d = 3;
        if (d >= 0) {
            wdir = d;
            int nx = wx + DX[d], ny = wy + DY[d];
            if (!IsSolid(TileAt(nx, ny)) && NpcAt(nx, ny) < 0) {
                wtx = nx; wty = ny; wmoving = true; wt = 0;
            }
        }
        else if (confirm && inside >= 0) {
            int n = NpcAt(wx + DX[wdir], wy + DY[wdir]);
            if (n >= 0) {
                dlgTeacher = n;
                Speaker()->dir = 3 - wdir;           /* they turn to face you */
                dlg = DLG_TEXT; dlgChars = 0; dlgSel = 0;
            }
        }
    }
}

/* ---- drawing ---- */
static void DrawPerson(float x, float fy, int dir, Color shirt, Color hair, Color pants,
    bool glasses, bool pack, float ph)
{
    Color skin = { 240, 200, 160, 255 }, ink = { 30, 30, 40, 255 }, bagc = { 235, 140, 50, 255 };
    float s = sinf(ph) * 3.0f, bob = fabsf(sinf(ph)) * 1.5f;
    float offL = s > 0 ? s : 0, offR = s < 0 ? -s : 0;

    DrawEllipse((int)x, (int)fy, 14, 6, Fade(BLACK, 0.28f));
    DrawRectangleRounded((Rectangle) { x - 9, fy - 13 - offL, 8, 13 }, 0.3f, 4, pants);
    DrawRectangleRounded((Rectangle) { x + 1, fy - 13 - offR, 8, 13 }, 0.3f, 4, pants);

    float by = fy - 33 - bob;
    if (pack && (dir == 1 || dir == 2))
        DrawRectangleRounded((Rectangle) { dir == 1 ? x + 8 : x - 16, by + 3, 8, 16 }, 0.4f, 4, bagc);
    DrawRectangleRounded((Rectangle) { x - 13, by, 26, 22 }, 0.3f, 6, shirt);
    if (pack && dir == 3)
        DrawRectangleRounded((Rectangle) { x - 10, by + 2, 20, 17 }, 0.3f, 6, bagc);
    DrawRectangleRounded((Rectangle) { x - 19, by + 3 + s * 0.5f, 6, 15 }, 0.5f, 4, shirt);
    DrawRectangleRounded((Rectangle) { x + 13, by + 3 - s * 0.5f, 6, 15 }, 0.5f, 4, shirt);
    DrawCircle((int)x - 16, (int)(by + 20 + s * 0.5f), 3, skin);
    DrawCircle((int)x + 16, (int)(by + 20 - s * 0.5f), 3, skin);

    float hy = fy - 44 - bob;
    DrawCircle((int)x, (int)hy, 12, hair);
    if (dir == 0) {
        DrawCircle((int)x, (int)hy + 2, 10, skin);
        DrawCircle((int)x - 4, (int)hy + 3, 2, ink);
        DrawCircle((int)x + 4, (int)hy + 3, 2, ink);
        if (glasses) { DrawCircleLines((int)x - 4, (int)hy + 3, 4, ink); DrawCircleLines((int)x + 4, (int)hy + 3, 4, ink); }
    }
    else if (dir == 1 || dir == 2) {
        float o = dir == 1 ? -1.0f : 1.0f;
        DrawCircle((int)(x + o * 3), (int)hy + 2, 9, skin);
        DrawCircle((int)(x + o * 7), (int)hy + 3, 2, ink);
        if (glasses) DrawCircleLines((int)(x + o * 7), (int)hy + 3, 4, ink);
    }
}

static void DrawGrass(int x, int y, int sx, int sy)
{
    unsigned h = Hash(x, y) & 255;
    DrawRectangle(sx, sy, TS, TS, ((x + y) & 1) ? (Color) { 90, 162, 79, 255 } : (Color) { 96, 170, 84, 255 });
    if (h < 40)  DrawRectangle(sx + (int)(h % 34) + 4, sy + (int)((h / 2) % 30) + 8, 2, 6, (Color) { 70, 140, 62, 255 });
    if (h > 244) { DrawCircle(sx + 16, sy + 28, 3, (Color) { 250, 250, 250, 255 }); DrawCircle(sx + 16, sy + 28, 1, (Color) { 250, 210, 60, 255 }); }
    if (h > 230 && h <= 238) { DrawCircle(sx + 30, sy + 18, 3, (Color) { 245, 130, 170, 255 }); DrawCircle(sx + 30, sy + 18, 1, (Color) { 250, 230, 120, 255 }); }
}

static int BldIdx(char c)
{
    if (c == 'R' || c == 'k' || c == 'D') return 0;
    if (c == 'r' || c == 'l' || c == 'E') return 1;
    if (c == 'Q' || c == 'm' || c == 'A') return 2;
    return -1;
}

static bool IsRoof(char c) { return c == 'R' || c == 'r' || c == 'Q'; }

static void DrawCampusTile(char c, int x, int y, int sx, int sy)
{
    unsigned h = Hash(x, y) & 255;
    if (c == '.' || c == 'T' || c == 'B') DrawGrass(x, y, sx, sy);

    if (c == '_') {
        DrawRectangle(sx, sy, TS, TS, (Color) { 214, 190, 140, 255 });
        if (h < 50) DrawRectangle(sx + (int)(h % 36) + 4, sy + (int)((h / 3) % 36) + 4, 4, 3, (Color) { 190, 165, 115, 255 });
    }
    else if (c == 'w') {
        DrawRectangle(sx, sy, TS, TS, (Color) { 70, 140, 220, 255 });
        int off = (int)(4 * sinf((float)GetTime() * 2.0f + x + y));
        DrawRectangle(sx + 8 + off, sy + 14, 18, 2, (Color) { 150, 200, 255, 255 });
        DrawRectangle(sx + 22 - off, sy + 34, 16, 2, (Color) { 150, 200, 255, 255 });
    }
    else if (c == 'T') {
        DrawRectangle(sx + 20, sy + 28, 8, 18, (Color) { 105, 70, 40, 255 });
        DrawCircle(sx + 24, sy + 20, 20, (Color) { 40, 110, 60, 255 });
        DrawCircle(sx + 24, sy + 17, 16, (Color) { 56, 140, 74, 255 });
        DrawCircle(sx + 18, sy + 12, 5, (Color) { 90, 180, 100, 255 });
    }
    else if (c == 'B') {
        DrawRectangleRounded((Rectangle) { (float)sx + 4, (float)sy + 14, 40, 12 }, 0.3f, 4, (Color) { 140, 95, 55, 255 });
        DrawRectangle(sx + 8, sy + 26, 4, 10, (Color) { 90, 60, 35, 255 });
        DrawRectangle(sx + 36, sy + 26, 4, 10, (Color) { 90, 60, 35, 255 });
    }
    else if (IsRoof(c)) {
        Color rc = ROOFC[BldIdx(c)], dk = ColorBrightness(rc, -0.22f);
        DrawRectangle(sx, sy, TS, TS, rc);
        for (int k = 0; k < 4; k++) DrawRectangle(sx, sy + k * 12 + 10, TS, 2, dk);
        if (!IsRoof(TileAt(x, y - 1))) DrawRectangle(sx, sy, TS, 5, dk);
    }
    else if (BldIdx(c) >= 0) {
        int bi = BldIdx(c);
        Color rc = ROOFC[bi], dk = ColorBrightness(rc, -0.2f);
        bool door = (c == 'D' || c == 'E' || c == 'A');
        bool upper = IsRoof(TileAt(x, y - 1));
        DrawRectangle(sx, sy, TS, TS, (Color) { 232, 226, 210, 255 });
        if (upper && !door && (bi == 1 ? !(x & 1) : (x & 1))) {
            DrawRectangle(sx + 9, sy + 8, 30, 26, (Color) { 60, 70, 100, 255 });
            DrawRectangle(sx + 11, sy + 10, 26, 22, (Color) { 150, 200, 245, 255 });
            DrawRectangle(sx + 23, sy + 10, 2, 22, (Color) { 60, 70, 100, 255 });
            DrawRectangle(sx + 11, sy + 20, 26, 2, (Color) { 60, 70, 100, 255 });
        }
        if (door) {
            DrawRectangle(sx + 6, sy + 2, 36, TS - 2, (Color) { 95, 60, 35, 255 });
            DrawRectangle(sx + 10, sy + 7, 28, TS - 7, (Color) { 125, 82, 48, 255 });
            DrawCircle(sx + 33, sy + 30, 3, (Color) { 240, 200, 80, 255 });
            DrawRectangle(sx + 4, sy, 40, 5, rc);
        }
        else if (!upper) {
            DrawRectangle(sx, sy + TS - 6, TS, 6, dk);
        }
    }
}

static void DrawArenaTile(char c, int x, int y, int sx, int sy)
{
    unsigned h = Hash(x, y) & 255;
    if (c == '#') {
        DrawRectangle(sx, sy, TS, TS, (Color) { 40, 28, 44, 255 });
        DrawRectangle(sx, sy + TS - 5, TS, 5, ARENA_C);
        return;
    }
    if (c == 'u') {                                   /* crowd */
        DrawRectangle(sx, sy, TS, TS, (Color) { 52, 38, 66, 255 });
        for (int k = 0; k < 3; k++) {
            Color body = { (unsigned char)(110 + (h * (k + 1)) % 120), (unsigned char)(80 + (h * 7 * (k + 2)) % 130),
                           (unsigned char)(100 + (h * 3 * (k + 3)) % 120), 255 };
            int hx = sx + 9 + k * 15, hy = sy + 14 + (int)((h >> k) & 3);
            DrawRectangle(hx - 5, hy + 6, 11, 14, body);
            DrawCircle(hx, hy, 6, (Color) { 240, 200, 160, 255 });
        }
        return;
    }
    Color base = ((x + y) & 1) ? (Color) { 44, 48, 70, 255 } : (Color) { 40, 44, 64, 255 };
    if (c == 'o') base = ((x + y) & 1) ? (Color) { 96, 54, 48, 255 } : (Color) { 88, 48, 42, 255 };
    DrawRectangle(sx, sy, TS, TS, base);
    if (c == 'X') {
        DrawRectangle(sx + 4, sy + 10, TS - 8, TS - 14, (Color) { 120, 55, 50, 255 });
        CenterTxt(fBold, "EXIT", (float)sx + TS / 2, (float)sy + 14, 14, WHITE);
    }
}

static void DrawInteriorTile(char c, int x, int y, int sx, int sy, Color accent)
{
    if (inside == 2) { DrawArenaTile(c, x, y, sx, sy); return; }
    unsigned h = Hash(x, y) & 255;
    if (c == '#') {
        DrawRectangle(sx, sy, TS, TS, (Color) { 58, 64, 92, 255 });
        DrawRectangle(sx, sy, TS, 6, (Color) { 82, 90, 124, 255 });
        DrawRectangle(sx, sy + TS - 4, TS, 4, (Color) { 40, 45, 68, 255 });
        return;
    }
    if (c == ',' || c == 'X') {
        DrawRectangle(sx, sy, TS, TS, ((x + y) & 1) ? (Color) { 143, 153, 178, 255 } : (Color) { 150, 160, 185, 255 });
        if (c == 'X') {
            DrawRectangle(sx + 4, sy + 10, TS - 8, TS - 14, (Color) { 120, 55, 50, 255 });
            CenterTxt(fBold, "EXIT", (float)sx + TS / 2, (float)sy + 14, 14, WHITE);
        }
        return;
    }
    int room = (x - 1) / 6;
    Color fl = (room & 1) ? (Color) { 196, 170, 130, 255 } : (Color) { 203, 178, 140, 255 };
    if ((x + y) & 1) fl = ColorBrightness(fl, -0.04f);
    DrawRectangle(sx, sy, TS, TS, fl);
    if (c == '.' && h < 20) DrawRectangle(sx + 8, sy + 20, 14, 2, ColorBrightness(fl, -0.1f));
    if (c == 'h') {
        DrawRectangleRounded((Rectangle) { (float)sx + 3, (float)sy + 10, 42, 28 }, 0.2f, 6, (Color) { 120, 78, 45, 255 });
        DrawRectangleRounded((Rectangle) { (float)sx + 3, (float)sy + 8, 42, 26 }, 0.2f, 6, (Color) { 168, 118, 75, 255 });
        if (y == TROW) DrawRectangle(sx + 14, sy + 14, 16, 11, accent);
        else        DrawRectangle(sx + 16, sy + 14, 12, 9, (Color) { 235, 235, 240, 255 });
    }
}

static void DrawBoard(const char* room, const char* title, float sx, float sy, float w, float h)
{
    DrawRectangleRounded((Rectangle) { sx, sy, w, h }, 0.1f, 6, (Color) { 120, 80, 45, 255 });
    DrawRectangleRounded((Rectangle) { sx + 4, sy + 4, w - 8, h - 8 }, 0.08f, 6, (Color) { 34, 70, 56, 255 });
    CenterFit(fReg, room, sx + w / 2, sy + 8, 13, w - 20, (Color) { 190, 215, 200, 255 });
    CenterFit(fBold, title, sx + w / 2, sy + 28, 24, w - 28, (Color) { 240, 245, 240, 255 });
    DrawRectangle((int)(sx + w / 2 - 30), (int)(sy + h - 14), 60, 2, (Color) { 190, 215, 200, 255 });
}

static void DrawBubble(float cx, float y, const char* s, Color col)
{
    float bob = sinf((float)GetTime() * 4.0f) * 2.0f;
    DrawCircle((int)cx, (int)(y + bob), 10, col);
    CenterTxt(fBold, s, cx, y + bob - 9, 16, (Color) { 30, 30, 40, 255 });
}

static void DrawNpcs(float camX, float camY)
{
    int n = INHALL ? 5 : 3;
    for (int i = 0; i < n; i++) {
        Teacher* t = INHALL ? &TEACH[inside][i] : &RIVT[i];
        int tx = INHALL ? 3 + 6 * i : (i == 0 ? 4 : (i == 1 ? 10 : 16));
        float cx = tx * TS - camX + TS / 2.0f, fy = TROW * TS - camY + TS - 6;
        DrawPerson(cx, fy, t->dir, t->shirt, t->hair, (Color) { 50, 55, 80, 255 }, INHALL, false, 0);
        if (INHALL) {
            if (!prog.read[inside][i]) DrawBubble(cx, fy - 72, "!", (Color) { 250, 205, 70, 255 });
            else if (prog.best[inside][i] == LESSONS[inside][i].nQ) DrawBubble(cx, fy - 72, "*", GOOD);
        }
        else {
            if (!prog.won[i]) DrawBubble(cx, fy - 72, "!", (Color) { 240, 100, 90, 255 });
            else              DrawBubble(cx, fy - 72, "*", GOOD);
        }
    }
}

static void DrawWorld(void)
{
    float dt = GetFrameTime();
    if (dt > 0.05f) dt = 0.05f;
    UpdateWorld(dt);

    Color accent = inside == 2 ? ARENA_C : ACCENTS[inside >= 0 ? inside : lang];
    int mw = MapW() * TS, mh = MapH() * TS;
    float ppx = wx * TS + (wmoving ? DX[wdir] * wt * TS : 0);
    float ppy = wy * TS + (wmoving ? DY[wdir] * wt * TS : 0);
    float camX = ppx + TS / 2 - W / 2.0f, camY = ppy + TS / 2 - H / 2.0f;
    camX = mw <= W ? (mw - W) / 2.0f : (camX < 0 ? 0 : (camX > mw - W ? (float)(mw - W) : camX));
    camY = mh <= H ? (mh - H) / 2.0f : (camY < 0 ? 0 : (camY > mh - H ? (float)(mh - H) : camY));
    camX = floorf(camX); camY = floorf(camY);

    ClearBackground(inside < 0 ? (Color) { 60, 120, 56, 255 } : BG);

    int tx0 = (int)(camX / TS), ty0 = (int)(camY / TS);
    if (tx0 < 0) tx0 = 0;
    if (ty0 < 0) ty0 = 0;
    int tx1 = (int)((camX + W) / TS) + 1, ty1 = (int)((camY + H) / TS) + 1;
    if (tx1 > MapW() - 1) tx1 = MapW() - 1;
    if (ty1 > MapH() - 1) ty1 = MapH() - 1;

    for (int y = ty0; y <= ty1; y++)
        for (int x = tx0; x <= tx1; x++) {
            int sx = (int)(x * TS - camX), sy = (int)(y * TS - camY);
            if (inside < 0) DrawCampusTile(TileAt(x, y), x, y, sx, sy);
            else            DrawInteriorTile(TileAt(x, y), x, y, sx, sy, accent);
        }

    if (inside < 0) {
        for (int b = 0; b < 3; b++)
            CenterFit(fBold, BLD[b].name, (BLD[b].x + 3.5f) * TS - camX, BLD[b].y * TS - camY + 34, 22, 7 * TS - 20, WHITE);
    }
    else if (INHALL) {
        for (int r = 0; r < 5; r++) {
            int x0 = 1 + r * 6;
            DrawBoard(TextFormat("ROOM %d", r + 1), LESSONS[inside][r].name + 3,
                x0 * TS - camX + 6, 8 - camY, 5 * TS - 12, 2 * TS - 20);
        }
    }
    else {
        CenterFit(fBold, "BATTLE ARENA", AW * TS / 2.0f - camX, 8 - camY, 26, 420, (Color) { 255, 205, 90, 255 });
        CenterTxt(fBold, "VS", 10 * TS + TS / 2.0f - camX, 6 * TS - camY, 40, Fade((Color) { 255, 205, 90, 255 }, 0.55f));
    }

    /* people, drawn back to front (teachers / rivals all stand on row TROW) */
    float px = ppx - camX + TS / 2.0f, py = ppy - camY + TS - 6;
    bool front = ppy >= TROW * TS;
    if (inside >= 0 && front) DrawNpcs(camX, camY);
    DrawPerson(px, py, wdir, (Color) { 225, 85, 85, 255 }, (Color) { 70, 45, 30, 255 },
        (Color) {
        55, 70, 120, 255
    }, false, true, wmoving ? walkPhase : 0);
    if (inside >= 0 && !front) DrawNpcs(camX, camY);

    /* HUD */
    const char* loc = inside < 0 ? "Campus" : (inside == 0 ? "C Hall" : (inside == 1 ? "C++ Hall" : "Battle Arena"));
    float lw = TxtW(fMed, loc, 18) + 70;
    Panel((Rectangle) { 20, 20, lw, 44 }, 0.3f, Fade(SURF, 0.92f), BORDER);
    DrawCircle(42, 42, 6, accent);
    Txt(fMed, loc, 58, 31, 18, TXT);

    if (dlg == DLG_NONE) {
        const char* hint = "Arrows / WASD move    Shift run    Space talk    Esc study menu";
        float hw = TxtW(fMed, hint, 14) + 32;
        Panel((Rectangle) { 20, H - 56, hw, 36 }, 0.3f, Fade(SURF, 0.92f), BORDER);
        Txt(fMed, hint, 36, H - 48, 14, DIM);
    }
    if (toastT > 0 && toast) {
        float tw = TxtW(fBold, toast, 22) + 48;
        Panel((Rectangle) { W / 2.0f - tw / 2, 24, tw, 48 }, 0.4f, Fade(SURF, 0.95f), accent);
        CenterTxt(fBold, toast, W / 2.0f, 33, 22, TXT);
    }

    /* dialogue */
    if (dlg != DLG_NONE) {
        Teacher* t = Speaker();
        float bx = 60, bh = 170, by = H - 200.0f, bw = W - 120;
        Panel((Rectangle) { bx, by, bw, bh }, 0.08f, SURF, accent);
        DrawPerson(bx + 90, by + bh - 20, 0, t->shirt, t->hair, (Color) { 50, 55, 80, 255 }, INHALL, false, 0);

        float nw = TxtW(fBold, t->name, 18) + 40;
        DrawRectangleRounded((Rectangle) { bx + 180, by - 18, nw, 36 }, 0.4f, 8, accent);
        Txt(fBold, t->name, bx + 200, by - 12, 18, WHITE);

        int len = (int)strlen(t->greet);
        int n = dlg == DLG_MENU ? len : (int)dlgChars;
        WrappedTyped(fReg, t->greet, bx + 180, by + 34, bw - 220, 20, TXT, n);

        if (dlg == DLG_TEXT && n >= len && ((int)(GetTime() * 2) & 1))
            Txt(fMed, "Press Space", bx + bw - 150, by + bh - 36, 15, DIM);

        if (dlg == DLG_MENU) {
            static const char* hallOpts[3] = { "Attend lecture", "Take a pop quiz", "Maybe later" };
            static const char* arenaOpts[2] = { "Start battle", "Maybe later" };
            int cnt = inside == 2 ? 2 : 3;
            const char** opts = inside == 2 ? arenaOpts : hallOpts;
            float ow = 300, oh = cnt * 44 + 20, ox = W - 60 - ow, oy = by - oh - 12;
            Panel((Rectangle) { ox, oy, ow, oh }, 0.1f, SURF, accent);
            for (int i = 0; i < cnt; i++) {
                Rectangle r = { ox + 10, oy + 10 + i * 44, ow - 20, 40 };
                if (CheckCollisionPointRec(GetMousePosition(), r)) {
                    hand = true; dlgSel = i;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { DlgChoose(i); break; }
                }
                if (i == dlgSel) DrawRectangleRounded(r, 0.3f, 8, Fade(accent, 0.28f));
                TxtFit(fMed, TextFormat("%s%d.  %s", i == dlgSel ? "> " : "   ", i + 1, opts[i]), r.x + 12, r.y + 8, 18, r.width - 24, TXT);
            }
        }
    }

    if (fade > 0) DrawRectangle(0, 0, W, H, Fade(BLACK, fade));
}

/* ------------------------------------------------------------------ */
/*  Battle Arena: head-to-head coding duel against a rival             */
/*  Both of you get the same problem. The first correct answer wins    */
/*  the round and damages the other fighter. First to 0 HP loses.      */
/* ------------------------------------------------------------------ */
typedef struct { const char* q, * code; const char* opts[4]; int correct; const char* expl; } BQuestion;

#define BQN 17
#define BTIME 20.0f

static const BQuestion BQS[BQN] = {
  { "What does this print?", "int x = 5;\nint y = x++ + 2;\nprintf(\"%d %d\", x, y);",
    { "5 7", "6 7", "6 8", "5 6" }, 1, "x++ gives 5 and then x becomes 6, so y = 5 + 2 = 7. Output: 6 7." },
  { "What does this print?", "int a[3] = {1, 2, 3};\nint *p = a;\nprintf(\"%d\", *(p + 2));",
    { "1", "2", "3", "Garbage" }, 2, "p + 2 points at a[2], which holds 3." },
  { "What is wrong with this code?", "int *p = malloc(4 * sizeof(int));\np[4] = 10;\nfree(p);",
    { "Nothing is wrong", "p[4] is out of bounds", "free must come first", "malloc needs a cast in C" }, 1,
    "Valid indexes are 0 to 3. p[4] writes past the end of the buffer." },
  { "What does this print?", "char s[] = \"Hi\";\nprintf(\"%zu %zu\", sizeof(s), strlen(s));",
    { "2 2", "3 2", "3 3", "2 3" }, 1, "sizeof counts the null terminator (3 bytes). strlen does not (2)." },
  { "After this code runs, what is true?", "int x = 10;\nint *p = &x;\n*p = 20;",
    { "x is still 10", "x is now 20", "p is now 20", "It will not compile" }, 1, "*p = 20 writes through the pointer, so x becomes 20." },
  { "What does this print?", "for (int i = 0; i < 3; i++) {\n    if (i == 1) continue;\n    printf(\"%d \", i);\n}",
    { "0 1 2", "0 2", "1 2", "0" }, 1, "continue skips the rest of the loop body when i is 1." },
  { "What happens here?", "int x = 5;\nif (x = 10) {\n    printf(\"ten\");\n}",
    { "Nothing is printed", "x becomes 10 and it prints ten", "It compares x with 10", "It will not compile" }, 1,
    "= assigns. The condition evaluates to 10 (true), so it prints. You wanted ==." },
  { "What does this print?", "int a = 7, b = 2;\nprintf(\"%d\", a / b);",
    { "3.5", "3", "4", "2" }, 1, "Integer division drops the decimal part: 7 / 2 is 3." },
  { "What does this print?", "int n = 0;\nwhile (n < 10) {\n    n += 3;\n}\nprintf(\"%d\", n);",
    { "9", "10", "12", "15" }, 2, "n goes 3, 6, 9, 12. The loop only stops once n >= 10, so it prints 12." },
  { "What does this print?", "std::vector<int> v = {1, 2, 3};\nv.push_back(4);\nstd::cout << v.size();",
    { "3", "4", "5", "0" }, 1, "push_back adds a fourth element, so size() is 4." },
  { "What does this print?", "void f(int &n) { n *= 2; }\n\nint x = 4;\nf(x);\nstd::cout << x;",
    { "4", "8", "2", "Compile error" }, 1, "n is a reference to x, so doubling n doubles x." },
  { "What does this print?", "void f(int n) { n *= 2; }\n\nint x = 4;\nf(x);\nstd::cout << x;",
    { "8", "4", "0", "Compile error" }, 1, "x is passed by value, so f only changes a copy." },
  { "Which letter is printed?",
    "struct A { virtual void hi() { std::cout << \"A\"; } };\nstruct B : A { void hi() override { std::cout << \"B\"; } };\n\nA *p = new B();\np->hi();",
    { "A", "B", "AB", "Compile error" }, 1, "hi() is virtual, so the call uses the real object type, B." },
  { "Why does this fail to compile?", "class Dog {\npublic:\n    Dog(int a) {}\n};\n\nDog d;",
    { "Dog has no default constructor", "Dog must be a struct", "a is unused", "d needs new" }, 0,
    "Once you write a constructor with parameters, the compiler no longer provides a default one." },
  { "What does this print?", "std::string s = \"C\";\ns += \"++\";\nstd::cout << s.size();",
    { "2", "3", "4", "1" }, 1, "s becomes \"C++\", which has 3 characters." },
  { "What does this print?", "int x = 3;\nswitch (x) {\n    case 3: printf(\"A\");\n    case 4: printf(\"B\"); break;\n    default: printf(\"C\");\n}",
    { "A", "AB", "ABC", "B" }, 1, "Case 3 has no break, so it falls through into case 4 and stops at its break." },
  { "What does this print?", "template <typename T>\nT twice(T v) { return v + v; }\n\nstd::cout << twice(2.5);",
    { "5", "2.5", "25", "Compile error" }, 0, "T is double, so 2.5 + 2.5 = 5.0, which cout prints as 5." }
};

/* how good each rival is: chance of a correct answer, and how long they think (seconds) */
static const struct { float acc, tMin, tMax; } RSTAT[3] = {
    { 0.55f, 6.0f, 12.0f },   /* Rookie Ron   */
    { 0.75f, 4.0f, 9.0f },    /* Rival Rex    */
    { 0.90f, 2.5f, 6.0f }     /* Champion Cora */
};

static int bRival = 0, bOrder[BQN], bRound = 0, bPHP = 100, bRHP = 100, bPick = -1, bPhase = 1;
static float bT = 0, bRivalAt = 5, bDispP = 100, bDispR = 100;
static bool bRivalCorrect = false, bRivalDone = false, bPlayerDone = false, bWon = false;
static char bMsg[200] = "";
static Color bMsgCol = { 139, 148, 170, 255 };

static float Rand01(void) { return GetRandomValue(0, 1000) / 1000.0f; }

static void BeginRound(void)
{
    bPhase = 1; bT = 0; bPick = -1;
    bPlayerDone = false; bRivalDone = false;
    bRivalAt = RSTAT[bRival].tMin + (RSTAT[bRival].tMax - RSTAT[bRival].tMin) * Rand01();
    bRivalCorrect = Rand01() < RSTAT[bRival].acc;
    snprintf(bMsg, sizeof bMsg, "%s is thinking...", RIVT[bRival].name);
    bMsgCol = DIM;
}

static void StartBattle(int r)
{
    bRival = r; bPHP = bRHP = 100; bDispP = bDispR = 100; bRound = 0; bWon = false;
    for (int i = 0; i < BQN; i++) bOrder[i] = i;
    for (int i = BQN - 1; i > 0; i--) {
        int j = GetRandomValue(0, i), t = bOrder[i];
        bOrder[i] = bOrder[j]; bOrder[j] = t;
    }
    screen = SCR_BATTLE;
    BeginRound();
}

/* winner: 1 = you, -1 = rival, 0 = nobody */
static void EndRound(int winner, const char* msg)
{
    if (winner == 1) {
        int d = 25 + (int)(15.0f * (1.0f - bT / BTIME));   /* faster answer = more damage */
        bRHP -= d; if (bRHP < 0) bRHP = 0;
        snprintf(bMsg, sizeof bMsg, "%s  (%s loses %d HP)", msg, RIVT[bRival].name, d);
        bMsgCol = GOOD;
    }
    else if (winner == -1) {
        bPHP -= 25; if (bPHP < 0) bPHP = 0;
        snprintf(bMsg, sizeof bMsg, "%s  (you lose 25 HP)", msg);
        bMsgCol = BAD;
    }
    else {
        snprintf(bMsg, sizeof bMsg, "%s", msg);
        bMsgCol = DIM;
    }
    bPhase = 2;
}

static void PlayerAnswer(const BQuestion* Q, int i)
{
    if (bPhase != 1 || bPlayerDone) return;
    bPick = i; bPlayerDone = true;
    if (i == Q->correct) { EndRound(1, "You solved it first!"); return; }
    bPHP -= 10; if (bPHP < 0) bPHP = 0;
    if (bPHP <= 0)       EndRound(0, "Wrong answer - you are out of HP!");
    else if (bRivalDone) EndRound(0, "Nobody got it this round.");
    else {
        snprintf(bMsg, sizeof bMsg, "Wrong answer! -10 HP. Waiting to see if %s gets it...", RIVT[bRival].name);
        bMsgCol = BAD;
    }
}

static void UpdateBattle(float dt)
{
    bT += dt;
    if (!bRivalDone && bT >= bRivalAt) {
        bRivalDone = true;
        char buf[128];
        if (bRivalCorrect) {
            snprintf(buf, sizeof buf, "%s answered correctly first!", RIVT[bRival].name);
            EndRound(-1, buf);
            return;
        }
        if (bPlayerDone) { EndRound(0, "Nobody got it this round."); return; }
        snprintf(bMsg, sizeof bMsg, "%s got it wrong! Answer now to take the round.", RIVT[bRival].name);
        bMsgCol = GOOD;
    }
    if (bT >= BTIME) EndRound(0, "Time is up - round drawn.");
}

static void DrawFighter(float x, float y, float w, const char* name, float hp, bool you,
    Teacher* t, const char* status)
{
    Panel((Rectangle) { x, y, w, 96 }, 0.12f, SURF, BORDER);
    if (you) DrawPerson(x + 44, y + 88, 0, (Color) { 225, 85, 85, 255 }, (Color) { 70, 45, 30, 255 },
        (Color) {
        55, 70, 120, 255
    }, false, true, 0);
    else     DrawPerson(x + 44, y + 88, 0, t->shirt, t->hair, (Color) { 50, 55, 80, 255 }, false, false, 0);

    TxtFit(fBold, name, x + 90, y + 10, 20, w - 110, TXT);
    float bw = w - 110, frac = hp / 100.0f;
    if (frac < 0) frac = 0;
    DrawRectangleRounded((Rectangle) { x + 90, y + 46, bw, 14 }, 0.5f, 8, SURF2);
    Color hc = frac > 0.5f ? GOOD : (frac > 0.25f ? (Color) { 240, 180, 60, 255 } : BAD);
    if (bw * frac > 8) DrawRectangleRounded((Rectangle) { x + 90, y + 46, bw* frac, 14 }, 0.5f, 8, hc);
    Txt(fReg, TextFormat("HP %d / 100", (int)(hp + 0.5f)), x + 90, y + 66, 14, DIM);
    if (status) {
        float sw = TxtW(fMed, status, 14);
        Txt(fMed, status, x + w - 16 - sw, y + 66, 14, DIM);
    }
}

static void DrawBattle(void)
{
    float dt = GetFrameTime();
    if (dt > 0.05f) dt = 0.05f;
    if (bPhase == 1) UpdateBattle(dt);
    float k = dt * 6 > 1 ? 1 : dt * 6;
    bDispP += (bPHP - bDispP) * k;
    bDispR += (bRHP - bDispR) * k;

    const Color ac = ARENA_C;
    const char* rname = RIVT[bRival].name;
    const BQuestion* Q = &BQS[bOrder[bRound]];

    TopBar();
    if (Button((Rectangle) { 24, 14, 104, 44 }, "< Flee", SURF2, 16)) { GoMenu(); return; }
    TxtFit(fMed, TextFormat("Battle Arena  /  vs %s", rname), 150, 20, 22, 640, TXT);
    if (bPhase != 3) {
        const char* rt = TextFormat("Round %d", bRound + 1);
        Txt(fMed, rt, W - 36 - TxtW(fMed, rt, 18), 22, 18, ac);
    }

    float pw = 520;
    DrawFighter(36, 88, pw, "You", bDispP, true, NULL, NULL);
    DrawFighter(W - 36 - pw, 88, pw, rname, bDispR, false, &RIVT[bRival],
        bPhase != 1 ? NULL : (bRivalDone ? "locked out" : "thinking..."));
    CenterTxt(fBold, "VS", W / 2.0f, 112, 34, ac);

    /* ---- match over ---- */
    if (bPhase == 3) {
        float cx = W / 2.0f;
        Panel((Rectangle) { cx - 320, 210, 640, 440 }, 0.05f, SURF, bWon ? GOOD : BAD);
        CenterTxt(fBold, bWon ? "Victory!" : "Defeated", cx, 236, 46, bWon ? GOOD : BAD);
        CenterFit(fReg, bWon ? TextFormat("You beat %s!", rname) : TextFormat("%s wins this time.", rname), cx, 308, 22, 560, TXT);
        CenterTxt(fMed, TextFormat("Final HP   You %d   -   %s %d", bPHP, rname, bRHP), cx, 360, 18, DIM);
        CenterFit(fReg, bWon ? "Your win is saved - a star now shows above them on the map."
            : "Review the lessons in the halls, then challenge them again.", cx, 410, 17, 560, DIM);
        if (Button((Rectangle) { cx - 270, 520, 250, 56 }, "Rematch", ac, 18)) StartBattle(bRival);
        if (Button((Rectangle) { cx + 20, 520, 250, 56 }, "Back to campus", SURF2, 18)) GoMenu();
        return;
    }

    /* ---- timer ---- */
    float frac = 1.0f - bT / BTIME;
    if (frac < 0) frac = 0;
    DrawRectangleRounded((Rectangle) { 36, 196, W - 72, 8 }, 0.5f, 8, SURF2);
    if ((W - 72) * frac > 8) DrawRectangleRounded((Rectangle) { 36, 196, (W - 72)* frac, 8 }, 0.5f, 8, frac > 0.25f ? ac : BAD);

    /* ---- problem ---- */
    Txt(fBold, "PROBLEM", 36, 212, 13, ac);
    int qEnd = Wrapped(fBold, Q->q, 36, 230, W - 72, 22, TXT);
    DrawCode(Q->code, 36, (float)(qEnd + 4), W - 72, 18, "problem");

    if (bPhase == 1) {
        for (int i = 0; i < 4; i++) {
            Rectangle r = { 36 + (i & 1) * 571.0f, 548.0f + (i >> 1) * 66, 557, 56 };
            bool hov = CheckCollisionPointRec(GetMousePosition(), r);
            Color fill = SURF, border = BORDER, badge = SURF2, text = TXT;
            if (!bPlayerDone && hov) { fill = SURF2; border = ac; hand = true; }
            if (bPlayerDone && i == bPick) { fill = Fade(BAD, 0.13f); border = BAD; badge = BAD; }
            else if (bPlayerDone) text = DIM;
            Panel(r, 0.22f, fill, border);
            DrawCircle((int)r.x + 30, (int)r.y + 28, 16, badge);
            CenterTxt(fBold, TextFormat("%c", 'A' + i), r.x + 30, r.y + 16, 16, TXT);
            TxtFit(fReg, Q->opts[i], r.x + 60, r.y + 14, 20, r.width - 80, text);
            if (!bPlayerDone && ((hov && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ||
                IsKeyPressed(KEY_ONE + i) || IsKeyPressed(KEY_A + i)))
                PlayerAnswer(Q, i);
        }
        TxtFit(fMed, bMsg, 36, 686, 18, W - 72, bMsgCol);
    }
    else {
        Panel((Rectangle) { 36, 548, W - 72, 150 }, 0.08f, SURF, bMsgCol);
        TxtFit(fBold, bMsg, 58, 558, 20, W - 330, bMsgCol);
        Txt(fMed, TextFormat("Answer:  %c)  %s", 'A' + Q->correct, Q->opts[Q->correct]), 58, 592, 17, TXT);
        Wrapped(fReg, Q->expl, 58, 620, W - 72 - 290, 15, (Color) { 205, 211, 228, 255 });

        bool over = bPHP <= 0 || bRHP <= 0 || bRound >= BQN - 1;
        if (Button((Rectangle) { W - 36 - 190, 596, 170, 52 }, over ? "See result" : "Next round", ac, 18)
            || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            if (over) {
                bWon = bRHP <= 0 || (bPHP > 0 && bPHP > bRHP);
                if (bWon) { prog.won[bRival] = 1; SaveProgress(); }
                bPhase = 3;
            }
            else {
                bRound++; BeginRound();
            }
        }
    }
}

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */
int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);      /* smoother rounded corners */
    InitWindow(W, H, "CodeQuest - Learn C & C++");
    SetExitKey(KEY_NULL);                   /* we handle ESC ourselves */
    SetTargetFPS(60);

    fReg = LoadF("LiberationSerif-Regular.ttf", 64);
    fMed = LoadF("LiberationSerif-Bold.ttf", 64);
    fBold = LoadF("LiberationSerif-Bold.ttf", 64);
    fCode = LoadF("DejaVuSansMono.ttf", 18);   /* code is always drawn at size 18 */
    LoadProgress();
    BuildMaps();
    WorldEnter();                           /* start in the campus sim */

    while (!quit && !WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (screen == SCR_MENU) quit = true;
            else if (screen == SCR_WORLD) {
                if (dlg != DLG_NONE) dlg = DLG_NONE;
                else { fromWorld = false; screen = SCR_MENU; }
            }
            else GoMenu();
        }

        hand = false;
        Color accent = ACCENTS[lang];
        BeginDrawing();
        ClearBackground(BG);
        switch (screen) {
        case SCR_MENU:   DrawMenu(accent);   break;
        case SCR_LESSON: DrawLesson(accent); break;
        case SCR_QUIZ:   DrawQuiz(accent);   break;
        case SCR_RESULT: DrawResult(accent); break;
        case SCR_WORLD:  DrawWorld();        break;
        case SCR_BATTLE: DrawBattle();       break;
        }
        EndDrawing();
        SetMouseCursor(hand ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);
    }

    SaveProgress();
    UnloadFont(fReg); UnloadFont(fMed); UnloadFont(fBold); UnloadFont(fCode);
    CloseWindow();
    return 0;
}