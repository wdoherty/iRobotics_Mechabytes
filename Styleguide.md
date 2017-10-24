# Mechabytes Style Guide
Revised October 19, 2017


## Header Files
In general, every `.cpp` file should have an associated `.h` file.  Exceptions include unit tests and small `.cpp` files with only a `main()` function.

### The #define Guard
All header files should have `#define` guards to prevent multiple inclusion.  
The format of the symbol name should depends slightly on the scope of the file.  Standard libraries should use `<CLASSNAME>_H_`, while competition specific files should use `MRDC_<YEAR>_<CLASSNAME><_H_`.

For example, the 2018 Swerve Drive header file should have the following guard:

```c++
#ifndef MRDC_2018_SWERVEDRIVE_H_
#define MRDC_2018_SWERVEDRIVE_H_

...

#endif   // MRDC_2018_SWERVEDRIVE_H_
```

### Inline Functions
Define inline functions only when they are small (i.e. 10 lines or fewer).

### Names and Order of Includes
Use the following standard order to enhance readability and avoid hidden dependencies:

* Related header, C library, C++ library, other libraries' `.h`, your project's `.h`

Within each of these categories, includes should be ordered alphabetically.

You should include all the headers that define symbols you rely upon.  If you rely on symbols from `bar.h`, don't count on the fact that you included `foo.h` which (currently) includes `bar.h`: include `bar.h` yourself, unless `foo.h` explicitly demonstrates its intent to provide those symbols.  However, any includes present in the related header do not need to be included again in the related `.cpp`.

**Note:** If all `.h` files have been properly guarded, duplicate includes will have no effect.


## Scoping

### Namespaces
For the purposes of MRDC project code, do not use namespaces.  Instead, include relevant scope details in the symbol name.  This will prevent cluttering and complicating the codebase.

### Local Variables
Place a function's variables in the narrowest scope possible, and initialize the variables in the declaration.

Variables needed for `if` and `for` loops should normally be declared within those statements, so they are confined to those scopes.  E.g.:

```c++
for (int i = 0; i < limit; i ++) {}
```

There is one caveat: if the variable is an object, that object will be constructed and deconstructed every time the program enters and exits that scope.  It may be more efficient to declare such a variable just before the loop.

```c++
// Inefficient implementation:
for (int i = 0; i < 1000000; ++i) {
   Foo f;  // constructor and destructor get called 1000000 times each.
   f.doSomething(i);
}

// Better implementation
Foo f;  // constructor and destructor get called once each.
for (int i = 0; i < 1000000; ++i) {
  f.doSomething(i);
}
```

### Static and Global Variables
Static members may not be variables of class type.  This introduces problems and bugs when destructors are called before references are destroyed.

Objects with static storage duration (defined as `static`), including global variables, static variables, static class member variables, and function static variables, must be Plain Old Data (POD): only ints, chars, floats, or pointers, or arrays/structs of POD.


## Classes

### Doing Work in Constructor
Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.

If you must call other functions to properly initialize an object, consider using an `init()` method.

### Structs vs. Classes
Use a `struct` only for passive objects that carry data; everything else is a class.

`structs` should be used for passive objects that carry data, and may have associated constants, but lack any functionality other than access/setting of the data members.  The access/setting of data members is done by directly accessing the fields, rather than through method invocations.  Methods should not provide behavior but should only be used to set up data members, e.g., constructor, destructor, `initialize()`, `reset()`, `validate()`.

### Inheritance
Composition is often more appropriate than inheritance.  When using inheritance, make it `public`.  
There are two types of inheritance in C++: implementation inheritance, in which actual code is inherited by the child, and interface inheritance, in which only method names are inherited. Interface inheritance is useful for programmatically enforcing an API.

* All inheritance should be `public`.  If you want to do private inheritance, you should be including an instance of the base class as a member instead.  
* Do not overuse implementation inheritance. Composition is often more appropriate. Try to restrict use of inheritance to the "is-a" case: `Bar` subclasses `Foo` if it can reasonably be said that `Bar` "is a kind of" `Foo`.  
* Make your destructor `virtual` if necessary. If your class has virtual methods, its destructor should be virtual.  
* Limit the use of `protected` to those members that might need to be accessed from a subclass.  Note than data members should be `private`.  
* Explicitly annotate overrides of virtual functions with an `override` specifier.

### Operator Overloading
Overload operators judiciously. Do not create user-defined literals.

* Define overloaded operators only if their meaning is obvious, unsurprising, and consistent with the corresponding built-in operators. For example, use | as a bitwise- or logical-or, not as a shell-style pipe.
* Define operators only on your own types. More precisely, define them in the same headers, .cpp files, and namespaces as the types they operate on. That way, the operators are available wherever the type is, minimizing the risk of multiple definitions. If possible, avoid defining operators as templates, because they must satisfy this rule for any possible template arguments. If you define an operator, also define any related operators that make sense, and make sure they are defined consistently. For example, if you overload <, overload all the comparison operators, and make sure < and never return true for the same arguments.
* Prefer to define non-modifying binary operators as non-member functions. If a binary operator is defined as a class member, implicit conversions will apply to the right-hand argument, but not the left-hand one. It will confuse your users if a < b compiles but b < a doesn't.
* Don't go out of your way to avoid defining operator overloads. For example, prefer to define ==, =, and <<, rather than Equals(), CopyFrom(), and PrintTo(). Conversely, don't define operator overloads just because other libraries expect them. For example, if your type doesn't have a natural ordering, but you want to store it in a std::set, use a custom comparator rather than overloading <.
* Do not overload &&, ||, , (comma), or unary &. Do not overload operator"", i.e. do not introduce user-defined literals.

### Access Control
Make data members `private`, unless they are `static const`

### Declaration Order
Group similar declarations together, placing public parts earlier.

A class definition should usually start with a public: section, followed by protected:, then private:. Omit sections that would be empty.

Within each section, generally prefer grouping similar kinds of declarations together, and generally prefer the following order: types (including typedef, using, and nested structs and classes), constants, factory functions, constructors, assignment operators, destructor, all other methods, data members.

Do not put large method definitions inline in the class definition. Usually, only trivial or performance-critical, and very short, methods may be defined inline.


## Functions

### Parameter Ordering
When defining a function, parameter order is: inputs, then outputs.

Input parameters are usually values or `const` references, while output and input/output parameters are pointers to non-`const`.  When ordering function parameters, try to put all input parameters before any output parameters.  You should, however, maintain consistency with related functions.

### Write Short Functions
Prefer small and focused functions.

Since some long tasks make sense as a single function, there is no hard limit on function length.  Though, if a function exceeds about 40 lines, think about whether it can be broken up without harming the structure of the program.

Long functions can become cumbersome to maintain and could introduce difficult to track bugs if something changes.  It is easier to manage code written with smaller functions that are used together to accomplish larger tasks.

### Function Overloading
Use overloaded functions (including constructors) only if a reader looking at a call site can get a good idea of what is happening without having to first figure out exactly which overload is being called.

If you want to overload a function to accept different argument types, consider qualifying the name with some information about the arguments, e.g., `appendString(), appendInt()` rather than just `append()`.

### Default Arguments
Default arguments are allowed on non-virtual functions when the default is guaranteed to always have the same value.  Do no use default values where the specified default might not evaluate to the same value depending on when it was evaluated (e.g., don't write `void f(int n = counter++);`)

### Trailing Return Type Syntax
C++11 introduced the option to declare a function's return type after the argument list. For example, `int foo(int x);` could be written as `auto foo(int x) -int;` in C++11.  To maintain consistency and readability, avoid using this new syntax unless explicitly required (i.e. for lambda expressions), or it significantly improves the readability (i.e. for template parameters).


## Naming

### General Naming Rules
Names should be descriptive; avoid abbreviation.

Give as descriptive a name as possible, within reason. Do not worry about saving horizontal space as it is far more important to make your code immediately understandable by a new reader. Do not use abbreviations that are ambiguous or unfamiliar to readers outside your project, and do not abbreviate by deleting letters within a word.

```c++
int price_count_reader;    // No abbreviation.
int num_errors;            // "num" is a widespread convention.
int num_dns_connections;   // Most people know what "DNS" stands for.

...

int n;                     // Meaningless.
int nerr;                  // Ambiguous abbreviation.
int n_comp_conns;          // Ambiguous abbreviation.
int wgc_connections;       // Only your group knows what this stands for.
int pc_reader;             // Lots of things can be abbreviated "pc".
int cstmr_id;              // Deletes internal letters.
```

Note that certain universally-known abbreviations are OK, such as i for an iteration variable and T for a template parameter.

### File Names
Filenames should match the class name of the primary class in the file.  Underscores or dashes may be used to differentiate similar or ambiguous files.

C++ files should end in `.cpp` and header files should end in `.h`.  Use the same file name for both the C++ file and the header file if they refer to the same class.

Inline functions should be defined in a `.h` file.

### Type Names
Type names should use Upper Camel Case - starting with a capital letter and have a capital letter for each new word, with no underscores.  The names of all types - classes, structs, type aliases, enums, and type template parameters - have the same naming convention.

### Variable Names
Variable names should use Lower Camel Case - start with a lower case letter and capitalize each new word, with no dashes or underscores. Private data members of classes (but not structs) should also include a leading underscore to quickly identify public vs. private usage.

### Constant Names
Variables declared `const`, and whose value is fixed for the duration of the program, should be named with a leading "k" followed by mixed case. For example:

```c++
const int kDaysInAWeek = 7;
```

### Function Names
Functions should generally use Upper Camel Case; accessors and mutators (getters and setters) may be named like variables.

### Macro Names
Macros that implement a function should be avoided (use an inline function instead), but using a macro for a global constant is acceptable, though `const` variables are preferred to narrow the scope.

Name macros using all capitals and underscores.


## Comments
Though a pain to write, comments are absolutely vital to keeping our code readable. The following rules describe what you should comment and where. But remember: while comments are very important, the best code is self-documenting. Giving sensible names to types and variables is much better than using obscure names that you must then explain through comments.

### Comment Style
Use either `//` or `/* */` syntax, as long as you are consistent.

Since many IDEs and text editors can recognize and collapse block comments using the `/* */` syntax, it makes sense to use that for large comment sections, such as before a function or before a particularly complex part of code.  If your comment is less than 3-4 lines, consider using `//` to maintain consistency.

The single line comment syntax also has the advantage that most IDEs and editors can convert multiple lines to comments automatically using a keyboard shortcut, by placing `//` at the beginning of each line.

### File Comments
While not required, any file that contains significant functionality should include a comment at the beginning of the file to describe its purpose.  This should be a high level description of the functionality added by the file and should not get into implementation specifics.  However, the comment should include sufficient detail so a reader does not have to read the code to figure out what the file contains.  If a file contains a single class, and that class has a class comment as described below, the file comment can be omitted.

### Class Comments
Every non-obvious class declaration should have an accompanying comment that describes what it is for and how it should be used.

The class comment should provide the reader with enough information to know how and when to use the class, as well as any additional considerations necessary to correctly use the class.  This is often a good place to include a short snippet demonstrating a simple usage of the class.

When the declaration and definition are sufficiently separated (e.g. `.h` and `.cpp` files), comments describing the use of the class should go together with its interface definition; comments about the class operation and implementation should accompany the implementation of the class's methods.

### Function Comments
Declaration comments describe the use of a function (when it is non-obvious); comments at the definition of a function describe operation.

##### Function Declarations
Almost every function declaration should have comments immediately preceding it that describe what the function does and how to use it. These comments may be omitted only if the function is simple and obvious (e.g. simple accessors for obvious properties of the class). These comments should be descriptive ("Opens the file") rather than imperative ("Open the file"); the comment describes the function, it does not tell the function what to do. In general, these comments do not describe how the function performs its task. Instead, that should be left to comments in the function definition.

Types of things to mention in comments at the function declaration:

* What the inputs and outputs are.
* For class member functions: whether the object remembers reference arguments beyond the duration of the method call, and whether it will free them or not.
* If the function allocates memory that the caller must free.
* Whether any of the arguments can be a null pointer.
* If there are any performance implications of how a function is used.

When documenting function overrides, focus on the specifics of the override itself, rather than repeating the comment from the overridden function. In many of these cases, the override needs no additional documentation and thus no comment is required.

When commenting constructors and destructors, remember that the person reading your code knows what constructors and destructors are for, so comments that just say something like "destroys this object" are not useful. Document what constructors do with their arguments (for example, if they take ownership of pointers), and what cleanup the destructor does. If this is trivial, just skip the comment. It is quite common for destructors not to have a header comment.

##### Function Definitions
If there is anything tricky about how a function does its job, the function definition should have an explanatory comment. For example, in the definition comment you might describe any coding tricks you use, give an overview of the steps you go through, or explain why you chose to implement the function in the way you did rather than using a viable alternative.

Note you should not just repeat the comments given with the function declaration, in the .h file or wherever. It's okay to recapitulate briefly what the function does, but the focus of the comments should be on how it does it.

### Variable Comments
In general the actual name of the variable should be descriptive enough to give a good idea of what the variable is used for. In certain cases, more comments are required.

##### Class Data Members
The purpose of each class data member (also called an instance variable or member variable) must be clear. If there are any invariants (special values, relationships between members, lifetime requirements) not clearly expressed by the type and name, they must be commented. However, if the type and name suffice (int num_events_;), no comment is needed.

In particular, add comments to describe the existence and meaning of sentinel values, such as nullptr or -1, when they are not obvious.

##### Global Variables
All global variables should have a comment describing what they are, what they are used for, and (if unclear) why it needs to be global.

### Implementation Comments
In your implementation you should have comments in tricky, non-obvious, interesting, or important parts of your code.

##### Explanatory Comments
Tricky or complicated code blocks should have comments before them.

##### Line Comments
Also, lines that are non-obvious should get a comment at the end of the line.
You may choose to align multiple line comments with each other, or put them right after the code.  If placed after the code, these end-of-line comments should be separated from the code by 2 spaces.  If aligned with other comments, the alignment should be consistent within a file.

Whichever style you choose, be consistent with yourself.

##### Function Argument Comments
When the meaning of a function argument is non-obvious, consider one of the following remedies:

* If the argument is a literal constant, and the same constant is used in multiple function calls in a way that tacitly assumes they're the same, you should use a named constant to make that constraint explicit, and to guarantee that it holds.
* Consider changing the function signature to replace a bool argument with an enum argument. This will make the argument values self-describing.
* For functions that have several configuration options, consider defining a single class or struct to hold all the options , and pass an instance of that. This approach has several advantages. Options are referenced by name at the call site, which clarifies their meaning. It also reduces function argument count, which makes function calls easier to read and write. As an added benefit, you don't have to change call sites when you add another option.
* Replace large or complex nested expressions with named variables.
* As a last resort, use comments to clarify argument meanings at the call site.

##### Don'ts
Do not state the obvious. In particular, don't literally describe what code does, unless the behavior is nonobvious to a reader who understands C++ well. Instead, provide higher level comments that describe why the code does what it does, or make the code self describing.

### Punctuation, Spelling, and Grammar
Pay attention to punctuation, spelling, and grammar; it is easier to read well-written comments than badly written ones.

Comments should be as readable as narrative text, with proper capitalization and punctuation. In many cases, complete sentences are more readable than sentence fragments. Shorter comments, such as comments at the end of a line of code, can sometimes be less formal, but you should be consistent with your style.

### TODO Comments
Use TODO comments for code that is temporary, a short-term solution, or good-enough but not perfect. E.g.
```c++
// TODO: this method works, but does not handle edge cases. Fix before competition
void FunctionToBeFixed();
```


## Formatting
Coding style and formatting are pretty arbitrary, but a project is much easier to follow if everyone uses the same style. Individuals may not agree with every aspect of the formatting rules, and some of the rules may take some getting used to, but it is important that all project contributors follow the style rules so that they can all read and understand everyone's code easily.

### Line Length
Each line of text in your code should keep a reasonable length.  Traditionally, lines have been limited to 80 characters (or columns).  This is restrictive and reminiscent of early programming environments with low resolution displays.  Today's displays and environments are capable of displaying much longer lines with ease, though longer lines can be harder to read.

To balance readability and convenience, lines of text should be **at most 120 characters**, but the shorter the better.

Exceptions include string literals, comments, `#include` statements, and header guards that cannot be made to fit in the above restriction.

### Spaces vs. Tabs
Use only spaces, indenting 4 spaces at a time.  You should set your editor to use "soft tabs" (insert spaces when the tab key is pressed).  Tab characters will display differently on different machines/editors/viewers and must be avoided.

### Function Declarations and Definitions
Return type on the same line as function name, parameters on the same line if they fit. Wrap parameter lists which do not fit on a single line as you would wrap arguments in a function call.

Functions look like this:
```c++
ReturnType ClassName::FunctionName(Type parameterName1, Type parameterName2) {
    DoSomething();
    ...
}
```
If you have too much text to fit on one line:
```c++
ReturnType ClassName::ReallyLongFunctionName(Type parameterName1, Type parameterName2,
                                             Type parameterName3) {
    DoSomething();
    ...
}
```
or if you cannot fit even the first parameter:
```c++
ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
        Type parameterName1,  // 8 space indent
        Type parameterName2,
        Type parameterName3) {
    DoSomething();  // 4 space indent
    ...
}
```

Some points to note:

* Choose good parameter names.
* Parameter names may be omitted only if the parameter is unused and its purpose is obvious.
* If you cannot fit the return type and the function name on a single line, break between them.
* If you break after the return type of a function declaration or definition, do not indent.
* The open parenthesis is always on the same line as the function name.
* There is never a space between the function name and the open parenthesis.
* There is never a space between the parentheses and the parameters.
* The open curly brace is always on the end of the last line of the function declaration, not the start of the next line.
* The close curly brace is either on the last line by itself or on the same line as the open curly brace.
* There should be a space between the close parenthesis and the open curly brace.
* All parameters should be aligned if possible.
* Default indentation is 4 spaces.
* Wrapped parameters have an 8 space indent.

### Function Calls
Either write the call all on a single line, wrap the arguments at the parenthesis, or start the arguments on a new line indented by four spaces and continue at that 4 space indent. In the absence of other considerations, use the minimum number of lines, including placing multiple arguments on each line where appropriate.

Function calls have the following format:
```c++
bool result = DoSomething(argument1, argument2, argument3);
```
If the arguments do not all fit on one line, they should be broken up onto multiple lines, with each subsequent line aligned with the first argument. Do not add spaces after the open paren or before the close paren:
```c++
bool result = DoSomething(aVeryVeryVeryVeryLongArgument1,
                          argument2, argument3);
```
Arguments may optionally all be placed on subsequent lines with a four space indent:
```c++
if (...) {
    ...
    ...
    if (...) {
        bool result = DoSomething(
            argument1, argument2,  // 4 space indent
            argument3, argument4);
        ...
    }
```

Put multiple arguments on a single line to reduce the number of lines necessary for calling a function unless there is a specific readability problem. Some find that formatting with strictly one argument on each line is more readable and simplifies editing of the arguments. However, we prioritize for the reader over the ease of editing arguments, and most readability problems are better addressed with the following techniques.

If having multiple arguments in a single line decreases readability due to the complexity or confusing nature of the expressions that make up some arguments, try creating variables that capture those arguments in a descriptive name:
```c++
int myHeuristic = scores[x] * y + bases[x];
bool result = DoSomething(myHeuristic, x, y, z);
```
Or put the confusing argument on its own line with an explanatory comment:
```c++
bool result = DoSomething(scores[x] * y + bases[x],  // Score heuristic.
                          x, y, z);
```
If there is still a case where one argument is significantly more readable on its own line, then put it on its own line. The decision should be specific to the argument which is made more readable rather than a general policy.

Sometimes arguments form a structure that is important for readability. In those cases, feel free to format the arguments according to that structure:
```c++
// Transform the widget by a 3x3 matrix.
myWidget.Transform(x1, x2, x3,
                   y1, y2, y3,
                   z1, z2, z3);
```

### Conditionals
The only spaces present in the conditional parentheses should be to separate logical expressions or operators.  Boolean expressions should be formatted according to the rules listed below.

All conditional statements must include a space between the `if` and open parenthesis, as well as between the closing parenthesis and curly brace.

The `else` keyword can be placed on the same line as the closing brace or on the next line. Just be consistent.

Curly braces are always required, even for single line statements.  The curly braces and statement may appear on the same line, or on separate lines, but the opening curly brace must always be on the same line as the end of the conditional expression.

Examples:
```c++
// Good
if (condition) {    // no space inside parenthesis
    ...             // 4 space indent
} else if (...) {   // else on the same line as closing brace
    ...
} else {            // opening brace on same line as keyword

}

// Good
if (condition) {    // space after if and before opening brace
    ...
}
else {              // else on line after closing brace
    ...
}

// Ok
if (condition) { DoSomething(); }

// Bad
if( condition ){    // improper spacing
    ...
} else              // do not break else-if into multiple lines
if (...){
    ...
}

// Bad
if (condition)      // always include curly braces
    DoSomething();
```

### Loops and Switch Statements
Switch statements may use braces for blocks. Annotate non-trivial fall-through between cases. Braces are optional for single-statement loops. Empty loop bodies should use empty braces or continue.

case blocks in switch statements can have curly braces or not, depending on your preference. If you do include curly braces they should be placed as shown below.

If not conditional on an enumerated value, switch statements should always have a default case (in the case of an enumerated value, the compiler will warn you if any values are not handled). If the default case should never execute, simply assert:
```c++
switch (var) {
  case 0: {  // 2 space indent
    ...      // 4 space indent
    break;
  }
  case 1: {
    ...
    break;
  }
  default: {
    assert(false);
  }
}
```
Braces are still required for single-statement loops.
```c++
for (int i = 0; i < kSomeNumber; ++i)       // Bad
  printf("I love you\n");

for (int i = 0; i < kSomeNumber; ++i) {     // Good
  printf("I take it back\n");
}
```
Empty loop bodies should use an empty pair of braces and an optional `continue`, but not a single semicolon.
```c++
while (condition) {
  // Repeat test until it returns false.
}
for (int i = 0; i < kSomeNumber; ++i) {}  // Good - one newline is also OK.
while (condition) { continue; }  // Good - continue indicates no logic.
```
```c++
while (condition);  // Bad - looks like part of do/while loop.
```

### Pointer and Reference Expressions
No spaces around period or arrow. Pointer operators do not have trailing spaces.

The following are examples of correctly-formatted pointer and reference expressions:
```c++
x = *p;
p = &x;
x = r.y;
x = r->y;
```
Note that:
* There are no spaces around the period or arrow when accessing a member.
* Pointer operators have no space after the * or &.

When declaring a pointer variable or argument, you may place the asterisk adjacent to either the type or to the variable name:
```c++
// These are fine, space preceding.
char *c;
const string &str;

// These are fine, space following.
char* c;
const string& str;
```

It is allowed (if unusual) to declare multiple variables in the same declaration, but it is disallowed if any of those have pointer or reference decorations. Such declarations are easily misread.
```c++
// Fine if helpful for readability.
int x, y;
int x, *y;  // Disallowed - no & or * in multiple declaration
char * c;  // Bad - spaces on both sides of *
const string & str;  // Bad - spaces on both sides of &
```

You should be consistent within a single file, so, when modifying an existing file, use the style in that file.

### Boolean Expressions
When you have a boolean expression that is longer than the standard line length, be consistent in how you break up the lines.

In this example, the logical AND operator is always at the end of the lines:
```c++
if (this_one_thing > this_other_thing &&
    a_third_thing == a_fourth_thing &&
    yet_another && last_one) {
    ...
}
```
Note that when the code wraps in this example, both of the && logical AND operators are at the end of the line. Feel free to insert extra parentheses judiciously because they can be very helpful in increasing readability when used appropriately. Also note that you should always use the punctuation operators, such as `&&` and `~`, rather than the word operators, such as `and` and `compl`.

### Return Values
Do not needlessly surround the `return` expression with parentheses.

Use parentheses in `return expr;` only where you would use them in `x = expr;`.

### Preprocessor Directives
The hash mark that starts a preprocessor directive should always be at the beginning of the line.

Even when preprocessor directives are within the body of indented code, the directives should start at the beginning of the line.

### Class Format
Sections in `public`, `protected` and `private` order, each indented two spaces.

The basic format for a class definition (lacking the comments, see Class Comments for a discussion of what comments are needed) is:
```c++
class MyClass : public OtherClass {
  public:      // Note the 2 space indent!
    MyClass();  // Regular 4 space indent.
    explicit MyClass(int var);
    ~MyClass() {}

    void SomeFunction();
    void SomeFunctionThatDoesNothing() {
    }

    void setSomeVar(int var) { _some_var = var; }
    int someVar() const { return _some_var; }

  private:
    bool SomeInternalFunction();

    int _some_var;
    int _some_other_var;
};
```
Things to note:

* Any base class name should be on the same line as the subclass name, subject to the 120-column limit.
* The `public:`, `protected:`, and `private:` keywords should be indented two spaces.
* Except for the first instance, these keywords should be preceded by a blank line. This rule is optional in small classes.
* Do not leave a blank line after these keywords.
* The `public` section should be first, followed by the `protected` and finally the `private` section.
* See Declaration Order for rules on ordering declarations within each of these sections.

### Horizontal Whitespace
Use of horizontal whitespace depends on location. Never put trailing whitespace at the end of a line.

##### General
```c++
void f(bool b) {  // Open braces should always have a space before them.
  ...
int i = 0;  // Semicolons usually have no space before them.
// Spaces inside braces for braced-init-list are optional.  If you use them,
// put them on both sides!
int x[] = { 0 };
int x[] = {0};

// Spaces around the colon in inheritance and initializer lists.
class Foo : public Bar {
  public:
    // For inline function implementations, put spaces between the braces
    // and the implementation itself.
    Foo(int b) : Bar(), _baz(b) {}  // No spaces inside empty braces.
    void Reset() { _baz = 0; }  // Spaces separating braces from implementation.
    ...
```
Adding trailing whitespace can cause extra work for others editing the same file, when they merge, as can removing existing trailing whitespace. So: Don't introduce trailing whitespace. Remove it if you're already changing that line, or do it in a separate clean-up operation (preferably when no-one else is working on the file).

##### Loops and Conditionals
```c++
if (b) {          // Space after the keyword in conditions and loops.
} else {          // Spaces around else.
}
while (test) {}   // There is usually no space inside parentheses.
switch (i) {
for (int i = 0; i < 5; ++i) {
// Loops and conditions may have spaces inside parentheses, but this
// is rare.  Be consistent.
switch ( i ) {
if ( test ) {
for ( int i = 0; i < 5; ++i ) {
// For loops always have a space after the semicolon.  They may have a space
// before the semicolon, but this is rare.
for ( ; i < 5 ; ++i) {
    ...

// Range-based for loops always have a space before and after the colon.
for (auto x : counts) {
    ...
}
switch (i) {
    case 1:         // No space before colon in a switch case.
        ...
    case 2: break;  // Use a space after a colon if there's code after it.
```

##### Operators
```c++
// Assignment operators always have spaces around them.
x = 0;

// Other binary operators usually have spaces around them, but it's
// OK to remove spaces around factors.  Parentheses should have no
// internal padding.
v = w * x + y / z;
v = w*x + y/z;
v = w * (x + z);

// No spaces separating unary operators and their arguments.
x = -5;
++x;
if (x && !y)
   ...
```

### Vertical Whitespace
Minimize use of vertical whitespace.

This is more a principle than a rule: don't use blank lines when you don't have to. In particular, don't put more than one or two blank lines between functions, resist starting functions with a blank line, don't end functions with a blank line, and be discriminating with your use of blank lines inside functions.

The basic principle is: The more code that fits on one screen, the easier it is to follow and understand the control flow of the program. Of course, readability can suffer from code being too dense as well as too spread out, so use your judgement. But in general, minimize use of vertical whitespace.

Some rules of thumb to help when blank lines may be useful:

* Blank lines at the beginning or end of a function very rarely help readability.
* Blank lines inside a chain of if-else blocks may well help readability.
