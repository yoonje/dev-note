interface CompFactory {
  public Component getComp (Usage usage);
}

// 라이트 테마 공장
class LightCompFactory implements CompFactory {

  @Override
  public Component getComp (Usage usage) {
    if (usage == Usage.PRESS) {
      return new LightButton();
    } else if (usage == Usage.TOGGLE) {
      return new LightSwitch();
    } else {
      return new LightDropdown();
    }
  }
}

// 다크 테마 공장
class DarkCompFactory implements CompFactory {

  @Override
  public Component getComp (Usage usage) {
    if (usage == Usage.PRESS) {
      return new DarkButton();
    } else if (usage == Usage.TOGGLE) {
      return new DarkSwitch();
    } else {
      return new DarkDropdown();
    }
  }
}