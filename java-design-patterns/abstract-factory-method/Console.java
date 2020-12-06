class Console {

  private CompFactory lightCompFactory = new LightCompFactory();
  private CompFactory darkCompFactory = new DarkCompFactory();

  Component comp1;
  Component comp2;
  Component comp3;

  void withFactory () {
    comp1 = lightCompFactory.getComp(Usage.PRESS);
    comp2 = lightCompFactory.getComp(Usage.TOGGLE);
    comp3 = lightCompFactory.getComp(Usage.EXPAND);
    // 라이트 버튼 생성
    // 라이트 스위치 생성
    // 라이트 드랍다운 생성

    comp1 = darkCompFactory.getComp(Usage.PRESS);
    comp2 = darkCompFactory.getComp(Usage.TOGGLE);
    comp3 = darkCompFactory.getComp(Usage.EXPAND);
    // 다크 버튼 생성
    // 다크 스위치 생성
    // 다크 드랍다운 생성
  }
}

enum Usage {
  PRESS, TOGGLE, EXPAND
}