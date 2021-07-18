#pragma once

#include "TokenKinds.h"
#include <sstream>
#include <exception>
#include <tuple>
#include <string>
#include <list>

struct Token {
  TokenKind kind;
  int       Length;

  std::tuple<TokenKind, TokenKind> SplitIntoTwo(TokenKind t);
};

struct UnknownCharErr : public std::exception {

};

class Tokenizer {
 private:
  std::string input_;
  int index = 0;
  Token Advance();

  TokenKind LineComment();
  TokenKind BlockComment();
  TokenKind CharToken(const TokenKind kind);
  TokenKind String();
  TokenKind Number();
  TokenKind CharToken();
  TokenKind SkipWhiteSpaces();
  TokenKind Identifier();

  bool IdStart();
  bool IdContinue();
 public:
  std::list<Token> Start();
  Tokenizer(std::string text);
};