# Mechabytes Style Guide

---------------
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

- Related header, C library, C++ library, other libraries' `.h`, your project's `.h`

Within each of these categories, includes should be ordered alphabetically.

You should include all the headers that define symbols you rely upon.  If you rely on symbols from `bar.h`, don't count on the fact that you included `foo.h` which (currently) includes `bar.h`: include `bar.h` yourself, unless `foo.h` explicitly demonstrates its intent to provide those symbols.  However, any includes present in the related header do not need to be included again in the related `.cpp`.

**Note:** If all `.h` files have been properly guarded, duplicate includes will have no effect.

---------------
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

---------------
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
* Define operators only on your own types. More precisely, define them in the same headers, .cpp files, and namespaces as the types they operate on. That way, the operators are available wherever the type is, minimizing the risk of multiple definitions. If possible, avoid defining operators as templates, because they must satisfy this rule for any possible template arguments. If you define an operator, also define any related operators that make sense, and make sure they are defined consistently. For example, if you overload <, overload all the comparison operators, and make sure < and > never return true for the same arguments.
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

---------------
## Functions


---------------
## Naming


---------------
## Comments


---------------
## Formatting


---------------
Camel case  
4 spaces
