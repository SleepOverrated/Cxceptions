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

TRYs with no CATCH will stop the execution and therefor exit the TRY block after a exception was thrown, but offer no option to handle them.

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
    return 0;
}
```

In this case there is a TRY with no CATCH.
The exception will not stop the execution of the print statement, will however exit the nested try block once thrown.

## Limitations

Due to my lilited knowledge of C it currently is not possible to open two TRY blocks in the same line.
