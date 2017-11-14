FROM pritunl/archlinux:latest

COPY gjs /gjs

EXPOSE 8085

RUN pacman --noconfirm -S gtk3 xfce4 midori mypaint gedit nautilus gnome-mines htop gcc pkg-config gjs vim
#toilix
RUN pacman --noconfirm -S arc-gtk-theme git wget yajl dub dmd terminator

RUN pacman -S --noconfirm --needed base-devel 

RUN pacman -S --noconfirm gnome gnome-extra mate mate-extra

RUN git clone https://github.com/gnunn1/tilix.git; cd tilix; dub build --build=release; ./install.sh

#useradd -m -g user bash user

ENV GDK_BACKEND broadway
ENV BROADWAY_DISPLAY :5

COPY init.sh /init.sh
CMD ["/init.sh"]
