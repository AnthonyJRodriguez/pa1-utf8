# PA1 - UTF-8 and Binary Representations

Representing text is straightforward using ASCII: one byte per character fits well within `char*` and it represents most English text. However, there are many more than 256 characters in the text we use, from non-Latin alphabets (Cyrillic, Arabic, and Chinese character sets, etc.) to emojis and other symbols like €, to accented characters like é and ü.

The [UTF-8 encoding](https://en.wikipedia.org/wiki/UTF-8#Encoding) is the default encoding of text in the majority of software today.
If you've opened a web page, read a text message, or sent an email [in the past 15 years](https://en.wikipedia.org/wiki/UTF-8#/media/File:Unicode_Web_growth.svg) that had any special characters, the text was probably UTF-8 encoded.

Not all software handles UTF-8 correctly! For example, I got a marketing email recently with a header “Take your notes further with Connectâ€‹” I'm guessing that was supposed to be an ellipsis (…), [UTF-8 encoded as the three bytes 0xE2 0x80 0xA6](https://www.compart.com/en/unicode/U+2026), and likely the software used to author the email mishandled the encoding and treated it as [three extended ASCII characters](https://en.wikipedia.org/wiki/Extended_ASCII).

This can cause real problems for real people. For example, people with accented letters in their names can run into issues with sign-in forms (check out Twitter/X account [@yournameisvalid](https://x.com/yournameisvalid?lang=en) for some examples). People with names best written in an alphabet other than Latin can have their names mangled in official documents, and need to have a "Latinized" version of their name for business in the US.

UTF-8 bugs can and do cause security vulnerabities in products we use every day. A simple search for UTF-8 in the CVE database of security vulnerabilities turns up [hundreds of results](https://cve.mitre.org/cgi-bin/cvekey.cgi?keyword=utf-8).

It's useful to get some experience with UTF-8 so you understand how it's supposed to work and can recognize when it doesn't.
To that end, you'll write several functions that work with UTF-8 encoded text, and use them to analyze some example texts.

## Functions

### `uint32_t utf8_code_points(char* str)`

Takes a UTF-8 encoded string and returns the number of UTF-8 code points it represents.

### `int32_t utf8bytes_range(char* str, uint32_t start, uint32_t end)`

Takes a UTF-8 encoded string and start and end indices, and returns the number of _bytes_ taken up by the unicode code points in that range of indices (`start` inclusive, `end` exclusive. (This is not the same as the number of code points!)

Returns -1 if `start` is below 0, `end` is greater than the length of the string, or `start` is after `end`.

Examples:

```
utf8bytes_range("Joe Politz", 0, 3) == 3
utf8bytes_range("José", 1, 4) == 4 // é is two bytes
utf8bytes_range("🦀🦮🦮🦀🦀🦮🦮", 3, 7) == 16 // these emoji are 4 bytes long
```

### `uint8_t is_validutf8(char* str)`

Takes a UTF-8 encoded string and returns if it is valid UTF-8.

### `uint8_t is_ascii(char* str)`

Takes a UTF-8 encoded string and returns if it is valid ASCII (e.g. all bytes are 127 or less).

### `uint8_t is_animal_emoji_at(char* str, uint32_t index)`

Takes a UTF-8 encoded string and an index, and returns if the code point at that index is an animal emoji.

For simplicity for this question, we will define that that the “animal emojii” are in two ranges: from 🐀 to 🐿️ and from 🦀 to 🦮. (Yes, this technically includes things like 🐽 which are only related to or part of an animal, and excludes a few things like 🙊, 😸, which are animal faces.). You may find the [wikipedia page on Unicode emoji](https://en.wikipedia.org/wiki/List_of_emojis) helpful here.

### `uint32_t code_point_at(char* str, unsigned int index)`

Takes a UTF-8 encoded string and an index, and returns the code point at that index.

### `void utf8substring(char* str, int start, int end, char* result)`

Takes a UTF-8 encoded string and start and end indices, and writes the substring between those indices to `result`, and includes a null terminator. Assumes that `result` has at least `utf8bytes_range(str, start, end) + 1` bytes of space available.

### `void code_points_to_utf8(unsigned uint32_t* code_points, char* str)`

Takes an array of code points and writes the UTF-8 encoded string to `str`.

### `uint32_t capitlize_ascii(char* str)`

## UTF-8 Analyzer

You'll also write a program that reads (purportedly) UTF-8 input and prints out some information about it.

Here's what a sample run of your program should look like:

```
$ ./utf8analyzer
Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
Valid UTF-8: true
Valid ASCII: false
Number of code points: FILL
Code points as decimal numbers: 
Substring of the first 6 code points: "My 🐩’s"
Number of bytes in the first 6 code points: 10
Length in bytes: FILL
Animal emojis: 🐩
Bytes per code point: 1 1 1 4 FILL ....
```

You can also test the contents of _files_ by using the `<` operator:

```
$ cat utf8test.txt
FILL
$ ./utf8analyzer < utf8test.txt
Enter a UTF-8 encoded string:
Number of code points: FILL
Substring up to the first ASCII space: FILL
Length in bytes: FILL
Valid UTF-8: true
Valid ASCII: false
Animal emojis: FILL
Bytes per code point: FILL
```

## Testing

Here are some ideas for tests you should write. They aren't necessarily comprehensive (you should design your own!) but they should get you started. For each of these kinds of strings, you should check how UTF-8 analyzer handles them:

- Strings with a single UTF-8 character that is 1, 2, 3, 4 bytes
- Strings with two UTF-8 characters in all combinations of 1/2/3/4 bytes. (e.g. `"aa"`, `"aá"`, `"áa"`, `"áá"`, and so on)
- Strings with and without animal emojii, including at the beginning, middle, and end of the string, and at the beginning, middle, and end of the range
- Strings of exactly 5 characters

There are several files of junk data
Don't print contents if invalid
What happens if you try to print it?

Show CVEs

popcnt

Alternative ambiguous encoding

Question about wasted space (compare to UTF-16, ASCII)

Funky characters

## What to Hand In

- Any `.c` files you wrote (can be one file or many). We will run `gcc *.c -o utfanalyzer` to compile your code, so you should make sure it works when we do that.
- A file `DESIGN.md` (with exactly that name) containing the answers to the design questions
- Your tests with expected output in files `tests/*.txt`, `tests/*.txt.expect`

Hand in to the `pa1` assignment on Gradescope. The submission system will show you the output of compiling and running your program on the test input described above to make sure the baseline format of your submission works. You will not get feedback about your overall grade before the deadline.