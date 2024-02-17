#ifndef _CONIO3_H_
#define _CONIO3_H_

// bom dia

#include <conio.h>
#ifdef UNICODE
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Colors which you can use in your application.
 */
typedef enum {
  PRETO,
  AZUL,
  VERDE,
  CIANO,
  VERMELHO,
  ROSA,
  MARROM,
  CINZA_CLARO,
  CINZA_ESCURO,
  AZUL_CLARO,
  VERDE_CLARO,
  CIANO_CLARO,
  VERMELHO_CLARO,
  ROSA_CLARO,
  AMARELO,
  BRANCO
} CORES;

typedef enum {
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  PURPLE,
  BROWN,
  LIGHT_GRAY,
  DARK_GREY,
  LIGHT_BLUE,
  LIGHT_GREEN,
  LIGHT_CYAN,
  LIGHT_RED,
  LIGHT_PURPLE,
  YELLOW,
  WHITE
} COLORS;

/*@{*/
/**
 * Esses defines sao para voce poder utilizar todas as funcoes do conio.h
 * original sem a sublinha.
 */
#define cgets _cgets
#define cprintf _cprintf
#define cputs _cputs
#define cscanf _cscanf

#ifdef UNICODE
#define cgetws _cgetws
#define getwch _getwch
#define getwche _getwche
#define putwch _putwch
#define ungetwch _ungetwch
#define cputws _cputws
#define cwprintf _cwprintf
#define cwscanf _cwscanf
#endif
/*@}*/

/**
 * Define um alias para _conio_gettext
 * Se voce importar outra biblioteca com o mesmo nome gettext
 * voce precisa definir _CONIO_NO_GETTEXT_ e entao voce nao tera conflito
 * de nome
 */
#ifndef _CONIO_NO_GETTEXT_
#define gettext _conio_gettext
#endif

#define ScreenClear clrscr

/**
 * @anchor cursortypes
 * @name Cursor types
 * Tipos pre-definidos de cursor */
/*@{*/
#define _NOCURSOR 0      /**< Sem cursor */
#define _SOLIDCURSOR 100 /**< Cursor preenchendo todo o espaco */
#define _NORMALCURSOR 20 /**< Cursor preenchendo 20% da celula alvo */
/*@}*/

/**
 * Estrutura recebendo informacoes sobre a tela.
 * @see gettextinfo
 * @see inittextinfo
 */
struct text_info {
  unsigned char curx;         /**< coordenada do cursor x */
  unsigned char cury;         /**< coordenada do cursor y */
  unsigned short attribute;   /**< text attribute atual */
  unsigned short normattr;    /**  valor original do text_attribute apos
                                   o inicio da aplicacao. Se voce nao
                                   chamou <TT>inittextinfo</TT> no comeco
                                   da sua aplicacao, isso sempre sera
                                   o fundo preto com a fonte cinza_claro */
  unsigned char screenwidth;  /**< largura da tela */
  unsigned char screenheight; /**< altura da tela */
};

/**
 * Estrutura usada pelo gettext/puttext.
 * @see _conio_gettext
 * @see puttext
 */
struct char_info {
#ifdef UNICODE
  wchar_t letter; /**< character value */
#else
  char letter; /**< character value */
#endif
  unsigned short attr; /**< attribute value */
};

/**
 * Retorna uma estrutura contendo as informacoes da tela
 * struct text_info na documentacao
 * @see text_info
 */
void gettextinfo(struct text_info *info);

/**
 * Chame essa funcao se voce necessita do valor atual normattr da estrutura
 * text_info
 * @see text_info
 */
void inittextinfo(void);

/**
 * Limpa o resto da linha partindo da posicao do cursor até o final da linha
 * sem mover o cursor
 */
void clreol(void);

/**
 * Limpa a tela inteira
 */
void clrscr(void);

/**
 * Deleta a linha atual (linha onde está posiscionado o cursor) entao move
 * todas as linhas uma linha acima. Linhas abaixo da linha sao movidas uma
 * linha acima.
 */
void delline(void);

/**
 * Insere uma linha em branco na posicao atual do cursor.
 * O conteudo original da linha e o conteudo das linhas abaixo sao movidas uma
 * linha abaixo.
 * A ultima linha sera deletada
 */
void insline(void);

/**
 * Recebe texto da tela. Se voce nao definiu <TT>_CONIO_NO_GETTEXT_</TT> sobre
 * o include <TT>conio3.h</TT> voce pode usar essa funcao com o nome
 * <TT>gettext</TT>.
 * @see char_info
 * @see puttext
 * @param left Coordenada esquerda do retangulo, inclusive, a partir de 1.
 * @param top Coordenada superior do retangulo, inclusive, a partir de 1.
 * @param right Coordenada direita do retangulo, inclusive, a partir de 1.
 * @param bottom Coordenada inferior do retangulo, inclusive, a partir de 1.
 * @param buf Voce precisa passar o tamanho do buffer
 * <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
 */
void _conio_gettext(int left, int top, int right, int bottom,
                    struct char_info *buf);

/**
 * Insere o texto de volta para a tela.
 * @see char_info
 * @see _conio_gettext
 * @param left Coordenada esquerda do retangulo, inclusive, a partir de 1.
 * @param top Coordenada superior do retangulo, inclusive, a partir de 1.
 * @param right Coordenada direita do retangulo, inclusive, a partir de 1.
 * @param bottom Coordenada inferior do retangulo, inclusive, a partir de 1.
 * @param buf Voce precisa passar o tamanho do buffer
 * <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
 */
void puttext(int left, int top, int right, int bottom, struct char_info *buf);

/**
 * Copia texto
 * @param left Coordenada esquerda do retangulo, inclusive, a partir de 1.
 * @param top Coordenada superior do retangulo, inclusive, a partir de 1.
 * @param right Coordenada direita do retangulo, inclusive, a partir de 1.
 * @param bottom Coordenada inferior do retangulo, inclusive, a partir de 1.
 * @param destleft Coordenada esquerda do retangulo de destino.
 * @param desttop Coordenada superior do retangulo de destino.
 */
void movetext(int left, int top, int right, int bottom, int destleft,
              int desttop);

/**
 * Move o cursor para a posicao desejada
 * Considere 1, 1 para a primeira posicao
 * @param x posicao horizontal
 * @param y posicao vertical
 */
void gotoxy(int x, int y);

/**
 * Insere uma *string na posicao desejada
 * @param x posicao horizontal
 * @param y posicao vertical
 * @param str string
 */
void cputsxy(int x, int y, char *str);

/**
 * Insere um caractere numa posicao especifica
 * @param x posicao horizontal
 * @param y posicao vertical
 * @param ch char
 */
void putchxy(int x, int y, char ch);

/**
 * [DEPRECIADO] Define o tipo do cursor
 * @see @ref cursortypes
 * @param type tipo do cursor, sobre Win32, o tamanho do cursor em porcentagem
 */
void _setcursortype(int type);

/**
 * Seta o atributo do novo texto a ser impresso
 * @param _attr novo atributo
 */
void textattr(int _attr);

/**
 * Define o atributo de texto de volta a ultima pre-definicao criada
 * antes do programa iniciar.
 * Usa o valor de text_info normattr
 * @see text_info
 */
void normvideo(void);

/**
 * Define a cor de fundo do texto
 * @see COLORS
 * @param color nova cor de fundo
 */
void textbackground(int color);

/**
 * Define a cor da fonte
 * @see COLORS
 * @param color nova cor da fonte
 */
void textcolor(int color);

/**
 * Le e retorna a posicao X do cursor
 * @returns posicao X do cursor
 */
int wherex(void);

/**
 * Le e retorna a posicao Y do cursor
 * @returns posicao Y do cursor
 */
int wherey(void);

/**
 * Le uma senha. Como se fosse cgets.
 *
 * @see cgets
 * @param prompt prompt which will be displayed to user
 * @param str string for the password. <TT>str[0]</TT> have to contain
 * length of the <TT>str</TT> - 3
 * @returns <TT>&str[2]</TT>, the password will be stored in <TT>str</TT>
 * beginning at <TT>str[2]</TT>, in <TT>str[1]</TT> will be length of the
 * string without <TT>\\0</TT>, at <TT>str[2 + str[1]]</TT> will be \\0.
 */
char *getpass(const char *prompt, char *str);

/**
 * Faz as cores de fonte ficarem claras.
 * Se a cor atual das fontes forem menores que <TT>CINZA_ESCURO</TT> adiciona
 * 8 para o seu valor, deixando as cores escuras, claras.
 * @see COLORS
 * @see lowvideo
 */
void highvideo(void);

/**
 * Faz as cores de fundo ficarem escuras.
 * Se a cor atual das fontes forem menores que <TT>CINZA_CLARO</TT> subtrai
 * 8 do seu valor, deixando as cores claras, escuras.
 * @see COLORS
 * @see highvideo
 */
void lowvideo(void);

/*@{*/
/*
 * You may need to link with libmsvcr70.a or libmsvcr70d.a or libmsvcr71.a
 *  or libmsvcr71d.a if you want any of these functions.
 */
#ifdef UNICODE
_CRTIMP wchar_t *__cdecl _cgetws(wchar_t *);
_CRTIMP unsigned short __cdecl _getwch(void);
_CRTIMP unsigned short __cdecl _getwche(void);
_CRTIMP unsigned short __cdecl _putwch(wchar_t);
_CRTIMP unsigned short __cdecl _ungetwch(unsigned short);
_CRTIMP int __cdecl _cputws(const wchar_t *);
_CRTIMP int __cdecl _cwprintf(const wchar_t *, ...);
_CRTIMP int __cdecl _cwscanf(const wchar_t *, ...);
#endif
/*@}*/

/**
 * Pausa o programa por alguns milissegundos.
 * @see switchbackground
 * @param ms milissegundos
 */
void delay(int ms);

/**
 * Repoe a cor de fundo de toda a tela. O texto, permanece intacto.
 * Nao modifica textbackground()
 * @see flashbackground
 * @param color cor de fundo
 */
void switchbackground(int color);

/**
 * Muda a cor de fundo por um certo periodo, entao a restora de volta.
 * Voce pode usar isso para um sino visual. Nao modifica textbackground()
 * @see switchbackground
 * @see delay
 * @param color cor de fundo
 * @param ms milissegundos
 */
void flashbackground(int color, int ms);

/**
 * Limpa o buffer do teclado
 * Para ve-lo em efeito, execute <TT>conio_test</TT> e tente apertar alguma
 * tecla durante a fase "Flashing..."
 */
void clearkeybuf(void);

#ifdef __cplusplus
}
#endif

#endif /* _CONIO3_H_ */
