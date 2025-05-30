# 🐚 Minishell

Minishell is a simplified Unix shell implemented in C as part of the 42 curriculum. It aims to mimic basic behavior of Bash, including command execution, redirections, pipes, built-in commands, signal handling, and more.

## 🧑‍💻 Authors

- [mel-adna](https://github.com/mel-adna)
- [szemmouri](https://github.com/szemmouri)

## 🚀 Features

- Command parsing and execution
- Built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Pipes (`|`)
- Input/output redirection (`>`, `>>`, `<`)
- Heredoc (`<<`)
- Environment variable expansion (`$VAR`)
- Signal handling (`Ctrl+C`, `Ctrl+\`)
- Wildcard expansion (`*`)
- Error handling with clear messages

## 📚 Resources & References

We learned a lot from the following resources and would like to give credit to all these excellent articles, repositories, and tools:

- [explainshell.com](https://explainshell.com/)
- [Parsing Expressions by Precedence Climbing](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing)
- [Minishell — Building a Mini Bash (m4nnb3ll)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- [Wildcard Pattern Matching - GeeksforGeeks](https://www.geeksforgeeks.org/wildcard-pattern-matching/)
- [ERROR244/minishell](https://github.com/ERROR244/minishell)
- [42docs: Minishell](https://harm-smits.github.io/42docs/projects/minishell)
- [Abkabex's Minishell Guide](https://medium.com/@abkabex/minishell-42-f680eadde592)
- [m4nnb3ll's minishell repo](https://github.com/m4nnb3ll/minishell)
- [cclaude42's minishell](https://github.com/cclaude42/minishell)
- [How to Write a Shell in C - brennan.io](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Achraf Belarif's Blog](https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6)
- [GNU Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/index.html)
- [POSIX Shell Command Language Specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Here Documents in Bash - HowToGeek](https://www.howtogeek.com/719058/how-to-use-here-documents-in-bash-on-linux/)
- [Course Notes - UWE](http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/lrc/system/shell/)
- [Writing a Unix Shell - igupta.in (Part 2)](https://igupta.in/blog/writing-a-unix-shell-part-2/)
- [Writing a Unix Shell - igupta.in (Part 3)](https://igupta.in/blog/writing-a-unix-shell-part-3/)
- [exec - Linux Manual Page](https://linux.die.net/man/3/exec)
- [42_minishell_tester](https://github.com/zstenger93/42_minishell_tester)
- [mpanic](https://github.com/ChewyToast/mpanic)
- [thallard/minishell_tester](https://github.com/thallard/minishell_tester)
- [Minishell Parsing Visualizer](https://minishell-parsing.vercel.app/)
- [Signals in C - GeeksforGeeks](https://www.geeksforgeeks.org/signals-c-language/)

## 🛠️ Build

```bash
make
```

## 🧪 Usage

```bash
./minishell
```

# You can then run commands just like in a regular shell:

```bash
$ echo Hello, world!
Hello, world!
$ ls -la | grep .c > files.txt
```

## 📄 License

This project was developed as part of the 42 School curriculum and is shared for educational purposes only.

```Feel free to fork, learn from it, and give it a ⭐ if it helped you! ```
