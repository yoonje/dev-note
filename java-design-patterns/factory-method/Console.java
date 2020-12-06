class Console {

  private CompFactory compFactory = new CompFactory();

  Component comp1;
  Component comp2;
  Component comp3;

  void withoutFactory () {
    comp1 = new Button();
    comp2 = new Switch();
    comp3 = new Dropdown();
  }

  void withFactory () {
    comp1 = compFactory.getComp(Usage.PRESS);
    comp2 = compFactory.getComp(Usage.TOGGLE);
    comp3 = compFactory.getComp(Usage.EXPAND);
  }
}

enum Usage {
  PRESS, TOGGLE, EXPAND
}