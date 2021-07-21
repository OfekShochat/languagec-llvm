#include "lexer.h"
#include "TokenKinds.h"
#include <iostream>
#include <chrono>

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  Tokenizer lexer(std::string("func main() { return 1.2; }"));
  auto o = lexer.Start();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  for (auto const& i : o) {
    std::cout << i.kind << " " << i.Length << std::endl;
  }
  std::cout << static_cast<float>(duration)/1000000000 << std::endl;
  return 0;
}