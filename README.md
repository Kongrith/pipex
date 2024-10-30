
Your program will be executed as follows:
./pipex file1 cmd1 cmd2 file2

It must take 4 arguments:
• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters.

$> ./pipex infile "ls -l" "wc -l" outfile
Should behave like: < infile ls -l | wc -l > outfile

$> ./pipex infile "grep a1" "wc -w" outfile
Should behave like: < infile grep a1 | wc -w > outfile

III.2 Requirements
Your project must comply with the following rules:
• You have to turn in a Makefile which will compile your source files. It must not
relink.
• You have to handle errors thoroughly. In no way your program should quit unexpectedly (segmentation fault, bus error, double free, and so forth).
• Your program mustn’t have memory leaks.
• If you have any doubt, handle the errors like the shell command:
< file1 cmd1 | cmd2 > file2


คำสั่ง
< file1.txt ls -l | grep "cuda" file1.txt > file2.txt

จะได้
cuda    1.0             yes