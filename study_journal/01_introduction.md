# Introduction
As soon as I don't have much experience with C++, and I woul'd like to leant it, I will try to implement this project side-by-side with it's Java version, as Java is the language chosen by the author

Well, I just discovered that there are many other options of languages that the readers themselves ported. Cool. It's possible to find this ports [here](https://github.com/munificent/craftinginterpreters/wiki/Lox-implementations)

Stills, probably I will walk my own path and then look on the repositories above, so I can see what different decisions they made and I. I like this way of learning. It's challenging (for you still need to do all by your own), you can have answers on "How can I do this in a better way?" (looking into other's well implemented solutions). Well, at least is my way of learning.

### 1.4
Uuuh, it seems we will write all the same, but in C. I like C :D 

Well, maybe I will use this opportunity to write it in C++ too.

## Challenges
Nice, there's challenges since the introduction of the book, good, good.

Well, let's do it.

### 1st:
> "There are at least six domain-specific languages used in the [little system I cobbled together](https://github.com/munificent/craftinginterpreters) to write and publish this book. What are they?"

looking for the little languages...

Well, maybe I can say that, as since there is one extension (eg '.exe') there's a language associated with that? 
- *look further on this question*

By now, let's stick to what I know that creates languages.

1. `Markdown` - since markdown is in all readme's. In fact, is the little language, or, **domain-specific language**, I'm using right now as I take down my notes.
2. `Makefile` - The Makefile is written in its own specific language, as far as I know, so, I think that counts.
3. `.gitignore` - It has a yaml-like sintax, but it doesn't seem yaml at all, so, I bet that this is a domain-specific language too
4. `.h files` - In the sorce repository, there is a folder named "c", wich has a lot of .c and .h files. Since .h files are headers for c programs, I think that this can be called "domain-specific"
5. `yaml` - There are yaml files, in the "tool" folder. Yaml files are designed for... uh, I don't know entirely. *Should see this later*.
6. `lock` - .lock files are used to... well, I don't understand them entirely too, but they "fix" a version in order for the pubspec.yaml knows what version it should seek when running `flutter pub get` or a similar command.

Well, that's it. Later I should seek the right answers to understand more about this.

### 2nd
Building a hello world in Java. Pretty simple.

Can be found in `/challenges/01/java`

### 3rd
3.1 Building a hello world in C. This was pretty simple also. 

The next step of the challenge was to define a doubly linked list, to get some practice with pointers.

The code should implement:
- an insert function
- a find function
- a delete function
- test them

This was not... hard, but kinda challenging and I found it pretty fun!

It was long ago since I coded in C so was fun to remember and to implement the linked list.

code for this challenge can be found in `/challenges/01/c`

### What I've learnt

From the third challenge, specially the linked list challenge, I could remember some things and learn other new exciting ones!

#### Memory Leaks
The challenge does not include to check for memory leaks, but I want to try it anyways.

I've dicovered how to check if your C code has memory leaks. Turns out that my actual code has mem leaks but, as I'm just returning, I will let them there until I get a way to solve them.

There's two tools that I discovered for that: [**Valgrind**](https://valgrind.org/) and [**Address Sanitizer**](https://clang.llvm.org/docs/AddressSanitizer.html).

The code for executing these tools is:
For **Valgrind**:

```bash
    $ valgrind --leak-check=full ./program
```

For **Address Sanitizer**:
```bash
    $ gcc -fsanitize=address -g program.c -o program
```

#### Functions "abstract" declarations
In C, you can define the functions declarations in top of the file, and then write the implementation bellow those declarations. 

Since C reads the code from top to bottom, this is helpful to avoid the loophole where, in a writed-above function (let's call it **func A**), you call a bellow-writed function (**func B**) and the compiler complains that the **func B**, called in **func A** does not exist.

These seem to me pretty close of the abstract declarations in Java. But I'm not sure. I can look over it later to find out.

#### Code organization
It's impressive how fast the code can get messy. Like, I'm just experementing and write a lot of functions to understand the different ways I can do one output, save duplicate code and another little things, and, at the moment of this writing, I have 15 different functions, and some of their implementation are... well, large.

Maybe this is wny thinks like KISS (Keep It Simple Stupid) were created in first place. When doing a lot of things, you can get a messy codebase that is a terror to navigate throught.

Well, after everything is working fine I will delete the experimenting functions I've created and this will be more readable, hopely.

> Note: update this section as soon I've deleted the experimenting functions

#### While loop VS Recursive function
I was writing a function and then the question arose in my mind: 
> What is more optimized? Executing a while loop or making the function recursive?

So, I asked AI the question, using the following prompt:
```
what is more performatic in C? Excuting a do while or using recursion? Let's say that both cases execute the same n times.

What is and why?
```

I asked both Chat GPT and Gemini, and the answer I've found is very cool. 

See, the `do while` loop is better, but the "why" resides on assembly level. 

When using iteration, for each iteration, the CPU must create a new stack frame in memory, pushing a lot of info (like function parameters and return address) onto the call stack.

But when you just iterate using a while loop, all the proccess is made on the same stack frame, so, is slightly better.

Exciting, isn't it?

#### Bad idea when returning strings.
At this point, I've created the following function:
```c
char *request_user_input() {
    char text_buffer[100];

    printf("Enter node text value: \n");
    fgets(text_buffer, sizeof(text_buffer), stdin);

    text_buffer[strcspn(text_buffer, "\n")] = 0;

    return text_buffer;
}
```

Well, I just discovered that this is a really bad ideia, since `text_buffer` is a local variable inside the scope of the function. So, when the function exits, that memory is gone (I don't get it yet if the memory is deallocated or just the value inside it is overwriten by some other random value), thus creating a [**Dangling Pointer**](https://medium.com/@sofiasondh/what-is-a-dangling-pointer-how-can-it-be-avoided-e72321e1fdf3).

Okay, we have a problem. What now?

It seems there's two approaches to this problem:
1. `Letting the caller providing the buffer`, by doing something like this:

    ```c
    void request_user_input(char *text_buffer, size_t buffer_size) {
        // char text_buffer[100];

        printf("Enter node text value: \n");
        fgets(text_buffer, buffer_size, stdin);

        text_buffer[strcspn(text_buffer, "\n")] = '\0';

        // return text_buffer;
    }

    int main() {
        char text_buffer[100];

        request_user_input(text_buffer, sizeof(text_buffer));

        printf("text in buffer: %s\n", text_buffer);

        return 0;
    }

    ```

**OR**

2. `Allocating memory dynamically`.

    This will use malloc (duh) and the memory will need to be freed thereafter.

    Since C is already complicated and such an error-prone language, the first approach seems the safier one.