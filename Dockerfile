FROM pritunl/archlinux:latest

EXPOSE 8085

RUN pacman --noconfirm -S gtk3

#docker exec gtk bash -c "GDK_BACKEND=broadway BROADWAY_DISPLAY=:5 gtk3-demo"

CMD ["broadwayd", ":5"]