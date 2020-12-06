public class PlasmaDecorator extends FighterDecorator {
  public PlasmaDecorator (Fighter _decoratedFighter) {
    super(_decoratedFighter);
  }
  @Override
  public void attack () {
    super.attack();
    System.out.println("플라즈마 발사");
  }
}