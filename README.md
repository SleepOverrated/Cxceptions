# Cxceptions - A lightweight C exception library

## Why exceptions?

Exceptions are a cleaner and easier way to trace unexpected errors or other mistakes in your code,
while also being easier to understand than unclear return values.

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

TRY blocks without a CATCH block exit the TRY block after an exception was thrown, but offer no way to handle it.
So you can have TRY blocks without a corresponding CATCH block.

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

In this case the exception will not stop the execution of the print statement, however will exit the nested TRY block once thrown.

## Limitations

Due to current implementation limitations, it currently is not possible to open two TRY blocks in the same line.
