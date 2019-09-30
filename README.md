# XMoon

An easy way to control your window

# Why Xlib

Xlib encapsulates the protocols to communicate with the 
Xserver, which is responsible to provide all the display including
all the windows.

Those processes who want to use GUI must communicate with the 
XServer. And the Xlib provides an easy to do that.

Many GUI development framework is based on Xlib, such as QT. And the
GTK is based on glib and GDK, which are also based on Xlib.

If you are able to communicate with the XServer, you should be able
to control all the windows, no matter the target process is build by 
QT or GTK.

# reference

A good blog to know the basic concepts of linux GUI
- [GTK、KDE、Gnome、XWindows 图形界面](https://blog.csdn.net/ithomer/article/details/9471841)

Some official sites where you can always find documents
- [gnome developer](https://developer.gnome.org/)
- [X Foundation](https://www.x.org/wiki/)
