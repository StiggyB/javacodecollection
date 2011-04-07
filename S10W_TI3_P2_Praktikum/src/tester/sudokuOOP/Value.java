package tester.sudokuOOP;

public enum Value {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE;

    public String toString() {
      return Integer.toString(ordinal() + 1);
    }
  }
