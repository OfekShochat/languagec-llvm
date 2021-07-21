#include "lexer.h"
#include <array>
#include <string>
#include <iostream>
#include <list>

std::tuple<TokenKind, TokenKind> Token::SplitIntoTwo(TokenKind t) {
  switch (t) {
    case DEq:
      return {Eq, Eq};
    case NotEq:
      return {Not, Eq};
    case AndAnd:
      return {And, And};
    case ColonColon:
      return {Colon, Colon};
    case OrOr:
      return {Or, Or};
    case RArrow:
      return {Sub, Gt};
    case FatRArrow:
      return {Eq, Gt};
    case AddEq:
      return {Add, Eq};
    case SubEq:
      return {Sub, Eq};
    case MulEq:
      return {Mul, Eq};
    case DivEq:
      return {Div, Eq};
  }
  return {Null, Null};
}

Tokenizer::Tokenizer(std::string text) {
  input_ = text;
}

TokenKind Tokenizer::BlockComment() {
  index = input_.find("*/", index);
  return Comment;
}

TokenKind Tokenizer::LineComment() {
  index = input_.find('\n', index);
  return Comment;
}

TokenKind Tokenizer::SkipWhiteSpaces() {
  int old = index;
  while (input_[index] == ' ' || input_[index] == '\t' || input_[index] == '\013') {
    index++;
  }
  return WhiteSpace;
}

TokenKind Tokenizer::String() {
  index = input_.find('"', index+1) + 1;
  return StringLiteral;
}

bool Tokenizer::IdStart() {
  return isalpha(input_[index]) || input_[index] == '_';
}

bool Tokenizer::IdContinue() {
  return IdStart() || isdigit(input_[index]);
}

TokenKind Tokenizer::Number() {
  auto kind = IntLiteral;
  do {
    index++;
    if (input_[index] == '.') {
      kind = FloatLiteral;
    }
  } while (isdigit(input_[index]) || input_[index] == '_' || input_[index] == '.');
  return kind;
}

TokenKind Tokenizer::CharToken(TokenKind kind) {
  index++;
  return kind;
}

TokenKind Tokenizer::Identifier() {
  do {
    index++;
  } while (IdContinue());
  return Ident;
}

Token Tokenizer::Advance() {
  int old_index = index;
  auto kind = Null;
  if (IdStart()) {
    kind = Identifier();
  } else {
    switch (input_[index]) {
      case '/':
        if (input_[index+1] == '/') {
          kind = LineComment();
        } else if (input_[index+1] == '*') {
          kind = BlockComment();
        } else {
          kind = Div;
          index++;
        }
        break;
      case '"':
        kind = String();
        break;
      case ' ':
      case '\r':
      case '\t':
      case '\013':
        kind = SkipWhiteSpaces();
        break;

      // one char 
      case ';':
        kind = CharToken(Semi);
        break;
      case ',':
        kind = CharToken(Comma);
        break;
      case '.':
        kind = CharToken(Dot);
        break;
      case '(':
        kind = CharToken(OpenParen);
        break;
      case ')':
        kind = CharToken(CloseParen);
        break;
      case '{':
        kind = CharToken(OpenBrace);
        break;
      case '}':
        kind = CharToken(CloseBrace);
        break;
      case '~':
        kind = CharToken(Tilde);
        break;
      case ':':
        kind = CharToken(Colon);
        break;
      case '=':
        kind = CharToken(Eq);
        break;
      case '!':
        kind = CharToken(Not);
        break;
      case '>':
        kind = CharToken(Gt);
        break;
      case '<':
        kind = CharToken(Lt);
        break;
      case '-':
        kind = CharToken(Sub);
        break;
      case '&':
        kind = CharToken(And);
        break;
      case '|':
        kind = CharToken(Or);
        break;
      case '+':
        kind = CharToken(Add);
        break;
      case '*':
        kind = CharToken(Mul);
        break;
      case '0'...'9':
        kind = Number();
        break;
      default:
        int d = static_cast<int>(input_[index]);
        std::cerr << "Unknown char '" << input_[index] << "' (utf-8 = " << d << ") at index " << index << std::endl;
        std::exit(1);
    }
  }
  return Token {.kind = kind, .Length = index - old_index};
}

std::map<std::string, TokenKind> KeywordMap{
  {"while", While},
  {"as", As},
  {"break", Break},
  {"continue", Continue},
  {"if", If},
  {"else", Else},
  {"true", True},
  {"false", False},
  {"func", Func},
  {"for", For},
  {"in", In},
  {"switch", Switch},
  {"const", Const},
  {"return", Return}
};

std::list<Token> Tokenizer::Start() {
  std::list<Token> tokens;
  for (index = 0; index < input_.size(); ) {
    auto token = Advance();
    if (token.kind == Ident && KeywordMap.find(input_.substr(index-token.Length, token.Length)) != KeywordMap.end()) {
      token.kind = KeywordMap[input_.substr(index-token.Length, token.Length)];
    }
    tokens.push_back(token);
  }
  return tokens;
}