#include <QtWidgets>

#include "game.h"

// *** bloco

QPoint bloco::posicao() {return QPoint(row(),column());}
game *bloco::jogo() {return (game*) tableWidget();}

bloco *bloco::deslocado(int x, int y) {return jogo()->Bloco(this->posicao() + QPoint(x,y));}

void bloco::deslocamento(bloco *fim) {entidade_->setbloco(fim); jogo()->livre1->setbloco(this);}

bool bloco::deslocamento(int x, int y) {deslocamento(deslocado(x,y)); return true;}

bool bloco::finaliza(QString texto) {if(entidade_==jogo()->jogador1) {jogo()->tela[0]->setText(QString(texto)); jogo()->ativo = false;} return false;}

bool bloco::tenta_mover(int x, int y) {return this->deslocado(x,y)->entidade_->reacao(x, y, this);}

// *** entidade

void entidade::setbloco(bloco *bloco_) {bloco_->setBackground(cor()); bloco_->setText(QString("")); bloco_->entidade_ = this;}
bool entidade::reacao(int x, int y, bloco *inicio) {return false;}
void entidade::acao() {}
int entidade::pontuacao() {return 0;}
bool entidade::soma(bloco *b) {return false;}
//bloco *entidade::Bloco() {}

//***pontuavel

pontuavel::pontuavel() {pontuacao(0);}
pontuavel::pontuavel(int x, int y) {pontuacao(QRandomGenerator::global()->bounded(x,y));}

void pontuavel::setbloco(bloco *bloco_) {entidade::setbloco(bloco_); bloco_->setText(QString("%1").arg(this->pontuacao()));}
bool pontuavel::reacao(int x, int y, bloco *inicio) {return inicio->entidade_->soma(inicio->deslocado(x,y));}
int pontuavel::pontuacao() {return pontuacao_;}
void pontuavel::pontuacao(int valor) {pontuacao_ = valor;}
bool pontuavel::soma(bloco *b) {pontuacao_ += b->entidade_->pontuacao(); delete b->entidade_; return true;}

//*** autonomo

void autonomo::acao() {

    int x = QRandomGenerator::global()->bounded(-1,2);
    int y = QRandomGenerator::global()->bounded(-1,2);

    Bloco()->tenta_mover(x,y);
}
bloco *autonomo::Bloco() {return bloco_;}
void movel_::acao() {autonomo::acao();}
void monstro_::acao() {autonomo::acao();}
void movel_::setbloco(bloco *b) {entidade::setbloco(b); bloco_ = b;}
void monstro_::setbloco(bloco *b) {pontuavel::setbloco(b); bloco_ = b;}

//*** lista

lista::lista() {

    entidades = new entidade*[30];
    quantidade = 0;
}

void lista::adiciona(entidade *ent) {if(quantidade < 35) {entidades[quantidade] = ent; quantidade++;}}

//*** entidades

      //*** construtores & destrutores

      bonus_::bonus_(int x, int y) : pontuavel(x, y) {}
      inativo_::inativo_(int x, int y) : pontuavel(x, y) {}
      amigo_::amigo_(bloco *bloco_) : pontuavel() {setbloco(bloco_);}
      monstro_::monstro_(lista *lista_) : pontuavel() {lista_->adiciona(this);}
      movel_::movel_(lista *lista_) {lista_->adiciona(this);}

      //*** cores

      QColor livre_::cor() {return Qt::white;}
      QColor obstaculo_::cor() {return Qt::black;}
      QColor movel_::cor() {return Qt::gray;}
      QColor empurravel_::cor() {return Qt::yellow;}
      QColor final_::cor() {return Qt::green;}
      QColor amigo_::cor() {return Qt::magenta;}
      QColor monstro_::cor() {return Qt::red;}
      QColor bonus_::cor() {return Qt::cyan;}
      QColor inativo_::cor() {return Qt::darkMagenta;}
      QColor jogador_::cor() {return Qt::blue;}

      //*** reacoes

      bool livre_::reacao(int x, int y, bloco *inicio) {return inicio->deslocamento(x,y);}

      bool empurravel_::reacao(int x, int y, bloco *inicio) {

          if(inicio->deslocado(x,y)->tenta_mover(x,y)) {return inicio->deslocamento(x,y);} else return false;
      }

      bool final_::reacao(int x, int y, bloco *inicio) {return inicio->finaliza("Voce venceu!");}

      bool monstro_::reacao(int x, int y, bloco *inicio) {return inicio->finaliza("Voce perdeu!");}

      bool bonus_::reacao(int x, int y, bloco *inicio) {

          if(this->pontuavel::reacao(x,y,inicio)) {return inicio->deslocamento(x,y);} else return false;}

      bool inativo_::reacao(int x, int y, bloco *inicio) {

          if(this->pontuavel::reacao(x,y,inicio)) {

              inicio->entidade_->setbloco(inicio);

              new amigo_(inicio->deslocado(x,y));
          }

          return false;
      }

      bool amigo_::reacao(int x, int y, bloco *inicio) {return false;}

      bool jogador_::reacao(int x, int y, bloco *inicio) {return false;}

//*** jogador

void jogador_::setbloco(bloco *b) {pontuavel::setbloco(b); bloco_ = b;}
bool jogador_::soma(bloco *b) {bool return_ = pontuavel::soma(b); bloco_->jogo()->tela[1]->setText(QString("Pontuacao: %1").arg(this->pontuacao())); return return_;}

QPoint jogador_::posicao() {return bloco_->posicao();}

// *** game

void game::criaBloco(int x, int y, entidade *ent) {

    bloco *bloco_ = new bloco();
    setItem(x,y,bloco_);
    ent->setbloco(bloco_);
}

bloco *game::Bloco(int x, int y) {return (bloco*) item(x,y);}

bloco *game::Bloco(QPoint ponto) {return (bloco*) item(ponto.x(),ponto.y());}

game::game(int rows, int columns, QWidget *parent, QLabel *tela_[2]) : QTableWidget(rows, columns, parent)
{

livre1 = new livre_();
obstaculo1 = new obstaculo_();
//movel1 = new movel_();
empurravel1 = new empurravel_();
final1 = new final_();

lista_ = new lista();
jogador1 = new jogador_();

for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {

        int rand = QRandomGenerator::global()->bounded(0,30);

        if (i==0 || j==0 || i==rows-1 || j==columns-1) criaBloco(i,j, obstaculo1);

        else if (i==1 && j==1) criaBloco(i,j, jogador1);

        else if (i<3 && j<3) criaBloco(i,j, livre1);

        else if (i==rows-2 && j==columns-2) criaBloco(i,j, final1);

        else if (i>rows-4 && j>columns-4) criaBloco(i,j, livre1);

        else if ((rand % 21) == 0) criaBloco(i,j, new bonus_(1,4));

        else if ((rand % 19) == 0) criaBloco(i,j, new monstro_(lista_));

        else if ((rand % 17) == 0) criaBloco(i,j, new inativo_(1,4));

        else if ((rand % 6) == 0) criaBloco(i,j, new movel_(lista_));

        else if ((rand % 5) == 0) criaBloco(i,j, obstaculo1);

        else if ((rand % 4) == 0) criaBloco(i,j, empurravel1);

        else criaBloco(i,j, livre1);
    }
}

ativo = true;

tela[0] = tela_[0];
tela[1] = tela_[1];

resizeRowsToContents();
resizeColumnsToContents();
this->setDisabled(1);
}

bool game::movimento(int x, int y, bloco *inicio) {

  mudanca();

  if (ativo) {

      return inicio->tenta_mover(x,y);
  }
      else {return false;}
}

void game::mudanca() {

    int ctrl = 0;
    int qt, item;
    while (ctrl<3) {

        qt = lista_->quantidade;
        item = QRandomGenerator::global()->bounded(0,qt);

        lista_->entidades[item]->acao();

        ctrl++;
    }
}

