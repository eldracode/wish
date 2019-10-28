# wish

A Linux Shell written in C

### To run the shell , open your terminal and type

```
make && ./wish
```


### To use the shell as the default shell for your system

```
cd
git clone https://github.com/eldraco19/wish.git
gcc -o wish shell.c
sudo echo "/home/$USER/wish/wish" >> /etc/shells
chsh -s wish $USER
```
