# TDDBCのC++の残念なサンプルコード

##このリポジトリは
- TDDBC大阪2.0の課題のサンプル(途中まで).  
  URL: http://devtesting.jp/tddbc/?TDDBC%E5%A4%A7%E9%98%AA2.0%2F%E8%AA%B2%E9%A1%8C

- このリポジトリには C++11 成分が含まれています: C++11が使える環境が必要.

- このリポジトリには Boost 成分が含まれています: Boostが使える環境が必要.

- このリポジトリには gtest 成分が含まれています: gtestをダウンロードしようね!  
URL: http://code.google.com/p/googletest/ 

- Mac OS X 上の g++ 4.7.2 と boost1.52.0 と gtest 1.6.0 で動作確認してます.

## このリポジトリを使いたい人へ
- Makefile の CXX を 適宜書き換よう!

- リポジトリのディレクトリのトップに落としてきたgtestのディレクトリを"gtest"と言う名前で置こう!

## Windows上のMinGWでg++を使うお方へ
- Makefile の CPPFLAGS の -std=c++11 を -std=gnu++11 に書き換えよう!

- .gitignore に *.exe を追加しよう!

## その他
- ま、まあ、がんばれや。
