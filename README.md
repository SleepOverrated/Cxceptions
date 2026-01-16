# Cxceptions - A lightweight C exception library

## Why exceptions?

Exceptions are a cleaner and easier way to trace unexpected errors or other mistakes in your code,
while also being easier to understand then unclear return values.

## Usage

```C
int main() {
    TRY {
        // some code here
        THROW(EXCEPTION("TestException", "This is a test exception! %d", 42));
    } CATCH(exception) {
        print_exception(exception);
    }
    return 0;
}
```

## Behavior

```C
int main() {
    TRY {
        // some code
        TRY {
            THROW(EXCEPTION("TestException", "This is a test exception! %d", 42));
        } // no CATCH block in this case
        printf("Test!\n");
    } CATCH (exception) {
        print_exception(exception);
    }
}
```

In this case there is a TRY with no CATCH.
The exception will not stop the execution of the print statement, will however exit the nested try block once thrown.
