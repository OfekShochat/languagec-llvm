#include "lexer.h"
#include "TokenKinds.h"
#include <iostream>

std::map<std::string, TokenKind> TokenMap{
  {"while", TokenKind::While},
  {"as", TokenKind::As},
  {"break", TokenKind::Break},
  {"continue", TokenKind::Continue},
  {"if", TokenKind::If},
  {"else", TokenKind::Else},
  {"true", TokenKind::True},
  {"false", TokenKind::False},
  {"func", TokenKind::Func},
  {"for", TokenKind::For},
  {"in", TokenKind::In},
  {"switch", TokenKind::Switch},
  {"const", TokenKind::Const},
  {"return", TokenKind::Return}
};

int main() {
  Tokenizer lexer(std::string("i32 pooop1()"));
  auto o = lexer.Start();
  for (auto const& i : o) {
    std::cout << i.kind << " " << i.Length << std::endl;
  }
  return 0;
}