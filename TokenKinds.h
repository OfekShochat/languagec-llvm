#pragma once

#include <string>
#include <map>
#include <tuple>

/*
struct Literal {
  LitKind kind;
};*/

enum TokenKind {
  /* - Expresion operators - */
  Eq, // '='
  DEq, // '=='
  NotEq, // '!='
  Gt, // '>' (Greater Than)
  Lt, // '<' (Less Than)
  AndAnd, // '&&'
  OrOr, // '||'
  Not, // '!'
  Tilde, // '~' (Wiggle)
  // Binary operators
  Add, // '+'
  Sub, // '-'
  Mul, // '*'
  Div, // '/'
  And, // '&'
  Or, // '|'
  // Equal-Binary operators Example: '+='
  AddEq, // '+='
  SubEq, // '-='
  MulEq, // '*='
  DivEq, // '/='
  // *(Maybe Remove) AndEq, // '&='
  // *(Maybe Remove) OrEq, // '|='
  

  /* - Features - */ // TODO(ghostway): find better name for this comment
  //At, // TODO(ghostway): check what is the At thing (maybe '[' (Bracket)?)
  Dot, // '.' (Period, Full-Stop)
  DotDot, // '..' (Like python's Range)
  Comma, // ','
  Semi, // ';'
  Colon, // ':'
  ColonColon, // '::'
  RArrow, // '->'
  FatRArrow, // '=>'
  Quote, // "'"

  // delims
  OpenParen, // '('
  CloseParen, // ')'
  OpenBrace, // '{'
  CloseBrace, // '}'
  OpenBracket, // '['
  CloseBracket, // ']
  EmptyDelim, // null

  // Keywords
  While,
  As,
  Break,
  Continue,
  If,
  Else,
  True,
  False,
  Func,
  For,
  In,
  Switch,
  Const,
  Return,

  Name,
  Comment,

  /* -- Literals -- */
  IntLiteral,
  FloatLiteral,
  CharLiteral,
  StringLiteral,
  WhiteSpace,
  Ident,

  Null
};