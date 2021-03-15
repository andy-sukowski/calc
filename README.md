# calc - arithmetic calculator

This is a simple arithmetic calculator, which parses mathematical expressions
specified in infix notation using the
[shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).

## Installation

Edit `config.mk` to match your local setup (calc is installed into the
`/usr/local` namespace by default).

Afterwards enter the following command to build and install calc (if necessary
as root):

    make clean install

## Running calc 

After successfully installing calc, you can run it:

    calc <arith_expr>

This is an example of running calc:

    calc "5 + 2 * 3"
