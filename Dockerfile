FROM pritunl/archlinux:latest

COPY gjs /gjs

EXPOSE 8085

RUN pacman --noconfirm -S gtk3 xfce4 midori mypaint gedit nautilus gnome-mines htop gcc pkg-config gjs remmina vim

ENV GDK_BACKEND broadway
ENV BROADWAY_DISPLAY :5

COPY init.sh /init.sh
CMD ["/init.sh"]
