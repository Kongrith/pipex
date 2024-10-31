pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)

// each cmd needs a stdin (input) and returns an output (to stdout)

    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes
        cmd1 stdout)                           cmd2 stdin)

การมองโจทย์ให้ง่าย
ref: https://42-cursus.gitbook.io/guide/rank-02/pipex/understand-pipex
< file1 cmd1 | cmd2 > file2
เทียบเท่ากับ
cmd1 < file1 | cmd2 > file2


คำสั่งที่ต้องรู้ในการทำ project
ref: https://reactive.so/post/42-a-comprehensive-guide-to-pipex/


เชื่อมงานปัจจุบันเข้ากับ remote github
git init
git remote add origin https://github.com/Kongrith/pipex.git
git add .
git commit -m "init"
git branch -M master
git push -u origin master
