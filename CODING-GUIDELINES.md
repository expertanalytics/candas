
Candas Codeing Guidelines
=========================

General
-------

* At most 120 character lines.
* Use four spaces for indentation. Not tabs.
* Always use `using` statements for aliases, not `typedef`.


Includes
--------

* Only includes at the beginning of the file, as far as possible.
* Sort includes in the following order, as far as possible:
  1. Standard library includes.
  2. Third-party libraries, sorted into separate groups.
  3. Local project includes.

Separate groups of includes are always separated by _a single_ blank line. Separate the last include
and the rest of the file using _two_ blank lines.

A group of includes may have a short description using a `/* ... */` comment.

**Example:**
```
#include <std-library-A>
#include <std-library-B>

#include <third-party-0-A>
#include <third-party-0-B>

/* short description */
#include <third-party-1-A>
#include <third-party-1-B>

#include "local-stuff-A"
#include "local-stuff-B"


/* code here */
```


Template arguments
------------------

* A single space around the opening `<` and before the closing `>`.
* The first template argument is on the same line as the `template` keyword.
* One line for each separate template argument.
* If there is only a single template argument, the closing `>` should be on the same line as
  the rest of the declaration; otherwise when there are multiple arguments it should be on a
  separate line, aligned with the opening `<`.
  **Example:**

        ```
        // yes
        template < typename T1 >
        // no
        template < typename T1
                 >

        // yes
        template < typename T1,
                   typename T2
                 >
        // no
        template < typename T1,
                   typename T2 >
        ```

* There should always be a single space between empty `<` and `>` in template declarations.
  **Example:**

        ```
        // yes
        template < >
        // no
        template <>
        ```

* Nested templates: If there is a nested template with a single type, write it without spaces.
  When there are multiple arguments write it as usual but indented.
  **Example:**

        ```
        template < typename A,
                   template<typename> B,  // nested with single type
                   template < typename,
                              std::size_t
                            > C           // nested with multiple arguments
                   template<>             // nested without arguments
                 >
        ```

Classes
-------

### Class declaration

* `{` and `}` on separate lines.
* Include a blank line after the opening `{`, and before the closing `}`.

### Class content ordering

* Class content should be ordered in the following manner:
  1. Type aliases and binding of static values.
  2. Class member variables.
  3. Constructors, the destructor, and move/copy operators.
  4. Other member functions.

### Class member functions

* No single line non-empty functions. Empty function should be on a single line.
  **Example:**

        ```
        // yes
        void foo(int bar)
        {
            do_stuff();
        }
        // no
        void foo(int bar) { do_stuff(bar); }

        // yes
        void foo(int bar) { }
        // no
        void foo(int bar)
        { }
        // no
        void foo(int bar) {
        }
        ```

* `{` and `}` on separate lines.
* Always have return statements on a separate line. When there are multiple lines in a function
  there should be a single blank line above the return statement.
* Always include a one-line description at the start of the function, it must use `/* ... */`
  style comments.
* There should be no space between the function name and the argument list. **Except** for
  operator overloads, then there should be a single space.
  **Example:**

        ```
        // yes
        void foo(int bar);
        // no
        void foo (int bar);

        // yes
        void operator== (int bar);
        // no
        void operator==(int bar);
        ```

