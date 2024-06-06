#include <iostream>
#include <Grapic.h>
#include <math.h>
using namespace std;
using namespace grapic;

const int DIMW=500;
const int MAXL=10;

struct couleur {
    unsigned int r, g, b;
};

struct casee {
    couleur c;
    int etat;
};

struct grille {
    int nb_cases;
    casee tab[MAXL][MAXL];
    int nb1, nb2, nb3, nb4, nb5;
};



bool triple(grille g) {
    bool triple=false;
    int i,j;
    for (i=0; i<MAXL; i++) {
        for (j=0; j<MAXL; j++) {
            if (i!=0 && j!=0 && i!=MAXL-1 && j!=MAXL-1) {

                if ((g.tab[i-1][j].etat==g.tab[i][j].etat && g.tab[i-1][j].etat==g.tab[i+1][j].etat && g.tab[i][j].etat==g.tab[i+1][j].etat)||(g.tab[i][j-1].etat==g.tab[i][j].etat && g.tab[i][j-1].etat==g.tab[i][j+1].etat && g.tab[i][j].etat==g.tab[i][j+1].etat)) {
                    triple=true;
                }
            } else if (i==0) {
                if (g.tab[i][j].etat==g.tab[i+1][j].etat && g.tab[i][j].etat==g.tab[i+2][j].etat && g.tab[i+1][j].etat==g.tab[i+2][j].etat) {
                    triple=true;
                }
            } else if (i==MAXL-1) {
                if (g.tab[i][j].etat==g.tab[i-1][j].etat && g.tab[i][j].etat==g.tab[i-2][j].etat && g.tab[i-1][j].etat==g.tab[i-2][j].etat) {
                    triple=true;
                }
            } else if (j==0) {
                if (g.tab[i][j].etat==g.tab[i][j+1].etat && g.tab[i][j].etat==g.tab[i][j+2].etat && g.tab[i][j+1].etat==g.tab[i][j+2].etat) {
                    triple=true;
                }
            } else if (j==MAXL-1) {
                if (g.tab[i][j].etat==g.tab[i][j-1].etat && g.tab[i][j].etat==g.tab[i][j-2].etat && g.tab[i][j-1].etat==g.tab[i][j-2].etat) {
                    triple=true;
                }
            }

        }
    }
    return triple;
}

void init(grille &g) {
    int i,j;
    g.nb_cases=0;
    g.nb1=0;
    g.nb2=0;
    g.nb3=0;
    g.nb4=0;
    g.nb5=0;
    do {
        for (i=0; i<MAXL; i++) {
            for (j=0; j<MAXL; j++) {
                g.tab[i][j].etat=rand()%5;
                if (g.tab[i][j].etat==0) {
                    g.nb1++;
                } else if(g.tab[i][j].etat==1) {
                    g.nb2++;
                } else if (g.tab[i][j].etat==2) {
                    g.nb3++;
                } else if  (g.tab[i][j].etat==3) {
                    g.nb4++;
                } else if  (g.tab[i][j].etat==4) {
                    g.nb5++;
                }
                g.nb_cases++;
            }
        }
    } while (triple(g)!=true);
}

void draw(grille g) {
    int i,j;
    int pasi=DIMW/MAXL;
    int pasj=DIMW/MAXL;
    for (i=0; i<MAXL; i++) {
        for (j=0; j<MAXL; j++) {
            if (g.tab[i][j].etat==0) {
                color(255,0,0);
            } else if(g.tab[i][j].etat==1) {
                color(0,255,0);
            } else if (g.tab[i][j].etat==2) {
                color(0,0,255);
            } else if  (g.tab[i][j].etat==3) {
                color (255,255,0);
            } else if  (g.tab[i][j].etat==4) {
                color (255,128,0);
            } else  {
                color(250,250,250);
            }
            circleFill(pasj/2+pasj*j,pasi/2+pasi*i,25);
        }
    }
}

void drawline(grille g, int &n1, int &m1, int &n2, int &m2, int &n3, int &m3) {
    int pasi=DIMW/MAXL;
    int pasj=DIMW/MAXL;
    int x1, y1;
    int i, j;
    if (isKeyPressed(SDLK_UP)) {
        mousePos(x1,y1);
        for (i=0; i<MAXL; i++) {
            for (j=0; j<MAXL; j++) {
                if (x1>j*pasj && x1<(j+1)*pasj && y1>i*pasi && y1<(i+1)*pasi) {
                    if (n1<0 and m1<0) {
                        n1=i;
                        m1=j;
                    } else if (n2<0 and m2<0 and !(i==n1 and j==m1) and ((abs(i-n1)<=1 and j==m1) or (i==n1 and abs(j-m1)<=1))) {
                        n2=i;
                        m2=j;
                    } else if (n3<0 and m3<0 and !(i==n1 and j==m1) and !(i==n2 and j==m2) and ((abs(i-n2)<=1 and j==m2 and j==m1) or (i==n2 and i==n1 and abs(j-m2)<=1))) {
                        n3=i;
                        m3=j;
                    }
                }
            }
        }
    }
    color(0,0,0);
    if (n1>=0 and m1>=0 and n2>=0 and m2>=0) {
        line(m1*pasj+pasj/2,n1*pasi+pasi/2,m2*pasj+pasj/2,n2*pasi+pasi/2);
    }
    if (n2>=0 and m2>=0 and n3>=0 and m3>=0) {
        line(m2*pasj+pasj/2,n2*pasi+pasi/2,m3*pasj+pasj/2,n3*pasi+pasi/2);
    }
    circleFill(m1*pasj+pasj/2,n1*pasi+pasi/2,3);
    circleFill(m2*pasj+pasj/2,n2*pasi+pasi/2,3);
    circleFill(m3*pasj+pasj/2,n3*pasi+pasi/2,3);
}

void update(grille &g, int &n1, int &n2, int &n3, int &m1, int &m2, int &m3, int &t1, int &t2, bool &ch) {
    int i;
    int l;
    if (t1-t2>0.2 and ch==true) {
        n1=-1;
        n2=-1;
        n3=-1;
        m1=-1;
        m2=-1;
        m3=-1;
        ch=false;
    }
    t1=elapsedTime();
    if (n1>=0 and n2>=0 and n3>=0 and m1>=0 and m2>=0 and m3>=0) {
        if (g.tab[n1][m1].etat!=g.tab[n2][m2].etat or g.tab[n1][m1].etat!=g.tab[n3][m3].etat or g.tab[n2][m2].etat!=g.tab[n3][m3].etat) {
            n1=-1;
            n2=-1;
            n3=-1;
            m1=-1;
            m2=-1;
            m3=-1;
            t2=elapsedTime();
            ch=true;
        } else {
            g.tab[n1][m1].etat=-1;
            g.tab[n2][m2].etat=-1;
            g.tab[n3][m3].etat=-1;
            if (m1==m2 && m1==m3 && m2==m3) {
                l=n1;
                if (n2>l) {
                    l=n2;
                }
                if (n3>l) {
                    l=n3;
                }
                for (i=l+1; i<MAXL; i++) {
                    g.tab[i-3][m1].etat=g.tab[i][m1].etat;
                }
                g.tab[MAXL-1][m1].etat=rand()%5;
                g.tab[MAXL-2][m1].etat=rand()%5;
                g.tab[MAXL-3][m1].etat=rand()%5;
            } else if (n1==n2 && n1==n3 && n2==n3) {
                for (i=n1+1; i<MAXL; i++) {
                    g.tab[i-1][m1].etat=g.tab[i][m1].etat;
                    g.tab[i-1][m2].etat=g.tab[i][m2].etat;
                    g.tab[i-1][m3].etat=g.tab[i][m3].etat;
                }
                g.tab[MAXL-1][m1].etat=rand()%5;
                g.tab[MAXL-1][m2].etat=rand()%5;
                g.tab[MAXL-1][m3].etat=rand()%5;
            }
            n1=-1;
            n2=-1;
            n3=-1;
            m1=-1;
            m2=-1;
            m3=-1;
            t2=elapsedTime();
            ch=true;
        }
    }

}

int main(int, char**) {
    winInit("Jeu",DIMW,DIMW);
    int n1=-1;
    int n2=-1;
    int n3=-1;
    int m1=-1;
    int m2=-1;
    int m3=-1;
    int t1, t2;
    bool ch=false;
    grille g;
    init(g);
    draw(g);
    bool stop=false;
    while (!stop) {
        winClear();
        if (not triple(g)) {
            init(g);
        }
        update(g,n1,n2,n3,m1,m2,m3,t1,t2,ch);
        draw(g);
        drawline(g,n1,m1,n2,m2,n3,m3);
        stop=winDisplay();
    }
    winQuit();
    return 0;
}
