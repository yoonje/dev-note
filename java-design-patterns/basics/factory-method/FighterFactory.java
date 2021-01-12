public class FighterFactory {
  public Fighter getFighter(boolean laser, boolean missile, boolean plasma) {
    Fighter fighter = new XWingFighter();

    if (laser) fighter = new LaserDecorator(fighter);
    if (missile) fighter = new MissileDecorator(fighter);
    if (plasma) fighter = new PlasmaDecorator(fighter);

    return fighter;
  }
}