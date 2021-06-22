# caesar-cipher
Simple Caesar Cipher written in C.

The test_files folder contains two test files:
> lorem_sm, lorem_big

Instructions:

Run the Makefile to compile the cipher and decipher executables.

```Bash
make
```

To encrypt: 

```Bash
./encrypt <shift> <file>
```

To decrypt:

Decrypt will create a .dec file with the same content as the the original file.

```Bash
./decrypt <shift> <.enc file>
```
