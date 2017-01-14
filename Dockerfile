FROM pritunl/archlinux:latest

EXPOSE 8085

RUN pacman --noconfirm -S gtk3 xfce4 midori mypaint gedit nautilus gnome-mines

ENV GDK_BACKEND broadway

ENV BROADWAY_DISPLAY :5

ADD init.sh /init.sh

ADD dock/dock /dock

CMD ["/init.sh"]