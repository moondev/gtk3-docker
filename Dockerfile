FROM pritunl/archlinux:latest

ADD dock/dock.c /opt/dock.c

EXPOSE 8085

RUN pacman --noconfirm -S gtk3 xfce4 midori mypaint gedit nautilus gnome-mines htop gcc pkg-config && \
    cd /opt/ && \
    gcc `pkg-config --cflags gtk+-3.0` -o dock dock.c `pkg-config --libs gtk+-3.0`

ENV GDK_BACKEND broadway
ENV BROADWAY_DISPLAY :5

ADD init.sh /init.sh
CMD ["/init.sh"]
