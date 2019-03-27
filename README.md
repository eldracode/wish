# wish

A LInux Shell written in C

A Project By -

[Ayush](https://github.com/eldraco19)

[Ayush Dwivedi](https://github.com/AyushOneironaut)

| Commands | Action                       |
| -------- | ---------------------------- |
| ls       | lists the files of directory |
| exit     | exits the shell              |

###To run the shell as the default shell for your system

```
cd
git clone https://github.com/eldraco19/wish.git
gcc -o shell shell.c
sudo "/home/$USER/wish/shell" -o /etc/shells
chsh -s shell $USER
```
