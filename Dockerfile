FROM pritunl/archlinux:latest

EXPOSE 8085

RUN pacman --noconfirm -S gtk3

RUN pacman --noconfirm -S xfce4

RUN pacman --noconfirm -S midori

ADD init.sh /init.sh

CMD ["/init.sh"]