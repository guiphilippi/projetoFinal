#include <QtWidgets>

#include "game.h"

// *** bloco

bloco::bloco() {}

bloco::bloco(int i, int j, game*jogo) {tipo_ = livre; jogo->setItem(i,j,this);}

//bloco::bloco(int i, int j, tipo tp, game *jogo) : QTableWidgetItem() {Tipo(tp); jogo->blocos[(i*jogo->columnCount())+j] = this; jogo->setItem(i,j,this);}

//bloco::bloco(tipo tp) : QTableWidgetItem() {tipo_ = tp;}

void bloco::Tipo(tipo tp) {tipo_ = tp;}

tipo bloco::Tipo() {return tipo_;}

QPoint bloco::posicao() {return QPoint(row(),column());}

int bloco::pontuacao() {return pontuacao_;}
void bloco::pontuacao(int valor) {pontuacao_ = valor;}
void bloco::soma(int valor) {pontuacao_ += valor;}

// *** entidade
/*
entidade::entidade(tipo tp) : bloco(tp) {}
entidade::entidade(int x, int y, tipo tp, game *jogo) : bloco(tp) {jogo->setbloco(x,y,empurravel); this->bloco_ = jogo->Bloco(x,y); this->bloco_->entidade_ = this;}

QPoint entidade::posicao() {return bloco_->posicao();}
int entidade::row() {return bloco_->row();}
int entidade::column() {return bloco_->column();}
*/
// *** jogador

jogador_::jogador_() {Tipo(jogador); pontuacao(0);}
//jogador_::jogador_(bloco *b, game *jogo) : entidade(jogador) {pontuacao(0); bloco_ = b; jogo->setbloco(1,1,jogador);}
QPoint jogador_::posicao() {return bloco_->posicao();}
int jogador_::row() {return bloco_->row();}
int jogador_::column() {return bloco_->column();}

// *** game

bloco *game::Bloco(int x, int y) {return blocos[(x*columnCount())+y];}

bloco *game::Bloco(QPoint pt) {return blocos[(pt.x()*columnCount())+pt.y()];}

void game::setbloco(int x, int y, tipo tp)
{
bloco *bloco_ = Bloco(x,y);
bloco_->Tipo(tp);
int rand = QRandomGenerator::global()->bounded(1,3);

if (tp==jogador) {bloco_->setBackground(Qt::blue); bloco_->setText(QString("%1").arg(jogador1->pontuacao())); jogador1->bloco_ = bloco_;}
if (tp==livre) {bloco_->setBackground(Qt::white); bloco_->setText(QString(""));}
if (tp==obstaculo) {bloco_->setBackground(Qt::black);}
if (tp==monstro) {bloco_->setBackground(Qt::red); bloco_->setText(QString("0"));}
if (tp==final) {bloco_->setBackground(Qt::green);}
if (tp==movel) {bloco_->setBackground(Qt::gray);}
if (tp==empurravel) {bloco_->setBackground(Qt::yellow);}
if (tp==bonus) {bloco_->setBackground(Qt::cyan); bloco_->pontuacao(rand); bloco_->setText(QString("%1").arg(bloco_->pontuacao()));}
if (tp==inativo) {bloco_->setBackground(Qt::darkMagenta); bloco_->pontuacao(rand); bloco_->setText(QString("%1").arg(bloco_->pontuacao()));}
if (tp==amigo) {bloco_->setBackground(Qt::magenta); bloco_->pontuacao(0); bloco_->setText(QString("%1").arg(bloco_->pontuacao()));}
}

game::game(int rows, int columns, QWidget *parent, QLabel *tela_[2]) : QTableWidget(rows, columns, parent)
{
jogador1 = new jogador_();
blocos = new bloco*[rows*columns];

for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {

        blocos[(i*columnCount())+j] = new bloco(i,j,this);

        int rand = QRandomGenerator::global()->bounded(0,30);

        if (i==0 || j==0 || i==rows-1 || j==columns-1) setbloco(i,j,obstaculo);

        else if (i==1 && j==1) setbloco(1,1,jogador);

        else if (i<3 && j<3) continue;

        else if (i==rows-2 && j==columns-2) setbloco(i,j,final);

        else if (i>rows-4 && j>columns-4) continue;

        else if ((rand % 30) == 0) setbloco(i,j,bonus);

        else if ((rand % 29) == 0) setbloco(i,j,monstro);

        else if ((rand % 20) == 0) setbloco(i,j,inativo);

        else if ((rand % 6) == 0) setbloco(i,j,movel);

        else if ((rand % 5) == 0) setbloco(i,j,obstaculo);

        else if ((rand % 4) == 0) setbloco(i,j,empurravel);
    }
}

ativo = true;

tela[0] = tela_[0];
tela[1] = tela_[1];

resizeRowsToContents();
resizeColumnsToContents();
//this->setDisabled(1);
}

bool game::movimento(int x, int y, bloco *inicio) {

  bool return_ = false;

  if (ativo) {

    QPoint vetor(x,y);

    QPoint fim_ = inicio->posicao() + vetor;

    bloco *fim = Bloco(fim_);

    //tela[1]->setText(tela[1]->text().append(QString("%1 %2 %3 %4 %5 %6 - ").arg(inicio->row()).arg(inicio->column()).arg(fim->row()).arg(fim->column()).arg(inicio->Tipo()).arg(fim->Tipo())));

       if (fim->Tipo()==livre) {

           setbloco(fim->row(),fim->column(),inicio->Tipo());

           setbloco(inicio->row(),inicio->column(),livre);

           return_ = true;
       }

       else if (fim->Tipo()==empurravel) {

           if(movimento(x,y,fim)==true) {

               setbloco(fim->row(),fim->column(),inicio->Tipo());

               setbloco(inicio->row(),inicio->column(),livre);

               return_ = true;
           }
       }

       else if (fim->Tipo()==bonus&&inicio->Tipo()==jogador) {

           jogador1->soma(fim->pontuacao());

           setbloco(fim->row(),fim->column(),inicio->Tipo());

           setbloco(inicio->row(),inicio->column(),livre);

           tela[1]->setText(QString("Pontuacao: %1").arg(jogador1->pontuacao()));
       }

       else if (fim->Tipo()==inativo&&inicio->Tipo()==jogador) {

           jogador1->soma(fim->pontuacao());

           setbloco(inicio->row(),inicio->column(),inicio->Tipo());

           setbloco(fim->row(),fim->column(),amigo);

           tela[1]->setText(QString("Pontuacao: %1").arg(jogador1->pontuacao()));
       }

       else if (fim->Tipo()==final&&inicio->Tipo()==jogador) {tela[0]->setText(QString("Voce venceu!")); ativo = false;}

       else if (fim->Tipo()==monstro&&inicio->Tipo()==jogador) {tela[0]->setText(QString("Voce perdeu!")); ativo = false;}

/*
    int ctrl = 0;
    while (ctrl<5) {

        bool res = mudanca();

        ctrl++;

        if(res==true) ctrl=10;
    }
*/
  }
    return return_;
}

bool game::mudanca() {

    tipo tipo_;
    bool return_ = false;
    int x, y;
    int i = QRandomGenerator::global()->bounded(0,this->rowCount()-1);
    int j = QRandomGenerator::global()->bounded(0,this->columnCount()-1);

    //for (int i = 0; i < 2; ++i) {

        //for (int j = 0; j < 2; ++j) {

            tipo_ = Bloco(i,j)->Tipo(); //tag[(i*this->columnCount())+j];

            if(tipo_==movel || tipo_==monstro) {

                //if ((random() % 5) == 0) {

                   x = QRandomGenerator::global()->bounded(-1,1);
                   y = QRandomGenerator::global()->bounded(-1,1);

                   QPoint pt(i,j);

                   //ponto->setX(i);
                   //ponto->setY(j);

                   //return_ = movimento(x,y,&pt);

                   //delete &pt;

                   //delete ponto1;

                   //tela->setText(QString("%1 %2 %3 %4 %5").arg(i).arg(j).arg(x).arg(y).arg(bloco));
                //}

            }

            return return_;
        //}
    //}
}
